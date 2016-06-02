#include <iostream>
#include <pair>
#include <cstring>
#include <string>

using namespace std;


class Figure
{
protected:
    pair<char,int> position;
    char color;
    string type;
public:
    Figure(position.first,position.second,char color)
    {
        this->position.first=position.first;
        this->position.second=position.second;
        this->color=color;
    }

    pair<char,int> getPosition()
    {
        return position;
    }

    char getColor()
    {
        return color;
    }

    string getType()
    {
        return type;
    }



   virtual bool move(char letter,int num)=0;


};

class Board
{
private:
    Figure* figures[32];
    int currentSize;
    int height;
    int width;

    bool removePiece(char posLet,int posNum);

public:
    Board()
    {
        //should initialize the board with all the figures.
    }
    Figure* getPieceOnPos(char posLetter,int posNum);

    bool moveFigure(char letterStart,int numStart,char letterEnd,int numEnd);
    void printBoard();

};

class Rook:public Figure
{
public:
    Rook(char posLetter,int posNumber,char color):Figure(posLetter,posNumber,color)
    {
        this->color=color;
    }

    bool move(char newPosLetter,int newPosNum)
    {
        bool isValidMove=true;

        if(newPosLetter==position.first || newPosNum==position.second)
            {
                position.first=newPosLetter;
                position.second=newPosNum;
            }
        else
            {
                isValidMove=false;
            }

        return isValidMove;
    }
};

class Pawn:public Figure
{

};

