#include "ChessBoardWnd.h"
#include "ChessBoard.h"

// Test
#include "Piece.h"
#include "GameMain.h"
#include "../../back/RtChessboard.h"
#include <memory>
extern std::unique_ptr<AppGameObject> pAppGameObject;
#include <Windows.h>
#include <string>
#include <sstream>
#include <map>


ChessBoardWnd::ChessBoardWnd():
	chessboard(nullptr)
{

}

ChessBoardWnd::~ChessBoardWnd(){

}

void ChessBoardWnd::Reg(
	SysReg* pReg,
	ChessBoard* p,
	int xPosParent, int yPosParent, int width, int height,
	float z
) {
	chessboard = p;
	GameWndComponent::Reg(pReg, xPosParent, yPosParent, width, height, z);
}

void ChessBoardWnd::OnClick(int xClickParent, int yClickParent){
	GameWndComponent::OnClick(xClickParent, yClickParent);

	/*
	// for test
	std::wstringstream s;
	s << L"Last Click Pos: x - " << xClickLastLocal << L" y - " << yClickLastLocal << L" .";
	MessageBox(0, s.str().c_str(), L"Test", MB_OK);
	*/

	// it should send this click msg to rule server,
	// but here, as no server is implemented, it directly make calls.
	GameMain* pGM = dynamic_cast<GameMain*>(pAppGameObject.get());

	ChessBoard::SizeInfo sinfo;
	chessboard->GetSizeInfo(&sinfo);

	int tx = xClickLastLocal + sinfo.xpiecegap / 2;
	int ty = yClickLastLocal + sinfo.ypiecegap / 2;
	int txch = tx / sinfo.xpiecegap;
	int tych = ty / sinfo.ypiecegap;
	if (txch < 0 || txch>8 || tych < 0 || tych>9)
		return;

	RtChessBoard::BoardClickInfo bdinfo{ txch, tych };
	pGM->tGetRtChessBoard()->OnBoardClick(&bdinfo);

}

bool ChessBoardWnd::IsInside(int xParent, int yParent){
	return true;
}
