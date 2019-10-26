// autor: Jardel Carvalho
// ano: 2019

#ifndef _FOX_FLOYD_WARSHALL_H_
#define _FOX_FLOYD_WARSHALL_H_

#include <stdlib.h>
#include <math.h>

void inicia_matriz_fl_war(float *m, int N);
void fox_floyd_warshall(float *my_m, float *rcvd_m, float *fwres, int N);

#endif