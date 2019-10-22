all: main.o leitura.o
	gcc -o main obj/main.o obj/leitura.o

main.o: src/main.c inc/leitura.h
	gcc -c src/main.c -Iinc -o obj/main.o

leitura.o: src/leitura.c inc/leitura.h
	gcc -c src/leitura.c -Iinc -o obj/leitura.o

clean: 
	rm obj/*.o
	rm main