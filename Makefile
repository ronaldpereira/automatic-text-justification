CC = gcc
CFLAGS = -Wall -Wextra -g -O0

all: tp3.exe

tp3.exe: tp3.o function_tp3.o
	$(CC) $(CFLAGS) tp3.o function_tp3.o -lm -o tp3.exe

tp3.o: tp3.c bruteforce.h dynamic.h greedy.h
	$(CC) $(CFLAGS) -c tp3.c

function_tp3.o: function_tp3.c bruteforce.h dynamic.h greedy.h
	$(CC) $(CFLAGS) -c function_tp3.c

clean:
	rm *.o tp3.exe

run:
	make all && ./tp3.exe -d testes/teste.txt testes/resposta-pd.txt && ./tp3.exe -g testes/teste.txt testes/resposta-gu.txt && ./tp3.exe -b testes/teste.txt testes/resposta-fb.txt && make clean

g:
	make all && ./tp3.exe -g testes/teste.txt testes/resposta-gu.txt && make clean

b:
	make all && ./tp3.exe -b testes/teste.txt testes/resposta-fb.txt && make clean

d:
	make all && ./tp3.exe -d testes/teste.txt testes/resposta-pd.txt && make clean
