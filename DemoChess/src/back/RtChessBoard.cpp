#include "RtChessboard.h"

//Test
#include "../front/game/Piece.h"
#include "../front/game/GameMain.h"

RtChessBoard::BoardClickInfo::BoardClickInfo():
	BoardClickInfo(-1, -1)
{

}

RtChessBoard::BoardClickInfo::BoardClickInfo(int xch, int ych){
	this->xch = xch;
	this->ych = ych;
}

RtChessBoard::BoardState::BoardState():
	bRTurn(true), bBTurn(true),bRPickup(false),bBPickup(false),
	pPickedUp(nullptr)
{

}

RtChessBoard::RtChessBoard():
	pieces(nullptr), cbrd(nullptr)
{

}

RtChessBoard::~RtChessBoard(){

}

void RtChessBoard::Init(GameMain* pGM){
	for (int i = 0; i < 90; ++i) {
		cbrdPiece[i] = 0;
	}

	cbrd = pGM->tGetChessBoard();

	pieces = pGM->tGetPieces();
	for (int i = 0; i < 32; ++i) {
		Piece& aPiece = pieces[i];
		if (aPiece.IsTaken())
			continue;
		Piece::CInfo cinfo;
		aPiece.GetCoord(&cinfo);
		cbrdPiece[cinfo.xch + cinfo.ych * 9] = &aPiece;
	}
}

void RtChessBoard::OnBoardClick(const BoardClickInfo* pInfo){
	bool nonePick = true;
	int txch = pInfo->xch;
	int tych = pInfo->ych;

	// it should send the result of diff types to game client,
	// but here, as no game client is implemented, it directly call, return or throw.

	Piece* pPiece = cbrdPiece[txch + tych * 9];
	if (boardState.bRTurn && !boardState.bRPickup) {
		if (!pPiece)
			return;
		else {
			if (pPiece->GetCamp() == Piece::Camp::Red) {
				if (!pPiece->IsPickedUp()) {
					pPiece->OnPickUp();
					pPiece->ListAvailablePos(cbrdPiece, pieceAvailablePos);
					cbrd->ShowAvailablePos(pieceAvailablePos);
					boardState.bRPickup = true;
					boardState.pPickedUp = pPiece;
				}
				else {
					throw;
				}
			}
			else if (pPiece->GetCamp() == Piece::Camp::Black) {
				return;
			}
			else {
				throw;
			}
		}
	}
	else if (boardState.bRTurn && boardState.bRPickup) {
		Piece& aPiece = *boardState.pPickedUp;
		Piece::CInfo cinfo;
		aPiece.GetCoord(&cinfo);
		// if put down back
		if (txch == cinfo.xch && tych == cinfo.ych) {
			aPiece.OnPutDown(txch, tych);
			cbrd->ClearAvailablePos();
			boardState.bRPickup = false;
			boardState.pPickedUp = nullptr;
		}
		else if (pieceAvailablePos.find(txch + tych * 9) != pieceAvailablePos.end()) {
			// if this step is allowed
			cbrdPiece[cinfo.xch + cinfo.ych * 9] = 0;  // before put down, erase it from origin.
			cbrdPiece[txch + tych * 9] = &aPiece;  // put the picked up to the new place.
			aPiece.OnPutDown(txch, tych);  // put the picked up to the new place.
			cbrd->ClearAvailablePos();
			if (pPiece) {
				pPiece->SetTaken();
			}
			boardState.bRTurn = false;
			boardState.bBTurn = true;
			boardState.bRPickup = false;
			boardState.bBPickup = false;
			boardState.pPickedUp = nullptr;			
		}
		else {
			return;
		}
	}
	else if (boardState.bBTurn && !boardState.bBPickup) {
		if (!pPiece)
			return;
		else {
			if (pPiece->GetCamp() == Piece::Camp::Black) {
				if (!pPiece->IsPickedUp()) {
					pPiece->OnPickUp();
					pPiece->ListAvailablePos(cbrdPiece, pieceAvailablePos);
					cbrd->ShowAvailablePos(pieceAvailablePos);
					boardState.bBPickup = true;
					boardState.pPickedUp = pPiece;
				}
				else {
					throw;
				}
			}
			else if (pPiece->GetCamp() == Piece::Camp::Red) {
				return;
			}
			else {
				throw;
			}
		}
	}
	else if (boardState.bBTurn && boardState.bBPickup) {
		Piece& aPiece = *boardState.pPickedUp;
		Piece::CInfo cinfo;
		aPiece.GetCoord(&cinfo);
		// if put down back
		if (txch == cinfo.xch && tych == cinfo.ych) {
			aPiece.OnPutDown(txch, tych);
			cbrd->ClearAvailablePos();
			boardState.bBPickup = false;
			boardState.pPickedUp = nullptr;
		}
		// if this step is allowed
		else if (pieceAvailablePos.find(txch + tych * 9) != pieceAvailablePos.end()) {
			cbrdPiece[cinfo.xch + cinfo.ych * 9] = 0;  // before put down, erase it from origin.
			cbrdPiece[txch + tych * 9] = &aPiece;  // put the picked up to the new place.
			aPiece.OnPutDown(txch, tych);  // put the picked up to the new place.
			cbrd->ClearAvailablePos();
			if (pPiece) {
				pPiece->SetTaken();
			}
			boardState.bRTurn = true;
			boardState.bBTurn = false;
			boardState.bRPickup = false;
			boardState.bBPickup = false;
			boardState.pPickedUp = nullptr;
		}
		else {
			return;
		}
	}
}

