#include <stdlib.h>
#include <stdio.h>

#define _NAMESIZE 100

float fiCalMin(int _iHour1, int _iMin1, int _iHour2, int _iMin2);

int main(void){

    int iMemberAmount = 0;

    //char cMemberCheck = 0; //
    char cMemberName[_NAMESIZE]; // also I will store here if user is member or not

    printf("Enter the number of people in the center: ");
    scanf("%d", &iMemberAmount);

    int i = 0;
    while(i < iMemberAmount){

        printf("Enter member or not (Y/N):");
        scanf(" %c",&cMemberName); // store in Name if they are member or not



        if(*cMemberName == 89 || *cMemberName == 121){
            i = i +1;

            int iHour1, iMin1, iHour2, iMin2, iMemberId; // To store check-in check-out times
            //int iMemberId = 0;
            printf("Member of the sports center,");
            printf("\nEnter member id: ");
            scanf("%d",&iMemberId);

            printf("Enter member name: ");
            scanf("%s",&cMemberName);

            printf("Member of the sports center, %d, %s,",iMemberId, cMemberName);
            // get check in/out times
            printf("\nEnter the check-in time (HH:MM): ");
            scanf("%d%c%d",&iHour1,&iMin1,&iMin1);

            printf("Enter the check-out time (HH:MM): ");
            scanf("%d%c%d",&iHour2,&iMin2,&iMin2);

            printf("The total time of the member stays in the sports center is %0.1f minutes.\n",fiCalMin(iHour1, iMin1, iHour2, iMin2));

        }else if(*cMemberName == 78 || *cMemberName == 110){
            i = i +1;

            //char cReason;
            printf("Enter the reason to come the sports center:\nEnter R or r for registering, C or c for cafe: ");
            scanf(" %c", &cMemberName);

            switch(*cMemberName){
                case 82://Register
                case 114:
                    printf("Enter the name: ");
                    scanf("%s",&cMemberName);
                    //cMemberName[0] = 0;
                    //fgetc(stdin); DAMN YOU GOTHAM PEOPLE
                    //fgets(cMemberName, _NAMESIZE, stdin);


                    printf("%s just came to register.\n",cMemberName);

                    break;



                case 67://Café
                case 99:
                    printf("Enter the name: ");
                    scanf("%s",&cMemberName);
                    //fgetc(stdin);
                    //fgets(cMemberName, _NAMESIZE, stdin);
                    printf("%s just came to cafe.\n", cMemberName);

                    break;

                default:
                    printf("\nPlease enter your choice correctly");

            }

        }else{
            printf("\n Please enter your choice correctly");

        }



    }




    return 0;
}



float fiCalMin(int _iHour1, int _iMin1, int _iHour2, int _iMin2){
    return (float)( (_iHour2*60 + _iMin2) - (_iHour1*60 + _iMin1) );
}








