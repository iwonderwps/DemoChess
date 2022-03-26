#pragma once

#include <map>
#include <set>

// Test
class Piece;
class ChessBoard;
class GameMain;

class RtChessBoard {
public:
	struct BoardClickInfo {
		int xch;
		int ych;
		BoardClickInfo();
		BoardClickInfo(int xch, int ych);
	};
protected:
	struct BoardState {
		bool bRTurn;
		bool bBTurn;
		bool bRPickup;
		bool bBPickup;
		Piece* pPickedUp;
		BoardState();
	};
public:
	RtChessBoard();
	virtual ~RtChessBoard();
public:
	void Init(GameMain* pGM);
public:
	virtual void OnBoardClick(const BoardClickInfo* pInfo);
protected:
	std::map<int, Piece*> cbrdPiece;
	std::set<int> pieceAvailablePos;
	BoardState boardState;
//Test
protected:
	Piece* pieces;
	ChessBoard* cbrd;
};
