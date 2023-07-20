#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int particiona(int vetor[], int inicio, int fim){
    int pos, pivot, temp;
    int i = inicio + 1;
    int j = fim - 1;
    srand(time(NULL));
    pos = (rand() % ((fim - 1) - inicio + 1)) + inicio;
    pivot = vetor[pos];
    vetor[pos] = vetor[inicio];
    vetor[inicio] = pivot;
    while(i <= j){
        while(i < fim && vetor[i] <= pivot){
            i++;
        }
        while(j > inicio && vetor[j] >= pivot){ 
            j--;
        }
        if(i < j){
            temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp; 
        }
    }
    vetor[inicio] = vetor[j];
    vetor[j] = pivot;
    return j;
}

int qSelect(int vetor[], int inicio, int fim, int k){
    int pospivot;
    if(fim - inicio == 1){
        return vetor[inicio];   
    }
    pospivot = particiona(vetor, inicio, fim);
    if(pospivot == k)
        return vetor[pospivot];
    else {
        if(k < pospivot){
            qSelect(vetor, inicio, pospivot, k);
        }
        else {
            qSelect(vetor, pospivot + 1, fim, k);
        }
    }
}

int main(int argc, char *argv[]){
    if(argc != 3){
        printf("Erro. Entrar com k");
    }
    int k = atoi(argv[2]) - 1;
    int len = 5, m = 0, num, pos;
    int *v;
    v = malloc (len * sizeof (int));    
    while(scanf("%d", &num) != EOF)
    {
        if(m < len){
            v[m++] = num;
        }
        else{
            len = len * 2;
            v = realloc (v, len * sizeof (int));
            v[m++] = num;
        }
    }
    if(k < m){
        pos = qSelect(v, 0, m, k);
        printf("%d", pos);
    } else{
        printf("A posição pedida não existe nesse array\n");
    }
    return 0;
}