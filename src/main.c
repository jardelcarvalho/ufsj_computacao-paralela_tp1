// autor: Jardel Carvalho
// ano: 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"
#include "leitura.h"

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log/valgrind-out.txt ./obj/main file/m.txt 

// teste
void print_m(float *m_, int N) {
    for(int i = 0; i < N * N; i++) {
        if(i % N == 0) {
            printf("\n");
            continue;
        }
        printf("%.2f ", m_[i]);
    }
}

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("erro: parâmetros insuficientes\n");
        return 0;
    }

    int num_procs;
    int my_rank;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    float *sm;

    if(my_rank == 0) {
        int N;
        float *m = matriz(argv[1], &N);
        if(!m) {
            MPI_Finalize();
            return 0;
        }
        int k = N * N;

        /* 
            Verificando se a matriz é válida (condição de Fox)
            Para matrizes de dimensão N × N e P processos disponı́veis
            no sistema, deve existir um inteiro Q tal que P = Q^2 e N mod Q = 0 
        */
        int q = sqrt(num_procs);
        if(!(q * q == num_procs && N % q == 0)) {
            printf("erro: matriz inapropriada para o número de processos");
            MPI_Finalize();
            return 0;
        }

        // envia submatrizes para os demais processos
        int j = 0;
        for(int i = 1; i < num_procs; i++) {
            int k = i % N;
            int i = k * N 
            if(i % q == 0) {
                j++;
            }
            
            // j = ?
            // (id % q) * (N / q) + N * l + j * (N * q)
            // ((id % q) + 1) * (N / q) + N * l + j * (N * q)
        }


        // desaloca matriz
        free(m);
    } else {
        printf("Sou o %d\n", my_rank);
        
    }


    MPI_Finalize();

    return 0;
}