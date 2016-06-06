#include <stdio.h>
#include "dominion.h"

int myassert(int element, char* msg){
	if(element == 1 ){
		printf("Failed: %s\n", msg);
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
	int supply = supplyCount(smithy,p);
	result= myassert( supply != 10, "The supply of smithy is not 10, bug!\n");
	if (result == -1)
		return 0;
	
	/*second test*/
	supply = supplyCount(province,p);
	result= myassert( supply !=8, " The supply of province is not 8, bug!\n");
	if (result == -1)
		return 0;
	else if(result == 0)
		printf("No bugs for supplyCount \n");
	return 0;
}	
