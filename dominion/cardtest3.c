#include "dominion.h"
#include <stdio.h>

int result = 1;

int myassert(int element, char* msg){
	if(element == 0 ){
		printf("Failed Assert: %s\n", msg);
		result = 0;
	}
	return 0;
}

int main(){
	struct gameState G;
	struct gameState *p = &G;
	int k[10] ={smithy,village,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	printf ("Starting game.\n");
	initializeGame(2,k,3,p);
	p->hand[0][1] = village;
	playCard(1,0,0,0,p);
	myassert(p->handCount[0]==5,"+1 Cards function got bugs \n");
	myassert(p->numActions==2, "+1 action function got bugs \n");
	if(result == 1){
		printf("No functional bugs for village\n");
	}
	return 0;
}
