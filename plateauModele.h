#pragma once
#include <vector>
#include <QDebug>
#include "casePlateauModele.h"
class Plateau
{

public:
	Plateau();
	~Plateau() = default;


	void ajouterPiece(shared_ptr<Piece> piece, pair<int, int> pos);
	void bougerPiece(pair<int, int> posInit, pair<int, int> moveTo);
	void enleverPiece(shared_ptr<Piece> piece, pair<int, int> pos);

	bool isCaseOccupe(pair<int, int> pos);

	shared_ptr<Piece> getPieceAtPos(pair<int, int> pos);

	void eatPiece(pair<int, int> pieceAndPos);

	void reinitialiserPlateau();

	bool firstRoundBlack = true;
	bool firstRoundWhite = true;
	
private:
	shared_ptr<CasePlateau> matricePlateau[8][8];

	vector<shared_ptr<Piece>> fallenWhite;
	vector<shared_ptr<Piece>> fallenBlack;

	pair<int, int> WKingPos;
	pair<int, int> BKingPos;

	Color couleurPrise;

	bool isCheck;


};

