#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dominion.h"

char* get_name(int card){
    char* name = malloc(sizeof(char)*20);
    if(card == curse)
        strcpy(name, "curse");
    else if(card == estate)
        strcpy(name, "estate");
    else if(card == duchy)
        strcpy(name, "duchy");
    else if(card == province)
        strcpy(name, "province");
    else if(card == copper)
        strcpy(name, "copper");
    else if(card == silver)
        strcpy(name, "silver");
    else if(card == gold)
        strcpy(name, "gold");
    else if(card == adventurer)
        strcpy(name, "adventurer");
    else if(card == council_room)
        strcpy(name, "council_room");
    else if(card == feast)
        strcpy(name, "feast");
    else if(card == gardens)
        strcpy(name, "gardens");
    else if(card == mine)
        strcpy(name, "mine");
    else if(card == remodel)
        strcpy(name, "remodel");
    else if(card == smithy)
        strcpy(name, "smithy");
    else if(card == village)
        strcpy(name, "village");
    else if(card == baron)
        strcpy(name, "baron");
    else if(card == great_hall)
        strcpy(name, "great_hall");
    else if(card == minion)
        strcpy(name, "minion");
    else if(card == steward)
        strcpy(name, "steward");
    else if(card == tribute)
        strcpy(name, "tribute");
    else if(card == ambassador)
        strcpy(name, "ambassador");
    else if(card == cutpurse)
        strcpy(name, "cutpurse");
    else if(card == embargo)
        strcpy(name, "embargo");
    else if(card == outpost)
        strcpy(name, "outpost");
    else if(card == salvager)
        strcpy(name, "salvager");
    else if(card == sea_hag)
        strcpy(name, "sea_hag");
    else if(card == treasure_map)
        strcpy(name, "treasure_map");
    else
        strcpy(name, "OUT OF RANGE");

    return name;
}

void play(int handLoc, struct gameState* p){
	//define the action of each card
    int card = handCard(handLoc, p);
    char* name = get_name(card);
    printf("Play action -------> who(%d) plays: %s\n", p->whoseTurn, name);

    if(card == adventurer || card == council_room || card == gardens || card == smithy ||
		card == village || card == great_hall || card == tribute ||	card == cutpurse ||
		card == outpost ||card == sea_hag ||card == treasure_map
		)
        playCard(handLoc, -1, -1, -1, p);
    else if(card == feast)
        playCard(handLoc, 0, -1, -1, p);
    else if(card == mine)
        playCard(handLoc, copper, silver, -1, p);
    else if(card == remodel)
        playCard(handLoc, copper, estate, -1, p);
    else if(card == baron)
        playCard(handLoc, 0, -1, -1, p);
    else if(card == minion)
        playCard(handLoc, 1, -1, -1, p);
    else if(card == steward)
        playCard(handLoc, 2, -1, -1, p);
    else if(card == ambassador)
        playCard(handLoc, 0, 0, -1, p);
    else if(card == embargo)
        playCard(handLoc, 0, -1, -1, p);
    else if(card == salvager)
        playCard(handLoc, 0, -1, -1, p);
}


int bought(int deck[10], struct gameState* p, int card){
	//each card only bought once
    int i;
    for(i = 0; i < 10; i++){
        if(card == deck[i]){
			//set as null card, never buy it
            deck[i] = -2;
            return 1;
        }
    }
    return 0;
}

int played(int hand[10], struct gameState* p, int card){
	//each card only played once
    int i;
    for(i = 0; i < 10; i++){
        if(card == hand[i]){
			//set as null card, never played it
            hand[i] = -2;
            return 1;
        }
    }
    return 0;
}

void mybuycard(struct gameState* p,int deck[10], int k[10]){
	int money = 0, i;
	//calucate the total money
	for(i = 0; i < numHandCards(p); i++){
		if(handCard(i,p) == copper){
			playCard(i, -1, -1, -1, p);
			money++;
		}    
		if(handCard(i,p) == silver){
			playCard(i, -1, -1, -1, p);
			money += 2;
		}
		if(handCard(i,p) == gold){
			playCard(i, -1, -1, -1, p);
			money += 3;
		}
	}
	//buy stuff	
	if(money > 7){
		buyCard(province, p);
		printf("Player%d Bought province \n", p->whoseTurn);
	}
	else if(money > 5){
		for(i = 0; i < 10; i++){
			if(bought(deck, p, k[i])){
				buyCard(k[i], p);
				printf("Player%d Bought %s\n", p->whoseTurn, get_name(k[i]));
				break;
			}
		}
	}
	else if(money > 5){
		buyCard(gold, p);
		printf("Player%d Bought gold\n", p->whoseTurn);
	}
	else if(money > 2){
		buyCard(silver, p);
		printf("Player%d Bought silver\n", p->whoseTurn);
	}
	else{
		buyCard(copper, p);
		printf("Player%d Bought copper\n", p->whoseTurn);
	}
}

void print_state(struct gameState* p, int players){
    int i, winner[players];
    getWinners(winner, p);
    printf("\nThe result is:\n");
    for(i = 0; i < players; i++){
        printf("Player%d:\n", i);
        if(winner[i])
            printf("WINNER!\n");
        printf("Score: %d\n", scoreFor(i, p));
		printf("\n");
    }
}

void randomdeck(int k[10]){
	//random generate deck card
	int i, j, exist, temp;
	for(i=0; i<10 ; i++){
		temp = (rand() % 20) +7;
		exist = 1;
		for(j=0; j<10; j++){
			if(k[j] == temp){
				exist = 0;
			}
		}
		if(exist){
			k[i] = temp;
		}
		else
			i--;
	}
}	

int main(int argc, char** argv){
	int did, k[10], i, j, seed, players, money, action, buy;
	time_t t;
	struct gameState g;
	struct gameState *p = &g;
	if(argc>2){
		printf("Error, You must input 2 argument for this system \n");
		return 0;
	}
	else{
		seed = atoi(argv[1]);
	}
	srand(seed);
	randomdeck(k);

	//copy kingdom card to different playce for avoid dulipce buy or play
	int deck[10],discard[10];
	for(i=0; i<10; i++){
		deck[i] = k[i];
		discard[i] = k[i];
	}
	//initializegame
	players = (rand()%3) + 2;
	initializeGame(players, k , seed, p);	

	//start game
	while(!isGameOver(p)){
		for(i=0 ; i<players; i++){
			action = 1;
			buy = 1;
			money = 0;
			while(action){
				did = -1;
				for(j=0 ; j<numHandCards(p); j++){
					if(played(discard,p,handCard(j,p))){
						did = j;
						break;
					}
				}
				if(did > -1){
					play(did,p);
					action = 0;
				}
				else
					action = 0;
			}
			mybuycard(p,deck,k);
			endTurn(p);
		}
			printf("\n");
	}
	print_state(p, players);
	return 0;
}	

