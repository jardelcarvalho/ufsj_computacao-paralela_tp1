#include "leitura.h"

int *matriz(char *caminho, int *N) {
    int *m;

    FILE *f = fopen(caminho, "r");
    if(!f) {
        printf("problema na leitura de %s", caminho);
        return NULL;
    }

    // caminha até o fim do arquivo e conta os bytes
    fseek(f, 0L, SEEK_END);
    int n_bytes = ftell(f);
    rewind(f);
    // salva o arquivo em um vetor
    char bytes[n_bytes + 1];
    fread(bytes, 1, n_bytes, f);
    bytes[n_bytes] = '\0';

    // caminha até a primeira quebra de linha
    int i = 0;
    for(; bytes[i] != '\n'; i++);
    bytes[i] = '\0';
    i++;
    
    // converte substring que contém o valor de N
    // aloca a matriz
    *N = atoi(bytes);
    m = malloc((*N * *N) * sizeof(int));
    int k = 0;

    // grava valores da matriz no vetor
    int j = i;
    for(; bytes[i] != '\0'; i++) {
        if(bytes[i] == ' ' || bytes[i] == '\n') {
            bytes[i] = '\0';
            int v = atoi(bytes + j);
            m[k] = v;
            k++;
            j = i + 1;
        }
    }
    
    fclose(f);

    return m;
}