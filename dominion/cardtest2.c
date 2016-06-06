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
	int k[10] ={smithy,council_room,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	initializeGame(2,k,3,p);
	p->hand[0][1] = council_room;
	playCard(1,0,0,0,p);
	myassert(p->handCount[0]==8,"+4 Cards function got bugs \n");
	myassert(p->numBuys ==2, "+1 buy function got bugs \n");
	myassert(p->handCount[1]=6,"each other plyaer draw function got bugs \n");
	if(result == 1){
		printf("No functional bugs for council_room \n");
	}
	return 0;
}	
