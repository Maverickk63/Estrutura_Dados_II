#include <stdio.h>
#include <stdlib.h>

// Definição dos possíveis valores de cor
#define VERMELHO 0
#define PRETO 1

// Definição dos possiveis valores para rotação 
#define ESQUERDA 10
#define DIREITA 11

// Aluno : Yuri Salim CC6M

typedef struct no {
    int num, cor; // Valor do nó e sua cor
    struct no *esq, *dir, *pai; // Ponteiros para os filhos e o pai
} no;

// Funções utilizadas
no *novoNo(int num);
void rotacao(struct no **raiz, struct no *extra, int direcao);
void regrasRB(no **raiz, no *novo);
no* inserirNo(no *raiz, no *novo);
void insercao(no **raiz, int num);
void imprimeArvore(no *raiz);


int main() {
    // Main , possui apenas o menu que chama as funçoes para trabalhar com a arvore
    struct no *raiz = NULL;
    int opcao = 0;
    while(opcao != 3){
        printf("___________MENU___________\n");
        printf("Opcao 1 : Inserir No\n");
        printf("Opcao 2 : Imprimir Arvore\n");
        printf("Opcao 3 : Fechar\n");
        printf("__________________________\n");
        scanf("%d", &opcao);
        printf("__________________________\n");
        if(opcao == 1){
            int num;
            printf("Escolha um numero :");
            scanf("%d", &num);
            insercao(&raiz, num);
        }
        if(opcao == 2){
            imprimeArvore(raiz);
        }
    }
    return 0;
}

// Função para criar novo nó
no *novoNo(int num) {
    no *novo = malloc(sizeof(no));
    novo->num = num;
    novo->cor = VERMELHO; // por padrão nó novo é vermelho
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    return novo;
}

// Função responsavel pelas rotações
void rotacao(struct no **raiz, struct no *extra, int direcao) {
    // Todos os tipos de rotação são feitas por esta funcão unificando ela , uso do #DEFINE para evitar confusão e deixar mais facil a coompreensão
    if (direcao == ESQUERDA) { //rotação a esquerda
        // O no extra é ou o novo ou o avô do novo dependendo da situação
        struct no *temp = extra->dir; // No temporario para fazer rotacao
        extra->dir = temp->esq;
        if (temp->esq != NULL) {
            temp->esq->pai = extra;
        }
        temp->pai = extra->pai;
        if (extra->pai == NULL) {
            *raiz = temp; // caso de rotação na raiz
        } else if (extra == extra->pai->esq) {
            extra->pai->esq = temp;
        } else {
            extra->pai->dir = temp;
        }
        temp->esq = extra;
        extra->pai = temp;
    } else if (direcao == DIREITA) { //rotação a direita
        // mesmo funcionamento do metodo da esquerda porem "espelhado"
        struct no *temp = extra->esq;
        extra->esq = temp->dir;
        if (temp->dir != NULL) {
            temp->dir->pai = extra;
        }
        temp->pai = extra->pai;
        if (extra->pai == NULL) {
            *raiz = temp;
        } else if (extra == extra->pai->dir) {
            extra->pai->dir = temp;
        } else {
            extra->pai->esq = temp;
        }
        temp->dir = extra;
        extra->pai = temp;
    }
}

