#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    char *nome;
    struct No * filhoEsq;
    struct No * filhoDir;
} No;

void insere(No *ptrRaiz, int *bin, int qtdDigitos, char nome[50]){
    int i;
    No *temp, *novoNo;
    temp = ptrRaiz;
    for(i = 0; i < qtdDigitos; i++){
        if(bin[i] == 0){
            if(temp->filhoEsq != NULL)
                temp = temp->filhoEsq;
            else{
                novoNo = malloc(sizeof(No));
                if(novoNo == NULL){
                    printf("Sem memória");
                    exit(0);
                }
                novoNo->filhoEsq = NULL;
                novoNo->filhoDir = NULL;
                novoNo->nome = NULL;
                temp->filhoEsq = novoNo;
                temp = temp->filhoEsq;
            }
        } else{
            if(temp->filhoDir != NULL)
                temp = temp->filhoDir;
            else{
                novoNo = malloc(sizeof(No));
                if(novoNo == NULL){
                    printf("Sem memória");
                    exit(0);
                }
                novoNo->filhoEsq = NULL;
                novoNo->filhoDir = NULL;
                novoNo->nome = NULL;
                temp->filhoDir = novoNo;
                temp = temp->filhoDir;
            }
        }

        if(i + 1 == qtdDigitos){
            temp->nome = nome;
        }   
    }
}

char* busca(No *ptrRaiz, int *bin, int qtdDigitos){
    int i;
    No *temp;
    char *nome; 
    temp = ptrRaiz;
    nome = "N/A";
    for(i = 0; i < qtdDigitos && temp != NULL; i++){
        if(bin[i] == 0){
            temp = temp->filhoEsq;
        } else{
            temp = temp->filhoDir;
        }
        if(temp!= NULL && temp->nome != NULL){
            nome = temp->nome;
        }
    }
    return nome;
}

void decimalEmBinario(int num, int *array_binario, int indice) {
    int i;
    for (i = 7; i >= 0; i--) {
        array_binario[indice + i] = num % 2;
        num = num / 2;
    }
}

void decimalEmBinario32bits(int num1, int num2, int num3, int num4, int *array_binario){
    decimalEmBinario(num1, array_binario, 0);
    decimalEmBinario(num2, array_binario, 8);
    decimalEmBinario(num3, array_binario, 16);
    decimalEmBinario(num4, array_binario, 24);
}

int main(void){
    int *array_binario;
    int i, num1, num2, num3, num4, mascara, qtd;
    char *nome, *result;
    No *ptrRaiz;
    
    ptrRaiz = malloc(sizeof(No));
    array_binario = malloc(32 * sizeof(int));

    if(array_binario == NULL){
        printf("Sem memória");
        exit(0);
    }

    if(ptrRaiz == NULL){
        printf("Sem memória");
        exit(0);
    }

    ptrRaiz->filhoDir=NULL;
    ptrRaiz->filhoEsq=NULL;
    ptrRaiz->nome="N/A";

    scanf("%d", &qtd);

    for(i = 0; i < qtd; i++){
        nome = malloc(50 * sizeof(char));
        if(nome == NULL){
            printf("Sem memória");
            exit(0);
        }
        scanf("%d.%d.%d.%d/%d %[^\n]%*c", &num1, &num2, &num3, &num4, &mascara, nome);
        decimalEmBinario32bits(num1, num2, num3, num4, array_binario);
        insere(ptrRaiz, array_binario, mascara, nome);
    }

    for(i = 0; i < 3; i++){
        scanf("%d.%d.%d.%d", &num1, &num2, &num3, &num4);
        decimalEmBinario32bits(num1, num2, num3, num4, array_binario);
        result = busca(ptrRaiz, array_binario, 32);
        printf("%d.%d.%d.%d %s\n", num1, num2, num3, num4, result);
    }

    return 0;
}