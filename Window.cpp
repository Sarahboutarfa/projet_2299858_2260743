/**
* Programme implémentant une interface graphique pour un jeu d'échecs en utilisant le framework Qt.
* \file   plateauModele.cpp
* \author Sarah Boutarfa et Kenza Zaimi
* \date   3 mai 2024
* Créé le 7 avril 2024
*/


#include "Window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    turnWhiteOrBlack();
    createChessboard();
    setupMenu();
    connect(ui.pushButton, &QPushButton::clicked, this, &Window::whichState);
   
}


Window::~Window(){
    for (const auto& ligne : grille) {
        for (QPushButton* bouton : ligne) {
            delete bouton;
        }
    }
}


void Window::createChessboard()
{
    QGridLayout* gridLayout = ui.gridLayout_4;
    const int boardSize = 8;
    rules.setColorCurrentPlayer(Color::WHITE);
    gridLayout->setSpacing(0);
    gridLayout->setContentsMargins(0, 0, 0, 0);
    for (int row = 0; row < boardSize; ++row) {
        std::vector<QPushButton*> rowButtons;
        for (int col = 0; col < boardSize; ++col) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(90, 90); 
            if ((row + col) % 2 == 0) {
                button->setStyleSheet("background-color: #A9A9A9;");
            }
            else {
                button->setStyleSheet("background-color: #D3D3D3;");
            }
            gridLayout->addWidget(button, row, col);

            connect(button, &QPushButton::clicked, this, &Window::handleSquareClick);
            rowButtons.push_back(button);
        }
        grille.push_back(rowButtons);
    }

}


void Window::handleSquareClick(){
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    showPossibleMoves(clickedButton);
};



void Window::turnClickedSquareGreen(QPushButton* clickedButton) {
    if (gameStarted && isAllowed) {
        clickedButton->setStyleSheet("background-color: green;");
        isAllowed = false;
    }
}


void Window::showPossibleMoves(QPushButton* clickedButton) {

    pair<int, int> pos = getPosCaseClicked(clickedButton);        

    shared_ptr<Piece> aPiece = rules.getPlateau()->getPieceAtPos(pos);             

    if (aPiece != nullptr) {
        currentPiece = rules.getPlateau()->getPieceAtPos(pos); 
    }

    QGridLayout* gridLayout = ui.gridLayout_4;                          

    if (aPiece != nullptr && pieceWasSelected == false ) {                                                                      

        if (pieceWasSelected == false && currentPiece->getColor() != rules.getColorCurrentPlayer()) {                                    
            Type type = currentPiece->getType();                               
            movemenValide = rules.whosValideMoves(type, pos);

            if (!movemenValide.empty()) {
                goBackColor();

                for (int i = 0; i < movemenValide.size(); i++) {
                    QPushButton* possibleMove = grille[movemenValide[i].first][movemenValide[i].second];

                    if (gameStarted && !clickedButton->icon().isNull() && clickedButton) {                      
                        pair<int, int> position = getPosCaseClicked(possibleMove);
                        shared_ptr<Piece> checkPiece = rules.getPlateau()->getPieceAtPos(position);
                        if (checkPiece != nullptr) {
                            if (checkPiece->getType() == Type::KING) {
                                possibleMove->setStyleSheet("background-color: red;");                         
                                isAllowed = true;
                            }
                            else {
                                possibleMove->setStyleSheet("background-color: lightgreen;");
                                isAllowed = true;
                            }
                        }
                        else {
                            possibleMove->setStyleSheet("background-color: lightgreen;");                        
                            isAllowed = true;
                        }  
                    }
                }
            }
            turnClickedSquareGreen(clickedButton);                                                                 
            pieceWasSelected = true;                                                                             
            previous = pos;
        }
    }

    else if (pieceWasSelected == true) {                                                           

        auto it = std::find(movemenValide.begin(), movemenValide.end(), pos);
       
        if (it != movemenValide.end() && aPiece == nullptr) {
            QPushButton* oldB = grille[previous.first][previous.second];
            oldB->setIcon(QIcon());
            QPushButton* newB = grille[pos.first][pos.second];
            loadAnImage(newB, getImage(rules.getPlateau()->getPieceAtPos(previous)));
            rules.getPlateau()->bougerPiece(previous, pos);
            rules.getPlateau()->ajouterPiece(nullptr, previous);
            counterTurn++;
            turnWhiteOrBlack();
            goBackColor();
            switchTurnColor();
            pieceWasSelected = false;
            currentPiece = nullptr;
            movemenValide.clear();
        }

        else if (aPiece != nullptr && it == movemenValide.end() && aPiece->getColor() != rules.getColorCurrentPlayer()) {

            Type type = aPiece->getType();
            movemenValide = rules.whosValideMoves(type, pos);

            if (!movemenValide.empty()) {
                goBackColor();

                for (int i = 0; i < movemenValide.size(); i++) {
                    QPushButton* possibleMove = grille[movemenValide[i].first][movemenValide[i].second];
                    if (clickedButton != nullptr) {
                        if (gameStarted && !clickedButton->icon().isNull() && clickedButton) {
                            possibleMove->setStyleSheet("background-color: lightgreen;");
                            isAllowed = true;
                        }
                    }
                }
            }
            turnClickedSquareGreen(clickedButton);
            pieceWasSelected = true;
            previous = pos;
        }

        else if (aPiece != nullptr && it != movemenValide.end()) {
            
            pieceWasSelected = false;
            switchTurnColor();

            QPushButton* newB = grille[pos.first][pos.second];
            QPushButton* oldB = grille[previous.first][previous.second];

            oldB->setIcon(QIcon());
            newB->setIcon(QIcon());
         
            loadAnImage(newB, getImage(rules.getPlateau()->getPieceAtPos(previous)));
            Type type = aPiece->getType();
            if (type == Type::KING) {
                rules.getPlateau()->bougerPiece(previous, pos);
                Color color = aPiece->getColor();
                if (color == Color::WHITE){
                    blackIsCheckMate = true;
                }
                else if (color == Color::BLACK){
                    whiteIsCheckMate = true;
                }
                gameStarted = true;
                whichState();  
            }
            else {
                rules.getPlateau()->bougerPiece(previous, pos);
                counterTurn++;
                turnWhiteOrBlack();
                goBackColor();
            }
        }
    };
}


