/*

You will write the program of an action-rpg-like game.
In the console, player sees a grid by 20x30 (row x column). In this grid, player’s character starts in
the first cell, and certain amounts of trees and enemies are located in random cells. Each cell are
hidden, that means player doesn’t see the enemies or trees. Player only see the cells that are next
around the him/her or the cells that has been already passed by and make it visible (fog of war). Player
can see the all of the grid with activating the cheat. Pressing c activate and deactivate the cheat. If the
cheat is active all the cells in the grid will be visible, otherwise all of them will be hidden. Player can
move in the grid with using w-a-s-d keys. If there is a tree or enemy appear in the path of the player,
he/she can’t move to that direction. If the enemy is right next to the player, the player can kill the
enemy with pressing h. If all the enemies are death or the player presses q game ends.
*/
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <time.h>


//#define _ROW 20    That would be more useful, but f document wants it to pass via parameter
//#define _COLUMN 30
#define _DEBUG 0 // DEBUG USE THAT I USE IN IF STATEMENTS, YOU SHOULD NOT CHANGE IT.
#define _ROW 20
#define _COLUMN 30
#define _ENEMYAMOUNT 5
#define _TREEAMOUNT 5

int iPlayerPos[2] = {0,0}; // x,y
int iPrepareDisplayMatrix(int _iRow, int _iColmn,char array[_ROW][_COLUMN]);/* It takes the
                            sizes of the matrix and the displayMatrix as parameters.
                            Assign ‘P’to the first cell where player starts
                            and ▓(Ascii = -78) to the others.
                            */

int iPreparePlacementMatrix(int _iRow,int _iColmn, int iTreeAmount, int iEnemyAmount, char array[_ROW][_COLUMN]);/* It takes the sizes of the matrix, the placementMatrix,
                            tree count and enemy count as parameters.
                            Assign each cell a space character (‘ ‘) first,
                            then select random cells amount of tree count and enemy count parameters
                            and assing ‘T’ for trees and ‘E’ for enemies.
                            Enemies and trees cannot be generated in the first cell
                            and the cells one next around it.
                            To generate random numbers you can use rand() function.
                            rand()%number gives you random values between 0 and number.
                            Also you need to add srand() function,
                            to generate different sequence of random numbers each time game run, to the main function.
                            To use these functions, you need to add stdlib.h and time.h libraries to your code.
                            */


int  iUpdate(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], int * ipEnemyAmount);/*It takes size of the matrices,
displayMatrix, placementMatrix and an integer value to store enemy count as parameters

             */

int iNearCheck(int _iRandX, int _iRandY, char array[_ROW][_COLUMN]);


int iPrepareTheGame(int _iX, int _iY, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], int iTreeAmount, int iEnemyAmount);/*
                 It takes size of the matrices, displayMatrix, placementMatrix, tree count and enemy count as parameters
                    */
int iDisplay(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN],int _iCheatMode);/*

                akes sizes of the matrix and displayMatrix as parameters and shows the
                displayMatrix on the console.
                */

int iUpdateDisplayMatrix(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], char _cUserInput);/*
                            to check if player moves and display the grid with using display()

                            takes sizes of the matrices, displayMatrix, placementMatrix
                            and the Input character as parameters

                        */


int iFightWithTheEnemy(char iArrayPlacement[_ROW][_COLUMN],int *_iEnemyAmount); // function to check if the player fights with the enemy,
                            /*
                            placementMatrix, Input character
                            and the refence of the integer parameter of the update function as parameters.
                            */


//int iDisplayGodMode(int _iRow, int _iColmn, char cArrayDisplay[20][30], char cArrayPlacement[20][30]); // FOR CHEAT



/*       x
[ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ]    y
[ ][ ][ ][ ][ ][ ]
[ ][ ][ ][ ][ ][ ]

*/

