#pragma once
#include <vector>
#include "plateauModele.h"

class Rules
{
public:
	Rules() {
		plateau_ = make_shared<Plateau>();
		turnWhichColor_ = Color::WHITE;
	}

	vector<pair<int, int>> movesValidePawnAtPos(pair<int, int> pos);
	vector<pair<int, int>> movesValideBishopAtPos(pair<int, int> pos);
	vector<pair<int, int>> movesValideKnightAtPos(pair<int, int> pos);
	vector<pair<int, int>> movesValideKingAtPos(pair<int, int> pos);
	vector<pair<int, int>> movesValideQueenAtPos(pair<int, int> pos);
	vector<pair<int, int>> movesValideRookAtPos(pair<int, int> pos);

	vector<pair<int, int>> whosValideMoves(Type typePiece, pair<int, int> pos);

	bool isPositionDansPlateau(pair<int, int> pos);

	shared_ptr<Plateau> getPlateau() {
		return plateau_;
	}
	Color getColorCurrentPlayer() {
		return turnWhichColor_;
	}
	void setColorCurrentPlayer(Color color) {
		turnWhichColor_ = color;
	}

private:
	shared_ptr<Plateau> plateau_;
	Color turnWhichColor_ = Color::WHITE;
};

