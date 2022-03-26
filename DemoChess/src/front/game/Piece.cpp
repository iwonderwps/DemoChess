#include "Piece.h"
#include "ChessBoard.h"

#include "../arch/ImgGraphics.h"

using std::wstring;

SimpleLoader Piece::cfgPieces;
bool Piece::bCfgLoaded = false;

Piece::Piece():
	x(0), y(0),
	width(0), height(0),
	xch(-1), ych(-1),
	bPickedUp(false), bTaken(false),
	imgComp(nullptr), chessboard(nullptr)
{

}

Piece::~Piece(){

}

Piece::CInfo::CInfo():
	xch(-1), ych(-1)
{

}

Piece::CInfo::CInfo(int x, int y):
	xch(x), ych(y)
{

}

void Piece::Init(Name pieceName, ChessBoard* pCbrd){
	if (!bCfgLoaded) {
		wstring settingsFileName(L"cfg/Pieces.txt");
		cfgPieces.load(settingsFileName);
		bCfgLoaded = true;
	}
	width = cfgPieces.get<int>(L"pieceWidth");
	height = cfgPieces.get<int>(L"pieceHeight");
	wstring pathImg;
	chessboard = pCbrd;
	ChessBoard::SizeInfo cbrdSize;
	chessboard->GetSizeInfo(&cbrdSize);
	int xgap = cbrdSize.xpiecegap;
	int ygap = cbrdSize.ypiecegap;
	name = pieceName;
	switch (pieceName)
	{
	case Piece::Name::Jiang:
		xch = 4;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BJiang_path");
		break;
	case Piece::Name::Shuai:
		xch = 4;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RJiang_path");
		break;
	case Piece::Name::Shi_R1:
		xch = 3;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RShi_path");
		break;
	case Piece::Name::Shi_R2:
		xch = 5;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RShi_path");
		break;
	case Piece::Name::Shi_B1:
		xch = 3;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BShi_path");
		break;
	case Piece::Name::Shi_B2:
		xch = 5;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BShi_path");
		break;
	case Piece::Name::Xiang_R1:
		xch = 2;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RXiang_path");
		break;
	case Piece::Name::Xiang_R2:
		xch = 6;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RXiang_path");
		break;
	case Piece::Name::Xiang_B1:
		xch = 2;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BXiang_path");
		break;
	case Piece::Name::Xiang_B2:
		xch = 6;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BXiang_path");
		break;
	case Piece::Name::Che_R1:
		xch = 0;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RChe_path");
		break;
	case Piece::Name::Che_R2:
		xch = 8;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RChe_path");
		break;
	case Piece::Name::Che_B1:
		xch = 0;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BChe_path");
		break;
	case Piece::Name::Che_B2:
		xch = 8;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BChe_path");
		break;
	case Piece::Name::Ma_R1:
		xch = 1;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RMa_path");
		break;
	case Piece::Name::Ma_R2:
		xch = 7;
		ych = 9;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RMa_path");
		break;
	case Piece::Name::Ma_B1:
		xch = 1;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BMa_path");
		break;
	case Piece::Name::Ma_B2:
		xch = 7;
		ych = 0;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BMa_path");
		break;
	case Piece::Name::Pao_R1:
		xch = 1;
		ych = 7;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RPao_path");
		break;
	case Piece::Name::Pao_R2:
		xch = 7;
		ych = 7;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RPao_path");
		break;
	case Piece::Name::Pao_B1:
		xch = 1;
		ych = 2;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BPao_path");
		break;
	case Piece::Name::Pao_B2:
		xch = 7;
		ych = 2;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BPao_path");
		break;
	case Piece::Name::Bing_1:
		xch = 0;
		ych = 6;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RBing_path");
		break;
	case Piece::Name::Bing_2:
		xch = 2;
		ych = 6;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RBing_path");
		break;
	case Piece::Name::Bing_3:
		xch = 4;
		ych = 6;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RBing_path");
		break;
	case Piece::Name::Bing_4:
		xch = 6;
		ych = 6;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RBing_path");
		break;
	case Piece::Name::Bing_5:
		xch = 8;
		ych = 6;
		camp = Camp::Red;
		pathImg = cfgPieces.get<std::wstring>(L"RBing_path");
		break;
	case Piece::Name::Zu_1:
		xch = 0;
		ych = 3;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BBing_path");
		break;
	case Piece::Name::Zu_2:
		xch = 2;
		ych = 3;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BBing_path");
		break;
	case Piece::Name::Zu_3:
		xch = 4;
		ych = 3;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BBing_path");
		break;
	case Piece::Name::Zu_4:
		xch = 6;
		ych = 3;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BBing_path");
		break;
	case Piece::Name::Zu_5:
		xch = 8;
		ych = 3;
		camp = Camp::Black;
		pathImg = cfgPieces.get<std::wstring>(L"BBing_path");
		break;
	default:
		xch = -1;
		ych = -1;
		break;
	}
	x = xgap * xch;
	y = ygap * ych;
	x += cbrdSize.xpos;
	y += cbrdSize.ypos;
	x -= width / 2;
	y -= height / 2;
	Component* p = AddNewComponent<ImgGraphics>(pathImg.c_str(), x, y, width, height);
	imgComp = dynamic_cast<ImgGraphics*>(p);
	imgComp->SetZ(2.0f);
}