int main(void){

    srand(time(NULL)); // set seed to create random number


    // I would not have this line if instrutcions were not ask to (iRow, iColmn). It makes change row and column easier though.
    int iRow = _ROW, iColumn= _COLUMN, iTreeAmount = _TREEAMOUNT, iEnemyAmount = _ENEMYAMOUNT;

    char cDisplayMatrix[iRow][iColumn];
    char cPlacementMatrix[iRow][iColumn];

    /*
    iPrepareDisplayMatrix(iRow, iColumn, cDisplayMatrix);

    iPreparePlacementMatrix(iRow, iColumn, 5,5,cPlacementMatrix);
    */

    iPrepareTheGame(iColumn, iRow, cDisplayMatrix, cPlacementMatrix, iTreeAmount, iEnemyAmount);

    if(_DEBUG){// print cDisplaymatrix
        printf("\n");

        for(int yy = 0; yy<iRow; yy++){//print PlacementMatrix
            for(int xx = 0; xx<iColumn; xx++){
                //printf("%c",cDisplayMatrix[yy][xx]);
                printf("%c",cPlacementMatrix[yy][xx]);
            }
            printf("%d \n",yy);
        }
        //getch();

        if(!_DEBUG){
            system("cls");
        }
        //system("cls");

    }



    iUpdate(iRow, iColumn,cDisplayMatrix, cPlacementMatrix, &iEnemyAmount);


    return 0;
}




int iPrepareDisplayMatrix(int _iRow, int _iColmn,char cArrayDisplay[_ROW][_COLUMN]){ // get cDisplayMatrix addresss,  80 -> P ascii table
    for(int yy = 0; yy<_iRow; yy++){ // yy -> row, xx -> column
        for(int xx = 0; xx < _iColmn; xx++){
            cArrayDisplay[yy][xx] = -78;
        }

    }
    cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = 80;

    return 0;
}




int iPreparePlacementMatrix(int _iRow,int _iColmn, int iTreeAmount, int iEnemyAmount, char cArrayPlacement[_ROW][_COLUMN]){ // get placement matrix, tree count, enemy count
                                // 32 space ascii table
    // fill with space
    for(int yy = 0; yy<_iRow; yy++){ // yy -> row, xx -> column
        for(int xx = 0; xx < _iColmn; xx++){
            cArrayPlacement[yy][xx] = 32; // space in ascii
        }

    }

    int iRandX, iRandY;
    // Random_Control:

    while(iTreeAmount != 0){
        iRandX = rand()%_iRow;
        iRandY = rand()%_iColmn;

        if(iRandX <2 && iRandY < 2){
            continue;
        }

        if(_DEBUG){
            printf("[Tree] RandX:%d, RandY%d",iRandX,iRandY);
        }


        if(iNearCheck(iRandX, iRandY, cArrayPlacement)){
            iTreeAmount = iTreeAmount -1;
            cArrayPlacement[iRandY][iRandX] = 84; // T in ascii

        }


    }



    while(iEnemyAmount != 0){
        iRandX = rand()%_iRow;
        iRandY = rand()%_iColmn;

        if(iRandX <2 && iRandY < 2){
            continue;
        }

        if(_DEBUG){
            printf("[Enemy] RandX:%d, RandY:%d",iRandX,iRandY);
        }


        if(iNearCheck(iRandX, iRandY, cArrayPlacement)){
            iEnemyAmount = iEnemyAmount -1;
            cArrayPlacement[iRandY][iRandX] = 69; // E in ascii

        }


    }




    return 0;
}


int iNearCheck(int _iX, int _iY, char array[_ROW][_COLUMN]){ // Get matrix, get randx, randy
    /*  x
    [ ][ ][ ]
    [ ][ ][ ] y
    [ ][ ][ ]
    */

    for(int yy = _iY -1; yy<=_iY +1;yy++){
        for(int xx = _iX -1; xx <= _iX +1;xx++){

            if(_DEBUG){
            printf("%d %d\n", _iX, _iY);
            printf("xx: %d || yy %d\n",xx,yy);

            }

            if(array[yy][xx] != 32){
                return 0;
            }

        }
    }


    return 1;

}


int iPrepareTheGame(int _iX, int _iY, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], int iTreeAmount, int iEnemyAmount){


    iPrepareDisplayMatrix(_iY, _iX, cArrayDisplay);

    iPreparePlacementMatrix(_iY, _iX, iTreeAmount,iEnemyAmount,cArrayPlacement);



    return 0;
}





