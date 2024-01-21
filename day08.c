#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMIT_INCREASE 10


typedef struct{
	char* head;
	char* left;
	char* right;
}Element;

unsigned long gcd(unsigned long a, int b) {
    if (b == 0){
        return a;
    }
    return gcd(b, a % b);
}

unsigned long lcm(unsigned long a, int b){
	return (a / gcd(a, b)) * b;
}

int find_element_index_p2(char* head, Element** elements, int* n_elements){
	for(int i = 0; i < *n_elements; i++){
		if(strcmp(elements[i]->head, head) == 0){
			return i;
		}
	}
}

int find_element_index(char* head, Element** elements, int* n_elements){
	if(strcmp(head, "ZZZ") == 0){
		return -1;
	}
	for(int i = 0; i < *n_elements; i++){
		if(strcmp(elements[i]->head, head) == 0){
			return i;
		}
	}
}

int find_first_element_index(Element** elements, int* n_elements){
	for(int i = 0; i < *n_elements; i++){
		if(strcmp(elements[i]->head, "AAA") == 0){
			return i;
		}
	}
}

int main(int argc, char** argv){

	char line[BUFSIZ];
	int part1 = 0;
	unsigned long part2 = 1;

	int limit = LIMIT_INCREASE;
	Element** elements = malloc(sizeof(Element*) * limit);
	int n_elements = 0;
	char* instructions;
	int read_instructions = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		if(!read_instructions){
			instructions = strdup(line);
			read_instructions = 1;
			continue;
		}
		if(strlen(line) == 0) continue;
		elements[n_elements] = malloc(sizeof(Element));
		char* head = strdup("");
		char* left = strdup("");
		char* right = strdup("");
		sscanf(line, "%s = (%3[^,], %3[^)])", head, left, right);
		elements[n_elements]->head = head;
		elements[n_elements]->left = left;
		elements[n_elements]->right = right;
		n_elements++;
		if(n_elements == limit){
			limit += LIMIT_INCREASE;
			elements = realloc(elements, sizeof(Element*) * limit);
		}
	}
	
	int instruction_length = strlen(instructions);
	int instruction_index = 0;
	Element* current_element = elements[find_first_element_index(elements, &n_elements)];
	
	while(1){
		int next_index;
		part1++;
		if(instructions[instruction_index] == 'L'){
			next_index = find_element_index(current_element->left, elements, &n_elements);
		}
		else{
			next_index = find_element_index(current_element->right, elements, &n_elements);
		}
		if(next_index == -1){
			break;
		}
		current_element = elements[next_index];
		instruction_index++;
		if(instruction_index == instruction_length){
			instruction_index = 0;
		}
	}
	
	limit = LIMIT_INCREASE;
	Element** elements_p2 = malloc(sizeof(Element*) * limit);
	int n_elements_p2 = 0;
	for(int i = 0; i < n_elements; i++){
		if(elements[i]->head[2] == 'A'){
			elements_p2[n_elements_p2] = malloc(sizeof(Element));
			memcpy(elements_p2[n_elements_p2], elements[i], sizeof(Element));
			n_elements_p2++;
			if(n_elements_p2 == limit){
				limit += LIMIT_INCREASE;
				elements_p2 = realloc(elements_p2, sizeof(Element*) * limit);
			}
		}
	}
	
	int cycles[n_elements_p2];
	for(int i = 0; i < n_elements_p2; i++){
		current_element = elements_p2[i];
		int step_counter = 0;
		char* first_z = strdup("");
		while(1){
			while(step_counter == 0 || current_element->head[2] != 'Z'){
				int next_index;
				step_counter++;
				if(instructions[instruction_index] == 'L'){
					next_index = find_element_index_p2(current_element->left, elements, &n_elements);
				}
				else{
					next_index = find_element_index_p2(current_element->right, elements, &n_elements);
				}
				current_element = elements[next_index];
				instruction_index++;
				if(instruction_index == instruction_length){
					instruction_index = 0;
				}
			}
			cycles[i] = step_counter;
			
			if(strlen(first_z) == 0){
				first_z = strdup(current_element->head);
				step_counter = 0;
			}
			if(strcmp(current_element->head, first_z) == 0){
				break;
			}
		}
	}
	
	for(int i = 0; i < n_elements_p2; i++){
		part2 = lcm(part2, cycles[i]);
	}
	
	printf("part1: %d\n", part1);
	printf("part2: %lu\n", part2);

	return 0;
}
