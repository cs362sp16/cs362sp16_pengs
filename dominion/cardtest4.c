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
	p->numActions = 2;
	p->hand[0][1] = baron;
	p->hand[0][2] = baron;
	p->hand[0][3] = estate;
	int recoin = p->coins;
	playCard(1,0,0,0,p);    //Don't discard an estate
	myassert(p->hand[0][1]!=baron,"Bargon got bugs, Can't trash it from hand\n");
	myassert(p->numBuys==2,"+1 buy function got bugs \n");
	playCard(2,1,0,0,p);	//Discard an estate
	myassert(p->coins==recoin+4, "+4 coins function got bugs \n");
	myassert(p->numBuys==3,"+1 buy function got bugs \n");
	if(result == 1){
		printf("No functional bugs for village\n");
	}
	return 0;
}
