#include <stdio.h>
#include <stdlib.h>
#include "leitura.h"

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log/valgrind-out.txt ./obj/main file/m.txt 

// Para matrizes de dimensão N × N e P processos disponı́veis
// no sistema, deve existir um inteiro Q tal que P = Q 2 e N mod Q = 0

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("parâmetros insuficientes");
        return 0;
    }

    int N;
    int *m = matriz(argv[1], &N);
    int k = N * N;


    // teste
    // for(int i = 0; i < k; i++) {
    //     if(i % N == 0) {
    //         printf("\n");
    //         continue;
    //     }
    //     printf("%d ", m[i]);
    // }


    // desaloca matriz
    free(m);

    return 0;
}