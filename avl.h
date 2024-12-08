/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075
*/

#ifndef _AVL_H
#define _AVL_H

    typedef struct avl AVL;

    // Função responsável por criar a árvore avl
    AVL *avl_criar(unsigned char tipo);

    // Função responsável por verificar se um elemento está na árvore avl
    bool avl_pertence(AVL *A, int elemento);

    // Função responsável por inserir um elemento na árvore avl
    bool avl_inserir (AVL *s, int elemento);

    // Função responsável por remover um elemento da árvore avl
    bool avl_remover(AVL *s, int elemento);

    // Função responsável por apagar a árvore avl
    void avl_apagar(AVL **s);

    // Função responsável por imprimir os nós da árvore avl
    void avl_imprimir(AVL *s);

    // Função responsável por fazer a união de 2 árvores avl
    AVL *avl_uniao(AVL *A, AVL *B);

    // Função responsável por fazer a intersecção entre 2 árvores avl 
    AVL *avl_interseccao(AVL *A, AVL *B);
  
#endif