// Conjunto de regras para manter a árvore Red-Black (corrigir as cores, chamar as rotações quando necessário)
void regrasRB(no **raiz, no *novo) {
    // feito de forma iterativa com base no codigo do fork
    while (novo != *raiz && novo->pai->cor == VERMELHO) {
        // caminho se o no novo nao for raiz e seu pai é vermelho
        if (novo->pai == novo->pai->pai->esq) {
            // se ele for o "neto" da esquerda
            no *tio = novo->pai->pai->dir; // No filho da direita do pai do pai do novo (razao do nome tio)
            if (tio != NULL && tio->cor == VERMELHO) { // Realiza a correção de cores , vermelho repetido
                novo->pai->cor = PRETO;
                tio->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                novo = novo->pai->pai;
            } else { // Ocorre quando tem 2 filhos consecutivos a esquerda sem algum a direita para balancear , realiza as rotações
                if (novo == novo->pai->dir) {
                    novo = novo->pai;
                    rotacao(raiz, novo, ESQUERDA);
                }
                novo->pai->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                rotacao(raiz, novo->pai->pai, DIREITA);
            }
        } else {
            // Mesmo processo do primeiro if acima porem "espelhado" ("neto" da direita)
            no *tio = novo->pai->pai->esq;
            if (tio != NULL && tio->cor == VERMELHO) {
                novo->pai->cor = PRETO;
                tio->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                novo = novo->pai->pai;
            } else {
                if (novo == novo->pai->esq) {
                    novo = novo->pai;
                    rotacao(raiz, novo, DIREITA);
                }
                novo->pai->cor = PRETO;
                novo->pai->pai->cor = VERMELHO;
                rotacao(raiz, novo->pai->pai, ESQUERDA);
            }
        }
    }
    (*raiz)->cor = PRETO; // Garante que a raiz é de cor preta
}

no* inserirNo(no *raiz, no *novo) {
    // função de inserção padrão recursiva em arvores de busca, porem com a adição do valor pai , importante para o balanceamento da arvore
    if (raiz == NULL) {
        return novo;
    }
    if (novo->num < raiz->num) { // Menor vai para esquerda
        raiz->esq = inserirNo(raiz->esq, novo);
        raiz->esq->pai = raiz;
    } else{ // Maior ou Igual vai para a direita
        raiz->dir = inserirNo(raiz->dir, novo);
        raiz->dir->pai = raiz;
    }
    return raiz;
}

void insercao(no **raiz, int num){
    // Função criada para solucionar o problema de interação entre Regras RB que é iterativa com a inserir que é recursiva
    no *novo = novoNo(num); // Cria o No
    *raiz = inserirNo(*raiz, novo); // Passa o no para ser inserido
    regrasRB(raiz, novo); // Aplica as regras
}

void imprimeArvore(no *raiz){
    // Função para a impressão da arvore em pre ordem
    if(raiz != NULL){
        if(raiz->cor == 0){
            if(raiz->esq != NULL && raiz-> dir != NULL){
                printf("| Valor = %d | cor = Vermelho | Filho esquerdo = %d | Filho direita = %d |\n", raiz->num, raiz->esq->num, raiz->dir->num);
            }
            else if(raiz->esq == NULL && raiz-> dir != NULL){
                printf("| Valor = %d | cor = Vermelho | Filho esquerdo = NULL | Filho direita = %d |\n", raiz->num,  raiz->dir->num);
            }
            else if(raiz->esq != NULL && raiz-> dir == NULL){
                printf("| Valor = %d | cor = Vermelho | Filho esquerdo = %d | Filho direita = NULL |\n", raiz->num, raiz->esq->num);
            }
            else{
                printf("| Valor = %d | cor = Vermelho | Filho esquerdo = NULL | Filho direita = NULL |\n", raiz->num);
            }
        }
        else{
            if(raiz->esq != NULL && raiz-> dir != NULL){
                printf("| Valor = %d | cor = Preto | Filho esquerdo = %d | Filho direita = %d |\n", raiz->num, raiz->esq->num, raiz->dir->num);
            }
            else if(raiz->esq == NULL && raiz-> dir != NULL){
                printf("| Valor = %d | cor = Preto | Filho esquerdo = NULL | Filho direita = %d |\n", raiz->num,  raiz->dir->num);
            }
            else if(raiz->esq != NULL && raiz-> dir == NULL){
                printf("| Valor = %d | cor = Preto | Filho esquerdo = %d | Filho direita = NULL |\n", raiz->num, raiz->esq->num);
            }
            else{
                printf("| Valor = %d | cor = Preto | Filho esquerdo = NULL | Filho direita = NULL |\n", raiz->num);
            }
        }
        imprimeArvore(raiz->esq);
        imprimeArvore(raiz->dir);
    }
}
