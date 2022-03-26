#pragma once

#include <set>

#include "../arch/CircleGraphics.h"

class ChessBoard;

class ChessBoardHNGraphics :public CircleGraphics {
public:
	ChessBoardHNGraphics();
	virtual ~ChessBoardHNGraphics();
public:
	virtual void Reg(SysReg* pReg, ChessBoard* p, int radius, COLOR ctype);
	virtual void Draw(D2DRenderer* pD2D) override;
public:
	void UpdateHintData(const std::set<int>& pos);
	void UpdateHintData();
private:
	std::set<int> posHint;
private:
	ChessBoard* chessboard;
};
