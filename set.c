#include <stdlib.h>
#include "SET.h"
#include "avl.h"

struct set {
    void* estrutura;
    unsigned char tipo;
};

SET* set_criar(unsigned char tipo) {
    SET* novo_set = (SET*)malloc(sizeof(SET));
    if (novo_set != NULL) {
        novo_set->tipo = tipo;
        if (tipo == 1) 
        {
            novo_set->estrutura = avl_criar();
        }
        else 
        {
            //ed2
        }
    }
    return novo_set;
}
