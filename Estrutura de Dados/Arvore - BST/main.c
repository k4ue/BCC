#include <stdio.h>
#include <stdlib.h>


struct no {
    int info;           // chave
    struct no * fesq;   // endereço do filho esquerdo
    struct no * fdir;   // endereço do filho direito
    /* struct no * pai;    // endereço do pai */
};

typedef struct no * Arvore;

/* Faz alocação de um novo nó contendo o dado fornecido como parâmetro.
   Retorna o endereço (ponteiro) do nó criado. */
Arvore novo_no(int dado) {
    Arvore novo = (Arvore) malloc(sizeof(struct no));
    if (novo == NULL) {
        printf("Falha na alocacao de memoria.\n");
        exit(1);
    }
    novo->info = dado;
    novo->fesq = novo->fdir = NULL;
    return novo;
}

/* Recebe o endereço da raiz de uma árvore e imprime todo o seu conteúdo,
percorrendo a estrutura da forma "IN-ORDEM" */
void mostra_in_ordem(Arvore r) {
    if (r == NULL) {
        return;
    }
    printf("%d\n", r->info);    // mostra a informação da raiz
    mostra_in_ordem(r->fesq);   // mostra a sub-árvore esquerda
    mostra_in_ordem(r->fdir);   // mostra a sub-árvore direita
    
}

/* Recebe o endereço da raiz de uma árvore e imprime todo o seu conteúdo,
percorrendo a estrutura da forma "PRE-ORDEM"
    Ou seja:
        primeiro imprime tudo à esquerda
        em seguida o contéudo da raiz
        e por último tudo à direita */
void mostra_pre_ordem(Arvore r) {
    if (r == NULL) {
        return;
    }
    mostra_pre_ordem(r->fesq);  // mostra conteúdo da sub-árvore esquerda
    printf("%d\n", r->info);    // mostra conteúdo da raiz
    mostra_pre_ordem(r->fdir);  // mostra conteúdo da sub-árvore direita
}

/* Recebe endereço da raiz de uma árvore e libera a memória da árvore
inteira. */
void libera(Arvore r) {
    if (r == NULL)      // se o endereço for NULL não faço nada
        return;
    libera(r->fesq);    // libera toda a sub-árvore esquerda
    libera(r->fdir);    // libera toda a sub-árvore direita
    free(r);            // libera a própria raiz
}

/*  Essa função recebe o endereço da raiz de uma árvore e também um "alvo" para
procurar na árvore.
    Considerando que a árvore é do tipo BST (Árvore Binária de Busca), faz a
busca binária.
    Se algum nó contém o alvo, retorna o endereço desse nó.
    Caso contrário, retorna NULL. */

/* Custo: O(h), onde h é a altura da árvore */
Arvore busca_BST(Arvore r, int alvo) {
    if (r == NULL) {    // árvore vazia OU alvo não encontrado
        return NULL;
    }
    else if (r->info == alvo) { // raiz contém alvo!
        return r;
    }
    else if (r->info > alvo) { // raiz contém chave maior do que alvo
        return busca_BST(r->fesq, alvo);
    }
    else { // raiz contém chave menor do que alvo
        return busca_BST(r->fdir, alvo);
    }
}

/* versão compacta do código acima
Arvore busca_BST(Arvore r, int alvo) {
    if (r == NULL) return NULL;
    if (r->info == alvo) return r;
    if (r->info > alvo) return busca_BST(r->fesq, alvo);
    return busca_BST(r->fdir, alvo);
}
*/

/* EXERCÍCIO 1
    Escreva uma função que recebe o endereço da raiz de uma BST
    e encontra a MENOR CHAVE contida nos nós dessa árvore.*/
int minimo_BST(Arvore r){
  if(r == NULL) return -1;
  if(r->fesq == NULL) return r->info;
  else return minimo_BST(r->fesq);
}

