#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Student_s{
	char *num;
	char *name;
	char *program;
	char *sinif;
	char *mail;
	char *status;
};



typedef struct Student_s Student;


#define DEBUG 0
#define BUFFSIZE 1024 // 2 ^ X
#define MAPSIZE 64

Student *DB1[MAPSIZE] = {NULL};
Student *DB2[MAPSIZE] = {NULL};
Student *RET[MAPSIZE] = {NULL}; // return DB
void faultyInput(){
	  fprintf(stderr,
                "\nInputs are not good");
    exit(-1);

}




// will reworked
void readFile (Student **DB, char *namefile);
void writeFile(Student **DB, char *namefile);


void Union();
void Inter();


// should fine
void fillStudent(Student *dest, char *pnum, char *pname, char *pprogam,
            char *psinif,char *pmail,char *pstatus);

void printStudent(Student *dest);


int weightofStudent(Student *S1, Student *S2, int *flagName, int *flagSurname, int *flagMail); //in test

void sortDB(Student **DB);

int StudentCheck(Student *s1, Student *s2);

void printDB(Student **DB);



int main(int argc,char **argv){
    if(argc != 5 && !DEBUG){
	faultyInput();
    }
    char *program ,*inputF1, *inputF2, *outputF1, *op;
    // > hw.exe course1.txt course2.txt course_1_2_intersect.txt -i

    if(!DEBUG){
    //char *program ,*inputF1, *inputF2, *outputF1, *op;
    program = *argv;++argv;
    inputF1 = *argv;++argv;
    inputF2 = *argv;++argv;
    outputF1 = *argv;++argv;
    op = *argv;//++argv;
    printf("\n %s\n %s\n %s\n %s\n %c", program, inputF1, inputF2, outputF1, *(op+1));
    }	
    
   	if(*(op+1) == 'i'){
   		readFile(DB1, inputF1);
   		readFile(DB2, inputF2);
   		//sortDB(DB1);
   		//sortDB(DB2);
   		Inter();
   		sortDB(RET);
   		writeFile(RET,outputF1);
   		exit(0);
   	}else if(*(op +1) == 'u'){
		readFile(DB1, inputF1);
   		readFile(DB2, inputF2);
   		//sortDB(DB1);
   		//sortDB(DB2);
   		Union();
   		sortDB(RET);
   		writeFile(RET,outputF1);
   		exit(0);
   	} 

	faultyInput();

	//
	
	return 0;
}

int checkMultiple(Student **DB, Student *S){
	int i;//return 0 if not found

		// retruns true if they are same ->StudentCheck
	for(i = 0; DB[i] != NULL; ++i){
		if(StudentCheck(S, DB[i])){
			return 1;
		}

	}
	return 0;

}

void Union(){
	int i,k = 0;

	for(int i = 0; DB1[i] != NULL; ++i){
		if(!checkMultiple(RET, DB1[i])){
			RET[k] = DB1[i];
			++k;
		}
	}

	for(i = 0; DB2[i] != NULL; ++i){
		if(!checkMultiple(RET,DB2[i])){
			RET[k] = DB2[i];
			++k;
		}

	}

}

void Inter(){
	int i,j, k = 0;

	for(i = 0; DB1[i] != NULL; ++i){
		for(j = 0;  DB2[j] != NULL;  ++j){
					// retruns true if they are same ->StudentCheck
			//return 0 if not found check multiple
			if(StudentCheck(DB1[i],DB2[j])){
				if(!checkMultiple(RET,DB1[i])){
					RET[k] = DB1[i];
					++k;
				}

			}

		}

	}


}


int StudentCheck(Student *s1, Student *s2){
	if(s1 == NULL || s2 == NULL){
		return -1;
	}
	// retruns true if they are same
	return !strcmp(s1->num, s2->num);
}



