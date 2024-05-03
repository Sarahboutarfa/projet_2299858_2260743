#pragma once


enum class Type { ROOK, PAWN, KING, QUEEN, KNIGHT, BISHOP, EMPTY };
enum class Color { WHITE, BLACK, NOCOLOR };


class Piece
{
public:
	Piece(Type type, Color color){
		type_  = type;
		color_ = color;
	};
	
	Piece(){
		type_   = Type::EMPTY;
		color_  = Color::NOCOLOR;
	};

	~Piece() = default;
	Color getColor();
	Type getType();

private:
	Type type_;
	Color color_;

};

