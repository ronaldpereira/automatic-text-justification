#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include "bruteforce.h"
#include "dynamic.h"
#include "greedy.h"
#define	 INFINITO INT_MAX

void dynamicProgramming(FILE *input, FILE *output) // Funcao que executa o algoritmo de programacao dinamica
{
	int l, h, x, k;
	int *tamanho, *cost, *range, **memoization;
	unsigned int offset, offend;
	int numpalavras, linhasgeradas, length, funcaocusto, i, j, aux;
	int inicio, final;
	char *string;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k); // Leitura das variaveis a serem aplicadas na funcao de custo

	offset = ftell(input); // Guarda o offset do começo do texto no arquivo para que seja possível voltar nessa posição do arquivo depois
	fseek(input, 0, SEEK_END); // Vai ate o  final do arquivo
	offend = ftell(input); // Grava o offset do final do arquivo
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	for(numpalavras = 0; fscanf(input, " %s", string) != EOF; numpalavras++);// Conta quantas palavras tem no texto de entrada

	tamanho = (int*) calloc(numpalavras,sizeof(int)); // Vetor para guardar o tamanho das palavras do texto de entrada
	cost = (int*) calloc(numpalavras,sizeof(int)); // Vetor para guardar o custo de cada linha = (L - length(li))^x
	range = (int*) calloc(numpalavras,sizeof(int)); // Vetor para guardar a abrangencia da palavra na linha, isto e, ate aonde somatorio(palavra(i)) <= L

	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	for(i = 0; fscanf(input, "%s", string) != EOF; i++)
		tamanho[i] = strlen(string); // Grava o tamanho de cada palavra do texto de entrada

	memoization = (int**) calloc(numpalavras,sizeof(int*));
	for(i = 0; i < numpalavras; i++)
		memoization[i] = (int*) calloc(numpalavras,sizeof(int));
	/* Alocacao da tabela que vai ser usada para a memoizacao */

	/* Montagem da tabela de memoizacao */
	for(i = 0; i < numpalavras; i++)
	{
		for(j = i; j < numpalavras; j++)
		{
			length = 0;
			for(aux = i; aux <= j; aux++)
				length += tamanho[aux];

			aux = l - length - (j - i); // = L - length(li)

			if(aux < 0)
				memoization[i][j] = INFINITO; // Nao e possivel colocar as palavras na mesma linha

			else
				memoization[i][j] = pow((aux), x); // E possivel colocar as palavras na mesma linha, por isso aplica-se o aux^x para ja calcular o custo da linha atual
		}
	}

	/* Montagem do vetor de abrangencia da palavra */
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
	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

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

	/* Liberacao da memoria alocada */
	free(string);
	free(tamanho);
	free(cost);
	free(range);
	for(i = 0; i < numpalavras; i++)
		free(memoization[i]);
	free(memoization);
}

void greedyHeuristic(FILE *input, FILE *output) // Funcao que executa a heuristica gulosa
{
	FILE *tmp; // Arquivo temporario
	int l, h, x, k;
	int offset, offend;
	int aux, sum, *numpalavras, numlinhas, funcaocusto, i;
	char *string;

	tmp = fopen("tmp.txt", "w+r"); // Abertura do arquivo temporario

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k); // Leitura das variaveis a serem aplicadas na funcao de custo

	offset = ftell(input); // Guarda o offset do começo do texto no arquivo para que seja possível voltar nessa posição do arquivo depois
	fseek(input, 0, SEEK_END); // Vai ate o  final do arquivo
	offend = ftell(input); // Grava o offset do final do arquivo
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	numpalavras = (int*) calloc(h,sizeof(int));
	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	/* Montagem do custo minimo para cada linha da heuristica gulosa */
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
			sum += pow((l-(aux-1)), x);
			fseek(tmp, -1, SEEK_CUR); // Volta uma posicao no arquivo para substituir o " " por um "\n"
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
	sum += pow((l-(aux-1)), x);
	numlinhas++;

	funcaocusto = k*pow((h-(numlinhas)), x) + k*sum;

	/* Impressao do resultado */
	fseek(tmp, 0, SEEK_SET);
	fscanf(tmp, "%[^*]", string);
	fprintf(output, "%d\n%s", funcaocusto, string);

	/* Liberacao do espaco alocado */
	fclose(tmp);
	remove("tmp.txt"); // Deleta o arquivo temporario
	free(string);
	free(numpalavras);
}

