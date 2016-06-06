#include <stdio.h>
#include "dominion.h"

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
	initializeGame(2,k,2,p);
	/*first test*/
	int count = fullDeckCount(0,copper,p);
	result=myassert(count != 7, "Bug is here, no 7 copper after initialize \n");
	if (result == -1)
		return 0;
	/* second test */
	count = fullDeckCount(0,estate,p);
    result=myassert(count != 3, "Bug is here, no 3 estate after initialize \n");
	if (result == -1)
		return 0;
   	else if(result ==0)
	   printf("No bugs for fullDeckCount \n");
	return 0;
}	
