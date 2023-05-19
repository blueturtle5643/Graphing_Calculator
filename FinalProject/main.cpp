/*********************************************************
* AUTHOR : Brian Ouyang
* PROJECT: Assignment # 19 : Chapter 15
* CLASS : CS 3A
* SECTION : MTH: 1:00p – 3:05p
* Due Date : 5/24/20
*********************************************************/
#include <iostream>
#include "animate.h"
#include "system.h"
#include "constants.h"
using namespace std;
/**********************************************************
*
* Programming Project: Graphing Calculator
*_________________________________________________________
*
* Write a program that imitates an graphing ca
* Allow user to zoom, pan, add equations, clear, and
* display on the board.
*_________________________________________________________
* INPUT:
*
* Equation
*
* OUTPUT:
*
* Interactable screen of the equation graphed on the screen
*
*
* PROCESSING:
*
* Program utilizes several classes to handle logic and
* flow of the project. Classes are divided by the type of
* work they handle.
*
***********************************************************/
// functions



int main( )
{

    char option;

    do

    {

        animate game;

        game.run();

//        string ಠ_ಠ;

//        ಠ_ಠ = "gang gang";

//        cout << ಠ_ಠ;

        cout << "\nDo you want to repeat the calculation? Enter 'Y' or 'y': ";

        cin >> option;
    }

    while (option == 'y' || option == 'Y');

    return 0;
}
/**********************************************************
*
*
*
*
*
*
*
*
*
*
*
*Do you want to repeat the calculation? Enter 'Y' or 'y':
*
***********************************************************/