/* EXERCÍCIO 2
    Escreva uma função que recebe o endereço da raiz de uma BST
    e encontra a MAIOR CHAVE contida nos nós dessa árvore.*/
int maximo_BST(Arvore r){
  if(r == NULL) return -1;
  if(r->fdir == NULL) return r->info;
  else return maximo_BST(r->fdir);
}

/* EXERCÍCIO 3
    Escreva uma função que recebe o endereço da raiz de uma árvore
    binária e retorna a ALTURA dessa árvore. */
unsigned altura(Arvore r){
  
  if(r == NULL) return -1;

  int altEsq = altura(r->fesq);
  int altDir = altura(r->fdir);

  if(altEsq < altDir){
    return altDir+1;
  } else {
    return altEsq+1;
  }
}


void insere_recursivo(Arvore raiz, Arvore novo) {
    if (raiz->info > novo->info) { // tenho que inserir à ESQUERDA da raiz
        if (raiz->fesq != NULL)
            insere_recursivo(raiz->fesq, novo);
        else
            raiz->fesq = novo;
    }
    else { // tenho que inserir à DIREITA da raiz
        if (raiz->fdir != NULL)
            insere_recursivo(raiz->fdir, novo);
        else
            raiz->fdir = novo;
    }
}

/* Insere dado "novo" na raiz.
Retorna 1 se for bem-sucedida, 0 caso contrário */
int insere_BST(Arvore raiz, int dado_novo) {
    Arvore novo;
    if (busca_BST(raiz, dado_novo) != NULL) {
        // elemento já existe na árvore!
        return 0;
    }
    novo = novo_no(dado_novo);
    insere_recursivo(raiz, novo);
    return 1;
}

void mostra_estrutura(Arvore raiz, int espaco) {
    int i;
    if (raiz == NULL) return;
    for (i = 0; i < espaco; i++) printf("-");
    printf("%d\n", raiz->info);
    mostra_estrutura(raiz->fesq, 4 + espaco);
    mostra_estrutura(raiz->fdir, 4 + espaco);
}


int main() {
    Arvore raiz, busca;
    
    // essa ordem de inserção gera árvore com altura 5
    // (o ótimo para 8 elementos é altura 4)
    raiz = novo_no(10);
    insere_BST(raiz, 9);
    insere_BST(raiz, 6);
    insere_BST(raiz, 8);
    insere_BST(raiz, 14);
    insere_BST(raiz, 7);
    insere_BST(raiz, 21);
    insere_BST(raiz, 18);
    
    // inserir em ordem crescente gera árvore horrível
    /* raiz = novo_no(6);
    insere_BST(raiz, 7);
    insere_BST(raiz, 8);
    insere_BST(raiz, 9);
    insere_BST(raiz, 10);
    insere_BST(raiz, 14);
    insere_BST(raiz, 18);
    insere_BST(raiz, 21);*/


    printf("pre-ordem:\n");
    mostra_pre_ordem(raiz);

    printf("\nestrutura:\n");
    mostra_estrutura(raiz, 0);

    busca = busca_BST(raiz, 14);
    printf("Encontrei o 14? %s\n", (busca == NULL) ? "NAO" : "SIM");
    busca = busca_BST(raiz, 12);
    printf("Encontrei o 12? %s\n", (busca == NULL) ? "NAO" : "SIM");
    busca = busca_BST(raiz, 10);
    printf("Encontrei o 10? %s\n", (busca == NULL) ? "NAO" : "SIM");
    busca = busca_BST(raiz, 8);
    printf("Encontrei o 8? %s\n", (busca == NULL) ? "NAO" : "SIM");

   

    printf("Chave de menor valor na arvore: %d\n", minimo_BST(raiz));

    printf("Chave de maior valor na arvore: %d\n", maximo_BST(raiz));

    printf("A altura da arvore eh: %d\n",altura(raiz));
    
    libera(raiz);
    // system("pause");
    return 0;
}
