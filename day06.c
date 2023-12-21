#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
	int time;
	int distance;
	int wins;
}Race;

int main(int argc, char** argv){

	char line[BUFSIZ];
	int part1 = 1;
	int part2 = 0;

	Race** races = malloc(sizeof(Race*) * 10);
	int n_races = 0;
	int parse_time = 1;
	int** wins = malloc(sizeof(int*) * 10);
	int n_wins = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		n_races = 0;
		if(parse_time){
			strtok(line, ":");
			char* values = strtok(NULL, ":");
			char* tkn = strtok(values, " ");
			while(tkn != NULL){
				int v;
				sscanf(tkn, "%d", &v);
				races[n_races] = malloc(sizeof(Race));
				races[n_races]->wins = 0;
				races[n_races++]->time = v;
				tkn = strtok(NULL, " ");
			}
			parse_time = 0;
			n_races = 0;
		}
		else{
			strtok(line, ":");
			char* values = strtok(NULL, ":");
			char* tkn = strtok(values, " ");
			while(tkn != NULL){
				int v;
				sscanf(tkn, "%d", &v);
				races[n_races++]->distance = v;
				tkn = strtok(NULL, " ");
			}
		}
	}

	for(int i = 0; i < n_races; i++){
		for(int j = 0; j < races[i]->time; j++){
			if(j * (races[i]->time - j) > races[i]->distance){
				races[i]->wins += 1;
			}
		}
		part1 *= races[i]->wins;
	}
	
	printf("part1: %d\n", part1);
	printf("part2: %d\n", part2);

	return 0;
}
