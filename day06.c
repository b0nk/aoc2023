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
	unsigned long part2 = 0;

	Race** races = malloc(sizeof(Race*) * 10);
	int n_races = 0;
	int parse_time = 1;
	int** wins = malloc(sizeof(int*) * 10);
	char *full_time_str = strdup(""), *full_distance_str = strdup("");
	unsigned long full_time, full_distance;

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
				char* vchar = strdup("");
				sprintf(vchar, "%d", v);
				full_time_str = strcat(full_time_str, vchar);
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
				char* vchar = strdup("");
				sprintf(vchar, "%d", v);
				full_distance_str = strcat(full_distance_str, vchar);
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

	sscanf(full_time_str, "%lu", &full_time);
	sscanf(full_distance_str, "%lu", &full_distance);

	for(int i = 0; i < full_time; i++){
		if(i * (full_time - i) > full_distance){
			part2++;
		}
	}
	
	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}
