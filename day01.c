#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_digit(char c){
	return c >= 48 && c <= 57;
}

int get_number(char* token, char* number[]){
	for(int i = 0; i < 9; i++){
		if(strcmp(token, number[i]) == 0){
			return i + 48 + 1;
		}
	}
	return -1;
}

void get_digits_p2(char digits[], char* line, char* numbers[]){
	int line_length = strlen(line) - 1;
	char* current_token = strdup("");
	int found_first = 0;
	int found_last = 0;

	for(int i = 0; i <= line_length && found_first == 0; i++){
		if(is_digit(line[i])){
			digits[0] = line[i];
			break;
		} else {
			for(int k = 3; k <= 5; k++){
				current_token[0] = '\0';
				memmove(current_token, &line[i], k);
				current_token[k] = '\0';
				int number = get_number(current_token, numbers);
				if(number != -1){
					digits[0] = number;
					found_first = 1;
					break;
				}
			}
		}
	}

	for(int i = line_length; i >= 0 && found_last == 0; i--){
		if(is_digit(line[i])){
			digits[1] = line[i];
			break;
		} else {
			for(int k = 3; k <= 5; k++){
				current_token[0] = '\0';
				memmove(current_token, &line[i - k + 1], k);
				current_token[k] = '\0';
				int number = get_number(current_token, numbers);
				if(number != -1){
					digits[1] = number;
					found_last = 1;
					break;
				}
			}
		}
	}
	free(current_token);
}

void get_digits_p1(char digits[], char* line){
	int line_length = strlen(line) - 1;

	for(int i = 0 ; i <= line_length; i++){
		if(is_digit(line[i])){
			digits[0] = line[i];
			break;
		}
	}
	for(int j = line_length; j >= 0; j--){
		if(is_digit(line[j])){
			digits[1] = line[j];
			break;
		}
	}
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	char digits_p1[3] = {0};
	char digits_p2[3] = {0};
	char* numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
	int sum1 = 0;
	int sum2 = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		line[strcspn(line, "\n")] = 0;
		get_digits_p1(digits_p1, line);
		sum1 += atoi(digits_p1);
		get_digits_p2(digits_p2, line, numbers);
		sum2 += atoi(digits_p2);
	}

	printf("part1: %d\n", sum1);
	printf("part2: %d\n", sum2);

	return 0;
}
