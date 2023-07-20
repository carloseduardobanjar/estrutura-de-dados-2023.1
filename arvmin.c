#include<stdio.h>
#include<stdlib.h>

typedef struct {
    int vertice1;
    int vertice2;
    int peso;
} Aresta;

typedef struct {
    int vertice;
    int tam;
} Conjunto;

int find(int *conj, int x){
    if(x != conj[x]){
        conj[x] = find(conj, conj[x]);
    }
    return conj[x];

    // while(x != conj[x]){ //Baixa complexidade
    //     x = conj[x];
    // }
    // return conj[x];
}

void une(int *conj, int *tam, int a, int b){
    int c, d;
    
    if(a == b) return;

    c = find(conj, a);
    d = find(conj, b);
    if(tam[c] < tam[d]){
        conj[c] = d;
        tam[d] += tam[c];
    } else{
        conj[d] = c;
        tam[c] += tam[d];
    }
}

void descer(Aresta *heap, int nelem, int pos){
    int posFilho, posFilhoDir;
    Aresta tmp; 
    posFilho = 2 * pos + 1; //Filho da esquerda
    if(posFilho < nelem){
        posFilhoDir = posFilho + 1; //Filho da direita
        if(posFilhoDir < nelem){
            if(heap[posFilhoDir].peso < heap[posFilho].peso){
                posFilho = posFilhoDir;
            }
        }
        if(heap[pos].peso > heap[posFilho].peso){
            tmp = heap[pos];
            heap[pos] = heap[posFilho];
            heap[posFilho] = tmp;
            descer(heap, nelem, posFilho);
        }
    }
}

void removerMin(Aresta *heap, int *nelem){
    Aresta x;
    if(nelem > 0){
        *nelem = *nelem - 1;
        x = heap[0];
        heap[0] = heap[*nelem];
        descer(heap, *nelem, 0);
    }
}

void subir(Aresta *heap, int pos){
    int pai;
    Aresta tmp;
    if(pos != 0){
        pai = (pos - 1) / 2;
        if(heap[pai].peso > heap[pos].peso){
            tmp = heap[pos];
            heap[pos] = heap[pai];
            heap[pai] = tmp;
            subir(heap, pai);
        }
    }
}

int insere(Aresta *heap, int *tam, int *nelem){
    Aresta temp;
    scanf("%d %d %d", &temp.vertice1, &temp.vertice2, &temp.peso);
    heap[*nelem] = temp;
    subir(heap, *nelem);
    (*nelem)++;
}

int main(void){
    int n, m, i; //n vértices e m arestas
    int tam = 5;
    int nelem = 0;
    int pesoTotal = 0;
    int *ptrConjunto;
    int *ptrComprimento;
    Aresta *ptrHeap;
    Aresta min;
    scanf("%d %d", &n, &m);
    ptrConjunto = (int *) malloc(n * sizeof(int));
    ptrComprimento = (int *) malloc(n * sizeof(int));
    ptrHeap = (Aresta *) malloc(m * sizeof(Aresta));
    if(ptrHeap == NULL || ptrComprimento == NULL || ptrConjunto == NULL){
        printf("Sem espaço suficiente\n");
        return 1;
    }
    
    for(i = 0; i < m; i++){
        insere(ptrHeap, &tam, &nelem);
    }

    for(i = 1; i <= n; i++){
        ptrConjunto[i] = i;
        ptrComprimento[i] = 1; 
    }

    while(nelem > 0){
        min = ptrHeap[0];
        removerMin(ptrHeap, &nelem);
        if(find(ptrConjunto, min.vertice1) != find(ptrConjunto, min.vertice2)){
            pesoTotal += min.peso;
            une(ptrConjunto, ptrComprimento, min.vertice1, min.vertice2);
        } 
    }

    printf("%d\n", pesoTotal);
    return 0;
}