pair<int, int> Window::getPosCaseClicked(QPushButton* clickedButton) {
    int row = -1;
    int col = -1;
    for (size_t i = 0; i <= grille.size(); i++) {
        auto it = std::find(grille[i].begin(), grille[i].end(), clickedButton);
        if (it != grille[i].end()) {
            row = i;
            col = it - grille[i].begin();
            break;
        }
    }
    return make_pair(row, col);
}


QString Window::getImagePath(enumImages image) {
    QString imagePath;
    switch (image) {
        case enumImages::ROOK_W:
            imagePath ="Images/Rook_W.png";
            break;
        case enumImages::ROOK_B:
            imagePath = "Images/Rook_B.png";
            break;
        case enumImages::KING_B:
            imagePath = "Images/King_B.png";
            break;
        case enumImages::KING_W:
            imagePath = "Images/King_W.png";
            break;
        case enumImages::QUEEN_B:
            imagePath = "Images/Queen_B.png";
            break;
        case enumImages::QUEEN_W:
            imagePath = "Images/Queen_W.png";
            break;
        case enumImages::KNIGHT_W:
            imagePath = "Images/Knight_W.png";
            break;
        case enumImages::KNIGHT_B:
            imagePath = "Images/Knight_B.png";
            break;
        case enumImages::PAWN_B:
            imagePath = "Images/Pawn_B.png";
            break;
        case enumImages::PAWN_W:
            imagePath = "Images/Pawn_W.png";
            break;
        case enumImages::BISHOP_B:
            imagePath = "Images/Bishop_B.png";
            break;
        case enumImages::BISHOP_W:
            imagePath = "Images/Bishop_W.png";
            break;
    }
    return imagePath;
}


void Window::loadAnImage(QPushButton* button, enumImages image) {
    QString imagePath = getImagePath(image);
    QPixmap pixmap(imagePath); 
    button->setIcon(QIcon(pixmap));
    button->setIconSize(QSize(50, 50));
  
}

void Window::setupMenu() {
    ui.comboBox->insertItem(0, "Select an option");
    ui.comboBox->addItem("Normal game");
    connect(ui.comboBox, QOverload<int>::of(&QComboBox::activated), this, &Window::handleComboBoxActivated);
}


void Window::handleComboBoxActivated(int index) {
    if (index == 1) { // Vérifie si l'option sélectionnée est "Normal game"
        isTypeGameSelected = true; // Définit isTypeGameSelected sur vrai
    }
}


void Window::loadPieces() {

    loadAnImage(grille[0][0], ROOK_B);
    loadAnImage(grille[0][1], KNIGHT_B);
    loadAnImage(grille[0][2], BISHOP_B);
    loadAnImage(grille[0][3], QUEEN_B);
    loadAnImage(grille[0][4], KING_B);
    loadAnImage(grille[0][5], BISHOP_B);
    loadAnImage(grille[0][6], KNIGHT_B);
    loadAnImage(grille[0][7], ROOK_B);
    
    for (int col = 0; col < 8; ++col) {
        loadAnImage(grille[1][col], PAWN_B);
    }
    loadAnImage(grille[7][0], ROOK_W);
    loadAnImage(grille[7][1], KNIGHT_W);
    
    loadAnImage(grille[7][2], BISHOP_W);
    loadAnImage(grille[7][3], QUEEN_W);
    loadAnImage(grille[7][4], KING_W);
    loadAnImage(grille[7][5], BISHOP_W);
    loadAnImage(grille[7][6], KNIGHT_W);
    loadAnImage(grille[7][7], ROOK_W);

    for (int col = 0; col < 8; ++col) {
        loadAnImage(grille[6][col], PAWN_W);
    }
}