void Piece::GetCoord(CInfo* pout) const{
	pout->xch = xch;
	pout->ych = ych;
}

void Piece::SetCoord(CInfo* p){
	SetCoord(p->xch, p->ych);
}

void Piece::SetCoord(int x, int y){
	xch = x;
	ych = y;
}

bool Piece::IsPickedUp() const{
	return bPickedUp;
}

void Piece::OnPickUp(){
	if (!bPickedUp) {
		bPickedUp = true;
		// under dev
		// inc the size of the img
	}
}

void Piece::OnPutDown(int xch, int ych){
	if (bPickedUp) {
		bPickedUp = false;
		this->xch = xch;
		this->ych = ych;
		ChessBoard::SizeInfo cbrdSize;
		chessboard->GetSizeInfo(&cbrdSize);
		int xgap = cbrdSize.xpiecegap;
		int ygap = cbrdSize.ypiecegap;
		x = xgap * xch + cbrdSize.xpos - width / 2;
		y = ygap * ych + cbrdSize.ypos - height / 2;
		imgComp->MoveTo(x, y);
		// under dev
		// play animation of moving
		// dec the size of the img
	}
}

bool Piece::IsTaken() const{
	return bTaken;
}

void Piece::SetTaken(bool state){
	bTaken = state;
	imgComp->SetHide(state);
}

Piece::Name Piece::GetName() const{
	return name;
}

Piece::Camp Piece::GetCamp() const{
	return camp;
}

