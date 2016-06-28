#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"
#define	 INFINITO INT_MAX

void imprime(int **m, int l)
{
	int i, j;

	for(i = 0; i < l; i++)
	{
		for(j = 0; j < l; j++)
		{
			printf("%d ", m[i][j]);

			if(j == l-1)
				printf("\n");
		}
	}
}

//Fim Funcões Teste

void dynamicProgramming(FILE *input, FILE *output)
{
	int l, h, x, k;
	int *tamanho, *cost, *range, **memoization;
	int offset, offend;
	int numpalavras, linhasgeradas, length, funcaocusto, i, j, aux;
	int inicio, final;
	char *string;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada

	for(numpalavras = 0; fscanf(input, " %s", string) != EOF; numpalavras++);

	tamanho = (int*) calloc(numpalavras,sizeof(int));
	cost = (int*) calloc(numpalavras,sizeof(int));
	range = (int*) calloc(numpalavras,sizeof(int));

	fseek(input, offset, SEEK_SET);

	for(i = 0; fscanf(input, "%s", string) != EOF; i++)
		tamanho[i] = strlen(string);

	memoization = (int**) calloc(numpalavras,sizeof(int*));
	for(i = 0; i < numpalavras; i++)
		memoization[i] = (int*) calloc(numpalavras,sizeof(int));

	for(i = 0; i < numpalavras; i++)
	{
		for(j = i; j < numpalavras; j++)
		{
			length = 0;
			for(aux = i; aux <= j; aux++)
				length += tamanho[aux];

			aux = l - length - (j - i);

			if(aux < 0)
				memoization[i][j] = INFINITO;

			else
				memoization[i][j] = pow((aux), x);
		}
	}

	for(i = numpalavras-1; i >= 0; i--)
	{
		j = numpalavras-1;

		if(memoization[i][j] < INFINITO)
		{
			cost[i] = memoization[i][j];
			range[i] = j+1;
		}

		else
		{
			while(memoization[i][j-1] == INFINITO)
				j--;

			cost[i] = memoization[i][j-1] + cost[j];
			range[i] = j;

			while(j != i)
			{
				aux = memoization[i][j-1] + cost[j];

				if(cost[i] > aux)
				{
					cost[i] = aux;
					range[i] = j;
				}

			j--;
			}
		}
	}

	/* Impressão do resultado */
	for(linhasgeradas = 1, i = 0; range[i] < numpalavras; linhasgeradas++)
		i = range[i];

	funcaocusto = k*pow((h-linhasgeradas), x) + k*cost[0];
	fprintf(output, "%d\n", funcaocusto);

	/* Impressão do texto justificado */
	fseek(input, offset, SEEK_SET);

	inicio = 0;
	final = 0;
	aux = 0;

	for(i = 0; i < linhasgeradas; i++)
	{
		inicio = final;
		final = range[aux];
		aux = range[aux];
		printf("inicio = %d / final = %d\n", inicio, final);
		while(inicio != final)
		{
			fscanf(input, "%s", string);
			fprintf(output, "%s", string);
			inicio++;

			if(inicio != final)
				fprintf(output, " ");
			else
				fprintf(output, "\n");
		}
	}


	free(string);
	free(tamanho);
	free(cost);
	free(range);
	for(i = 0; i < numpalavras; i++)
		free(memoization[i]);
	free(memoization);
}

void greedyHeuristic(FILE *input, FILE *output)
{
	/* TODO Pegar o texto e ver quantas palavras cabem no maximo de cada linha para minimizar o numero de espaços em branco em cada linha e calcular a função de custo pra cada */
	int l, h, x, k;
	char *string;
	int offset, offend;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada

	fscanf(input, " %s", string);
	printf("%s\n", string);


	free(string);
}

void bruteForce(FILE *input, FILE *output)
{
	/* TODO Pegar o texto e ver quantas palavras cabem no maximo de cada linha e calcular a função de custo de cada disposição -> Começando no máximo de palavras por linha e indo até sobrar uma palavra por linha -> Salvo o menor custo e o vetor Li -> Reconstruo a linha e imprimo o menor custo e a resposta */
	int l, h, x, k;
	char *string;
	int offset, offend;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	fseek(input, offset, SEEK_SET);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada

	fscanf(input, " %s", string);
	printf("%s\n", string);

	free(string);
}
