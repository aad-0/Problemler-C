/* EXAMPLE OUTPUT:

You are expected to use the help of
pointers to change the values of these variables from the function.


    Output:
    A lucky number has been generated randomly.
    The lucky number is: 617                                                // Print the lucky number

    ********************************
    Player 1 enter your guess: 200                                          // Get the guesses
    Player 2 enter your guess: 317

    Proxymity of Player 1's guess to the lucky number is: 417               // Print the numbers
    Proxymity of Player 2's guess to the lucky number is: 300

    Player 2's guess is the closest guess to the lucky number.              // Print who is closer to lucky number
    ********************************
    Player 1 enter your guess: -100                                         // DO NOT EXECPT negative numbers
    Player 2 enter your guess: 217

    There is an invalid guess! Try again.
    ********************************
    Player 1 enter your guess: 610
    Player 2 enter your guess: 617

    Proxymity of Player 1's guess to the lucky number is: 7
    Proxymity of Player 2's guess to the lucky number is: 0

    Player 2's guess 's the cloesest guess to the lucky number.

    The scores are:                                                     // Print scores
    Player 1: 1
    Player 2: 4




*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h> // to have seed for srand()

void check_Guess(int *ipGuess_playerone, int *ipGuess_playertwo, int *ipLucky_num, int *ipScore_playerone, int *ipScore_playertwo, int *ipFlag);
void get_Guess(int *ipP1_guess, int *ipP2_guess);

int main(void){
    srand(time(0));     // set seed

    int iScore_playerone = 0;
    int iScore_playertwo = 0;

    int iGuess_playerone;
    int iGuess_playertwo;

    int iLucky_num = (rand() % 1000) +1;                    // Have random int between 0 and 1000
    printf("\nA lucky number has been generated randomly.");
    printf("\nThe lucky number is: %d\n",iLucky_num);

    /*
        You will have a loop that will ask the Player 1 and the Player 2 for a guess input until there is a correct guess
        (which can be checked if flag value is set to 1). If there is a negative guess number,
        print the message “There is an invalid guess! Try again." .
        In your loop, you will call a function called void checkGuess which should do three objectives:

    */

    int iFlag = 0; // Control flag for do-while loop

    do{
        get_Guess(&iGuess_playerone, &iGuess_playertwo); // Get guess input
        check_Guess(&iGuess_playerone, &iGuess_playertwo, &iLucky_num, &iScore_playerone, &iScore_playertwo, &iFlag); // Check Guess

    }while(iFlag == 0);// check_Guess will return iFlag 1 if it takes guesses properly

    printf("\n\nThe Scores are\nPlayer 1: %d\nPlayer 2: %d",iScore_playerone,iScore_playertwo); // Print Score Table

    return 0;

}
void get_Guess(int *ipP1_guess, int *ipP2_guess){
    printf("\n********************************");
    printf("\nPlayer 1 enter your guess: ");
    scanf("%d", ipP1_guess);
    printf("Player 2 enter your guess: ");
    scanf("%d", ipP2_guess);
    //???? Should I put a limit for 1000 to warn player? [ + ]

    if((*ipP1_guess > 1000 || *ipP1_guess < 0) || (*ipP2_guess > 1000 || *ipP2_guess < 0) ){
        printf("\nThere is an invalid guess! Try again, Input has to be positive and equal or less than 1000");
        get_Guess(ipP1_guess, ipP2_guess);
    }

}


void check_Guess(int *ipGuess_playerone, int *ipGuess_playertwo, int *ipLucky_num, int *ipScore_playerone, int *ipScore_playertwo, int *ipFlag){
/*
1. Calculation & printing of the Player 1’s and Player 2’s guess proximities to the lucky number.
    Display the message “Proximity of Player 1’s guess to the lucky number is: X” where X is the proximity value.

2. Checks if either one of these players or both guessed the number correctly.
    ✓ If there is a correct guess, change the flag value to 1 and return it.
    ✓ Display the message “Player n has guessed the number correctly.” where n represents either 1 or 2 for Player 1 and Player 2 respectively.

3. Update the scores of Player 1 and Player 2. Whoever makes the closest guess to the lucky number is printed as a message “Player n’s guess is the closest to the lucky number.” And their scores are returned as increased by one.
    ✓ If both the players make the same guess they both get +1 points. Print a message to show their guesses are the same.
    ✓ Guessing the lucky number itself is also grants +1 points.


*/


    *ipGuess_playerone = abs(*ipLucky_num - *ipGuess_playerone); // put the difference of guess to avoid calculate more than once
    *ipGuess_playertwo = abs(*ipLucky_num - *ipGuess_playertwo);

    // 1
    printf("\nProximity of Player 1's guess to the lucky number is: %d", *ipGuess_playerone);
    printf("\nProximity of Player 2's guess to the lucky number is: %d", *ipGuess_playertwo);
    // /1

    // 2
    if(*ipGuess_playerone == 0){
        printf("\nPlayer 1 has guessed the number correctly!");
        *ipFlag = 1;
    }
    if(*ipGuess_playertwo == 0){
        printf("\nPlayer 2 has guessed the number correctly!");
        *ipFlag = 1;
    }
    // /2

    // 3
    if(*ipGuess_playerone > *ipGuess_playertwo ){
        printf("\n\nPlayer 2's guess 's the closest guess to the lucky number.");
        *ipScore_playertwo = *ipScore_playertwo + 1;
    }else if(*ipGuess_playertwo > *ipGuess_playerone){
        printf("\n\nPlayer 1's guess 's the closest guess to the lucky number.");
        *ipScore_playerone = *ipScore_playerone + 1;
    }else{
        *ipScore_playerone = *ipScore_playerone + 1;
        *ipScore_playertwo = *ipScore_playertwo + 1;
    }

    // /3

}







