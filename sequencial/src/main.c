// autor: Jardel Carvalho
// ano: 2019

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "arquivo.h"
#include "floyd_warshall.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        printf("erro: parâmetros insuficientes\n");
    }

    int N;
    float *m = matriz(argv[1], &N);
    if(!m) {
        printf("erro: problema na leitura do arquivo\n");
        return 0;
    }

    // medição de tempo
    clock_t t;
    t = clock();

    // algoritmo
    float *dist = floyd_warshall_m(m, N);

    // medição de tempo
    t = clock() - t;
    double t_res = ((double) t) / CLOCKS_PER_SEC;
	
    for(int i = 0; i < N * N; i++) {
        printf("%.2f ", dist[i]);
        if((i + 1) % N == 0) {
            printf("\n");
            continue;
        }
    }

    free(m);
    free(dist);

    printf("\nt = %.15lf\n", t_res);

    return 0;
}
