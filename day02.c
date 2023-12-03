#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXRED 12
#define MAXGRN 13
#define MAXBLU 14


typedef struct{
	int red;
	int grn;
	int blu;
} Game;

Game* create_game(int r, int g, int b){
	Game* game = malloc(sizeof(Game));
	game->red = r;
	game->grn = g;
	game->blu = b;
	return game;
}

int is_turn_possible(Game* game){
	if(game->red <= MAXRED && game->grn <= MAXGRN && game->blu <= MAXBLU){
		return 0;
	}
	return 1;
}

int is_revealed_possible(char* revealed){
	char* turn = malloc(sizeof(char) * BUFSIZ);
	char* comma_pointer;
	int qty;
	char* color = malloc(sizeof(char) * BUFSIZ);
	Game *current_game = create_game(0, 0, 0);
	turn = strtok_r(revealed, ",", &comma_pointer);
	while(turn != NULL){
		sscanf(turn, "%d %s", &qty, color);
		if(strcmp(color, "red") == 0){
			current_game->red = qty;
		}
		if(strcmp(color, "green") == 0){
			current_game->grn = qty;
		}
		if(strcmp(color, "blue") == 0){
			current_game->blu = qty;
		}
		turn = strtok_r(NULL, ",", &comma_pointer);
		if(turn != NULL){
			turn = &turn[1];
		}
	}
	if(is_turn_possible(current_game) != 0){
		return 1;
	}
	return 0;
}

int is_possible_game(char* game_info){
	char* revealed = malloc(sizeof(char) * BUFSIZ);
	char* semicolon_pointer;
	revealed = strtok_r(game_info, ";", &semicolon_pointer);
	while(revealed != NULL){
		if(is_revealed_possible(revealed) != 0){
			return 1;
		}
		revealed = strtok_r(NULL, ";", &semicolon_pointer);
		if(revealed != NULL){
			revealed = &revealed[1];
		}
	}
	return 0;
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	char* comma_pointer;
	char* game_info = malloc(sizeof(char) * BUFSIZ);
	int game_counter = 1;
	int sum1 = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		strtok_r(line, ":", &comma_pointer);
		game_info = &strtok_r(NULL, ":", &comma_pointer)[1];
		if(is_possible_game(game_info) == 0){
			sum1 += game_counter;
		}
		game_counter++;
	}

	printf("part1: %d\n", sum1);
	printf("part2: %d\n", 0);

	return 0;
}
