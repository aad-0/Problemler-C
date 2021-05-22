/*Rule 1 : There must not be any duplicate letters for the inputs that the user enter. If a
duplicate letter or space character is detected, all of the extra letters should be deleted until
only one of the letters remain. This condition of being ‘duplicate’ and/or ‘multiple’ is
constrained by some rules. The rule is applied over only consecutive character forms that are
right next to each other.
Example
Base Version: I wass waalkinng in thhee Ankarraa.
Fixed Version: I was walking in the Ankara.
You are expected to apply this rule inside a function. Function will have a void return type
and will accept the input string from the main as parameter. Your function will be called from
the main, fix the string and update it to it’s correct form by regarding to this rule.


Rule 2 : Eliminate unnecessary space characters, add space characters if you need to. The
spacing structure rule for the given paragraphs is given as;
1- Punctuation marks must not have any space between them and the word before them
(the word they belong to). Any punctuation must be the first character to come right
after a word is finished.
2- After every word with or punctuation mark, there must always be a single space
character before the next word starts. (There is no need to apply this at the end of the
input string). This means, if there are no space between a punctuation and the next
word’s first character, you must add a space character between the punctuation and the
beginning of the next word.
After applying rule 2, you will call the rule 2’s function from the main and perform the space
elimination, addition over the string or just stay neutral since there might be no need for fixing
spaces after the appliance of rule 1 over certain strings. The function should apply the rules
given.
Sample Paragraphs:
 Paragraph 1: Ppeaace is the resullt of retrraining yYyyour miiind to proccess
liife as it is ,ratheer than as you think it shhould be .
 Paragraph 2: ssSpaccce TttrRavel is life - enhancing,, AaaAnd anything that' s
life - enhanncing is woOorth doinnng….
Expected Output:
 Fixed Paragraph 1: Peace is the result of retraining your mind to proces life as it is,
rather than as you think it should be.
 Fixed Paragraph 2: space Travel is life- enhancing, and anything that's lifeenhancing is worth doing.
After the program ends, you will output the final version of the string. In between the
appliance of these rules, you will print the result of the applied rules as output. Sample runs
and important remarks are given in the documentation further below.
Important Remarks
 You can code your assignment with or without the help of the string.h and/or ctype.h
libraries functions. Algorithms are up to you as long as you can perform the necessary
string operations and build the correct coding structure as expected.
 You can define any variables of any type you need as long as the general program
structure is working as the given guidelines in your assignment document
*/

#include <stdlib.h>
#include <stdio.h>

#define _DEBUG 0
#define _STRSIZE 200

void vFixMultiple(char *pString, int *iLength);
void vFixSpace(char *pString, int *iLength);
int iFindLength(char *pString);


int main(void){

    char *String = (char*) malloc(_STRSIZE * sizeof(char));
    int iLength;

    //scanf("%[^\n]%*c",String);
    //scanf("%s",String);

    if(_DEBUG){
            /*Test Strings:
            : Ppeaace is the resullt of retrraining yYyyour miiind to proccess liife as it is ,ratheer than as you think it shhould be .
            ssSpaccce TttrRavel is life - enhancing,, AaaAnd anything that' s life - enhanncing is woOorth doinnng....
            ssSpaccce TttrRavel is life - enhancing,, AaaAnd anything that' s life - enhanncing-is woOorth doinnng....
            */
        char input[] = "ssSpaccce TttrRavel is life - enhancing,, AaaAnd anything that' s life - enhanncing-is woOorth doinnng....";

        for(int i = 0; i < sizeof(input)/sizeof(char); i++){ // a way to set input
            *(String+i) = input[i];

        }

    }else{
        printf("Enter a string: ");
        fgets(String, _STRSIZE, stdin); // get input via fgets so overflow can be controlled
    }


    if(_DEBUG){ // print String
        printf("String: %s\n",String);

    }

    iLength = iFindLength(String); // Get length



    vFixMultiple(String, &iLength);
    printf("Fixed duplicates:\n%s\n",String);


    vFixSpace(String, &iLength);
    printf("Fixed spaces:\n%s\n",String);

    printf("Final version of the String:\n%s\n",String);

    return 0;

}