int  iUpdate(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], int* ipEnemyAmount){
    /*you will create a game loop. Inside this loop, get input from the player with using getch()
function.

    */

    char cUserInput = NULL; // cUserInput = 0
    int iCheatMode = 0;

    iUpdateDisplayMatrix(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, cUserInput);
    iDisplay(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, iCheatMode);

    while(!(cUserInput == 113 || *ipEnemyAmount == 0)){ // GAME LOOP
            // Get user input to move 'P'layer
        cUserInput = getch();

        if(cUserInput == 99){
            iCheatMode = (iCheatMode+1) %2;

        }else if(cUserInput == 104){
            iFightWithTheEnemy(cArrayPlacement, ipEnemyAmount);
        }

        iUpdateDisplayMatrix(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, cUserInput);
        iDisplay(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, iCheatMode);

    }


    return 0;
}





int iUpdateDisplayMatrix(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], char _cUserInput){/*
                            to check if player moves and display the grid with using display()

                            takes sizes of the matrices, displayMatrix, placementMatrix
                            and the Input character as parameters

                        */

    if(_DEBUG){
        printf("X: %d, Y: %d\n", iPlayerPos[0],iPlayerPos[1]);
    }

    // MOVE AROUND
    switch(_cUserInput){
        //case 'W': // User may forget capslock on
        case 97: // Left || Y 119 -> A in asci
            if(iPlayerPos[1] > 0 && cArrayPlacement[iPlayerPos[0]][iPlayerPos[1] -1] == 32){
                cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = -80;
                iPlayerPos[1] = iPlayerPos[1] -1;
            }
            break;
        case 100: // Right || Y D
            //printf("\N HERE HONEY %d",_iColmn-1);
            if(iPlayerPos[1] < _iColmn-1 && cArrayPlacement[iPlayerPos[0]][iPlayerPos[1] +1] == 32){
                cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = -80;
                iPlayerPos[1] = iPlayerPos[1] +1;
            }
            break;
        case 119: // Up || X W
            if(iPlayerPos[0] > 0 && cArrayPlacement[iPlayerPos[0] -1][iPlayerPos[1]] == 32){
                cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = -80;
                iPlayerPos[0] = iPlayerPos[0] -1;
            }
            break;
        case 115: // Down || X S
            if(iPlayerPos[0] < _iRow-1 && cArrayPlacement[iPlayerPos[0] +1][iPlayerPos[1]] == 32){
                cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = -80;
                iPlayerPos[0] = iPlayerPos[0] +1;
            }
            break;
        /*case 99:
            //iDisplayGodMode(_iRow, _iColmn, cArrayDisplay, cArrayPlacement);
            //iDisplay(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, _cUserInput);
            _iCheatMode = (_iCheatMode +1)% 2;
            break;
        */

    }
    cArrayDisplay[iPlayerPos[0]][iPlayerPos[1]] = 80;

    if(_DEBUG){

        for(int yy = 0; yy<_iRow; yy++){
            for(int xx = 0; xx<_iColmn; xx++){
                //printf("%c",cArrayDisplay[yy][xx]);
                printf("%c",cArrayPlacement[yy][xx]);
            }
        printf("%d \n",yy); // table on right
        }

    }



    /*


    for(int yy= _iY -1; yy<=_iY +1;yy++){
        for(int xx = _iX -1; xx <= _iX +1;xx++){

            if(!_DEBUG){
            printf("%d %d\n", _iX, _iY);
            printf("xx: %d || yy %d\n",xx,yy);

            }


            if(array[yy][xx] != 32){
                return 0;
            }

        }
    }

    */
        /*  x
    [ ][ ][ ]
    [ ][P][ ] y
    [ ][ ][ ]

    for(int yy= _iY -1; yy<=_iY +1;yy++){
        for(int xx = _iX -1; xx <= _iX +1;xx++){

    */

    //int _iY = iPlayerPos[0]; for(int yy= _y[0] -1; yy<=_y[0] +1;yy++)
    //int _iX = iPlayerPos[1];for(int xx = _x[1] -1; xx <= _x[1] +1;xx++) That was meaningless to have another variable in ram
    /*TODO
        make able to work for edges
    */
    //
    for(int yy= iPlayerPos[0] -1; yy<=iPlayerPos[0] +1;yy++){// It will work every time // UNFOG WHERE I WENT
        for(int xx = iPlayerPos[1] -1; xx <= iPlayerPos[1] +1;xx++){
            if((yy == iPlayerPos[0] && xx == iPlayerPos[1]) || (yy == -1 || yy == _iRow || xx == -1 || xx == _iColmn)){ // TO DONT edditing 'P'layer
                continue;
            }

            if(cArrayPlacement[yy][xx] == 32){
                //printf("HERE");
                cArrayDisplay[yy][xx] = -80; //░
                //cArrayPlacement[yy][xx] = -80; // Just override to Placement Array, so I will not lose || UPDATED JUST CHECK THE DISPLAY FUNC, I JUST PRINTED WHİLE CHECKİNG BOTH ARRAYS
            }else{
                cArrayDisplay[yy][xx] = cArrayPlacement[yy][xx];
            }
        }
    }


    /*for(int yy= _iColmn -1; yy<_iColmn +1;yy++){ // It will work every time

        for(int xx = _iRow -1; xx < _iRow +1;xx++){


            printf("WHAT IS I'M LOOKING FOR %d",cArrayPlacement[yy][xx]);
            if(cArrayPlacement[yy][xx] == 32){
                    printf("HERE");
                //cArrayDisplay[yy][xx] = -80; //░

            }else{
                //cArrayDisplay[yy][xx] = cArrayPlacement[yy][xx];
            }
        }
    }*/

    //iDisplay(_iRow, _iColmn, cArrayDisplay, cArrayPlacement, _cUserInput);

    return 0;
}


