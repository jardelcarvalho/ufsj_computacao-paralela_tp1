// autor: Jardel Carvalho
// ano: 2019

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "mpi.h"

#include "leitura.h"
#include "matriz_tr.h"
#include "floyd_warshall_mmult.h"

#define P_MASTER_RANK 0

// valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=valgrind_log/valgrind-out.txt ./obj/main file/m.txt 
// mpirun --oversubscribe -np 4 main file/m.txt

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

    int q = sqrt(num_procs);

    if(my_rank == P_MASTER_RANK) {
        int N;
        float *m = matriz(argv[1], &N);
        if(!m) {
            MPI_Finalize();
            exit(EXIT_FAILURE);
        }

        // condição para uso do algoritmo de Fox
        if(!(q * q == num_procs && N % q == 0)) {
            printf("erro: condição de Fox não foi satisfeita\n");
            free(m);
            MPI_Finalize();
            exit(EXIT_FAILURE);
        }

        // inicia matriz com pesos infinitos onde (i = j) o peso é 0
        // inicialização Floyd-Warshall
        inicia_matriz_fl_war(m, N);

        // envia submatrizes para os demais processos
        int t = N / q;
        t *= t;
        for(int p = 0; p < num_procs; p++) {
            float *sm = submatriz(p, N, q, m);
            if(!sm) {
                free(m);
                MPI_Finalize();
                exit(EXIT_FAILURE);
            }
            // enviando valor de N
            MPI_Send(&N, 1, MPI_INT, p, 0, MPI_COMM_WORLD);

            // enviando submatriz
            MPI_Send(sm, t, MPI_FLOAT, p, 0, MPI_COMM_WORLD);

            // desalocando submatriz enviada
            free(sm);
        }

        // desaloca matriz base
        free(m);
    }

    // o código a partir daqui será executado por todos os processos
    // com exceção dos condicionais para P_MASTER_RANK

    // recebe dados enviados pelo master
    int N;
    MPI_Recv(&N, 1, MPI_INT, P_MASTER_RANK, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    int t = N / q;
    t *= t;
    float *my_sm = malloc(t * sizeof(float));
    if(!my_sm) {
        printf("erro: problema ao receber submatriz");
        free(my_sm);
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    MPI_Recv(my_sm, t, MPI_FLOAT, P_MASTER_RANK, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

    // tamanho de uma dimensão da submatriz
    int sm_dim = sqrt(t);

    // aloca matrizes auxiliares
    float *m_a = malloc(t * sizeof(float));
    float *m_b = malloc(t * sizeof(float));
    float *m_res = malloc(t * sizeof(float));
    if(!m_a || !m_b || !m_res) { // TODO: resolver esses frees
        printf("erro: problema ao alocar matrizes auxiliares\n");
        free(my_sm);
        MPI_Finalize();
        exit(EXIT_FAILURE);
    }
    memcpy(m_res, my_sm, t * sizeof(float));

    // rotinas do Floyd-Warshall usando algorítmo de Fox
    int u, r = my_rank / q;
    int rank_acima = (my_rank + q * (q - 1)) % num_procs;
    int rank_abaixo = (my_rank + q) % num_procs;

    for(int f = 1; f < N; f *= 2) {

        for(int i = 0; i < t; i++) {
            m_b[i] = my_sm[i];
        }

        for(int step = 0; step < q; step++) {
            u = (r + step) % q;

            if(u == my_rank % q) {
                // enviando submatriz escolhida para demais processos da linha
                for(int sp = q * r; sp < q * r + q; sp++) {
                    MPI_Send(my_sm, t, MPI_FLOAT, sp, 0, MPI_COMM_WORLD);
                }
            }

            // recebendo submatriz u da sua linha
            MPI_Recv(m_a, t, MPI_FLOAT, r * q + u, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // Floyd-Warshall
            fox_floyd_warshall(m_a, m_b , m_res, sm_dim);

            // envia própria matriz para processo da linha de cima
            MPI_Send(m_b, t, MPI_FLOAT, rank_acima, 0, MPI_COMM_WORLD);

            // recebe matriz do processo da linha de baixo
            MPI_Recv(m_b, t, MPI_FLOAT, rank_abaixo, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // if(u == my_rank % q)
            // printf("rank: %d\nintervalo: %d <= %d < %d\nenviou: sim\nrecebeu de: %d\nrank acima: %d\nrank abaixo: %d\n\n",
            // my_rank, q * r, my_rank, q * r + q, r * q + u, rank_acima, rank_abaixo);
            // else
            // printf("rank: %d\nintervalo: %d <= %d < %d\nenviou: não\nrecebeu de: %d\nrank acima: %d\nrank abaixo: %d\n\n",
            // my_rank, q * r, my_rank, q * r + q, r * q + u, rank_acima, rank_abaixo);
        }
        // break;

        for(int i = 0; i < t; i++) {
            my_sm[i] = m_res[i];
        }
    }

    // envia submatriz para o master
    MPI_Send(m_res, t, MPI_FLOAT, P_MASTER_RANK, 0, MPI_COMM_WORLD);

    // master recebe e agrupa submatrizes
    if(my_rank == P_MASTER_RANK) {
        float *m = malloc(N * N * sizeof(float));
        if(!m) {
            printf("erro: problema ao agrupar as submatrizes\n");
            free(m_a);
            free(m_b);
            free(m_res);
            free(my_sm);
            MPI_Finalize();
            exit(EXIT_FAILURE);
        }
        for(int p = 0; p < num_procs; p++) {
            MPI_Recv(m_res, t, MPI_FLOAT, p, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            encaixa(m_res, m, N, q, p);
            // print_m(p, m_res, sqrt(t));
            // printf("\n");
        }
        print_m(my_rank, m, N);
        printf("\n");
        
        free(m);
    }

    // desalocando dados
    free(m_a);
    free(m_b);
    free(m_res);
    free(my_sm);

    MPI_Finalize();

    return 0;
}