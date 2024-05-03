/**
* Programme qui est une implémentation d'un plateau de jeu d'échecs avec des fonctionnalités de manipulation de pièces, de mouvement et de capture.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Créé le 7 avril 2024
*/

#include "plateauModele.h"

Plateau::Plateau() {

	for (int line = 0; line < 8; line++) {
		for (int col = 0; col < 8; col++) {
			matricePlateau[line][col] = make_shared<CasePlateau>();
		}
	}
	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::WHITE), make_pair(0, 0));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::WHITE), make_pair(0, 1));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::WHITE), make_pair(0, 2));
	ajouterPiece(make_shared<Piece>(Type::QUEEN, Color::WHITE), make_pair(0, 3));
	ajouterPiece(make_shared<Piece>(Type::KING, Color::WHITE), make_pair(0, 4));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::WHITE), make_pair(0, 5));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::WHITE), make_pair(0, 6));
	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::WHITE), make_pair(0, 7));
	for (int col = 0; col < 8; ++col) {
		ajouterPiece(make_shared<Piece>(Type::PAWN, Color::WHITE), make_pair(1, col));
	}

	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::BLACK), make_pair(7, 0));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::BLACK), make_pair(7, 1));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::BLACK), make_pair(7, 2));
	ajouterPiece(make_shared<Piece>(Type::QUEEN, Color::BLACK), make_pair(7, 3));
	ajouterPiece(make_shared<Piece>(Type::KING, Color::BLACK), make_pair(7, 4));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::BLACK), make_pair(7, 5));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::BLACK), make_pair(7, 6));
	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::BLACK), make_pair(7, 7));
	for (int col = 0; col < 8; ++col) {
		ajouterPiece(make_shared<Piece>(Type::PAWN, Color::BLACK), make_pair(6, col));
	}
	
}


void Plateau::reinitialiserPlateau() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++){
			matricePlateau[i][j]->setPiece(nullptr);

		}
	}

	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::WHITE), make_pair(0, 0));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::WHITE), make_pair(0, 1));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::WHITE), make_pair(0, 2));
	ajouterPiece(make_shared<Piece>(Type::QUEEN, Color::WHITE), make_pair(0, 3));
	ajouterPiece(make_shared<Piece>(Type::KING, Color::WHITE), make_pair(0, 4));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::WHITE), make_pair(0, 5));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::WHITE), make_pair(0, 6));
	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::WHITE), make_pair(0, 7));
	for (int col = 0; col < 8; ++col) {
		ajouterPiece(make_shared<Piece>(Type::PAWN, Color::WHITE), make_pair(1, col));
	}

	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::BLACK), make_pair(7, 0));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::BLACK), make_pair(7, 1));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::BLACK), make_pair(7, 2));
	ajouterPiece(make_shared<Piece>(Type::QUEEN, Color::BLACK), make_pair(7, 3));
	ajouterPiece(make_shared<Piece>(Type::KING, Color::BLACK), make_pair(7, 4));
	ajouterPiece(make_shared<Piece>(Type::BISHOP, Color::BLACK), make_pair(7, 5));
	ajouterPiece(make_shared<Piece>(Type::KNIGHT, Color::BLACK), make_pair(7, 6));
	ajouterPiece(make_shared<Piece>(Type::ROOK, Color::BLACK), make_pair(7, 7));
	for (int col = 0; col < 8; ++col) {
		ajouterPiece(make_shared<Piece>(Type::PAWN, Color::BLACK), make_pair(6, col));
	}

	firstRoundWhite = true;
	firstRoundBlack = true;

	fallenBlack.clear();
	fallenWhite.clear();
}




void Plateau::ajouterPiece(shared_ptr<Piece> piece, pair<int, int> pos) {

	if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7) {
		qDebug() << "position out of range";
	}
	else {
		matricePlateau[pos.first][pos.second]->setPiece(piece);
	}
}



void Plateau::enleverPiece(shared_ptr<Piece> piece, pair<int, int> pos) {
	if (pos.first < 0 || pos.first > 7 || pos.second < 0 || pos.second > 7) {
		qDebug() << "position out of range";
	}
	else {
		matricePlateau[pos.first][pos.second]->setPiece(nullptr);
	}
}



bool Plateau::isCaseOccupe(pair<int, int> pos) {
	if (matricePlateau[pos.first][pos.second]->getPiece() == nullptr) {
		return false;
	}
	else {
		return true;
	}
}


void Plateau::eatPiece(pair<int, int> pos) {
	shared_ptr<Piece> piece = getPieceAtPos(pos);
	if (piece->getColor() == Color::BLACK) {
		fallenBlack.push_back(piece);
		couleurPrise = Color::BLACK;
	}
	else {
		fallenWhite.push_back(piece);
		couleurPrise = Color::WHITE;
	}
	matricePlateau[pos.first][pos.second]->setPiece(nullptr);
}


void Plateau::bougerPiece(pair<int, int> posInit, pair<int, int> moveTo) {
	if (firstRoundBlack == true || firstRoundWhite == true) {
		shared_ptr<Piece> piece = getPieceAtPos(posInit);
		Color color = piece->getColor();

		if (color == Color::WHITE) {
			firstRoundWhite = false;
		}
		else if (color == Color::BLACK) {
			firstRoundBlack = false;
		}
	}
	

	if (isCaseOccupe(posInit)) {
		
		if(isCaseOccupe(moveTo)) {
			eatPiece(moveTo);
		}
		matricePlateau[moveTo.first][moveTo.second]->setPiece(matricePlateau[posInit.first][posInit.second]->getPiece());
		matricePlateau[posInit.first][posInit.second]->setPiece(nullptr);

	}
}


shared_ptr<Piece> Plateau::getPieceAtPos(pair<int, int> pos) {
	if (isCaseOccupe(pos) == true) {
		return matricePlateau[pos.first][pos.second]->getPiece();
	}
	else {
		return nullptr;
	}
}
