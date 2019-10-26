// autor: Jardel Carvalho
// ano: 2019

#include "fox_floyd_warshall.h"

void inicia_matriz_fl_war(float *m, int N) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {   
            if(i == j) {
                // para este programa a diagonal principal é sempre zero
                m[i + i * N] = 0;
            } else if(m[i + j * N] == 0) {
                m[i + j * N] = INFINITY;
            } else {
                m[i + j * N] = m[i + j * N];
            }
        }
    }
}


void fox_floyd_warshall(float *my_m, float *rcvd_m, float *fwres_m, int N) {
    float s;
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {

            // posição da matriz de resultado recebe infinito
            fwres_m[j + i * N] = INFINITY;

            for(int k = 0; k < N; k++) {
                s = rcvd_m[k + i * N] + my_m[j + k * N];
                if(fwres_m[j + i * N] > s) {
                    fwres_m[j + i * N] = s;
                }
            }
        }
    }
}