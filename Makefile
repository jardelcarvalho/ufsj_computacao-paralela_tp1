CC = mpicc
A = gcc
FLAGS = -lm

all: dir_obj main.o leitura.o matriz_tr.o floyd_warshall_mmult.o
	$(CC) -o main obj/main.o obj/leitura.o obj/matriz_tr.o obj/floyd_warshall_mmult.o $(FLAGS)

main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o $(FLAGS)

leitura.o: src/leitura.c
	$(CC) -c src/leitura.c -Iinc -o obj/leitura.o

matriz_tr.o: src/matriz_tr.c inc/matriz_tr.h
	$(CC) -c src/matriz_tr.c -Iinc -o obj/matriz_tr.o

floyd_warshall_mmult.o: src/floyd_warshall_mmult.c inc/floyd_warshall_mmult.h
	$(CC) -c src/floyd_warshall_mmult.c -Iinc -o obj/floyd_warshall_mmult.o $(FLAGS)

dir_obj:
	mkdir -p obj

clean: 
	rm obj/*.o
	rm main
	rm -R obj