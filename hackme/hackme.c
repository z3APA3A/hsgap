#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



void InitRnd(){
	srand((getpid() << 16) + time(0));
}

void GenPass(char * cpPassword, int len){
	int i;
	for(i=0; i<len - 1; i++) cpPassword[i] = 33 + (rand()%95);
	cpPassword[i] = 0;
}

int main() {
	int i, iYear, len;
	char cpBuf[20], cpPassword[]="1234567890", cpYear[]="1900";

 	InitRnd();

	for(i=0; i < 3; i++){
		GenPass(cpPassword, sizeof(cpPassword));
		printf(
			"\n"
			"+-----------------------+\n"
			"| Warning: adults only! |\n"
			"+-----------------------+\n"
			"\n"
			"Enter you birth year: "
		);
		if(!fgets(cpBuf, sizeof(cpBuf), stdin)) continue;
		if(!(iYear = atoi(cpBuf))) continue;
		if(iYear < 1000) iYear += 1900;
		if(iYear >= 2000) {
			printf("You are a scholar, don't try to fool me\n", iYear);
			return iYear;
		}
		sprintf(cpYear, "%d", iYear);
		printf("OK, dude, born in %s, enter the password: \n", cpYear);
		memset(cpBuf, 0, sizeof(cpBuf));
		if(!fgets(cpBuf, sizeof(cpBuf), stdin)) continue;
		if((len = strlen(cpBuf))>0 && cpBuf[len - 1] == '\n')
			cpBuf[len - 1] = 0;
		if (strcmp(cpBuf, cpPassword)){
			printf(
			 "Nope, dude, your password is '%s', mine is '%s'.\n"
			 "I will generate new one.\n",
			 cpBuf, cpPassword
			);
			continue;
		}
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
		printf("Game over, baby. Bye-bye\n");
		return i;
	}

	system("cmd /K pause");
	return 0;
}
