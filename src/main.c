// autor: Jardel Carvalho
// ano: 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

#include "leitura.h"
#include "matriz_tr.h"
#include "comunicacao.h"

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log/valgrind-out.txt ./obj/main file/m.txt 
// mpirun --oversubscribe -np 9 main file/m.txt

// teste
void print_m(int rank, float *m_, int N) {
    printf("\n%d\n", rank);
    for(int i = 0; i < N * N; i++) {
        printf("%.2f ", m_[i]);
        if((i + 1) % N == 0) {
            printf("\n");
            continue;
        }
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

        /* 
            Verificando se a matriz é válida (condição de Fox)
            Para matrizes de dimensão N × N e P processos disponı́veis
            no sistema, deve existir um inteiro Q tal que P = Q^2 e N mod Q = 0 
        */
        int q = sqrt(num_procs);
        if(!(q * q == num_procs && N % q == 0)) {
            printf("erro: matriz inapropriada para o número de processos\n");
            free(m);
            MPI_Finalize();
            return 0;
        }

        // lê a própria submatriz
        float *my_sm = submatriz(my_rank, N, q, m);

        // envia submatrizes para os demais processos
        int t = N / q;
        t *= t;
        for(int i = 1; i < num_procs; i++) {
            float *sm = submatriz(i, N, q, m);
            if(!sm) {
                free(m);
                MPI_Finalize();
                return 0;
            }
            // enviando
            MPI_Send(&t, 1, MPI_FLOAT, i, 0, MPI_COMM_WORLD);
            MPI_Send(sm, t, MPI_FLOAT, i, 0, MPI_COMM_WORLD);

            // desalocando submatriz enviada
            free(sm);
        }

        // busca com quais processos haverá troca de dados
        int *p_ranks = dependencias(my_rank);
        if(!p_ranks) {
            free(my_sm);
            free(m);
            MPI_Finalize();
            return 0;
        }

        // iniciar floyd warshall
        // ...
        // ...


        // desaloca dados
        free(my_sm);
        free(m);
        free(p_ranks);
    } else {
        int t;
        float *my_sm;

        // recebe submatriz
        MPI_Recv(&t, 1, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        my_sm = malloc(t * sizeof(float));
        if(!my_sm) {
            printf("erro: problema ao receber submatriz");
            MPI_Finalize();
            return 0;
        }
        MPI_Recv(my_sm, t, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        // busca com quais processos haverá troca de dados
        int *p_ranks = dependencias(my_rank);
        if(!p_ranks) {
            free(my_sm);
            MPI_Finalize();
            return 0;
        }
        // 
        // entrar nas rotinas do floyd warshall
        // ...
        // ...


        // desalocando submatriz recebida
        free(my_sm);
        free(p_ranks);
    }

    MPI_Finalize();

    return 0;
}