void Window::goBackColor() {
    for (int col = 0; col < 8; col++) {
        for (int line = 0; line < 8; line++) {
            QPushButton* button = grille[line][col];
            button->setStyleSheet("QPushButton { margin 0; padding 0; background-color: " + QString(((line + col) % 2 == 0) ? "#A9A9A9" : "#D3D3D3") + "; }");
        }
    }
}


void Window::turnWhiteOrBlack() {
    QFont font = ui.label->font(); // Obtenir la police actuelle
    font.setPointSize(14); // Définir la taille de la police
    ui.label->setFont(font); // Appliquer la nouvelle police
    QFont fontBold = ui.label->font(); // Obtenir la police actuelle
    fontBold.setBold(true); // Rendre le texte en gras
    ui.label->setFont(fontBold);
    ui.label->setAlignment(Qt::AlignCenter);
    
    if (whiteIsCheckMate == false && blackIsCheckMate == false) {
        if (gameStarted == false)
            ui.label->setText("SELECT A GAME AND PRESS PLAY TO START");
        if (counterTurn == 0 && gameStarted)
            ui.label->setText("PLAYER WHITE, BEGIN THE GAME");
        else if (counterTurn % 2 != 0 && gameStarted == true)
            ui.label->setText("PLAYER BLACK, IT IS YOUR TURN");
        else if (counterTurn % 2 == 0 && gameStarted == true)
            ui.label->setText("PLAYER WHITE, IT IS YOUR TURN");
    }

    else if (whiteIsCheckMate == true && blackIsCheckMate == false) {
        ui.label->setText("BLACK, YOU WON! \n PRESS RESTART TO PLAY AGAIN");
    }
    else if (whiteIsCheckMate == false && blackIsCheckMate == true) {
        ui.label->setText("WHITE, YOU WON! \n PRESS RESTART TO PLAY AGAIN");
    }
}


void Window::clearBoard() {
  
   const int boardSize = 8;
   QGridLayout* gridLayout = ui.gridLayout_4;

   goBackColor();

   for (int row = 0; row < boardSize; ++row) {
       for (int col = 0; col < boardSize; ++col) {
           QPushButton* button = qobject_cast<QPushButton*>(gridLayout->itemAtPosition(row, col)->widget());
           button->setIcon(QIcon()); 
       }
   }
}


void Window::loadPiecesWhenStartClicked() {
    gameStarted = true;
    loadPieces();
    turnWhiteOrBlack();
    ui.pushButton->setText("Restart");
}


void Window::resetGameWhenRestart() {
    gameStarted = false;
    pieceWasSelected = false;
    rules.setColorCurrentPlayer(Color::WHITE);
    rules.getPlateau()->reinitialiserPlateau();
    counterTurn = 0;
    clearBoard();
    turnWhiteOrBlack();
    ui.pushButton->setText("Start"); 
}


void Window::restartGameWhenCHeckMate() {

    clearBoard();
    ui.pushButton->setText("Restart");
    turnWhiteOrBlack();
    gameStarted = true;
    blackIsCheckMate = false;
    whiteIsCheckMate = false;
}


void Window::whichState() {

    if (gameStarted) {
        if (blackIsCheckMate == true || whiteIsCheckMate == true) {
            restartGameWhenCHeckMate();
        }
        else{
            resetGameWhenRestart();
        }
    }
    else if(gameStarted == false && isTypeGameSelected == true){
       loadPiecesWhenStartClicked(); 
        isTypeGameSelected = false;
    }
}


enumImages Window::getImage(shared_ptr<Piece> piece) {
    if (piece != nullptr) {

        Type type = piece->getType();
        Color color = piece->getColor();

        if (color == Color::BLACK) {
            if (type == Type::ROOK) {
                return enumImages::ROOK_W;
            }
            else if (type == Type::KING) {
                return enumImages::KING_W;
            }
            else if (type == Type::QUEEN) {
                return enumImages::QUEEN_W;
            }
            else if (type == Type::PAWN) {
                return enumImages::PAWN_W;
            }
            else if (type == Type::BISHOP) {
                return enumImages::BISHOP_W;
            }
            else if (type == Type::KNIGHT) {
                return enumImages::KNIGHT_W;
            }
        }
        if (color == Color::WHITE) {
            if (type == Type::ROOK) {
                return enumImages::ROOK_B;
            }
            else if (type == Type::KING) {
                return enumImages::KING_B;
            }
            else if (type == Type::QUEEN) {
                return enumImages::QUEEN_B;
            }
            else if (type == Type::PAWN) {
                return enumImages::PAWN_B;
            }
            else if (type == Type::BISHOP) {
                return enumImages::BISHOP_B;
            }
            else if (type == Type::KNIGHT) {
                return enumImages::KNIGHT_B;
            }
        }
    }
}

void Window::switchTurnColor() {
    if (rules.getColorCurrentPlayer() == Color::WHITE) {
        rules.setColorCurrentPlayer(Color::BLACK);
    }
    else {
        rules.setColorCurrentPlayer(Color::WHITE);
    }
}
