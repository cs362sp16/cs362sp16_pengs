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
	int i, j, numofplayer, initreasure, handtreasure , player, card, handnum, decknum, discardnum;
	time_t t;
	if (argc < 2){
		printf("Error,you forget input the seed \n");
		exit(0);
	}

	int k[10] ={smithy,adventurer,gardens,embargo,cutpurse,mine,ambassador,outpost,baron,tribute};
	srand((unsigned) time(&t));
	numofplayer = rand()%2+2;		//make sure there is at least 2 player
	for(i=0 ; i< MAX_TEST; i++){
		//initializeGame
		initreasure = 0;
 		handtreasure= 0;
		initializeGame(numofplayer,k,atoi(argv[1]),g);
		player = g->whoseTurn;
		//set up the random value
		handnum = rand()%10;
		g->handCount[player] = handnum;
		decknum = rand()%20+5;
		g->deckCount[player] = decknum;
		discardnum = rand()%10;
		g->discardCount[player] = discardnum;

		for(j=0;j<handnum;j++){
			card = rand()%15;
			//know how many treasure card we have
			if(card == copper || card == silver || card == gold){
				initreasure++;
				}	
				g->hand[player][j] = card;
		}
		for(j=0;j<decknum;j++){
			card = rand()%15;
			g->deck[player][j] = card;
		}
		for(j=0;j<discardnum;j++){
			card = rand()%15;
			g->discard[player][j] = card;
		}
		g->discard[player][0] = gold;
		g->discard[player][1] = silver;
		//put the adventure card to hand
		g->hand[player][0] = adventurer;
		//Use this card
		playCard(0,0,0,0,g);
		for(j = 0; j< handnum; j++){
			// how many treasure card in hand
			if(g->hand[player][j] == copper || g->hand[player][j] == silver || g->hand[player][j] == gold){
				handtreasure++;
				}
		}
		//check the error
		myassert(handtreasure = (initreasure+2), "Adventure get bugs, it's not work! \n ");
	   	myassert(g->handCount[player] == (handnum +1), "Hand card number is not right! \n ");
		myassert(g->playedCardCount == 1, "We didn't play this card out! \n ");
		if(result == 1){
			printf("There is no bugs for smithy \n");
		}
	}
	return 0;	
}
