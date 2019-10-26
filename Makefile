CC = mpicc
A = gcc
FLAGS = -lm

all: dir_obj main.o leitura.o matriz_tr.o fox_floyd_warshall.o
	$(CC) -o main obj/main.o obj/leitura.o obj/matriz_tr.o obj/fox_floyd_warshall.o $(FLAGS)

main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o $(FLAGS)

leitura.o: src/leitura.c
	$(CC) -c src/leitura.c -Iinc -o obj/leitura.o

matriz_tr.o: src/matriz_tr.c inc/matriz_tr.h
	$(CC) -c src/matriz_tr.c -Iinc -o obj/matriz_tr.o

fox_floyd_warshall.o: src/fox_floyd_warshall.c inc/fox_floyd_warshall.h
	$(CC) -c src/fox_floyd_warshall.c -Iinc -o obj/fox_floyd_warshall.o $(FLAGS)

dir_obj:
	mkdir -p obj

clean: 
	rm obj/*.o
	rm main
	rm -R obj