void bruteForce(FILE *input, FILE *output) // Funcao que executa o algoritmo de forca bruta
{
	int l, h, x, k;
	int offset, offend;
	int numpalavras, *tamanho, *binvec, *solucaobin;
	int i, length, sum, count, numlinhas, funcaocusto, menorcusto = INFINITO;
	char *string;

	fscanf(input, "%d %d\n%d %d", &l, &h, &x, &k); // Leitura das variaveis a serem aplicadas na funcao de custo

	offset = ftell(input); // Guarda o offset do começo do texto no arquivo para que seja possível voltar nessa posição do arquivo depois
	fseek(input, 0, SEEK_END); // Vai ate o  final do arquivo
	offend = ftell(input); // Grava o offset do final do arquivo
	string = (char*) malloc((offend - offset)*sizeof(char)); // Aloca o espaço máximo necessário para alocar uma palavra do texto de entrada
	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	for(numpalavras = 0; fscanf(input, " %s", string) != EOF; numpalavras++);// Conta quantas palavras tem no texto de entrada

	tamanho = (int*) calloc(numpalavras,sizeof(int)); // Vetor para armazenar os tamanhos das palavras do texto da entrada
	binvec = (int*) calloc(numpalavras,sizeof(int)); // Vetor para armazenar a combinacao binaria possivel para as quebras de linhas
	solucaobin = (int*) calloc(numpalavras,sizeof(int)); // Vetor para armazenar a combinacao binaria possivel para as quebras de linhas que possui o menor peso

	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	for(i = 0; fscanf(input, " %s", string) != EOF; i++)
		tamanho[i] = strlen(string); // Grava o tamanho de cada palavra do texto da entrada

	/**
	 *
	 * 1 1 1 1 1 (...) 1 0  = (2^numpalavras)-2 -> a configuracao minima do texto, onde cada palavra dele e separada em todas as linhas
	 * O bit mais significativo (o mais à direita) nao modifica a solucao, e sim somente duplica os calculos
	 */
	for(count = 0; count <= pow(2,numpalavras)-2; count++)
	{
		binvec[numpalavras-1] += 1;
		for(i = numpalavras-1; i > 0; i--)
		{
			if(binvec[i] == 2)
			{
				binvec[i] = 0;
				binvec[i-1] += 1;
			}
		}

		if(binvec[numpalavras-1] == 0) // Considera somente os bits mais significativos iguais a 0 para executar essa parte do codigo
		{
			sum = 0;
			length = 0;
			numlinhas = 1;
			for(i = 0; i < numpalavras; i++)
			{
				if(binvec[i] == 1 || i == numpalavras-1)
				{
					length += tamanho[i];

					if(l - length < 0) // Se o custo da linha for negativo, ela nao e possivel de acontecer, portanto o custo sera INFINITO, logo qualquer custo adicional pode ser desconsiderado, pois a funcaocusto sera igual a INFINITO
					{
						sum = INFINITO;
						break;
					}

					sum += pow((l-length), x);
					length = 0;
					numlinhas++;
				}

				else
					length += tamanho[i] + 1;
			}
			numlinhas--;

			if(sum == INFINITO)
				funcaocusto = INFINITO;

			else
			{
				if(h - numlinhas < 0) // Se o numero de linhas do texto justificado for maior que o limite da pagina, o texto nao e valido, logo seu custo sera INFINITO
					funcaocusto = INFINITO;
				else
					funcaocusto = k*pow((h-numlinhas), x) + k*sum;
			}

			if(funcaocusto < menorcusto) // Se o custo calculado atualmente for menor que o menor custo ja calculado, substitui o valor do menor custo pela funcaocusto atual e guarda o vetor binario de combinacao das quebras de linhas
			{
				menorcusto = funcaocusto;
				for(i = 0; i < numpalavras; i++)
					solucaobin[i] = binvec[i];
			}
		}
	}

	/* Impressao da resposta */

	fprintf(output, "%d\n", menorcusto);

	fseek(input, offset, SEEK_SET); // Volta no inicio do texto

	/* Impressao do texto justificado */
	for(i = 0; i < numpalavras; i++)
	{
		if(solucaobin[i] == 0)
		{
			fscanf(input, "%s", string);
			fprintf(output, "%s", string);
			if(i < numpalavras-1) // Somente se nao for a ultima palavra do texto da entrada que imprime um espaco em branco para separar as palavras
				fprintf(output, " ");
		}

		else
		{
			fscanf(input, "%s", string);
			fprintf(output, "%s\n", string);
		}
	}

	/* Liberacao do espaco alocado */
	free(string);
	free(tamanho);
	free(binvec);
	free(solucaobin);
}
