CC = gcc
CFLAGS = -Wall -Wextra -g -O0

all: tp3.exe

tp3.exe: tp3.o function_tp3.o
	$(CC) $(CFLAGS) tp3.o function_tp3.o -o tp3.exe

tp3.o: tp3.c bruteforce.h dinamic.h greedy.h
	$(CC) $(CFLAGS) -c tp3.c

function_tp3.o: function_tp3.c bruteforce.h dinamic.h greedy.h
	$(CC) $(CFLAGS) -c function_tp3.c

clean:
	rm *.o tp3.exe
