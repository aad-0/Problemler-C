#include <stdio.h>
#include <stdlib.h>
//#define DOLAR 7.73
/*TODO
1 dolar = 7,72 Türk

int char float5.0 double 5.0

/TODO*/


double dolar_to_tl(double fUnitDolar_respect_to_Tl, double Tl);
void take_input(char *cMsg,double *addr);


int main(void){
    double dAnswer; // take address of it
    double ret_of;

    printf("Adress of ret_of %d \n",&ret_of);
    take_input("Please enter amount dolar: \n",&ret_of);
    printf("ret-of %f \n", ret_of);
    dAnswer = dolar_to_tl(7.72,ret_of);
    printf("Printing Tl ");
    printf("%f", dAnswer);
    return 0;
}


double dolar_to_tl(double fUnitDolar_respect_to_Tl, double Tl){
    return fUnitDolar_respect_to_Tl * Tl;
}
void take_input(char *cMsg,double *addr){ // Error returns, so I will send it to main via address
    printf(cMsg);
    printf("In Func \n");
    printf("Adress of -addr %d \n" ,addr);
    printf("Value in address %f \n", *addr);
    scanf("%lf",addr);



}
