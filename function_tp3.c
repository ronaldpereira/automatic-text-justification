#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"
#define	 INFINITO INT_MAX

void dynamicProgramming(FILE *input, FILE *output)
{
	int l, h, x, k;
	char *string;
	int offset, offend;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char));

	fscanf(input, " %s", string);
	printf("%s\n", string);

	free(string);
}

void greedyHeuristic(FILE *input, FILE *output)
{
/* Pegar o texto e ver quantas palavras cabem no maximo de cada linha e calcular a função de custo pra cada */
	int l, h, x, k;
	char *string;
	int offset, offend;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char));

	fscanf(input, " %s", string);
	printf("%s\n", string);

	free(string);
}

void bruteForce(FILE *input, FILE *output)
{
	int l, h, x, k;
	char *string;
	int offset, offend;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char));

	fscanf(input, " %s", string);
	printf("%s\n", string);

	free(string);
}
