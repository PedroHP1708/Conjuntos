/*
Autoria:
    Frederico Scheffel Oliveira 15452718
    Pedro Henrique Perez Dias   15484075

Baseado no código disponibilizado pelo professor
*/

#include "set.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    SET *A, *B;
    int n_a, n_b, x;
    int op;
    int tipo;

    scanf("%d", &tipo);

    A = set_criar(tipo);
    B = set_criar(tipo);

    scanf("%d %d", &n_a, &n_b);

    for(int i = 0; i < n_a; i++){
        scanf("%d",&x);
        set_inserir(A, x);
    }

    for(int i = 0; i < n_b; i++){
        scanf("%d",&x);
        set_inserir(B, x);
    }

    scanf("%d", &op);

    int valor;  
    switch(op){
        case 1: {
            scanf("%d", &valor);
            if(set_pertence(A, valor))
                printf("Pertence");
            else
                printf("Nao pertence");

            break;
        }
        case 2: {
            SET* uniao = set_uniao(A, B);
            set_imprimir(uniao);
            set_apagar(&uniao);
            break;
        }
        case 3: {
            SET* interseccao = set_interseccao(A, B);
            set_imprimir(interseccao);
            set_apagar(&interseccao);
            break;
        }
        case 4: {
            scanf("%d", &valor);
            set_remover(A, valor);
            set_imprimir(A);
            break;
        }
    }

    set_apagar(&A);
    set_apagar(&B);
    return 0;
}
