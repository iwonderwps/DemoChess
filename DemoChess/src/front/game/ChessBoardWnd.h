#pragma once

#include "../arch/GameWndComponent.h"

class ChessBoard;

class ChessBoardWnd :public GameWndComponent {
public:
	ChessBoardWnd();
	virtual ~ChessBoardWnd();
public:
	virtual void Reg(
		SysReg* pReg,
		ChessBoard* p,
		int xPosParent, int yPosParent, int width, int height,
		float z = 0
	);
public:
	virtual void OnClick(int xClickParent, int yClickParent) override;
	virtual bool IsInside(int xParent, int yParent) override;
private:
	ChessBoard* chessboard;
};
