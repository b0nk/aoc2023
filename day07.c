#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_INCREASE 10
#define DECK "23456789TJQKA"


enum HandType{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND,
};

typedef struct{
	enum HandType type;
	int bid;
	int cards_values[5];
	char* cards;
}Hand;

void calc_hand_score_p2(Hand* h){
	int n = strlen(h->cards);
	for(int i = 0; i < n; i++){
		if(h->cards[i] == 'J'){
			h->cards_values[i] = 0;
		} else {
			h->cards_values[i] = strchr(DECK, h->cards[i]) - DECK;
		}
	}
}

void calc_hand_score(Hand* h){
	int n = strlen(h->cards);
	for(int i = 0; i < n; i++){
		h->cards_values[i] = strchr(DECK, h->cards[i]) - DECK;
	}
}

enum HandType score_hand_p2(Hand* h){
	int counts[13] = {0};
    for(int idx = 0; idx < 5; idx++){
		counts[h->cards_values[idx]]++;
    }
	int match_counts[6] = {0};
    for(int match_count = 1; match_count <= 5; match_count++) {
        for (int idx = 0; idx < 13; idx++) {
            if (counts[idx] == match_count){
				match_counts[match_count] += 1;
			}
        }
    }
    if(match_counts[5] == 1) return FIVE_OF_A_KIND;
    if(match_counts[4] == 1) return FOUR_OF_A_KIND;
    if(match_counts[3] == 1 && match_counts[2] == 1) return FULL_HOUSE;
    if(match_counts[3] == 1) return THREE_OF_A_KIND;
    if(match_counts[2] == 2) return TWO_PAIR;
    if(match_counts[2] == 1) return ONE_PAIR;
    return HIGH_CARD;
}

enum HandType score_hand(Hand* h){
	int counts[13] = {0};
    for(int idx = 0; idx < 5; idx++){
		counts[h->cards_values[idx]]++;
    }
	int match_counts[6] = {0};
    for(int match_count = 1; match_count <= 5; match_count++) {
        for (int idx = 0; idx < 13; idx++) {
            if (counts[idx] == match_count){
				match_counts[match_count] += 1;
			}
        }
    }
    if(match_counts[5] == 1) return FIVE_OF_A_KIND;
    if(match_counts[4] == 1) return FOUR_OF_A_KIND;
    if(match_counts[3] == 1 && match_counts[2] == 1) return FULL_HOUSE;
    if(match_counts[3] == 1) return THREE_OF_A_KIND;
    if(match_counts[2] == 2) return TWO_PAIR;
    if(match_counts[2] == 1) return ONE_PAIR;
    return HIGH_CARD;
}

int hand_sort(const void *x, const void *y){
	const Hand *a = *(Hand **) x;
	const Hand *b = *(Hand **) y;

	if(a->type != b->type){
		return a->type - b->type;
	}
	for(int i = 0; i < 5; i++){
		if(a->cards[i] != b->cards[i]){
			return a->cards_values[i] - b->cards_values[i];
		}
	}
	return 0;
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
		calc_hand_score(hands[n_hands]);
		hands[n_hands]->type = score_hand(hands[n_hands]);
		n_hands++;
		if(n_hands == limit){
			limit += LIMIT_INCREASE;
			hands = realloc(hands, sizeof(Hand*) * limit);
		}
	}

	qsort(hands, n_hands, sizeof(Hand*), hand_sort);

	for(int i = 0; i < n_hands; i++){
		part1 += (i + 1) * hands[i]->bid;
	}
	
	for(int i = 0; i < n_hands; i++){
		calc_hand_score_p2(hands[i]);
		score_hand_p2(hands[i]);
	}
	
	qsort(hands, n_hands, sizeof(Hand*), hand_sort);
	
	for(int i = 0; i < n_hands; i++){
		part2 += (i + 1) * hands[i]->bid;
	}

	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
