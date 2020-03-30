#include <stdio.h>
#include <stdlib.h>

struct no {
    int info;
    struct no * fesq;
    struct no * fdir;
};

typedef struct no * Arvore;

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
    printf("%d\n", r->info);
    mostra_in_ordem(r->fesq);
    mostra_in_ordem(r->fdir);
    
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
    mostra_pre_ordem(r->fesq);
    printf("%d\n", r->info);
    mostra_pre_ordem(r->fdir);
}

/* Recebe endereço da raiz de uma árvore e libera a memória da árvore
inteira. */
void libera(Arvore r) {
    if (r == NULL)
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
Arvore busca_BST(Arvore r, int alvo) {
   if(r == NULL){
      printf("alvo não encontrado ou arvore nula");
      return NULL; //arvore vazia
   }

   if(r->info == alvo){ //raiz contem alvo
      printf("numero encontrado! %d\n", r->info);
      return r;
   }

   if(alvo < r->info){
      printf("o numero eh menor. Buscando na esquerda\n");
      return busca_BST(r->fesq, alvo);
   } else{
        printf("o numero eh maior. buscando na direita\n");
        return busca_BST(r->fdir, alvo);
  }
}

int main() {
    Arvore esquerdo, direito, raiz, resultado;
    esquerdo = novo_no(7);
    direito = novo_no(15);
    direito->fesq = novo_no(14);
    raiz = novo_no(12);
    raiz->fesq = esquerdo;
    raiz->fdir = direito;
    
    mostra_pre_ordem(raiz);

    busca_BST(raiz, 150);
    libera(raiz);
    return 0;
}