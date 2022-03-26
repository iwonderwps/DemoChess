#pragma once

#include "../arch/GameWndComponent.h"

class Piece;

// ----------------------------------------------------------------
// for now, this class should not be in use. 
// ----------------------------------------------------------------

class PieceWnd :public GameWndComponent
{
public:
	PieceWnd(Piece* pAttached);
	virtual ~PieceWnd();
public:
	virtual void OnClick(int xClickParent, int yClickParent) override;
private:
	Piece* piece;
};

