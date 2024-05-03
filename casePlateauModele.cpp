/**
* 
* Programme d�finissant une classe repr�sentant une case sur un plateau de jeu, permettant de stocker et de r�cup�rer une pi�ce associ�e � cette case.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Cr�� le 7 avril 2024
*/


#include "casePlateauModele.h"

shared_ptr<Piece> CasePlateau::getPiece() {
	return pieceDansCase_;
}


bool CasePlateau::getOccupe() {
	return isOccupe_;
}

void CasePlateau::setPiece(shared_ptr<Piece> piece){
	
	pieceDansCase_ = piece;
	if (piece == nullptr) {
		isOccupe_ = false;
	}
	else {
		isOccupe_ = true;
	}
}


