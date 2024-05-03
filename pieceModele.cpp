
/**
* Ce programme d�finit une classe repr�sentant une pi�ce dans un jeu d'�checs, permettant de r�cup�rer son type et sa couleur.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Cr�� le 7 avril 2024
*/


#include "pieceModele.h"

Type Piece::getType() {
	return type_;
}

Color Piece::getColor() {
	return color_;
}