void Piece::ListAvailablePos(const std::map<int, Piece*>& cbrdPiece, std::set<int>& outPos) {
	outPos.clear();
	switch (name)
	{
	// Red
	case Piece::Name::Shuai: {
		int xtemp = xch, ytemp = ych;
		int posEnum[8] = { 
			xch - 1, ych, 
			xch + 1,ych, 
			xch, ych - 1, 
			xch, ych + 1,
		};
		for (int i = 0; i < 8; i+=2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 3 && xtemp <= 5 && ytemp <= 9 && ytemp >= 7) {
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Black) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}
		break;
	}
	case Piece::Name::Shi_R1:
	case Piece::Name::Shi_R2: {
		int xtemp = xch, ytemp = ych;
		int posEnum[8] = {
			xch - 1, ych - 1,
			xch + 1, ych - 1,
			xch - 1, ych + 1,
			xch + 1, ych + 1,
		};
		for (int i = 0; i < 8; i += 2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 3 && xtemp <= 5 && ytemp <= 9 && ytemp >= 7) {
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Black) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}
		break;
	}		
	case Piece::Name::Xiang_R1:
	case Piece::Name::Xiang_R2: {
		int xtemp = xch, ytemp = ych;
		int eyeOffset[8]{
			-1, -1,
			+1, -1,
			-1, +1,
			+1, +1,
		};
		for (int i = 0; i < 8; i += 2) {
			xtemp = xch + eyeOffset[i];
			ytemp = ych + eyeOffset[i + 1];
			if (xtemp < 0 || xtemp > 8 || ytemp < 0 || ytemp > 9)
				continue;
			if (cbrdPiece.at(xtemp + ytemp * 9) != nullptr)
				continue;
			else {
				xtemp = xch + 2 * eyeOffset[i];
				ytemp = ych + 2 * eyeOffset[i + 1];
				if (xtemp >= 0 && xtemp <= 8 && ytemp <= 9 && ytemp >= 5) {
					const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
					if (!pPiece || pPiece->GetCamp() == Camp::Black) {
						outPos.insert(xtemp + ytemp * 9);
					}
				}
			}
		}		
		break;
	}		
	case Piece::Name::Ma_R1:
	case Piece::Name::Ma_R2: {
		int xtemp = xch, ytemp = ych;
		int posEnum[16] = {
			xch - 1, ych - 2, xch + 1, ych - 2,
			xch - 2, ych - 1, xch - 2, ych + 1,
			xch - 1, ych + 2, xch + 1, ych + 2,
			xch + 2, ych - 1, xch + 2, ych + 1,
		};
		for (int i = 0; i < 16; i+=2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 0 && xtemp <= 8 && ytemp <= 9 && ytemp >= 0) {
				int xleg = xch, yleg = ych;
				if (ytemp - ych == 2) {
					yleg = ych + 1;
				}
				else if (ytemp - ych == -2) {
					yleg = ych - 1;
				}
				else if (xtemp - xch == 2) {
					xleg = xch + 1;
				}
				else if (xtemp - xch == -2) {
					xleg = xch - 1;
				}
				else {
					throw;
				}
				if (cbrdPiece.at(xleg + yleg * 9) != nullptr) {
					continue;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Black) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}		
		break;
	}		
	case Piece::Name::Che_R1:
	case Piece::Name::Che_R2: {
		int xtemp = xch, ytemp = ych;
		int offset[8] = {
			-1, 0, 1, 0, 0, -1, 0, 1,
		};
		for (int i = 0; i < 8;/*null*/) {
			xtemp = xch, ytemp = ych;
			while (true) {
				xtemp += offset[i];
				ytemp += offset[i + 1];
				if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
					i += 2;
					break;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece) {
					outPos.insert(xtemp + ytemp * 9);
				}
				else if (pPiece->GetCamp() == Camp::Black) {
					outPos.insert(xtemp + ytemp * 9);
					i += 2;
					break;
				}
				else if (pPiece->GetCamp() == Camp::Red) {
					i += 2;
					break;
				}
			}			
		}		
		break;
	}	
	case Piece::Name::Pao_R1:
	case Piece::Name::Pao_R2: {
		int xtemp = xch, ytemp = ych;
		int offset[8] = {
			-1, 0, 1, 0, 0, -1, 0, 1,
		};
		for (int i = 0; i < 8;/*null*/) {
			xtemp = xch, ytemp = ych;
			while (true) {
				xtemp += offset[i];
				ytemp += offset[i + 1];
				if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
					i += 2;
					break;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece) {
					outPos.insert(xtemp + ytemp * 9);
				}
				else {
					while (true) {
						xtemp += offset[i];
						ytemp += offset[i + 1];
						if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
							break;
						}
						const Piece* pTry = cbrdPiece.at(xtemp + ytemp * 9);
						if (!pTry)
							continue;
						if (pTry->GetCamp() == Camp::Black) {
							outPos.insert(xtemp + ytemp * 9);
							break;
						}
						else if (pPiece->GetCamp() == Camp::Red) {
							break;
						}
						else {
							throw;
						}
					}
					i += 2;
					break;
				}
			}
		}
		break;
	}		
	case Piece::Name::Bing_1:
	case Piece::Name::Bing_2:
	case Piece::Name::Bing_3:
	case Piece::Name::Bing_4:
	case Piece::Name::Bing_5: {
		int xtemp = xch, ytemp = ych;
		if (ych > 4) {
			ytemp = ych - 1;
			const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
			if (!pPiece || pPiece->GetCamp() == Camp::Black) {
				outPos.insert(xtemp + ytemp * 9);
			}
		}
		else {
			int posEnum[6] = {
				xch - 1, ych, xch + 1, ych, xch, ych - 1
			};
			for (int i = 0; i < 6; i += 2) {
				xtemp = posEnum[i];
				ytemp = posEnum[i + 1];
				if (xtemp >= 0 && xtemp <= 8 && ytemp <= 4 && ytemp >= 0) {
					const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
					if (!pPiece || pPiece->GetCamp() == Camp::Black) {
						outPos.insert(xtemp + ytemp * 9);
					}
				}
			}
		}
		break;
	}		
	// Black
	case Piece::Name::Jiang:{
		int xtemp = xch, ytemp = ych;
		int posEnum[8] = {
			xch - 1, ych,
			xch + 1,ych,
			xch, ych - 1,
			xch, ych + 1,
		};
		for (int i = 0; i < 8; i += 2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 3 && xtemp <= 5 && ytemp <= 2 && ytemp >= 0) {
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Red) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}
		break;
	}
	case Piece::Name::Shi_B1:
	case Piece::Name::Shi_B2: {
		int xtemp = xch, ytemp = ych;
		int posEnum[8] = {
			xch - 1, ych - 1,
			xch + 1, ych - 1,
			xch - 1, ych + 1,
			xch + 1, ych + 1,
		};
		for (int i = 0; i < 8; i += 2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 3 && xtemp <= 5 && ytemp <= 2 && ytemp >= 0) {
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Red) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}
		break;
	}
	case Piece::Name::Xiang_B1:
	case Piece::Name::Xiang_B2: {
		int xtemp = xch, ytemp = ych;
		int eyeOffset[8]{
			-1, -1,
			+1, -1,
			-1, +1,
			+1, +1,
		};
		for (int i = 0; i < 8; i += 2) {
			xtemp = xch + eyeOffset[i];
			ytemp = ych + eyeOffset[i + 1];
			if (xtemp < 0 || xtemp > 8 || ytemp < 0 || ytemp > 9)
				continue;
			if (cbrdPiece.at(xtemp + ytemp * 9) != nullptr)
				continue;
			else {
				xtemp = xch + 2 * eyeOffset[i];
				ytemp = ych + 2 * eyeOffset[i + 1];
				if (xtemp >= 0 && xtemp <= 8 && ytemp <= 4 && ytemp >= 0) {
					const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
					if (!pPiece || pPiece->GetCamp() == Camp::Red) {
						outPos.insert(xtemp + ytemp * 9);
					}
				}
			}
		}
		break;
	}
	case Piece::Name::Ma_B1:
	case Piece::Name::Ma_B2: {
		int xtemp = xch, ytemp = ych;
		int posEnum[16] = {
			xch - 1, ych - 2, xch + 1, ych - 2,
			xch - 2, ych - 1, xch - 2, ych + 1,
			xch - 1, ych + 2, xch + 1, ych + 2,
			xch + 2, ych - 1, xch + 2, ych + 1,
		};
		for (int i = 0; i < 16; i += 2) {
			xtemp = posEnum[i];
			ytemp = posEnum[i + 1];
			if (xtemp >= 0 && xtemp <= 8 && ytemp <= 9 && ytemp >= 0) {
				int xleg = xch, yleg = ych;
				if (ytemp - ych == 2) {
					yleg = ych + 1;
				}
				else if (ytemp - ych == -2) {
					yleg = ych - 1;
				}
				else if (xtemp - xch == 2) {
					xleg = xch + 1;
				}
				else if (xtemp - xch == -2) {
					xleg = xch - 1;
				}
				else {
					throw;
				}
				if (cbrdPiece.at(xleg + yleg * 9) != nullptr) {
					continue;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece || pPiece->GetCamp() == Camp::Red) {
					outPos.insert(xtemp + ytemp * 9);
				}
			}
		}
		break;
	}
	case Piece::Name::Che_B1:
	case Piece::Name::Che_B2: {
		int xtemp = xch, ytemp = ych;
		int offset[8] = {
			-1, 0, 1, 0, 0, -1, 0, 1,
		};
		for (int i = 0; i < 8;/*null*/) {
			xtemp = xch, ytemp = ych;
			while (true) {
				xtemp += offset[i];
				ytemp += offset[i + 1];
				if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
					i += 2;
					break;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece) {
					outPos.insert(xtemp + ytemp * 9);
				}
				else if (pPiece->GetCamp() == Camp::Red) {
					outPos.insert(xtemp + ytemp * 9);
					i += 2;
					break;
				}
				else if (pPiece->GetCamp() == Camp::Black) {
					i += 2;
					break;
				}
			}
		}
		break;
	}
	case Piece::Name::Pao_B1:
	case Piece::Name::Pao_B2: {
		int xtemp = xch, ytemp = ych;
		int offset[8] = {
			-1, 0, 1, 0, 0, -1, 0, 1,
		};
		for (int i = 0; i < 8;/*null*/) {
			xtemp = xch, ytemp = ych;
			while (true) {
				xtemp += offset[i];
				ytemp += offset[i + 1];
				if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
					i += 2;
					break;
				}
				const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
				if (!pPiece) {
					outPos.insert(xtemp + ytemp * 9);
				}
				else {
					while (true) {
						xtemp += offset[i];
						ytemp += offset[i + 1];
						if (xtemp < 0 || xtemp>8 || ytemp < 0 || ytemp>9) {
							break;
						}
						const Piece* pTry = cbrdPiece.at(xtemp + ytemp * 9);
						if (!pTry)
							continue;
						if (pTry->GetCamp() == Camp::Red) {
							outPos.insert(xtemp + ytemp * 9);
							break;
						}
						else if (pPiece->GetCamp() == Camp::Black) {
							break;
						}
						else {
							throw;
						}
					}
					i += 2;
					break;
				}
			}
		}
		break;
	}
	case Piece::Name::Zu_1:
	case Piece::Name::Zu_2:
	case Piece::Name::Zu_3:
	case Piece::Name::Zu_4:
	case Piece::Name::Zu_5: {
		int xtemp = xch, ytemp = ych;
		if (ych < 5) {
			ytemp = ych + 1;
			const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
			if (!pPiece || pPiece->GetCamp() == Camp::Red) {
				outPos.insert(xtemp + ytemp * 9);
			}
		}
		else {
			int posEnum[6] = {
				xch - 1, ych, xch + 1, ych, xch, ych + 1
			};
			for (int i = 0; i < 6; i += 2) {
				xtemp = posEnum[i];
				ytemp = posEnum[i + 1];
				if (xtemp >= 0 && xtemp <= 8 && ytemp <= 9 && ytemp >= 5) {
					const Piece* pPiece = cbrdPiece.at(xtemp + ytemp * 9);
					if (!pPiece || pPiece->GetCamp() == Camp::Red) {
						outPos.insert(xtemp + ytemp * 9);
					}
				}
			}
		}
		break;
	}
	default:
		break;
	}
}