int iDisplay(int _iRow, int _iColmn, char cArrayDisplay[_ROW][_COLUMN], char cArrayPlacement[_ROW][_COLUMN], int _iCheatMode){/* // MOD 0 just normal,

                akes sizes of the matrix and displayMatrix as parameters and shows the
                displayMatrix on the console.
                */

        /*
            I would use static int, but I'm not sure that we discuss about at class. Therefore I will just use a pointer
            Since I cannot have any static variable here, I will have a pointer in (func)iUpdate
        */
        //printf("\n");
        if(!_DEBUG){
            system("cls");
        }


        if(_iCheatMode == 0){
            for(int yy = 0; yy<_iRow; yy++){
                for(int xx = 0; xx<_iColmn; xx++){
                    //printf("%c",cDisplayMatrix[yy][xx]);
                    printf("%c",cArrayDisplay[yy][xx]);
                }
                if(_DEBUG){
                    printf("%d",yy); // y table on right
                }
                printf("\n");
            }
        return 0;
        }

        for(int yy = 0; yy< _iRow; yy++){
            for(int xx = 0; xx<_iColmn; xx++){
                if(yy == iPlayerPos[0] && xx == iPlayerPos[1]){
                    printf("%c",80);
                }else if(cArrayPlacement[yy][xx] == 32){
                    //printf("Gere");
                    printf("%c",-80);
                }else{
                    printf("%c",cArrayPlacement[yy][xx]);
                }
            }
            printf("\n");
        }
        return -1;

}



/*
int iDisplayGodMode(int _iRow, int _iColmn, char cArrayDisplay[20][30], char cArrayPlacement[20][30]){
    //printf("HERE");

    return 0;
}

*/





int iFightWithTheEnemy(char cArrayPlacement[_ROW][_COLUMN],int *_iEnemyAmount){ // function to check if the player fights with the enemy,
                            /*
                            placementMatrix, Input character
                            and the refence of the integer parameter of the update function as parameters.POINTER JUST SAY POINTER
                            */



    //int _iY = iPlayerPos[0];
    //int _iX = iPlayerPos[1];

    for(int yy= iPlayerPos[0] -1; yy<=iPlayerPos[0] +1;yy++){
        for(int xx = iPlayerPos[1] -1; xx <= iPlayerPos[1] +1;xx++){
            if(cArrayPlacement[yy][xx] == 69){
                *_iEnemyAmount = *_iEnemyAmount -1;
                cArrayPlacement[yy][xx] = 32;
                return 0;
            }

        }
    }

    return -1;
}




