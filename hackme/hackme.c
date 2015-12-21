#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <process.h>


/*
	Seeds PRNG with some data
*/
void InitRnd(){
	srand((getpid() << 16) + time(0));
}

/*
	Generates password with rand()
*/
void GenPass(char * cpPassword, int len){
	int i;
	for(i=0; i<len - 1; i++) cpPassword[i] = 33 + (rand()%95);
	cpPassword[i] = 0;
}


struct user {
	char cpYear[5] ;
	char cpPassword[11];
} u = {"1900", "1234567890"};

int main() {
	int i, iYear, len;
	char cpBuf[20];

 	InitRnd();   /* Init PRNG */

	for(i=0; i < 3; i++){   /* Give 'im 3 attemps */
		/* generate new password for each */
		GenPass(u.cpPassword, sizeof(u.cpPassword)); 

		/* get year of birth */
		printf(
			"\n"
			"+-----------------------+\n"
			"| Warning: adults only! |\n"
			"+-----------------------+\n"
			"\n"
			"Enter your birth year: "
		);
		if(!fgets(cpBuf, sizeof(cpBuf), stdin)) continue;
		if(!(iYear = atoi(cpBuf))) continue;

		/* add 1900 for 2-digit years */
		if(iYear < 1000) iYear += 1900;

		/* check he is not scholar */
		if(iYear >= 2000) {
			printf("You are a scholar, don't try to fool me\n");
			return iYear;
		}

		/* convert year to string */
		sprintf(u.cpYear, "%d", iYear);

		/* ask for password */
		printf("OK, dude, born in %s, enter the password: \n", u.cpYear);

		/* zero cpBuf and read new password to it */
		memset(cpBuf, 0, sizeof(cpBuf));
		if(!fgets(cpBuf, sizeof(cpBuf), stdin)) continue;

		/* remove trailing \n */
		if((len = strlen(cpBuf))>0 && cpBuf[len - 1] == '\n')
			cpBuf[len - 1] = 0;

		/* compare passwords */
		if (strcmp(cpBuf, u.cpPassword)){
			/* wrong password */
			printf(
			 "Nope, dude, your password is '%s', mine is '%s'.\n"
			 "I will generate new one.\n",
			 cpBuf, u.cpPassword
			);
			continue;
		}

		/* password was OK */
		printf(
			"\n"
			"+-------------------------------+\n"
			"| Yeeeeeeh! you did it. Come in |\n"
			"+-------------------------------+\n"
			"\n"
		);
		break;
	}

	if(i == 3) {
		/* loooo0o00o0ser, he had 3 failed attempts */
		printf("Game over, baby. Bye-bye\n");
		return i;
	}

	/* he wins */
	system("cmd /K pause");
	return 0;
}
