#pragma once

#include "../arch/GameObject.h"
#include "../arch/ImgGraphics.h"
#include "../arch/GameWndComponent.h"

#include "../../util/SimpleLoader.h"

#include <map>
#include <set>


class ChessBoard;

class Piece :public GameObject {
public:
	enum class Name	{
		Jiang, Shuai, 
		Shi_R1, Shi_R2, Shi_B1, Shi_B2,
		Xiang_R1, Xiang_R2, Xiang_B1, Xiang_B2,
		Che_R1, Che_R2, Che_B1, Che_B2,
		Ma_R1, Ma_R2, Ma_B1, Ma_B2,
		Pao_R1, Pao_R2, Pao_B1, Pao_B2,
		Bing_1, Bing_2, Bing_3, Bing_4, Bing_5,
		Zu_1, Zu_2, Zu_3, Zu_4, Zu_5,
	};
	enum class Camp {
		Red, Black,
	};
	// pos of the piece in rule logic. 
	struct CInfo {
		int xch;
		int ych;
		CInfo();
		CInfo(int x, int y);
	};
public:
	Piece();
	~Piece();
public:
	// a piece should know its name/type and the chessboard size.
	void Init(Name pieceName, ChessBoard* pCbrd);
public:
	// op of the coord.
	void GetCoord(CInfo* pout) const;
	void SetCoord(CInfo* p);
	void SetCoord(int x, int y);
public:
	bool IsPickedUp() const;
	void OnPickUp();
	void OnPutDown(int xch, int ych);
	bool IsTaken() const;
	void SetTaken(bool state = true);
public:
	Name GetName() const;
	Camp GetCamp() const;
public:
	void ListAvailablePos(const std::map<int, Piece*>& cbrdPiece, std::set<int>& outPos);
private:
	// width and height of the img for the piece.
	int width;
	int height;
private:
	// x and y coord of the img pos in pixel.
	int x;
	int y;
private:
	// x and y coord of the piece on the chessboard. 
	// (0,0) is upper left of the chessboard from the perspective of the Red, where lies Black's Che/Jv on Black's 1st line.
	int xch;
	int ych;
private:
	bool bPickedUp;
	bool bTaken;
private:
	Name name;
	Camp camp;
private:
	ImgGraphics* imgComp;
	ChessBoard* chessboard;
private:
	// for the current cfg loading strategy. All pieces share a cfg file.
	static SimpleLoader cfgPieces;
	static bool bCfgLoaded;
};
