#pragma once

#include <Windows.h>
#include <d2d1.h>
#include <directxmath.h>
#include <wincodec.h>

#include <vector>

#pragma comment (lib, "d2d1.lib")
#pragma comment (lib, "windowscodecs.lib")

class GraphicsComponent;

class D2DRenderer {
public:
	D2DRenderer();
	~D2DRenderer();
public:
	void CreateWindowSizeDependentResources(HWND hwnd);
	void BeforeRenderLoop();
	void Update(float dt);
	void Render(float farsee);
	void AddGraphicsComponent(GraphicsComponent* p);
	void LoadImgFromFile(PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppImg);
public:
	ID2D1RenderTarget* GetRenderTarget();
	void DrawEllipse(int x, int y, int rx, int ry, ID2D1SolidColorBrush* pBrush);
	void DrawImg(ID2D1Bitmap* pBitmap, int x, int y, int width, int height);
public:
	void OnReSort();
private:
	void LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);
private:
	ID2D1Factory* pD2DFactory;
	ID2D1HwndRenderTarget* pRT;
	D2D1_COLOR_F bgColor;
	IWICImagingFactory* pIWICFactory;
private:
	struct TargetWithZ {
		GraphicsComponent* p;
		float z;
		static bool less(const TargetWithZ& left, const TargetWithZ& right);
	};
	// if bInRenderLoop == true, then accept call for OnReSort().
	bool bInRenderLoop;
private:
	// see but not own
	std::vector<TargetWithZ> graphicsComponents;
};
