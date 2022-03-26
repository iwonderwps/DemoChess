#pragma once

#include "../arch/AppGameObject.h"
#include "TestObj.h"
#include "ChessBoard.h"
#include "Piece.h"
// Test
#include "../../back/RtChessboard.h"

class GameMain :public AppGameObject {
public:
	GameMain();
	~GameMain();
public:
	virtual void OnInit() override;
	virtual void OnEnd() override;
private:
	ChessBoard chessBoard;
	TestObj testObj;
	Piece* pPieces;
private:
	RtChessBoard rtChessBoard;
public:
	Piece* tGetPieces();
	RtChessBoard* tGetRtChessBoard();
	ChessBoard* tGetChessBoard();
};

