#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
	int n_ranges;
	unsigned long** ranges[3];
}Map;

void take_seeds(char line[], unsigned long** seeds, int* seed_count){
	strtok(line, ":");
	char* seed_line = strtok(NULL, ":");
	char* seed = strtok(seed_line, " ");
	while (seed != NULL){
		unsigned long value;
		sscanf(seed, "%lu", &value);
		seeds[*seed_count] = malloc(sizeof(unsigned long));
		memcpy(seeds[*seed_count], &value, sizeof(unsigned long));
		*seed_count += 1;
		seed = strtok(NULL, " ");
	}
}

Map* create_map(){
	Map* m = malloc(sizeof(Map));
	m->n_ranges = 0;
	*m->ranges = malloc(sizeof(unsigned long*) * 50);
	return m;
}

void fill_map(char* line, Map* map){
	char* tkn = strtok(line, " ");
	map->ranges[map->n_ranges] = malloc(sizeof(unsigned long*));
	for(int i = 0; tkn != NULL; tkn = strtok(NULL, " "), i++){
		unsigned long value;
		sscanf(tkn, "%lu", &value);
		map->ranges[map->n_ranges][i] = malloc(sizeof(unsigned long));
		memcpy(map->ranges[map->n_ranges][i], &value, sizeof(unsigned long));
	}
	map->n_ranges += 1;
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	int section = 0;
	unsigned long** seeds = malloc(sizeof(unsigned long*) * 20);
	Map** almanac = malloc(sizeof(Map*));
	int seed_count = 0;
	int created = 0;
	unsigned long part1 = (unsigned long) - 1; // max unsigned long
	unsigned long part2 = (unsigned long) - 1; // max unsigned long

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(strlen(line) == 0){
			section++;
			created = 0;
			continue;
		}
		switch (section){
			case 0:
			take_seeds(line, seeds, &seed_count);
			break;

			default:
			if(created){
				fill_map(line, almanac[section - 1]);
				break;
			} else {
				almanac[section - 1] = create_map();
				created = 1;
				break;
			}
		}
	}

	for(int i = 0; i < seed_count; i++){
		unsigned long seed_n = *seeds[i];
		for(int j = 0; j < section; j++){
			for(int k = 0; k < almanac[j]->n_ranges; k++){
				if(seed_n >= *almanac[j]->ranges[k][1] && seed_n <= *almanac[j]->ranges[k][1] + *almanac[j]->ranges[k][2]){
					seed_n = *almanac[j]->ranges[k][0] + (seed_n - *almanac[j]->ranges[k][1]);
					break;
				}
			}
		}
		if(seed_n < part1){
			part1 = seed_n;
		}
	}

	for(int i = 0; i < seed_count; i += 2){
		unsigned long start = *seeds[i], finish = *seeds[i] + *seeds[i + 1] - 1;
		for(int count = 0; count < finish - start + 1; count++){
			unsigned long seed_n = start + count;
			for(int j = 0; j < section; j++){
				for(int k = 0; k < almanac[j]->n_ranges; k++){
					if(seed_n >= *almanac[j]->ranges[k][1] && seed_n <= *almanac[j]->ranges[k][1] + *almanac[j]->ranges[k][2]){
						seed_n = *almanac[j]->ranges[k][0] + (seed_n - *almanac[j]->ranges[k][1]);
						break;
					}
				}
			}
			if(seed_n < part2){
				part2 = seed_n;
			}
		}
	}

	printf("part1: %lu\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}
