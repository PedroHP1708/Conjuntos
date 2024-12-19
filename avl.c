/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "avl.h"

#ifndef STRUCTS_
    #define STRUCTS_
    typedef struct no NO;

    // Define a struct do nó da árvore
    struct no {
        int chave;
        NO *esq;
        NO *dir;
        int altura;  // Altura da subárvore
        int fb;      // Fator de balanceamento (FB)
    };

    // Define a struct da árvore avl
    struct avl {
        NO *raiz;
    };
#endif

// Função para obter a altura de um nó
int avl_altura_no(NO* raiz) {
    if (raiz == NULL)
        return 0;

    return raiz->altura;
}

// Função para calcular o fator de balanceamento (FB) de um nó
int avl_calcular_fb(NO *raiz) {
    if (raiz == NULL)
        return 0;

    return avl_altura_no(raiz->esq) - avl_altura_no(raiz->dir);
}

// Função para criar um nó, com base na chave especificada
NO* avl_cria_no(int chave) {
    NO *no = (NO *) malloc(sizeof(NO));
    if (no != NULL) {
        no->chave = chave;
        no->esq = NULL;
        no->dir = NULL;
        no->altura = 1;  // Altura de um nó recém-criado é 1
        no->fb = 0;      // Fator de balanceamento inicial é 0
    }
    return no;
}

// Função para criar a árvore AVL
AVL* avl_criar(void) {
    AVL *arvore = (AVL *) malloc(sizeof(AVL));
    if (arvore != NULL)
        arvore->raiz = NULL;

    return arvore;
}

// Função auxiliar para liberar memória de cada nó
void avl_apagar_aux(NO *raiz) {
    if (raiz != NULL) {
        avl_apagar_aux(raiz->esq);
        avl_apagar_aux(raiz->dir);
        free(raiz);
    }
}

// Função para apagar a árvore, que consequentemente acaba apagando todos os nós
void avl_apagar(AVL **arvore) {
    avl_apagar_aux((*arvore)->raiz);
    free(*arvore);
    *arvore = NULL;
}

// Função para rotacionar à direita
NO* rodar_direita(NO *a) {
    NO *b = a->esq;
    a->esq = b->dir;
    b->dir = a;

    // Atualizando altura dos nós
    a->altura = 1 + (avl_altura_no(a->esq) > avl_altura_no(a->dir) ? avl_altura_no(a->esq) : avl_altura_no(a->dir));
    b->altura = 1 + (avl_altura_no(b->esq) > avl_altura_no(b->dir) ? avl_altura_no(b->esq) : avl_altura_no(b->dir));

    // Atualizando os fatores de balanceamento
    a->fb = avl_calcular_fb(a);
    b->fb = avl_calcular_fb(b);

    return b;
}

// Função para rotacionar à esquerda
NO* rodar_esquerda(NO *a) {
    NO *b = a->dir;
    a->dir = b->esq;
    b->esq = a;

    // Atualizando altura dos nós
    a->altura = 1 + (avl_altura_no(a->esq) > avl_altura_no(a->dir) ? avl_altura_no(a->esq) : avl_altura_no(a->dir));
    b->altura = 1 + (avl_altura_no(b->esq) > avl_altura_no(b->dir) ? avl_altura_no(b->esq) : avl_altura_no(b->dir));

    // Atualizando os fatores de balanceamento
    a->fb = avl_calcular_fb(a);
    b->fb = avl_calcular_fb(b);

    return b;
}

// Função para rotacionar à esquerda e depois à direita (esq-dir)
NO* rodar_esquerda_direita(NO *a) {
    a->esq = rodar_esquerda(a->esq);
    return rodar_direita(a);
}

// Função para rotacionar à direita e depois à esquerda (dir-esq)
NO* rodar_direita_esquerda(NO *a) {
    a->dir = rodar_direita(a->dir);
    return rodar_esquerda(a);
}

