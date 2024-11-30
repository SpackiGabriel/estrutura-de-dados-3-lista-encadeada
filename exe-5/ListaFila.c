#include <stdio.h>
#include <stdlib.h>

struct fila {
    int info;
    struct fila *prox;
    struct fila *ant;
};

struct nodesc {
    struct fila *ini;
    struct fila *fim;
};

typedef struct nodesc* noDesc;

noDesc* inicializa_noDesc() {
    noDesc* no = (noDesc*)malloc(sizeof(noDesc));  

    if (!no) return NULL;

    *no = (noDesc)malloc(sizeof(struct nodesc));  

    if (!(*no)) {
        free(no);
        return NULL;
    }

    (*no)->ini = NULL;
    (*no)->fim = NULL;

    return no;
}

/*
    - Atribui o valor do elemento ao novo nó
    - O novo nó será o último da fila, então seu próximo é NULL
    - Se a fila não estiver vazia, o antigo último nó aponta para o novo nó
    - Se a fila estiver vazia, o novo nó é o início da fila
    - Retorna 1 para indicar sucesso
*/
int enfileirar(noDesc *n, int elem) {
    struct fila *novo = (struct fila*)malloc(sizeof(struct fila));

    if (!novo) return 0;

    novo->info = elem;
    novo->prox = NULL;
    novo->ant = (*n)->fim;

    if ((*n)->fim) {
        (*n)->fim->prox = novo;
    } 
    
    else {
        (*n)->ini = novo;
    }

    (*n)->fim = novo;
    return 1;
}

/*
    - Armazena o nó a ser removido em uma variável temporária
    - Atualiza o início da fila
    - Se a fila não ficou vazia, o novo início não tem nó anterior
    - Se a fila ficou vazia, o fim também deve ser NULL
    - Libera o nó removido
    - Retorna 1 para indicar sucesso

*/

int desenfileirar(noDesc *n, int *elem) {
    if ((*n)->ini == NULL) return 0;

    struct fila *temp = (*n)->ini;
    *elem = temp->info;

    (*n)->ini = temp->prox;

    if ((*n)->ini) {
        (*n)->ini->ant = NULL;
    } 
    
    else {
        (*n)->fim = NULL;
    }

    free(temp);
    return 1;
}

int main() {
    noDesc* fila = inicializa_noDesc();

    enfileirar(fila, 10);
    enfileirar(fila, 20);
    enfileirar(fila, 30);

    int elem;
    while (desenfileirar(fila, &elem)) {
        printf("Desenfileirado: %d\n", elem);
    }

    free(fila);
    return 0;
}