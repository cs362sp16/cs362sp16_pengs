#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int result = 1;
int MAX_TEST = 2000;
int myassert(int element, char* msg){
	if(element == 0 ){
		printf("Failed Assert: %s\n", msg);
		result = 0;
	}
	return 0;
}

int main(int argc, char* argv[]){
	struct gameState G;
	struct gameState *g = &G;
	int i, j, numofplayer, player, card, handnum, decknum, buytime;
	time_t t;
	if (argc < 2){
		printf("Error,you forget input the seed \n");
		exit(0);
	}

	int k[10] ={smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	srand((unsigned)time(&t));
	numofplayer = rand()%2+2;		// at least 2 player is here
	for(i=0 ; i< MAX_TEST; i++){
		//initializeGame
		initializeGame(numofplayer,k,atoi(argv[1]),g);
		player = g->whoseTurn;
		buytime = g->numBuys;
		handnum = rand()%10;
		g->handCount[player] = handnum;
		decknum = rand()%20+5;		// at least 5 card in deck
		g->deckCount[player] = decknum;
		for(j=0;j<handnum;j++){
			card = rand()%15;
			g->hand[player][j] = card;
		}
		for(j=0;j<decknum;j++){
			card = rand()%15;
			g->deck[player][j] = card;
		}
		g->hand[player][0] = council_room;		//put card in hand
		playCard(0,0,0,0,g);					//use this card
		//check the error
		myassert(g->handCount[player] == (handnum +3), "Error Hand count! \n");
		myassert(g->deckCount[player] == (decknum -4), "Error Deck count! \n");
		myassert(g->numBuys == (buytime +1), "Error Buy num! \n");
		if(result == 1){
			printf("There is no bugs for smithy \n");
		}
	}
	return 0;
}
