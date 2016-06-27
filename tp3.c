#include <stdio.h>
#include <stdlib.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"

int main(int argc, char *argv[])
{
	char option;
	FILE *input, *output;
	option = argv[1][1];
	input = fopen(argv[2], "r");
	output = fopen(argv[3], "w");

	if(option == 'd')
	{
		printf("Dynamic Programming\n");
		/* Function calls */
		dynamicProgramming(input, output);
	}

	else if(option == 'g')
	{
		printf("Greedy Heuristic\n");
		/* Function calls */
		greedyHeuristic(input, output);
	}

	else if(option == 'b')
	{
		printf("Brute Force Algorithm\n");
		/* Function calls */
		bruteForce(input, output);
	}

	fclose(input);
	fclose(output);

	return 0;
}
