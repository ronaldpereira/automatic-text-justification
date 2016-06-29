#include <stdio.h>
#include <stdlib.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"

int main(int argc, char *argv[])
{
	char option;
	FILE *input, *output;
	option = argv[1][1]; // Char que representa o argumento da escolha do algoritmo a ser executado
	input = fopen(argv[2], "r");
	output = fopen(argv[3], "w");

	if(option == 'd')
		dynamicProgramming(input, output);

	else if(option == 'g')
		greedyHeuristic(input, output);

	else if(option == 'b')
		bruteForce(input, output);

	fclose(input);
	fclose(output);

	return 0;
}
