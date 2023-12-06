#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 140
#define MAX_PARTS 1000


typedef struct{
	int value, x, y, length;
} Part;

int is_digit(char c){
	return 48 <= c && c <= 57;
}

int is_dot(char c){
	return c == 46;
}

int is_symbol(char c){
	return !is_dot(c) && !is_digit(c);
}

Part create_part(int v, int x, int y){
	int len;
	if(v >= 100){
		len = 3;
	} else if(v >= 10){
		len = 2;
	} else {
		len = 1;
	}

	Part new_part;
	new_part.value = v;
	new_part.x = x;
	new_part.y = y;
	new_part.length = len;
	return new_part;
}

int is_valid_part(char** e, Part p){
	int line = p.x;
	int curs = p.y;
	int end_curs = p.y + p.length;

	while(curs < end_curs){
		//top
		if(line - 1 >= 0){
			if(curs - 1 >= 0){
				if(is_symbol(e[line - 1][curs - 1])){
					return 1;
				}
			}
			if(curs + 1 < STACK_SIZE){
				if(is_symbol(e[line - 1][curs + 1])){
					return 1;
				}
			}
			if(is_symbol(e[line - 1][curs])){
				return 1;
			}
		}
		//bottom
		if(line + 1 < STACK_SIZE){
			if(curs - 1 >= 0){
				if(is_symbol(e[line + 1][curs - 1])){
					return 1;
				}
			}
			if(curs + 1 < STACK_SIZE){
				if(is_symbol(e[line + 1][curs + 1])){
					return 1;
				}
			}
			if(is_symbol(e[line + 1][curs])){
				return 1;
			}
		}
		//left
		if(curs - 1 >= 0){
			if(is_symbol(e[line][curs - 1])){
				return 1;
			}
		}
		//right
		if(curs + 1 < STACK_SIZE){
			if(is_symbol(e[line][curs + 1])){
				return 1;
			}
		}
		curs++;
	}
	return 0;
}

void get_part_numbers(char** engine, Part* parts, int* parts_counter){
	int current = 0;
	for(int i = 0; i < STACK_SIZE; i++){
		for(int j = 0; j < STACK_SIZE; j++){
			if(is_digit(engine[i][j])){
				sscanf(&engine[i][j], "%d", &current);
				Part tmp = create_part(current, i, j);
				parts[*parts_counter] = tmp;
				*parts_counter += 1;
				j += tmp.length - 1;
			}
		}
	}
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	char** engine_map;
	Part parts[MAX_PARTS];
	int parts_counter = 0;
	int line_counter = 0;
	int sum1 = 0;

	engine_map = malloc(sizeof(*engine_map) * STACK_SIZE);
	for(int i = 0; i < STACK_SIZE; i++){
		engine_map[i] = malloc(sizeof(**engine_map) * STACK_SIZE);
	}

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		engine_map[line_counter++] = strdup(line);
	}

	get_part_numbers(engine_map, parts, &parts_counter);
	for(int i = 0; i < parts_counter; i++){
		if(is_valid_part(engine_map, parts[i])){
			sum1 += parts[i].value;
		}
	}

	printf("part1: %d\n", sum1);
	printf("part2: %d\n", 0);

	return 0;
}
