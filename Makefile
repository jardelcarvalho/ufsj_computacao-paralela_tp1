CC = mpicc
FLAGS = -lm

all: main.o leitura.o
	$(CC) -o main obj/main.o obj/leitura.o $(FLAGS)

main.o: src/main.c inc/leitura.h
	$(CC) -c src/main.c -Iinc -o obj/main.o

leitura.o: src/leitura.c inc/leitura.h
	$(CC) -c src/leitura.c -Iinc -o obj/leitura.o

clean: 
	rm obj/*.o
	rm main