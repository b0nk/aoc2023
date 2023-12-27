#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_INCREASE 10
#define DECK "23456789TJQKA"

typedef struct{
	int bid;
	int score;
	char* cards;
}Hand;

int get_deck_score(char c){
	int deck_size = strlen(DECK);
	for(int i = 0; i < deck_size; i++){
		if(DECK[i] == c){
			return i + 1;
		}
	}
}

void score_hand(Hand* h){
	int n = strlen(h->cards);

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (h->cards[i] > h->cards[j]) {
				char temp = h->cards[i];
				h->cards[i] = h->cards[j];
				h->cards[j] = temp;
			}
		}
	}

	int reps = 0;

	for(int i = 0; i < n; i++){
		for(int j = i + 1; j < n; j++){
			if(h->cards[i] == h->cards[j]){
				reps++;
			}
		}
		if(reps > 0){
			printf("card '%c', score: '%d', reps: '%d'\n", h->cards[i], get_deck_score(h->cards[i]), reps);
			h->score += get_deck_score(h->cards[i]) * reps;
		}
		i += reps;
		reps = 0;
	}
}

void rank_hands(Hand** hands, int size){
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (hands[i]->score > hands[j]->score) {
				Hand* temp = hands[i];
				hands[i] = hands[j];
				hands[j] = temp;
			}
		}
	}
}

int main(int argc, char** argv){

	char line[BUFSIZ];
	int part1 = 0, part2 = 0;

	int limit = LIMIT_INCREASE;
	Hand** hands = malloc(sizeof(Hand*) * limit);
	int n_hands = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		hands[n_hands] = malloc(sizeof(Hand));
		char* cards = strdup("");
		int bid;
		sscanf(line, "%s %d", cards, &bid);
		hands[n_hands]->cards = cards;
		hands[n_hands]->bid = bid;
		score_hand(hands[n_hands]);
		n_hands++;
		if(n_hands == limit){
			limit += LIMIT_INCREASE;
			hands = realloc(hands, sizeof(Hand*) * limit);
		}
	}

	rank_hands(hands, n_hands);

	for(int i = 0; i < n_hands; i++){
		printf("hand: %d (cards: %s, bid: %d, score: %d) \n", i, hands[i]->cards, hands[i]->bid, hands[i]->score);
		part1 += (i + 1) * hands[i]->bid;
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
