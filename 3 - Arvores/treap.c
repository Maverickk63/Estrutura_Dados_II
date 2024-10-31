#include <stdio.h>
#include <stdlib.h>

// Aluno : Yuri Salim CC6M

// Arvore treap

typedef struct no{
    int num;
    int prioridade;
    struct no *pai ,*esq, *dir; // Estrutura da arvore treap
} no;

no* novoNo(int num, int prioridade){
    no* novo = (no*)malloc(sizeof(no)); // Cria o nó
    novo->num = num; // Preenche o nó com num
    novo->prioridade = prioridade; // e com prioridade
    novo->pai = novo->dir = novo->esq = NULL; // Pai e filhos nulos
    return novo;
}

no* rotacaoEsquerda(no* y){
    // função responsavel pela rotação a esquerda
    no* x = y->dir; // x recebe o filho direito de y
    y->dir = x->esq; // enquanto y recebe o filho esquerdo de x , fazendo com que X suba e Y desca
    // Atualização dos pais
    if(x->esq != NULL){
        x->esq->pai = y;
    }
    x->pai = y->pai;
    if(y->pai != NULL){
        if(y == y->pai->esq){
            y->pai->esq = x;
        }else{
            y->pai->dir = x;
        }
    }
    // Termino da rotação
    x->esq = y;
    y->pai = x;
    return x;
}

no* rotacaoDireita(no* x){
    // função responsavel pela rotação a direita , mesma coisa que a esquerda porem espelhado
    no* y = x->esq;
    x->esq = y->dir; // X sobe Y desce
    // Atualização dos pais
    if(y->dir != NULL){
        y->dir->pai = x;
    }
    y->pai = x->pai;
    if(x->pai != NULL){
        if(x == x->pai->esq){
            x->pai->esq = y;
        }else{
            x->pai->dir = y;
        }
    }
    // Termino
    y->dir = x;
    x->pai = y;
    return y;
}

no* inserirTreap(no* raiz, int num, int prioridade){
    if(raiz == NULL){
        return novoNo(num, prioridade); // quando acha o espaço para colocar cria o no
    }
    if(num < raiz->num){
        raiz->esq = inserirTreap(raiz->esq, num, prioridade);
        raiz->esq->pai = raiz; // O pai do no criado é a raiz(no anterior)
        if(raiz->esq->prioridade < raiz->prioridade){ // Realiza rotação com base na prioridade
            raiz = rotacaoDireita(raiz);
        }
    }else{// mesma coisa do trecho acima porem para direita
        raiz->dir = inserirTreap(raiz->dir, num, prioridade);
        raiz->dir->pai = raiz;
        if(raiz->dir->prioridade < raiz->prioridade){
            raiz = rotacaoEsquerda(raiz);
        }
    }
    return raiz;
}

void imprimirPreOrdem(no* raiz) {
    if (raiz != NULL) {
        printf("Valor: %d, Prioridade: %d\n", raiz->num, raiz->prioridade); // Imprime o valor e prioridade do nó atual
        imprimirPreOrdem(raiz->esq); // Visita o filho da esquerda
        imprimirPreOrdem(raiz->dir);  // Visita o filho da direita
    }
}

int main() {
    int arr[20] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    no *raiz = NULL;
    for(int i = 0; i< 20 ; i++){
        raiz = inserirTreap(raiz, arr[i], rand()%1000); // Insere os valores no treap e gera uma prioridade aleatoria de 0 a 1000
    }
    printf("Impressão em pre-ordem :\n"); // impressão
    imprimirPreOrdem(raiz);
    return 0;
}
