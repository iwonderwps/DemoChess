#include "ChessBoardHNGraphics.h"

#include "ChessBoard.h"
#include "../fundamental/D2DRenderer.h"

ChessBoardHNGraphics::ChessBoardHNGraphics():
	chessboard(nullptr)
{

}

ChessBoardHNGraphics::~ChessBoardHNGraphics(){

}

void ChessBoardHNGraphics::Reg(SysReg* pReg, ChessBoard* p, int radius, COLOR ctype){
	CircleGraphics::Reg(pReg, 0, 0, radius, ctype);
	chessboard = p;
}

void ChessBoardHNGraphics::Draw(D2DRenderer* pD2D){
	if (posHint.empty())
		return;
	ChessBoard::SizeInfo sinfo;
	chessboard->GetSizeInfo(&sinfo);
	for (auto it = posHint.begin(); it != posHint.end(); ++it) {
		int xch, ych;
		int x, y;
		ych = (*it) / 9;
		xch = (*it) % 9;
		x = sinfo.xpos + xch * sinfo.xpiecegap;
		y = sinfo.ypos + ych * sinfo.ypiecegap;
		pD2D->DrawEllipse(x, y, radius, radius, pBrush);
	}
}

void ChessBoardHNGraphics::UpdateHintData(const std::set<int>& pos){
	posHint.clear();
	posHint = pos;
}

void ChessBoardHNGraphics::UpdateHintData(){
	posHint.clear();
}
