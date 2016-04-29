#include "dominion.h"
#include <stdio.h>
int myassert(int element, char* msg){
	if(element == 1 ){
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
	int score1 = scoreFor (0,p);
	printf ("The score is %d \n",score1);
	result = myassert( score1 !=3, "Bug is here, player 0 should have 3 score \n");
	if (result == -1)
		return 0;
	/*second test*/	
	int score2 = scoreFor (1,p);
	printf ("The score is %d \n",score2);
	result = myassert( score2 !=3, "Bug is here, player 1 should have 3 score \n");
	if (result == -1)
		return 0;
	else if (result == 0)
		printf("No bugs for scoreFor");
	return 0;
}



