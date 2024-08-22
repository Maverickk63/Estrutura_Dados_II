#include <stdio.h>
#include <stdlib.h>

// Aluno : Yuri Salim CC6M

typedef struct no{
    int num;
    struct no *dir;
    struct no *esq;
}no;

no *criar_no(int num){
  no *novo = (no*)malloc(sizeof(no));
  if (novo != NULL) {
      novo->num = num;
      novo->dir = NULL;
      novo->esq = NULL;
  }
  return novo;
}

no *inserir(no *raiz, int num){
  if (raiz == NULL){
      return criar_no(num);
  } else {
      if (num < raiz->num){
          raiz->esq = inserir(raiz->esq, num);
      } else {
          raiz->dir = inserir(raiz->dir, num);
      }
      return raiz;
  }
}

void pesquisa(no *raiz, int num){
  if (raiz == NULL){
      printf("Não encontrado\n");
  } else {
      if (num < raiz->num){
          pesquisa(raiz->esq, num);
      } else if (num > raiz->num){
          pesquisa(raiz->dir, num);
      } else {
          printf("Encontrado\n");
      }
  }
}

no *remover(no *raiz, int num){
  if (raiz == NULL){
    return raiz;
  }
  if (num < raiz->num){
    raiz->esq = remover(raiz->esq, num);
  } else if (num > raiz->num){
    raiz->dir = remover(raiz->dir, num);
  } else {
    // folha
    if (raiz->esq == NULL && raiz->dir == NULL){
      free(raiz);
      raiz = NULL;
    }
    // 1 filho
    else if (raiz->esq == NULL){
      no *temp = raiz->dir;
      free(raiz);
      raiz = temp;
    } else if (raiz->dir == NULL){
      no *temp = raiz->esq;
      free(raiz);
      raiz = temp;
    }
    // 2 filhos
    else{
      no *temp = raiz->dir;
      while (temp->esq != NULL){
        temp = temp->esq;
      }
      raiz->num = temp->num;
      raiz->dir = remover(raiz->dir, temp->num);
    }
  }
  return raiz;
}

int medirAltura(no *raiz, int alt){
  if (raiz == NULL){
    return -1;
  }
  else{
    if(raiz->esq == NULL && raiz->dir == NULL){
      return alt;
    }
    int esq = medirAltura(raiz->esq, alt+1);
    int dir = medirAltura(raiz->dir, alt+1);
    if(esq > dir){
      return esq;
    } else {
      return dir;
    }
  }
}

int main(void) {
  no *raiz = NULL;
  int opcao, num;
  do{
    printf("-----------------\n");
    printf("1 - Inserir\n");
    printf("2 - Pesquisar\n");
    printf("3 - Remover\n");
    printf("4 - Ver Altura\n");
    printf("0 - Sair\n");
    printf("-----------------\n");
    scanf("%d", &opcao);
    if(opcao == 1){
      printf("Digite um número: ");
      scanf("%d", &num);
      raiz = inserir(raiz, num);
    }
    if(opcao == 2){
      printf("Digite um número: ");
      scanf("%d", &num);
      pesquisa(raiz, num);
    }
    if(opcao == 3){
      printf("Digite um número: ");
      scanf("%d", &num);
      raiz = remover(raiz, num);
    }
    if(opcao == 4){
      printf("Altura: %d\n", medirAltura(raiz, 0));
    }
  }while(opcao != 0);
  return 0;
}
