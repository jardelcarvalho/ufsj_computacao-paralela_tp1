CC = gcc

all: dir_obj main.o arquivo.o floyd_warshall.o
	$(CC) -o main obj/main.o obj/arquivo.o obj/floyd_warshall.o

main.o: src/main.c
	$(CC) -c src/main.c -Iinc -o obj/main.o

arquivo.o: src/arquivo.c inc/arquivo.h
	$(CC) -c src/arquivo.c -Iinc -o obj/arquivo.o -lm

floyd_warshall.o: src/floyd_warshall.c inc/floyd_warshall.h
	$(CC) -c src/floyd_warshall.c -Iinc -o obj/floyd_warshall.o -lm

dir_obj: 
	mkdir -p obj

clean:
	rm main
	rm obj/*.o
	rm -R obj