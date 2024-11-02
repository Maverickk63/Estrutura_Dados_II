#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Aluno : Yuri Salim CC6m

// O codigo a seguir foi feito seguindo como base o codigo de arvore B presente no site : https://www.programiz.com/dsa/b-tree , encontrado no dia 30/10/2024 , a lógica foi seguida , modificações foram feitas e correção de erros causadas por essas modificações também foram realizadas junto da adição de comentarios para explicar o codigo

// Valor necessario para definir a ordem (neste caso sendo 3)
#define MAX 2

typedef struct no{
  int nums[MAX + 1],tamanho; // nums , guarda os numeros em si | tamanho , guarda o tamanho do vetor (quantos numeros ha)
  struct no *link[MAX + 1]; // Armazena ponteiros para as ligações dos nos (multiplos filhos, todas as ligações que o no faz)
}no;

no *raiz; //criando a raiz como variavel global

//Funções usadas
no *novoNo(int num, no *filho);
void inserirNoNo(int num, int pos, no *no_Atual, no *filho);
void quebrarONo(int val, int *pval, int pos, no *no_Atual, no *filho, no **novo);
bool promovedor(int val, int *pval, no *no_Atual, no **filho);
void insercao(int val);
void lerNo(no *no);

int main(){
  int opcao,num;
  do{
    printf("-------------------\n");
    printf("------ArvoreB------\n");
    printf("-------------------\n");
    printf("1 - Inserir\n");
    printf("2 - Imprimir árvore\n");
    printf("0 - Sair\n");
    printf("-------------------\n");
    scanf("%d", &opcao);
    printf("-------------------\n");
    if(opcao == 1){
      printf("Digite um número: ");
      scanf("%d", &num);
      insercao(num);
    }
    else if(opcao == 2){
      lerNo(raiz);
      printf("\n");
    }
  }while(opcao != 0);
  return 0;
}

// Cria um novo no para a arvore , preenche com os valores padrões e recebidos
no *novoNo(int num, no *filho){
  no *novo = (no *)malloc(sizeof(no));
  novo->nums[1] = num;
  novo->tamanho = 1;
  novo->link[0] = raiz;
  novo->link[1] = filho;
  return novo;
}

// Função para inserir dentro de um nó um numero
void inserirNoNo(int num, int pos, no *no_Atual, no *filho) {
  // Joga os valores para frente para abrir espaço para inserir o numero na POSição correta (marcado pela variavel pos)
  int x;
  for(x = no_Atual->tamanho; x >= pos; x--){
    no_Atual->nums[x + 1] = no_Atual->nums[x];
    no_Atual->link[x + 1] = no_Atual->link[x];
  }

  // Insere o novo valor e o novo link filho na posição correta
  no_Atual->nums[x + 1] = num;
  no_Atual->link[x + 1] = filho;

  // Aumenta o valor do tamanho para indicar o crescimento
  no_Atual->tamanho++;
}

// Função responsavel por quebrar o no quando ele estiver cheio
void quebrarONo(int num, int *pval, int pos, no *no_Atual, no *filho, no **novo) {
  int mediana, x;

  // Determina a posição mediana com base na posição de inserção
  if (pos >= MAX)
    mediana = MAX;
  else
    mediana = MAX-1;

  // Cria um novo no para armazenar metade dos elementos
  *novo = (no *)malloc(sizeof(no));
  x = mediana + 1;

  // Move a segunda metade dos valores e links do nó original para o novo no
  while (x <= MAX) {
    (*novo)->nums[x - mediana] = no_Atual->nums[x];
    (*novo)->link[x - mediana] = no_Atual->link[x];
    x++;
  }

  // Ajusta o tamanho dos nos
  no_Atual->tamanho = mediana;
  (*novo)->tamanho = MAX - mediana;

  // Insere o novo valor no no adequado (o original ou o novo)
  if (pos < MAX) {
    inserirNoNo(num, pos, no_Atual, filho);
  } else {
    inserirNoNo(num, pos - mediana, *novo, filho);
  }

  // Define o valor promovido e ajusta o link
  *pval = no_Atual->nums[no_Atual->tamanho];
  (*novo)->link[0] = no_Atual->link[no_Atual->tamanho];
  no_Atual->tamanho--;
}

// Função responsavel por chamar inserções e promover valores quando necessario
bool promovedor(int num, int *pval, no *no_Atual, no **filho) {
  int pos;

  // No nulo é folha , vai inserir o valor e retornar true
  if (!no_Atual) {
    *pval = num;
    *filho = NULL;
    return 1;
  }

  // Localiza a posição onde o valor deve ser inserido ou encontrado
  if (num < no_Atual->nums[1]) {
    pos = 0;
  } else {
    for (pos = no_Atual->tamanho; (num < no_Atual->nums[pos] && pos > 1); pos--); // se o valor for maior que o primeiro valor do no, ele passa por todos os valores do no testando
    if (num == no_Atual->nums[pos]) {
      printf("Sem repetir valor\n"); // Sem repetir valor
      return 0;
    }
  }

  // Chamada recursiva para inserir o valor no no filho apropriado
  if (promovedor(num, pval, no_Atual->link[pos], filho)) {
    // Se o no não está cheio, insere o valor diretamente
    if (no_Atual->tamanho < MAX) {
      inserirNoNo(*pval, pos, no_Atual, *filho);
    } else {
      // Caso contrário, divide o no e promove o valor médio
      quebrarONo(*pval, pval, pos, no_Atual, *filho, filho);
      return 1; // Indica que houve uma promoção para o nível superior
    }
  }
  return 0;
}

void insercao(int val) {
  bool promocao;
  int i;
  no *filho;

  // Tenta inserir o valor na árvore e recebe se ouve promoção ou não
  promocao = promovedor(val, &i, raiz, &filho);

  // Se o valor foi promovido, é necessário criar um novo no raiz
  if (promocao) {
    // Cria um novo no raiz que contém o valor promovido e o no filho resultante
    no *novo = novoNo(i, filho);
    // Atualiza a raiz da árvore para o novo no
    raiz = novo;
  }
}

//Função recursiva para ler a arvore
void lerNo(no *no){
    int i;
    if(no){ 
      for (i = 0; i <= no->tamanho; i++) { 
        lerNo(no->link[i]);// passa para o link do no no valor atual
        printf("%d ", no->nums[i]); // Imprime os valores do no atual
      }
      if(i != MAX + 1){ //Impede leitura de trechos inexistentes na memoria (estava causando erros)
        lerNo(no->link[i]);
      }
      }
}