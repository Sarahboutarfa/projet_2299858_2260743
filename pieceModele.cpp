
/**
* Ce programme définit une classe représentant une pièce dans un jeu d'échecs, permettant de récupérer son type et sa couleur.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Créé le 7 avril 2024
*/


#include "pieceModele.h"

Type Piece::getType() {
	return type_;
}

Color Piece::getColor() {
	return color_;
}
