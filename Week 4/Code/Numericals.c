/*
	Author: Michael Weaver
	Course: CST - 221
	University: GCU

	Description: This program takes a single user input, integer, between 0 and 4095 then proceeds
		to calculate the binary and hexadecimal of that number. After which it shifts the 
		number 16 bits to the left, performs additional calculations, then prints the new
		number, binary, and hexadecimal to the console.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int i, j, x, final;
unsigned int decimal = -1, transform;
char binary_array [32];

void* print_to_console (char message []){
	//Print message to console
	printf("%s", message);
}

void* get_from_console (){
	//Retrieve user input
	scanf("%d", &decimal);
	//Clear input buffer
	while ((getchar()) != '\n');
}

void* calculate_binary (){
	//Ensure that only valid numbers are calculated
	if (decimal >= 0 && decimal < 4096){
		unsigned int mask = 1<<31;
		//Loop to print binary number
		for (i = 0; i < 8; i++){
			for (j = 0; j < 4; j++){
				char c = (decimal & mask) == 0 ? '0' : '1';
				binary_array[x++] = c;
				putchar(c);
				mask >>= 1;
			}
			putchar(' ');
		}
		putchar('\n');
	}
}

void* print_hexadecimal (){
	//Easy, straightforward manner to print in hexidecimal
	printf("%04x\n", decimal);
}

void* calculate_decimal (){
	print_to_console("The number in binary: ");
	calculate_binary();
	print_to_console("The number in hexadecimal: ");
	print_hexadecimal();
}

void* transform_number (){
	//Shift decimal vaiable 16 bits left
	transform = decimal << 16;
	//Mask out bottom 16 bits
	final = transform & decimal;
	unsigned int addition = 0x07FF;
	//Add new hex number
	final = final | addition;
	printf("New number in decimal: %d\n", final);
	decimal = final;
	//Change decimal and print new numbers
	calculate_decimal();
}

int main (void){
	
	//Loop to ensure valid data
	while (decimal < 0 || decimal > 4095){
		//Opening user prompt
		print_to_console("Please enter a number between 0 and 4095: ");
		get_from_console();
		if (decimal < 0 || decimal > 4095){
			print_to_console("Only a number within range is accepted.\n");
		}
	}
	//Heart of program functions
	calculate_decimal();
	transform_number();
	return 0;
}
