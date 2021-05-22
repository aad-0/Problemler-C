/*

Your code should include both if and switch statements. In some decision statements
use if, in some decision statements use switch.


Working hour for a week: Payment for one hour:
More than 45                100$
Between 20-45               75$
Less than 20                50$

. Firstly, ask employees name and surname, then calculate base salary of the employee by
asking working hours for a week



After calculating the salary, you need to ask user to select extra payment method.
 If user enters k/K
you need to ask how many km the user comes to work; according to this value,
you need to increase
calculated salary based on given percentages



KM options (K/k) Extra payment percentages
More than 50 km %12
Between 25-50 %8
Less than 25 %4




*/
#include <stdlib.h>
#include <stdio.h>

int main(void){


    char cExtraPaymentMethod, cName_Lastname[40];

    float iStore, iExtraPaymentInput; // I will store the base salary in iStore


    printf("Enter your name and surname: ");
    //scanf("%40[^\n]",&cName_Lastname);
    fgets(cName_Lastname, 40, stdin);
    //gets(cName_Lastname); // fgets would be better, since it has overflow control

    printf("-------");

    printf("\nEnter the number of hours you are working for a week: ");
    scanf("%f",&iStore);



    // iStore will stores the base payment
    if(iStore < 20){
        iStore = 4 * iStore * 50;

    }else if(iStore < 45){
        iStore = 4 * iStore * 75;

    }else{
        iStore = 4 * iStore * 100;
    }




    // get km and put extra payment



    int iWhileFlag = -1;
    while(iWhileFlag == -1){
        printf("Select extra payment method. Enter K/k for km, C/c for amount of children: ");
        //scanf(" %[^\n]",cExtraPaymentMethod);
        scanf(" %c",&cExtraPaymentMethod);

        switch(cExtraPaymentMethod){
            case 'K':
            case 'k':

                iWhileFlag = 0;
                printf("Enter the km that you came to work: ");
                scanf("%f",&iExtraPaymentInput);

                if(iExtraPaymentInput < 25){
                    iStore = iStore + iStore * 4 / 100;

                }else if(iExtraPaymentInput < 50){
                    iStore = iStore + iStore * 8 / 100;

                }else{
                    iStore = iStore + iStore * 12 / 100;

                }

                break;

            case 'C':
            case 'c':

                iWhileFlag = 0;
                printf("Enter the amount of children you have: ");
                scanf("%f",&iExtraPaymentInput);

                if(iExtraPaymentInput == 1){
                    iStore = iStore + iStore * 5 / 100;

                }else if(iExtraPaymentInput < 5){
                    iStore = iStore + iStore * 9 / 100;

                }else{
                    iStore = iStore + iStore * 15 / 100;
                }

                break;

            default:
                printf("\nPlease enter a valid option.\n");

        }

    }

    printf("\nDear %s, your salary for month is %.2f",cName_Lastname, iStore);


    return 0;
}


















































