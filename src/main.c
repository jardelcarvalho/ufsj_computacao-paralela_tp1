// autor: Jardel Carvalho
// ano: 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "leitura.h"

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log/valgrind-out.txt ./obj/main file/m.txt 

int main(int argc, char **argv) {
    int num_procs;
    int my_rank;

    // MPI_Init(&argc, argv);
    // MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    // MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    if(argc != 2) {
        printf("erro: parâmetros insuficientes\n");
        return 0;
    }

    int N;
    float *m = matriz(argv[1], &N);
    int k = N * N;
    if(!m) {
        return 0;
    }

    // verificando se a matriz é válida (condição de Fox)
    // Para matrizes de dimensão N × N e P processos disponı́veis
    // no sistema, deve existir um inteiro Q tal que P = Q^2 e N mod Q = 0
    // int q = sqrt(num_procs);
    // if(!(q * q == p && N % q == 0F)) {
    //     printf("erro: matriz inapropriada para o número de processos");
    // }


    // teste
    for(int i = 0; i < k; i++) {
        if(i % N == 0) {
            printf("\n");
            continue;
        }
        printf("%.2f ", m[i]);
    }


    // desaloca matriz
    free(m);
    // MPI_Finalize();

    return 0;
}