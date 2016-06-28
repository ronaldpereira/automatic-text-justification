#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"
#define	 INFINITO INT_MAX

/* TEST */
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
	/* TODO Modularizar a função */
	int l, h, x, k;
	int *tamanho, *cost, *range, **memoization;
	unsigned int offset, offend;
	int numpalavras, linhasgeradas, length, funcaocusto, i, j, aux;
	int inicio, final;
	char *string;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	fseek(input, offset, SEEK_SET);

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
	/* TODO Pegar o texto e ver quantas palavras cabem no maximo de cada linha para minimizar o numero de espaços em branco em cada linha e calcular a função de custo pra cada, comparando de 2 em 2 linhas */
	FILE *tmp;
	int l, h, x, k;
	int offset, offend;
	int aux, sum, *numpalavras, numlinhas, funcaocusto, i;
	char *string;

	tmp = fopen("tmp.txt", "w+r");

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	numpalavras = (int*) calloc(h,sizeof(int));
	fseek(input, offset, SEEK_SET);

	aux = 0;
	numlinhas = 0;
	i = 0;
	sum = 0;
	while(fscanf(input, "%s", string) != EOF)
	{
		aux += strlen(string) + 1;

		if(aux <= l+1)
		{
			fprintf(tmp, "%s ", string);
			numpalavras[i]++;
		}

		else
		{
			aux -= strlen(string) + 1;
			sum += k*pow((l-(aux-1)), x);
			fseek(tmp, -1, SEEK_CUR);
			fprintf(tmp, "\n");
			numlinhas++;
			i++;
			fprintf(tmp, "%s ", string);
			numpalavras[i]++;
			aux = strlen(string) + 1;
		}
	}
	fseek(tmp, -1, SEEK_CUR);
	fprintf(tmp, "\n");
	sum += k*pow((l-(aux-1)), x);
	numlinhas++;

	funcaocusto = k*pow((h-(numlinhas)), x) + sum;

	fseek(tmp, 0, SEEK_SET);
	fscanf(tmp, "%[^-1]", string);
	fprintf(output, "%d\n%s", funcaocusto, string);

	fclose(tmp);
	remove("tmp.txt");
	free(string);
	free(numpalavras);
}

void bruteForce(FILE *input, FILE *output)
{
	/* TODO Pegar o texto e ver quantas palavras cabem no maximo de cada linha e calcular a função de custo de cada disposição -> Começando no máximo de palavras por linha e indo até sobrar uma palavra por linha -> Salvo o menor custo e o vetor Li -> Reconstruo a linha e imprimo o menor custo e a resposta */
	FILE *tmp_1, *tmp_2;
	int l, h, x, k;
	int offset, offend;
	int aux, sum, *numpalavras, numlinhas, funcaocusto, i;
	char *str;
	char *string;

	tmp_1 = fopen("tmp_1.txt", "w+r");
	tmp_2 = fopen("tmp_2.txt", "w+r");

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k);

	offset = ftell(input);
	fseek(input, 0, SEEK_END);
	offend = ftell(input);
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	numpalavras = (int*) calloc(h,sizeof(int));
	str = (char*) malloc(l+1*sizeof(char));
	fseek(input, offset, SEEK_SET);

	aux = 0;
	numlinhas = 0;
	i = 0;
	sum = 0;
	while(fscanf(input, "%s", string) != EOF)
	{
		aux += strlen(string) + 1;

		if(aux <= l+1)
		{
			fprintf(tmp_1, "%s ", string);
			numpalavras[i]++;
		}

		else
		{
			aux -= strlen(string) + 1;
			printf("aux = %d\n", aux);
			sum += k*pow((l-(aux-1)), x);
			fseek(tmp_1, -1, SEEK_CUR);
			fprintf(tmp_1, "\n");
			numlinhas++;
			i++;
			fprintf(tmp_1, "%s ", string);
			numpalavras[i]++;
			aux = strlen(string) + 1;
		}
	}
	fseek(tmp_1, -1, SEEK_CUR);
	fprintf(tmp_1, "\n");
	sum += k*pow((l-(aux-1)), x);
	numlinhas++;

	/* TEST */
	for(i = 0; i < h; i++)
	{
		printf("%d\n", numpalavras[i]);
	} // End

	funcaocusto = k*pow((h-(numlinhas)), x) + sum;
	fseek(tmp_1, 0, SEEK_SET);
	fgets(str, l+1, tmp_1);
	printf("%s\n", str);

	printf("funcao custo = %d\n", funcaocusto);

	fclose(tmp_1);
	fclose(tmp_2);
	/* TEST remove("tmp_1.txt"); */
	/* TEST remove("tmp_2.txt"); */
	free(string);
	free(str);
	free(numpalavras);
}
