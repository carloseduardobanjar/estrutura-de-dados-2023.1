#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int valor;
    struct No *proximo;
} No;

int main() {
  char linha[100];
  No **vetor;
  int qtd_vertices, qtd_arestas, k = 0, i;
  int * ordenacao, * grau_entrada;
  No * ptr, * ptr_aux;
  scanf("%d %d", &qtd_vertices, &qtd_arestas);
  getchar();
  vetor = (No **) malloc((qtd_vertices + 1) * sizeof(No *));
  ordenacao = (int *) malloc((qtd_vertices) * sizeof(int));
  grau_entrada = (int *) malloc((qtd_vertices + 1) * sizeof(int));
  for(i = 0; i < qtd_vertices; i++){
    fgets(linha, 100, stdin);
    char *token = strtok(linha, " ");
    while (token != NULL) { 
        int num = atoi(token);
        if(num != 0){
          if(vetor[i + 1] == NULL){
            ptr = (No*)malloc(sizeof(No));
            ptr->valor = num;
            ptr->proximo = NULL;
            vetor[i + 1] = ptr;
          } else{ 
            ptr = (No*)malloc(sizeof(No)); 
            ptr->valor = num;
            ptr->proximo = NULL;
            ptr_aux = vetor[i + 1];
            while(ptr_aux->proximo != NULL){
              ptr_aux = ptr_aux->proximo;
            }
            ptr_aux->proximo = ptr;
          }
        } else{
          vetor[i + 1] = NULL;
        }
        token = strtok(NULL, " "); // separar o próximo número da linha
    }
  }

  for(i = 1; i < qtd_vertices + 1; i++){ //Inicializa o vetor grau_entrada com os respectivos graus
    if(vetor[i] != NULL){
      ptr = vetor[i];
      while(ptr != NULL){
        grau_entrada[ptr->valor]++;
        ptr = ptr->proximo;
      }
    }
  }

  for(i = 1; i < qtd_vertices + 1; i++){ //Encontra os zeros no vetor grau_entrada
    if(grau_entrada[i] == 0){
      ordenacao[k++] = i;
    }
  }

  for(i = 0; i < qtd_vertices; i++){ //Encontra os vértices que foram virando zero
    if(ordenacao[i] != 0 ){
      ptr = vetor[ordenacao[i]];
      while(ptr != NULL){
        grau_entrada[ptr->valor]--;
        if(grau_entrada[ptr->valor] == 0){
          ordenacao[k++] = ptr->valor;
        }
        ptr = ptr->proximo;
      }
    }
  }

  for(i = 0; i < qtd_vertices; i++){
    printf("%d ", ordenacao[i]);
  }

  return 0;
}