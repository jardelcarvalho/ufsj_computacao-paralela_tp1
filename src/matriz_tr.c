// autor: Jardel Carvalho
// ano: 2019

#include "matriz_tr.h"

// int i = (rank % q) * (N / q) + N * l + a * ((N * N) / q);
// int f = ((rank % q) + 1) * (N / q) + N * l + a * ((N * N) / q);

float *submatriz(int rank, int N, int q, float *m) {
    int s = N / q;
    float *sm = malloc(s * s * sizeof(float));
    if(!sm) {
        printf("erro: problema ao alocar matriz\n");
        return NULL;
    }

    /* 
        faixa deve obrigatóriamente conter a parte inteira 
        da divisão rank / q como resultado
        se faixa for do tipo float vão surgir bugs
    */
    int faixa = rank / q;

    int k = 0;
    for(int l = 0; l < s; l++) {
        int x_coord = (rank % q) * (N / q);
        int y_coord = N * l;
        int offset = faixa * ((N * N) / q);

        int i = x_coord + y_coord + offset;
        int f = ((rank % q) + 1) * (N / q) + y_coord + offset;
        
        // for(int b = i; b < f; b++) printf("%.2f ", m[b]);
        // printf("\n");
        for(int t = i; t < f; t++) {
            sm[k] = m[t];
            k++;
        }
    }
    // printf("\n");

    return sm;
}