int _strcmp(char *str1, char *str2){
	// 0 equal
	// 1 str1 small
	// 2 str2 small
	int ret = 0;
	while(*str1 != '\x00' && *str2 != '\x00'){
		if(*str1 == *str2){
		
		}
		else if(*str1 < *str2){
			ret =  1;
			break;
		}else if(*str1 > *str2){
			ret =  2;
			break;
		}
		++str1;
		++str2;
	}
	if(strlen(str1) > strlen(str2) && ret == 0){
		ret = 2;
	}else if(strlen(str1) < strlen(str2) && ret == 0){
		ret = 1;
	}

	return ret;
}

// works // need for sorting output
int weightofStudent(Student *S1, Student *S2, int *flagName, int *flagSurname, int *flagMail){ //in test ///TODO get another parameter for mail weight


	char *pSname1 = NULL;
	char *pName1 = NULL;
	char *pSname2 = NULL;
	char *pName2 = NULL;

	pName1 = S1->name;
	pName2 = S2->name;

	while(*pName1 != '\x00'){
		++pName1; // will have null at the and
	}
	--pName1;

	while(*pName1 != ' '){
		--pName1;
	}
	pSname1 = pName1+1;

	char *_pName1 = pName1;
	*pName1 = '\x00';
	
	while(*pName2 != '\x00'){
		++pName2; // will have null at the and
	}--pName1;
	while(*pName2 != ' '){
		--pName2;

	}
	char *_pName2 = pName2;
	*pName2 = '\x00';
	pSname2 = pName2+1;

	pName1 = S1->name;
	pName2 = S2->name;


	*flagName = _strcmp(pName1, pName2);
	*flagSurname = _strcmp(pSname1, pSname2);
	*flagMail = _strcmp(S1->mail, S2->mail);

	*_pName1 = ' ';
	*_pName2 = ' ';

	return 0;
}


void sortDB(Student **DB){
	// check the suranems
	// then firstnames
	// if bothsame, check mail
	char *name,  *surname;
	Student *swap;

	int i, j, flagName = 0, flagSurname = 0, flagMail = 0;
	// 0 equal // dont know how that works, just works, do not change
	// 1 j small
	// 2 i small
	for(i = 0; DB[i] != NULL; ++i){
		flagSurname = flagName = flagMail = 0;
		for(j = 0; DB[j] != NULL; ++j){
			if(StudentCheck(DB[i],DB[j])){
				continue;
			}

			weightofStudent(DB[i],DB[j], &flagName, &flagSurname, &flagMail);
			if(flagSurname == 0){
				// same name
				if(flagName == 0){
					if(flagMail == 1){
						swap = DB[i];
						DB[i] = DB[j];
						DB[j] = swap;						
					}
				} if(flagName == 1){
					swap = DB[i];
					DB[i] = DB[j];
					DB[j] = swap;
				}
			} if(flagSurname == 1){
				swap = DB[i];
				DB[i] = DB[j];
				DB[j] = swap;
			}

		}


	}


}



//works1
void fillStudent(Student *dest, char *pnum, char *pname, char *pprogram,
            char *psinif,char *pmail,char *pstatus){ // works
/*

    char *num;
	char *name;
	char *program;
	char *sinif;
	char *mail;
	char *status;
*/

    if(dest == NULL){
        dest = (Student *) malloc(sizeof(Student));
    }
    dest->num = (char *) malloc(sizeof(char) * BUFFSIZE);
    dest->name = (char *) malloc(sizeof(char) * BUFFSIZE);
    dest->program = (char *) malloc(sizeof(char) * BUFFSIZE);
    dest->sinif = (char *) malloc(sizeof(char) * BUFFSIZE);
    dest->mail = (char *) malloc(sizeof(char) * BUFFSIZE);
    dest->status = (char *) malloc(sizeof(char) *2);

    char *_new ,*_pname = pname;
    _new = (char *) malloc(sizeof(char ) * BUFFSIZE);
    int i = 0;
    while(*(_pname+1) != '\0'){
    	if(*(_pname) == 32 && *(_pname+1) == 32 ){
    		// '..'
    	}else{
    		*(_new +i) = *_pname;
    		++i;
    	}
    	++_pname;

    }
    *(_new +i) = *(_pname);


    strncpy(dest->num, pnum, BUFFSIZE);
    strncpy(dest->name, _new, BUFFSIZE);
    strncpy(dest->program, pprogram, BUFFSIZE);
    strncpy(dest->sinif, psinif, BUFFSIZE);
    strncpy(dest->mail, pmail, BUFFSIZE);
    *dest->status = *pstatus;
    *(dest->status +1) = '\x00';

}



