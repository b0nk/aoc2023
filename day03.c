#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_SIZE 140
#define MAX_PARTS 1000


typedef struct{
	int value, x, y, length;
} Part;

typedef struct{
	int value, x, y;
} Gear;

int is_digit(char c){
	return 48 <= c && c <= 57;
}

int is_dot(char c){
	return c == 46;
}

int is_symbol(char c){
	return !is_dot(c) && !is_digit(c);
}

int is_asterisk(char c){
	return c == '*';
}

Gear create_gear(int x, int y, int v){
	Gear g;
	g.x = x;
	g.y = y;
	g.value = v;
	return g;
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

int is_valid_part(char** e, Part p, Gear g[], int* g_counter){
	int line = p.x;
	int curs = p.y;
	int end_curs = p.y + p.length;

	while(curs < end_curs){
		//top
		if(line - 1 >= 0){
			if(curs - 1 >= 0){
				if(is_symbol(e[line - 1][curs - 1])){
					if(is_asterisk(e[line - 1][curs - 1])){
						g[*g_counter] = create_gear(line - 1, curs - 1, p.value);
						*g_counter += 1;
					}
					return 1;
				}
			}
			if(curs + 1 < STACK_SIZE){
				if(is_symbol(e[line - 1][curs + 1])){
					if(is_asterisk(e[line - 1][curs + 1])){
						g[*g_counter] = create_gear(line - 1, curs + 1, p.value);
						*g_counter += 1;
					}
					return 1;
				}
			}
			if(is_symbol(e[line - 1][curs])){
				if(is_asterisk(e[line - 1][curs])){
					g[*g_counter] = create_gear(line - 1, curs, p.value);
					*g_counter += 1;
				}
				return 1;
			}
		}
		//bottom
		if(line + 1 < STACK_SIZE){
			if(curs - 1 >= 0){
				if(is_symbol(e[line + 1][curs - 1])){
					if(is_asterisk(e[line + 1][curs - 1])){
						g[*g_counter] = create_gear(line + 1, curs - 1, p.value);
						*g_counter += 1;
					}
					return 1;
				}
			}
			if(curs + 1 < STACK_SIZE){
				if(is_symbol(e[line + 1][curs + 1])){
					if(is_asterisk(e[line + 1][curs + 1])){
						g[*g_counter] = create_gear(line + 1, curs + 1, p.value);
						*g_counter += 1;
					}
					return 1;
				}
			}
			if(is_symbol(e[line + 1][curs])){
				if(is_asterisk(e[line + 1][curs])){
					g[*g_counter] = create_gear(line + 1, curs, p.value);
					*g_counter += 1;
				}
				return 1;
			}
		}
		//left
		if(curs - 1 >= 0){
			if(is_symbol(e[line][curs - 1])){
				if(is_asterisk(e[line][curs - 1])){
					g[*g_counter] = create_gear(line, curs - 1, p.value);
					*g_counter += 1;
				}
				return 1;
			}
		}
		//right
		if(curs + 1 < STACK_SIZE){
			if(is_symbol(e[line][curs + 1])){
				if(is_asterisk(e[line][curs + 1])){
					g[*g_counter] = create_gear(line, curs + 1, p.value);
					*g_counter += 1;
				}
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

int find_matching_gear(Gear gears[], int idx, int counter){
	int res = 0;
	int base_x = gears[idx].x;
	int base_y = gears[idx].y;
	for(int i = idx + 1 ; i < counter; i++){
		if(gears[i].x == base_x && gears[i].y == base_y){
			res = gears[i].value;
		}
	}
	return res;
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	char** engine_map;
	Part parts[MAX_PARTS];
	Gear gears[MAX_PARTS];
	int parts_counter, gears_counter, line_counter = 0;
	int sum1, sum2 = 0;

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
		if(is_valid_part(engine_map, parts[i], gears, &gears_counter)){
			sum1 += parts[i].value;
		}
	}

	for(int i = 0; i < gears_counter; i++){
		int v1 = gears[i].value;
		int v2 = find_matching_gear(gears, i, gears_counter);
		sum2 += v1 * v2;
	}

	printf("part1: %d\n", sum1);
	printf("part2: %d\n", sum2);

	return 0;
}
