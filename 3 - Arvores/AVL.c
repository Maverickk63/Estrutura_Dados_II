#include <stdio.h>
#include <stdlib.h>

// Aluno : Yuri Salim CC6M

typedef struct no{
  int num; // Valor do nó
  struct no *dir; // Filho a direita
  struct no *esq; // Filho a esquerda
  int alt; // Altura
}no;

// Funções criadas:
no *novoNo (int num);
int qualAltura (no *no);
int medirAltura(no *raiz, int alt);
no *rotacao(no *no, int lado);
no *aplicarAVL(no *no, int num);
no *inserir(no *raiz, int num);
no *remover(no *raiz, int num);
void printar(no *raiz);

int main(void){
  // Menu de interação
  no *raiz = NULL;
  int opcao = 1, num;
  do{
    printf("-----------------\n");
    printf("1 - Inserir\n");
    printf("2 - Imprimir arvore\n");
    printf("3 - Remover\n");
    printf("4 - Ver Altura\n");
    printf("0 - Sair\n");
    printf("-----------------\n");
    scanf("%d", &opcao);
    printf("-----------------\n");
    if(opcao == 1){
      printf("Digite um número: ");
      scanf("%d", &num);
      raiz = inserir(raiz, num);
    }
    else if(opcao == 2){
      printar(raiz);
    }
    else if(opcao == 3){
      printf("Digite um número: ");
      scanf(" %d", &num);
      raiz = remover(raiz, num);
    }
    else if(opcao == 4){
      printf("Altura da arvore = %d \n",medirAltura(raiz, 0));
    }
  }while(opcao != 0);
  return 0;
}

// Func responsavel pela criação de novos nós q serão inseridos na arvore (inserção e uma função separada)
no *novoNo (int num){
  no *novo = (no*)malloc(sizeof(no)); // Alocar memoria pro novo no
  novo->num = num;
  novo->dir = NULL;
  novo->esq = NULL;
  novo->alt = 0; //Altura padrão zero
  return novo; // nó pronto para inserção
}

// Essa função existe unica e exclusivamente para evitar erros caso em algum ponto do codigo ele tente pegar a altura de um nó que não existe
int qualAltura (no *no){
  if (no == NULL)
    return -1; //Nós não existentes (null apos a folha ou arvore vazia) tem altura -1
  else
    return no->alt; // altura adquirida de forma segura
}

// Função que realiza o calculo da altura de um nó , necessario para atualizar a altura dos nós que sera usado para o balanceamento AVL
int medirAltura(no *raiz, int alt){
  if (raiz == NULL){
    return -1; //Nó vazio = -1
  }
  else{
    if(raiz->esq == NULL && raiz->dir == NULL){
      return alt;
    }
    // Vai descendo na arvore até chegar em um nó folha
    int esq = medirAltura(raiz->esq, alt+1);
    int dir = medirAltura(raiz->dir, alt+1);
    if(esq > dir){ // Retorna o maio valor entre as alturas (se forem iguais retorna direita)
      return esq;
    } else {
      return dir;
    }
  }
}

//Função que realiza as rotações necessarias para balancear a arvore AVL
no *rotacao(no *no, int lado){
  struct no *novoNo;
  struct no *subArvore;
  if(lado == 2){
    // salva os dados em variaveis temporarias para não perder
    novoNo = no->dir;
    subArvore = novoNo->esq;

    // Trecho q realiza a rotação simples a esquerda
    novoNo->esq = no;
    no->dir = subArvore;
  } else if (lado == 1){
    // salva os dados em variaveis temporarias para não perder
    novoNo = no->esq;
    subArvore = novoNo->dir;

    // Trecho q realiza a rotação simples a direita
    novoNo->dir = no;
    no->esq = subArvore;
  }
  // Atualizar as alturas
  novoNo->alt = medirAltura(novoNo, 0);
  no->alt = medirAltura(no, 0);

  // Retorna o nó rodado
  return novoNo;
}