// Função de inserção de nós na árvore.
// Atua como auxiliar da função principal desta operação do TAD avl
NO* avl_inserir_no(NO *raiz, int chave) {
    if (raiz == NULL)
        return avl_cria_no(chave);

    if (chave < raiz->chave) {
        raiz->esq = avl_inserir_no(raiz->esq, chave);
    } 
    else if (chave > raiz->chave) {
        raiz->dir = avl_inserir_no(raiz->dir, chave);
    }
    else {
        return raiz;  // Não insere valores repetidos, facilita a operação de união
    }

    // Atualizando a altura do nó
    raiz->altura = 1 + (avl_altura_no(raiz->esq) > avl_altura_no(raiz->dir) ? avl_altura_no(raiz->esq) : avl_altura_no(raiz->dir));

    // Calculando o fator de balanceamento (FB)
    raiz->fb = avl_calcular_fb(raiz);

    // Verificando e realizando as rotações conforme o FB
    if (raiz->fb > 1 && chave < raiz->esq->chave) {
        return rodar_direita(raiz);
    }
    if (raiz->fb < -1 && chave > raiz->dir->chave) {
        return rodar_esquerda(raiz);
    }
    if (raiz->fb > 1 && chave > raiz->esq->chave) {
        return rodar_esquerda_direita(raiz);
    }
    if (raiz->fb < -1 && chave < raiz->dir->chave) {
        return rodar_direita_esquerda(raiz);
    }

    return raiz;
}

// Função para inserir um valor na árvore AVL.
// Função principal responsável por essa operação. Pode ser acessada externamente. 
bool avl_inserir(AVL *arvore, int chave) {
    if (arvore == NULL) 
        return false;
    arvore->raiz = avl_inserir_no(arvore->raiz, chave);
    return true;
}

// Função para encontrar o nó com o maior valor da subárvore. É utilizada na remoção de nós.
NO* avl_max_dir(NO* raiz) {
    // Loop para chegar ao valor mais à direita da árvore (maior valor). 
    while (raiz->dir != NULL) 
        raiz = raiz->dir;

    return raiz;
}

