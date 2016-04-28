#include <stdio.h>
#include "dominion.h"

int myassert(int element, char* msg){
	if(element !=5){
		printf("Failed Assert: %s\n", msg);
		return -1;
	}
	return 0;
}

int main(){
	struct gameState G;
	struct gameState *p =&G;
	int result=0;
	int k[10] ={smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	printf ("Starting game.\n");

	initializeGame(2,k,2,p);
	int numberofcard = numHandCards(p);
	result = myassert(numberofcard,"numHandCards has bugs ;( \n");
	if (result == 0){
		printf("No bugs here for numHandCards ;)\n");
	}	
	return 0;
}
