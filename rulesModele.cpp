/**
* Programme implémentant des règles de déplacement valides pour différents types de pièces d'un jeu d'échecs, en vérifiant les mouvements autorisés en fonction de la position et du type de pièce sur un plateau donné.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Créé le 7 avril 2024
*/

#include "rulesModele.h"

bool Rules::isPositionDansPlateau(pair<int, int> pos) {
	return pos.first >= 0 && pos.first < 8 && pos.second >= 0 && pos.second < 8;
}



vector<pair<int, int>> Rules::movesValidePawnAtPos(pair<int, int> pos) {
	vector<pair<int, int>> vecteurDeplacement;

	vector<pair<int, int>> goTo;

	if(plateau_->getPieceAtPos(pos)->getColor() == Color::BLACK){
		if (plateau_->firstRoundBlack == true) {
			goTo = { 
				make_pair(-1,  1), 
				make_pair(-1, -1), 
				make_pair(-1,  0), 
				make_pair(-2,  1), 
				make_pair(-2, -1), 
				make_pair(-2,  0) 
			};
		}
		else {
			goTo = { 
				make_pair(-1,  1), 
				make_pair(-1, -1), 
				make_pair(-1,  0) 
			};
		}
	}
	else{	
		if (plateau_->firstRoundWhite == true) {
			goTo = { 
				make_pair(2, 1), 
				make_pair(2,-1), 
				make_pair(2, 0), 
				make_pair(1, 1), 
				make_pair(1,-1), 
				make_pair(1, 0) 
			};
		}
		else {
			goTo = {
				make_pair(1, 1), 
				make_pair(1,-1),
				make_pair(1, 0)
			};
		}
	}

	for (const auto& position : goTo) {
		pair<int, int> versOu = make_pair(pos.first + position.first, pos.second + position.second);
		if (isPositionDansPlateau(versOu)) {
			if (position.second == 0) {
				if (!plateau_->isCaseOccupe(versOu))
					vecteurDeplacement.push_back(versOu);
			}

			else if (plateau_->isCaseOccupe(versOu) &&
				plateau_->getPieceAtPos(versOu)->getColor() != plateau_->getPieceAtPos(pos)->getColor())
				vecteurDeplacement.push_back(versOu);
		}
	}
	return vecteurDeplacement;
}



vector<pair<int, int>> Rules::movesValideBishopAtPos(pair<int, int> pos) {
	vector<pair<int, int>> goTo = { 
		make_pair( 1, 1),
		make_pair(1,-1),

		make_pair(-1, 1), 
		make_pair(-1,-1) 
	};
	vector<pair<int, int>> vecteurDeplacement;
	for (const auto& position : goTo) {
		int compteur = 1;
		bool indicateur = true;
		while (indicateur && compteur < 8) {
			pair<int, int> versOu = make_pair(pos.first + (position.first * compteur), pos.second + (position.second * compteur));
			
			if (isPositionDansPlateau(versOu) == false) {
				indicateur = false;
				continue;
			}

			if (plateau_->isCaseOccupe(versOu) == true) {
				Color checkColorInit = plateau_->getPieceAtPos(pos)->getColor();
				Color checkFutur = plateau_->getPieceAtPos(versOu)->getColor();
				
				if (checkColorInit != checkFutur)
					vecteurDeplacement.push_back(versOu);
				indicateur = false;
			}
			else {
				vecteurDeplacement.push_back(versOu);
			}
			compteur++;
		}
	}
	return vecteurDeplacement;
}



vector<pair<int, int>> Rules::movesValideRookAtPos(pair<int, int> pos) {
	vector<pair<int, int>> vecteurDeplacement;

	vector<pair<int, int>> goTo = { 
		make_pair( 0, 1),
		make_pair(0,-1),

		make_pair( 1, 0), 
		make_pair(-1, 0) 
	};

	for (const auto& position : goTo) {
		int counter = 1;
		bool indicateur = true;
		while (counter < 8 && indicateur) {
			pair<int, int> versOu = make_pair(pos.first + (position.first * counter), pos.second + (position.second * counter));
			
			if (isPositionDansPlateau(versOu) == false) {
				indicateur = false;
				continue;
			}
			if (plateau_->isCaseOccupe(versOu) == true) {
				if (plateau_->getPieceAtPos(versOu)->getColor() != plateau_->getPieceAtPos(pos)->getColor())
					vecteurDeplacement.push_back(versOu);
				indicateur = false;
			}
			else
				vecteurDeplacement.push_back(versOu);
			counter++;
		}
	}
	return vecteurDeplacement;
}



