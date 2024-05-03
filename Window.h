#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include "ui_Window.h"
#include "rulesModele.h"
#include "plateauModele.h"
#include "pieceModele.h"
#include <QGridLayout>
#include <QLabel>
#include <vector>
#include <QDebug>
#include <vector>
#include <utility>

enum enumImages { KING_B, KING_W, QUEEN_B, QUEEN_W, ROOK_B, ROOK_W, KNIGHT_B, KNIGHT_W, PAWN_B, PAWN_W, BISHOP_B, BISHOP_W };


class Window : public QMainWindow{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:
    Ui::WindowClass ui;
    //std::vector<std::vector<QLabel*>> chessboard; 
    std::vector<std::vector<QPushButton*>> grille; 
    std::vector<pair<int, int>> movemenValide;
    shared_ptr<Piece> currentPiece;
    pair<int, int> previous;
    QVector<QPixmap> pieceImages;
    

    bool gameStarted = false;
    bool isAllowed = false;
    bool pieceWasSelected = false;
    bool canBeCheckmate = false;
    bool whiteIsCheckMate = false;
    bool blackIsCheckMate = false;
    bool isTypeGameSelected = false;

    int counterTurn = 0;
    Rules rules;
   
    void createChessboard();
    void handleSquareClick();
    void handleComboBoxActivated(int index);
    void setupMenu();
    void turnWhiteOrBlack();
    void loadAnImage(QPushButton* button, enumImages image);
    void loadPieces();
    void clearBoard();
    void loadPiecesWhenStartClicked();
    void resetGameWhenRestart();
    void whichState();
    void showPossibleMoves(QPushButton* clickedButton);
    void goBackColor();
    void switchTurnColor();
    void turnClickedSquareGreen(QPushButton* clickedButton);
    void restartGameWhenCHeckMate();

    pair<int, int> getPosCaseClicked(QPushButton* clickedButton);
    enumImages getImage(shared_ptr<Piece> piece);
    QString getImagePath(enumImages image);


};




