#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int is_digit_p1(char c){
	return c >= 48 && c <= 57;
}

void get_digits_p1(char digits[], char* line){
	int line_length = strlen(line);

	for(int i = 0 ; i <= line_length; i++){
		if(is_digit_p1(line[i])){
			digits[0] = line[i];
			break;
		}
	}
	for(int j = line_length; j >= 0; j--){
		if(is_digit_p1(line[j])){
			digits[1] = line[j];
			break;
		}
	}
}

int main(int argc, char* argv){

	char line[BUFSIZ];
	char digits[3] = {0};
	int sum1 = 0;
	int sum2 = 0;

	while(fgets(line, BUFSIZ, stdin) != NULL) {
		get_digits_p1(digits, line);
		sum1 += atoi(digits);
	}

	printf("part1: %d\n", sum1);
	printf("part2: %d\n", sum2);

	return 0;
}
