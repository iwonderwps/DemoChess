#pragma once

#include <set>

#include "ChessBoardHNGraphics.h"
#include "../arch/GameObject.h"
#include "../../util/SimpleLoader.h"


class ChessBoard :public GameObject {
public:
	struct SizeInfo {
		int xpos;
		int ypos;
		int xlength;
		int ylength;
		int xpiecegap;
		int ypiecegap;
	};
public:
	ChessBoard();
	~ChessBoard();
public:
	void Init();
public:
	void GetSizeInfo(SizeInfo* pout) const;
public:
	void ShowAvailablePos(const std::set<int>& pos);
	void ClearAvailablePos();
private:
	SimpleLoader cfgChessBoard;
	SizeInfo size;
private:
	ChessBoardHNGraphics* hnComp;
};