// Função para remover um nó da árvore
// Atua como auxiliar da função principal desta operação do TAD avl
NO* avl_remover_no(NO* raiz, int chave) {
    if (raiz == NULL)
        return raiz;

    if (chave < raiz->chave) {
        raiz->esq = avl_remover_no(raiz->esq, chave);
    } else if (chave > raiz->chave) {
        raiz->dir = avl_remover_no(raiz->dir, chave);
    } else {
        if (raiz->esq == NULL || raiz->dir == NULL) {
            NO *temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else {
                *raiz = *temp;
            }
            free(temp);
        } else {
            NO *temp = avl_max_dir(raiz->esq);
            raiz->chave = temp->chave;
            raiz->esq = avl_remover_no(raiz->esq, temp->chave);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + (avl_altura_no(raiz->esq) > avl_altura_no(raiz->dir) ? avl_altura_no(raiz->esq) : avl_altura_no(raiz->dir));

    // Calculando o fator de balanceamento (FB)
    raiz->fb = avl_calcular_fb(raiz);

    // Verificando e realizando as rotações conforme o FB
    // Caso 1: Desbalanceamento à esquerda (esq-esq)
    if (raiz->fb > 1 && avl_calcular_fb(raiz->esq) >= 0) {
        return rodar_direita(raiz);
    }

    // Caso 2: Desbalanceamento à direita (dir-dir)
    if (raiz->fb < -1 && avl_calcular_fb(raiz->dir) <= 0) {
        return rodar_esquerda(raiz);
    }

    // Caso 3: Desbalanceamento à esquerda e à direita (esq-dir)
    if (raiz->fb > 1 && avl_calcular_fb(raiz->esq) < 0) {
        return rodar_esquerda_direita(raiz);
    }

    // Caso 4: Desbalanceamento à direita e à esquerda (dir-esq)
    if (raiz->fb < -1 && avl_calcular_fb(raiz->dir) > 0) {
        return rodar_direita_esquerda(raiz);
    }

    return raiz;
}

// Função para remover um valor da árvore
// Função principal responsável por essa operação. Pode ser acessada externamente. 
bool avl_remover(AVL *arvore, int chave) {
    if (arvore == NULL) 
        return false;

    arvore->raiz = avl_remover_no(arvore->raiz, chave);
    return true;
}

// Função para imprimir os nós da árvore em ordem
// Atua como auxiliar da função principal desta operação do TAD avl
void printEmOrdem(NO* no) {
    if (no != NULL) {
        printEmOrdem(no->esq);
        printf("%d ", no->chave);
        printEmOrdem(no->dir);
    }
}

// Função para imprimir a árvore em ordem
// Função principal responsável por essa operação. Pode ser acessada externamente. 
void avl_imprimir(AVL* arvore) {
    if (arvore == NULL || arvore->raiz == NULL)
        return;

    printEmOrdem(arvore->raiz);
    printf("\n");
}

// Função responsável pela verificação da chave em cada subárvore do nó
// Atua como auxiliar da função principal desta operação do TAD avl
bool avl_pertence_aux(NO* raiz, int chave) {
    if (raiz == NULL)
        return false;

    if (raiz->chave == chave)
        return true;
    
    if (chave < raiz->chave)
        return avl_pertence_aux(raiz->esq, chave);
    else
        return avl_pertence_aux(raiz->dir, chave);
}

// Função para verificação do pertencimento de um item na árvore.
// Função principal responsável por essa operação. Pode ser acessada externamente. 
bool avl_pertence(AVL* arvore, int chave) {
    if (arvore == NULL || arvore->raiz == NULL)
        return false;
    return avl_pertence_aux(arvore->raiz, chave);
}

// Função responsável por percorrer cada subárvore do nó, inserindo os valores na subárvore de união
// Atua como auxiliar da função principal desta operação do TAD avl
void avl_uniao_aux(AVL* uniao, NO* origem) {
    if (origem == NULL) 
        return;

    // Insere o nó atual na árvore destino
    avl_inserir(uniao, origem->chave);

    // Continua para as subárvores esquerda e direita
    avl_uniao_aux(uniao, origem->esq);
    avl_uniao_aux(uniao, origem->dir);
}

// Função para operação de união dos valores de 2 árvores.
// Função principal responsável por essa operação. Pode ser acessada externamente. 
AVL* avl_uniao(AVL* a, AVL* b) {
    if (a == NULL || b == NULL) 
        return NULL;

    // Cria a árvore de união
    AVL* uniao = avl_criar();

    // Copia elementos de 'a' para 'uniao'
    avl_uniao_aux(uniao, a->raiz);

    // Copia elementos de 'b' para 'uniao'
    avl_uniao_aux(uniao, b->raiz);

    return uniao;
}

// Função responsável por percorrer cada subárvore do nó, inserindo os valores na subárvore de intersecção
// Atua como auxiliar da função principal desta operação do TAD avl
void avl_interseccao_aux(AVL* destino, NO* origem, NO* referencia) {
    if (origem == NULL) 
        return;

    // Adiciona somente se o elemento de origem estiver na referência
    if (avl_pertence_aux(referencia, origem->chave)) {
        avl_inserir(destino, origem->chave);
    }

    // Continua para os subárvores esquerda e direita
    avl_interseccao_aux(destino, origem->esq, referencia);
    avl_interseccao_aux(destino, origem->dir, referencia);
}

// Função para operação de união dos valores de 2 árvores.
// Função principal responsável por essa operação. Pode ser acessada externamente.
AVL* avl_interseccao(AVL* a, AVL* b) {
    if (a == NULL || b == NULL) 
        return NULL;

    // Criação da árvore de intersecção
    AVL* interseccao = avl_criar();

    // Adiciona à interseção os elementos que estão em 'a' e também em 'b'
    avl_interseccao_aux(interseccao, a->raiz, b->raiz);

    return interseccao;
}
