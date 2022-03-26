#include "D2DRenderer.h"
#include "../arch/GraphicsComponent.h"
#include "../../util/SimpleRelease.h"

#include <algorithm>

D2DRenderer::D2DRenderer():
    pD2DFactory(0), pRT(0), pIWICFactory(0),
    bInRenderLoop(false)
{
    graphicsComponents.clear();
    bgColor = { 0 };
    HRESULT hr = D2D1CreateFactory(
        D2D1_FACTORY_TYPE_SINGLE_THREADED,
        &pD2DFactory
    );

    hr = CoInitialize(0);
}

D2DRenderer::~D2DRenderer(){
    SimpleRelease(&pRT);
    SimpleRelease(&pD2DFactory);
    SimpleRelease(&pIWICFactory);
    bInRenderLoop = false;
}

void D2DRenderer::CreateWindowSizeDependentResources(HWND hwnd){
    RECT rc;
    GetClientRect(hwnd, &rc);
    HRESULT hr = pD2DFactory->CreateHwndRenderTarget(
        D2D1::RenderTargetProperties(),
        D2D1::HwndRenderTargetProperties(
            hwnd,
            D2D1::SizeU(
                rc.right - rc.left,
                rc.bottom - rc.top)
        ),
        &pRT
    );
    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        NULL,
        CLSCTX_INPROC_SERVER,
        IID_IWICImagingFactory,
        (LPVOID*)&pIWICFactory
    );
}

void D2DRenderer::BeforeRenderLoop(){
    for (auto it = graphicsComponents.begin(); it != graphicsComponents.end(); ++it) {
        it->p->Init(this);
    }
    bInRenderLoop = true;
    OnReSort();
}

void D2DRenderer::Update(float dt){
    
}

void D2DRenderer::Render(float farsee){
    pRT->BeginDraw();
    pRT->Clear(&bgColor);
    for (auto it = graphicsComponents.begin(); it != graphicsComponents.end(); ++it) {
        it->p->Draw(this);
    }
    pRT->EndDraw();
}

void D2DRenderer::AddGraphicsComponent(GraphicsComponent* p){
    for (auto it = graphicsComponents.begin(); it != graphicsComponents.end(); ++it) {
        if (it->p == p)
            throw;
    }
    graphicsComponents.push_back({ p, p->GetZ()});
}

void D2DRenderer::LoadImgFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppImg){
    LoadBitmapFromFile(pRT, pIWICFactory, uri, destinationWidth, destinationHeight, ppImg);
}

void D2DRenderer::LoadBitmapFromFile(
    ID2D1RenderTarget* pRenderTarget,
    IWICImagingFactory* pIWICFactory,
    PCWSTR uri,
    UINT destinationWidth,
    UINT destinationHeight,
    ID2D1Bitmap** ppBitmap
){
    IWICBitmapDecoder* pDecoder = NULL;
    IWICBitmapFrameDecode* pSource = NULL;
    IWICStream* pStream = NULL;
    IWICFormatConverter* pConverter = NULL;
    IWICBitmapScaler* pScaler = NULL;

    HRESULT hr = pIWICFactory->CreateDecoderFromFilename(
        uri,
        NULL,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        &pDecoder
    );
    if (SUCCEEDED(hr)){
        // Create the initial frame.
        hr = pDecoder->GetFrame(0, &pSource);
    }
    if (SUCCEEDED(hr)){

        // Convert the image format to 32bppPBGRA
        // (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
        hr = pIWICFactory->CreateFormatConverter(&pConverter);

    }
    if (SUCCEEDED(hr)){
        hr = pConverter->Initialize(
            pSource,
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            NULL,
            0.f,
            WICBitmapPaletteTypeMedianCut
        );
        if (SUCCEEDED(hr)){

            // Create a Direct2D bitmap from the WIC bitmap.
            hr = pRenderTarget->CreateBitmapFromWicBitmap(
                pConverter,
                NULL,
                ppBitmap
            );
        }

        SimpleRelease(&pDecoder);
        SimpleRelease(&pSource);
        SimpleRelease(&pStream);
        SimpleRelease(&pConverter);
        SimpleRelease(&pScaler);

    }
}

ID2D1RenderTarget* D2DRenderer::GetRenderTarget(){
    return pRT;
}

void D2DRenderer::DrawEllipse(int x, int y, int rx, int ry, ID2D1SolidColorBrush* pBrush){
    D2D1_ELLIPSE circle;
    circle.point.x = static_cast<float>(x); 
    circle.point.y = static_cast<float>(y);
    circle.radiusX = static_cast<float>(rx);
    circle.radiusY = static_cast<float>(ry);
    pRT->DrawEllipse(&circle, pBrush);
}

void D2DRenderer::DrawImg(ID2D1Bitmap* pBitmap, int x, int y, int width, int height){
    pRT->DrawBitmap(
        pBitmap,
        D2D1::RectF(
            static_cast<float>(x),
            static_cast<float>(y),
            static_cast<float>(x + width),
            static_cast<float>(y + height)
        )
    );
}

void D2DRenderer::OnReSort(){
    if (!bInRenderLoop)
        return;
    for (auto it = graphicsComponents.begin(); it != graphicsComponents.end(); ++it) {
        it->z = it->p->GetZ();
    }
    std::sort(graphicsComponents.begin(), graphicsComponents.end(), TargetWithZ::less);
}

bool D2DRenderer::TargetWithZ::less(const TargetWithZ& left, const TargetWithZ& right){
    return left.z < right.z;
}
