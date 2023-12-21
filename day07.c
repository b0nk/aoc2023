#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_INCREASE 10


typedef struct{
	int bid;
	char* cards;
}Hand;

void sort_hand(Hand* h){
	char* sorted = h->cards;
	int n = strlen(sorted);

	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (sorted[i] > sorted[j]) {
				char temp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = temp;
			}
		}
	}
	h->cards = sorted;
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
		char* cards = strtok(line, " ");
		hands[n_hands]->cards = strdup(cards);
		sort_hand(hands[n_hands]);
		int bid;
		sscanf(strtok(NULL, " "), "%d", &bid);
		hands[n_hands]->bid = bid;
		n_hands++;
		if(n_hands == limit){
			limit += LIMIT_INCREASE;
			hands = realloc(hands, sizeof(Hand*) * limit);
		}
	}

	for(int i = 0; i < n_hands; i++){
		hands[i];
	}
	
	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
