#include "ChessBoard.h"

#include "../arch/ImgGraphics.h"

#include "ChessBoardWnd.h"

using std::wstring;


ChessBoard::ChessBoard():
	size(), hnComp(nullptr)
{

}

ChessBoard::~ChessBoard(){

}

void ChessBoard::Init(){
	wstring settingsFileName(L"cfg/ChessBoard.txt");
	cfgChessBoard.load(settingsFileName);
	int cbrdWidth = cfgChessBoard.get<int>(L"width");
	int cbrdHeight = cfgChessBoard.get<int>(L"height");
	wstring cbrdImgPath = cfgChessBoard.get<wstring>(L"path");
	int cbrdx = cfgChessBoard.get<int>(L"xpos");
	int cbrdy = cfgChessBoard.get<int>(L"ypos");
	int xgap = cfgChessBoard.get<int>(L"xgap");
	int ygap = cfgChessBoard.get<int>(L"ygap");
	int radHint = cfgChessBoard.get<int>(L"radHint");

	size = {
		cbrdx, cbrdy,
		cbrdWidth, cbrdHeight,
		xgap, ygap
	};

	Component* temp = AddNewComponent<ImgGraphics>(cbrdImgPath.c_str(), cbrdx, cbrdy, cbrdWidth, cbrdHeight);
	AddNewComponent<ChessBoardWnd>(this, cbrdx, cbrdy, cbrdWidth, cbrdHeight);
	ImgGraphics* tempImgComp = dynamic_cast<ImgGraphics*>(temp);
	tempImgComp->SetZ(1.0f);
	temp = AddNewComponent<ChessBoardHNGraphics>(this, radHint, CircleGraphics::COLOR::HotPink);
	hnComp = dynamic_cast<ChessBoardHNGraphics*>(temp);
	hnComp->SetZ(3.0f);
}

void ChessBoard::GetSizeInfo(SizeInfo* pout) const{
	*pout = this->size;
}

void ChessBoard::ShowAvailablePos(const std::set<int>& pos){
	hnComp->UpdateHintData(pos);
}

void ChessBoard::ClearAvailablePos(){
	hnComp->UpdateHintData();
}