// works
void readFile(Student **DB, char *namefile){ // not testet, should work,  working
    FILE *Fi;
    Fi = fopen(namefile, "r");
    if(Fi == NULL){
            faultyInput();
	}

    char
    *num  = (char *)malloc(sizeof(char) * BUFFSIZE),
    *name = (char *)malloc(sizeof(char) * BUFFSIZE),
    *program = (char *)malloc(sizeof(char) * BUFFSIZE),
    *sinif = (char *)malloc(sizeof(char) * BUFFSIZE),
    *mail = (char *)malloc(sizeof(char) * BUFFSIZE),
    *status = (char *)malloc(sizeof(char) *2);
	
	int flag, indx = 0;//, key;
	flag = fscanf(Fi,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",num,name, program, sinif, mail,status);
	//printf("%s %s %s %s %s %s", num, name, program, sinif, mail, status);
	//printf("\ninitflag %d", flag);
	while(!feof(Fi)){
        //clear status;
        *status = '\x00';// \x00
        flag = fscanf(Fi,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^\n]",num,name, program, sinif, mail,status);
        if(flag >= 5){
			Student *newS = (Student *)malloc(sizeof(Student));
			/*
void fillStudent(Student *dest, char *pnum, char *pname, char *pprogam,
			 *
			 * */
			fillStudent(newS, num, name,program,sinif,mail,status);
			DB[indx] = newS;
			++indx; 
			//mapAdd(DB,newS);	
            // correct input
            // it runs n+1, because of last line, fscanf returns 1
        }


	}
	fclose(Fi);

}

void writeFile(Student **DB, char *namefile){ // in test
   /*
struct Student_s{
	char *num;
	char *name;
	char *program;
	char *sinif;
	char *mail;
	char *status;
};
	*
	* */ 
	FILE *Fo;
    Fo = fopen(namefile, "w");
    fprintf(stdout, "\nFILE, TRY OPEN file:%s", namefile); 
	
	if(Fo == NULL){
            fprintf(stderr,
                "\nFILE, could not managed to open! file:%s",namefile);
            faultyInput();
	}
    fprintf(stdout ,"\nFILE, OPENED %s", namefile);
    

	char *pSname = NULL;
	char *pName = NULL;
	// i: Surname, Name, programe, year, mail
	int i, j = 1;



	for(i = 0; DB[i] != NULL; ++i){
		pName = DB[i]->name;
		while(*pName != '\x00'){
			++pName; // will have null at the and
		}
	--pName;	
	while(*pName != ' '){
		--pName;
	}
	*pName = '\x00';
	pSname =++pName;
	pName =  DB[i]->name;
	
			fprintf(Fo,//stdout, // Fo
			"%d: %s, %s, %s, %s, %s\n", j++, pSname, pName,
			DB[i]->program, DB[i]->sinif, DB[i]->mail);
		
	}
	fclose(Fo);
}



// works
void printStudent(Student *dest){
    printf("\n\nPrinting Student %X:",dest);
    printf("\nnum:%s", dest->num);
    printf("\nname:%s", dest->name);
    printf("\nprogram:%s", dest->program);
    printf("\nsinif:%s",dest->sinif);
    printf("\nmail:%s", dest->mail);
    printf("\nstatus:%s", dest->status);

}



// works
void printDB(Student **DB){
	int i;
	for(i = 0; i < MAPSIZE; ++i){
		if(DB[i] != NULL) printStudent(DB[i]);
	}

} 








