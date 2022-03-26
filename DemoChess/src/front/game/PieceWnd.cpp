#include "Piece.h"
#include "PieceWnd.h"

// ----------------------------------------------------------------
// for now, this class should not be in use. 
// ----------------------------------------------------------------

PieceWnd::PieceWnd(Piece* pAttached){
	piece = pAttached;
}

PieceWnd::~PieceWnd(){

}

void PieceWnd::OnClick(int xClickParent, int yClickParent){
	GameWndComponent::OnClick(xClickParent, yClickParent);
}