vector<pair<int, int>> Rules::movesValideQueenAtPos(pair<int, int> pos) {
	vector<pair<int, int>> vecteurDeplacement;

	vector<pair<int, int>> goTo = { 
		make_pair( 0, 1),
		make_pair( 0,-1),

		make_pair( 1, 1),
		make_pair( 1,-1),
		make_pair( 1, 0),

		make_pair(-1,  1), 
		make_pair(-1, -1), 
		make_pair(-1,  0) 

	};
	for (const auto& direction : goTo) {
		
		int compteur = 1;
		bool indicateur = true;
		
		
		while (compteur < 8 && indicateur) {

			pair<int, int> versOu = make_pair(pos.first + (direction.first * compteur), pos.second + (direction.second * compteur));
			
			if (isPositionDansPlateau(versOu) == false) {
				indicateur = false;
				continue;
			}
			if (plateau_->isCaseOccupe(versOu)) {
				if (plateau_->getPieceAtPos(versOu)->getColor() != plateau_->getPieceAtPos(pos)->getColor())
					vecteurDeplacement.push_back(versOu);
				indicateur = false;
			}
			else
				vecteurDeplacement.push_back(versOu);
			compteur++;
		}
	}
	return vecteurDeplacement;
}



vector<pair<int, int>> Rules::movesValideKingAtPos(pair<int, int> pos) {
	vector<pair<int, int>> goTo = { 
		make_pair(0, 1),
		make_pair(0,-1),

		make_pair( 1, 1), 
		make_pair( 1,-1),
		make_pair(1, 0),

		make_pair(-1, 1), 
		make_pair(-1,-1), 
		make_pair(-1, 0) 
	};
	vector<pair<int, int>> vecteurDeplacement;
	for (const auto& position : goTo) {
		pair<int, int> casePossible = make_pair(pos.first + position.first, pos.second + position.second);
		if (isPositionDansPlateau(casePossible) == true) {
			
			if (plateau_->isCaseOccupe(casePossible) == true) {
				
				if (plateau_->getPieceAtPos(casePossible)->getColor() != plateau_->getPieceAtPos(pos)->getColor()) {
					vecteurDeplacement.push_back(casePossible);
				}
			}
			else {
					vecteurDeplacement.push_back(casePossible);
			}
		}
	}
	return vecteurDeplacement;
}


vector<pair<int, int>> Rules::movesValideKnightAtPos(pair<int, int> pos) {
	vector<pair<int, int>> mouvementValide;

	vector<pair<int, int>> mouvementPossible = {
		make_pair(pos.first + 1,pos.second + 2),
		make_pair(pos.first + 1,pos.second - 2),


		make_pair(pos.first + 2,pos.second + 1),
		make_pair(pos.first + 2,pos.second - 1),


		make_pair(pos.first - 1,pos.second + 2),
		make_pair(pos.first - 1,pos.second - 2),

		make_pair(pos.first - 2,pos.second + 1),
		make_pair(pos.first - 2,pos.second - 1)
	};

	
	
	for (const auto& position : mouvementPossible) {
		
		if (isPositionDansPlateau(position)) {
			
			if (plateau_->isCaseOccupe(position) == true) {
				
				if (plateau_->getPieceAtPos(position)->getColor() != plateau_->getPieceAtPos(pos)->getColor())
					mouvementValide.push_back(position);
			}
			
			else {
				mouvementValide.push_back(position);
			}
		}
	}
	return mouvementValide;
}



vector<pair<int, int>> Rules::whosValideMoves(Type typePiece, pair<int, int> pos) {

	if (typePiece == Type::PAWN) {
		return movesValidePawnAtPos(pos);
	}
	else if (typePiece == Type::KNIGHT) {
		return movesValideKnightAtPos(pos);
	}
	else if (typePiece == Type::BISHOP) {
		return movesValideBishopAtPos(pos);
	}
	else if (typePiece == Type::QUEEN) {
		return movesValideQueenAtPos(pos);
	}
	else if (typePiece == Type::KING) {
		return movesValideKingAtPos(pos);
	}
	else if (typePiece == Type::ROOK) {
		return movesValideRookAtPos(pos);
	}

}

