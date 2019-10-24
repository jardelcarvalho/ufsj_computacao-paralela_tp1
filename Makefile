CC = mpicc
A = gcc
FLAGS = -lm

all: main.o leitura.o matriz_tr.o comunicacao.o
	$(CC) -o main obj/main.o obj/leitura.o obj/matriz_tr.o obj/comunicacao.o $(FLAGS)

test: main.o leitura.o matriz_tr.o
	$(A) -o main obj/main.o obj/leitura.o obj/matriz_tr.o $(FLAGS)

main.o: src/main.c inc/leitura.h
	$(CC) -c src/main.c -Iinc -o obj/main.o

leitura.o: src/leitura.c inc/leitura.h
	$(CC) -c src/leitura.c -Iinc -o obj/leitura.o

matriz_tr.o: src/matriz_tr.c inc/matriz_tr.h
	$(CC) -c src/matriz_tr.c -Iinc -o obj/matriz_tr.o

comunicacao.o: src/comunicacao.c inc/comunicacao.h
	$(CC) -c src/comunicacao.c -Iinc -o obj/comunicacao.o

clean: 
	rm obj/*.o
	rm main