#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bruteforce.h"
#include "dinamic.h"
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
		printf("Dinamic Programming\n");
		/* Function calls */
	}

	else if(option == 'g')
	{
		printf("Greedy Algorithm\n");
		/* Function calls */
	}

	else if(option == 'b')
	{
		printf("Brute Force Algorithm\n");
		/* Function calls */
	}

	fclose(input);
	fclose(output);

	return 0;
}
