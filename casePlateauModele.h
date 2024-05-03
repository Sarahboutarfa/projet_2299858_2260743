#pragma once
#include <iostream>
#include <pieceModele.h>
using namespace std;

class CasePlateau
{
public:
	CasePlateau(){
		pieceDansCase_ = nullptr;
		isOccupe_ = false;
	};

	CasePlateau(shared_ptr<Piece> piece){
		pieceDansCase_ = piece;
		isOccupe_ = true;
	};

	shared_ptr<Piece> getPiece();
	
	void setPiece(shared_ptr<Piece> piece);

	bool getOccupe();


private:
	bool isOccupe_;
	
	shared_ptr<Piece> pieceDansCase_;

};