// Função que realiza o balanceamento de uma Arvore AVL
no *aplicarAVL(no *no, int num){
  // PRIMEIRO passo é checar se é null
  if(no == NULL){
    return no;
  }
  // Segundo passo é atualizar a altura de todos os nós
  no->alt = medirAltura(no, 0);
  // Terceiro passo é pegar o fator de balanceamento do nó atual
  int fb = qualAltura(no->esq) - qualAltura(no->dir);
  // Quarto passo é verificar se o nó esta desbalanceado
  if (fb > 1 && no->esq != NULL && num < no->esq->num) {
    // Rotação simples à esquerda
    return rotacao(no, 1);
  }
  else if (fb > 1 && no->esq != NULL && num > no->esq->num) {
    // rotação dupla a direita
    no->esq = rotacao(no->esq, 2);
    return rotacao(no, 1);
  }
  else if (fb < -1 && no->dir != NULL && num > no->dir->num) {
    // Rotação simples à direita
    return rotacao(no, 2);
  }
  else if (fb < -1 && no->dir != NULL && num < no->dir->num) {
    // Rotação dupla a esquerda
    no->dir = rotacao(no->dir, 1);
    return rotacao(no, 2);
  }
  // Caso a arvore ja esteja balanceada:
  return no;
}

// Função basica de inserção em uma arvore binaria de busca como incremento de fazer um teste de balanceamento no final
no *inserir(no *raiz, int num){
    //Função responsavel pela inserção 
  if (raiz == NULL){ // Se a raiz for nula, cria um novo nó
      return novoNo(num);
  } else
  {// Proximo passo : caminhar pela arvore ate achar o lugar certo para inserir o novo nó
      if (num < raiz->num)
          raiz->esq = inserir(raiz->esq, num); // Menor vai para esquerda
      else if (num > raiz->num)
          raiz->dir = inserir(raiz->dir, num); // Maior vai para direita
      else if (num == raiz->num)
          return raiz; // Não se insere nós repetidos em árvore AVL
      }
  // aplica as regras de balanceamento AVL para todos os nós
  return aplicarAVL(raiz, num);
}

// Função para remover um nó da arvore
no *remover(no *raiz, int num){
    // Passa pela arvore para remover o no 
  if (raiz == NULL){
    return raiz; // Voltar caso a arvore esteja vazia
  }
  if (num < raiz->num){
    raiz->esq = remover(raiz->esq, num);
  } else if (num > raiz->num){
    raiz->dir = remover(raiz->dir, num);
  } else {
      // parte para ajeitar a arvore apos remover o nó caso ____
    // seja uma folha
    if (raiz->esq == NULL && raiz->dir == NULL){
      free(raiz);
      raiz = NULL;
    }
    // tem 1 filho
    else if (raiz->esq == NULL){
      no *temp = raiz->dir;
      free(raiz);
      raiz = temp;
    } else if (raiz->dir == NULL){
      no *temp = raiz->esq;
      free(raiz);
      raiz = temp;
    }
    // tem 2 filhos
    else{
      no *temp = raiz->dir;
      while (temp->esq != NULL){
        temp = temp->esq;
      }
      raiz->num = temp->num;
      raiz->dir = remover(raiz->dir, temp->num);
    }
  }
  // Tudo acima é a função de remover para uma arvore de busca comum, abaixo esta a unica diferença:
  
  return aplicarAVL(raiz, num); // Retorna testando a arvore para garantir q ela siga as regras de balanceamento AVL
}

// Função para imprimir a arvore em pre ordem , com altura e filhos para verificar se esta corretamente seguindo as regras de arvore AVL
void printar(no *raiz){
  if (raiz == NULL)
    return;
  if(raiz->esq != NULL && raiz->dir != NULL)
    printf("[ Nó : %d | Filho Esquerdo : %d | Filho Direito : %d | Altura : %d ]\n", raiz->num, raiz->esq->num, raiz->dir->num, raiz->alt);
  else if(raiz->esq != NULL && raiz->dir == NULL)
    printf("[ Nó : %d | Filho Esquerdo : %d | Filho Direito : NULL | Altura : %d ]\n", raiz->num, raiz->esq->num, raiz->alt);
  else if(raiz->esq == NULL && raiz->dir != NULL)
    printf("[ Nó : %d | Filho Esquerdo : NULL | Filho Direito : %d | Altura : %d ]\n", raiz->num, raiz->dir->num, raiz->alt);
  else if(raiz->esq == NULL && raiz->dir == NULL)
    printf("[ Nó : %d | Filho Esquerdo : NULL | Filho Direito : NULL | Altura : %d ]\n", raiz->num, raiz->alt);
  printar(raiz->esq);
  printar(raiz->dir);
}
