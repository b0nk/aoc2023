#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_CARDS 50
#define MAX_DECKS 250


typedef struct{
	int winning[MAX_CARDS];
	int hand[MAX_CARDS];
	int winning_count;
	int hand_count;
	int wins;
} Card;

Card* create_card(){
	Card* c = (Card*) malloc(sizeof(Card));
	c->winning_count = 0;
	c->hand_count = 0;
	c->wins = 0;
	return c;
}

void fill_card(Card* c, char* line){
	char* full_game_ptr;
	char* line_ptr;

	strtok_r(line, ":", &line_ptr);
	char* full_game = strtok_r(NULL, ":", &line_ptr);

	char* winning_str = strtok_r(full_game, "|", &full_game_ptr);
	char* hand_str = strtok_r(NULL, "|", &full_game_ptr);

	char* winning_ptr;
	char* winning_token = strtok_r(winning_str, " ", &winning_ptr);
	while(winning_token != NULL){
		int value;
		sscanf(winning_token, "%d", &value);
		c->winning[c->winning_count] = value;
		c->winning_count += 1;
		winning_token = strtok_r(NULL, " ", &winning_ptr);
	}

	char* hand_ptr;
	char* hand_token = strtok_r(hand_str, " ", &hand_ptr);
	while(hand_token != NULL){
		int value;
		sscanf(hand_token, "%d", &value);
		c->hand[c->hand_count] = value;
		c->hand_count += 1;
		hand_token = strtok_r(NULL, " ", &hand_ptr);
	}
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	Card** cards;
	int card_counter = 0;
	double sum1, sum2 = 0;

	cards = malloc(sizeof(*cards) * MAX_DECKS);
	for(int i = 0; i < MAX_DECKS; i++){
		cards[i] = malloc(sizeof(**cards) * MAX_DECKS);
	}

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		cards[card_counter] = create_card();
		fill_card(cards[card_counter], line);
		card_counter++;
	}

	for(int i = 0; i < card_counter; i++){
		for(int j = 0; j < cards[i]->winning_count; j++){
			for(int k = 0; k < cards[i]->hand_count; k++){
				if(cards[i]->winning[j] == cards[i]->hand[k]){
					cards[i]->wins += 1;
				}
			}
		}
		if(cards[i]->wins > 0){
			sum1 += (int)pow(2, cards[i]->wins - 1);
		}
	}

	printf("part1: %d\n", (int)sum1);
	printf("part2: %d\n", (int)sum2);

	return 0;
}
