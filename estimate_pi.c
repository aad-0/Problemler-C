#include <stdio.h>
#include <math.h>
#include <time.h>

float FindPi(int iDotAll);
float RandomUniform(void);

int main(){
    //printf("%f",RandomUniform());
    float Pi_but = FindPi(1000);
    printf("\n4*DotIn/DotAll: %f",Pi_but);

    return 0;
}

float RandomUniform(void){
    return (double)rand() / (double)((unsigned)TMP_MAX + 1);
}

float FindPi(int iDotAll){
    int iDotIn = 0;
    int iCPoint = 0;

    srand(time(NULL));
    while(iCPoint<=iDotAll){
        iCPoint++;

        float x = RandomUniform();
        float y = RandomUniform();

        //printf("x^2+y^2= \f\n",pow(x,2)+pow(y,2));
        //printf("FLOAT %f\n",pow(x,2) + (pow(y,2)));
        if(pow(x,2)+pow(y,2)<=1){
            //if(RandomUniform()<=1){
            //printf("x:%f, y:%f\n",x,y);
            iDotIn++;
        }
    }

    printf("Dotin: %d\nDotAll: %d",iDotIn,iDotAll);
    return (float)4*iDotIn/iDotAll;;
}