int iFindLength(char *pString){
    int iLength=0;

    while(*(pString+iLength)!= NULL){//0 or '\0'

        if(_DEBUG){ // print All chars
            printf("\n%c",*(pString+iLength));
        }
        iLength = iLength +1;

    }
    if(_DEBUG){ // Print Length
        printf("\nLENGTH: %d\n",iLength);
    }

    return iLength;

}



void vFixMultiple(char *pString, int *iLength){
    /*
    Base Version: I wass waalkinng in thhee Ankarraa.
    Fixed Version: I was walking in the Ankara.
        buff AaSSddfg
        stri 00000000

    */

    char *buff = (char*) malloc(*iLength * sizeof(char)); /* Buff will be hold original pString,
    Then I will overwrite to pString
    So i will not have any buff in main*/

    // DEEP COPY to Buff and write 0 to string
    for(int i = 0; i< *iLength; i++){
        *(buff+i) = *(pString +i);
        *(pString +i) = 0;
    }

    *(pString +0) = *(buff +0); // Set the first char

    int y = 0;
    for(int i = 1; i<*iLength; i++){ // control the after char

        if(*(pString+ (y)) != *(buff +i) && !( *(pString +(y)) == *(buff+i) +32 || *(pString +(y)) == *(buff+i) -32 )){
                    y = y +1;
                    //printf("\here\n");
                    *(pString +y) = *(buff +i);
        }
    }

    pString = realloc(pString, *iLength * sizeof(char));

    //printf("SIZE OF STRING %d\n",y);

    *iLength = y +1;

}




void vFixSpace(char *pString, int *iLength){
    /*
        1- Punctuation marks must not have any space between them and the word before them
(the word they belong to). Any punctuation must be the first character to come right
after a word is finished.

    2- After every word with or punctuation mark, there must always be a single space
    character before the next word starts. (There is no need to apply this at the end of the
    input string). This means, if there are no space between a punctuation and the next
    word’s first character, you must add a space character between the punctuation and the
    beginning of the next word.


    Peace is the result of retraining your mind to proces life as it is ,rather than as you think it should be .
    1: Peace is the result of retraining your mind to proces life as it is,rather than as you think it should be.


    space Travel is life - enhancing, And anything that' s life - enhancing is worth doing.

    space Travel is life- enhancing, and anything that's life- enhancing is worth doing.

    buff AaSSddfg
    stri 00000000

    */

    char * buff = (char*) malloc((*iLength) * sizeof(char));

    // DEEP COPY to Buff and write 0 to string

    for(int i = 0; i< *iLength; i++){
        *(buff+i) = *(pString +i);
        *(pString +i) = 0;
    }

    /*
    This    ,   is,   a  ,sample

    Fixed dupp -> This , is, a ,sample
    Fixed space-> This, is, a, sampie

    case */



    /*
    space Travel is life - enhancing, And anything that' s life -enhancing-is worth doing..
    spaceTravel


    1- Punctuation marks must not have any space between them and the word before them
(the word they belong to). Any punctuation must be the first character to come right
after a word is finished.

    2- After every word with or punctuation mark, there must always be a single space
character before the next word starts. (There is no need to apply this at the end of the
input string). This means, if there are no space between a punctuation and the next
word’s first character, you must add a space character between the punctuation and the
beginning of the next word.


    A B C D - E, F G H' I - J-K L M.
    A B C D - E, F G H' I - J-K L M.

    A B C D- E, F G H' I- J- K L M.
    A B C D-
    */

    int i = 0, y = 0;
    while(i < *iLength){

        if( ((65 <= *(buff +i) && *(buff +i) <= 90) || (97 <= *(buff +i) && *(buff +i) <= 122) ) ){
            *(pString +y) = *(buff +i);
            y = y +1;

        }else{

            if( *(buff +i) != 32){

                if( *(pString +(y-1)) != 32){
                    *(pString +y) = *(buff +i);
                    *(pString +(y+1)) = 32;
                    y = y +2;

                }else{
                    *(pString +(y-1)) = *(buff +i);
                    *(pString + y) = 32;
                    y = y +1;
                }

            }else{
                *(pString +y) = 32;
                y = y+1;

            }

        }

        i = i +1;

    }

    *iLength = iFindLength(pString);
    vFixMultiple(pString, iLength);

}






