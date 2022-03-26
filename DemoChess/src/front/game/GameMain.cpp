#include <memory>

#include "GameMain.h"


using std::unique_ptr;

extern unique_ptr<AppGameObject> pAppGameObject(new GameMain());

GameMain::GameMain():
	pPieces(nullptr)
{

}

GameMain::~GameMain(){

}

void GameMain::OnInit(){
	chessBoard.Init();
	testObj.Init();
	pPieces = new Piece[32];
	for (int i = 0; i < 32; ++i) {
		pPieces[i].Init(static_cast<Piece::Name>(i), &chessBoard);
	}
	rtChessBoard.Init(this);
}

void GameMain::OnEnd() {
	delete[] pPieces;
}

// ------------  test  ------------

Piece* GameMain::tGetPieces() {
	return pPieces;
}

RtChessBoard* GameMain::tGetRtChessBoard(){
	return &rtChessBoard;
}

ChessBoard* GameMain::tGetChessBoard(){
	return &chessBoard;
}

