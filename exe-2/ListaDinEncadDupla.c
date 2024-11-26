#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncadDupla.h" //inclui os Prot�tipos

//Defini��o do tipo lista
struct elemento{
    struct elemento *ant;
    struct aluno dados;
    struct elemento *prox;
};
typedef struct elemento Elem;

Lista* cria_lista(){
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li){
    if(li != NULL){
        Elem* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

int consulta_lista_pos(Lista* li, int pos, struct aluno *al){
    if(li == NULL || pos <= 0)
        return 0;
    Elem *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int consulta_lista_mat(Lista* li, int mat, struct aluno *al){
    if(li == NULL)
        return 0;
    Elem *no = *li;
    while(no != NULL && no->dados.matricula != mat){
        no = no->prox;
    }
    if(no == NULL)
        return 0;
    else{
        *al = no->dados;
        return 1;
    }
}

int insere_lista_final(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem *no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = NULL;
    if((*li) == NULL){//lista vazia: insere in�cio
        no->ant = NULL;
        *li = no;
    }else{
        Elem *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return 1;
}

int insere_lista_inicio(Lista* li, struct aluno al){
    if(li == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*li);
    no->ant = NULL;
    if(*li != NULL)//lista n�o vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return 1;
}

int remove_lista_inicio(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    *li = no->prox;
    if(no->prox != NULL)
        no->prox->ant = NULL;

    free(no);
    return 1;
}

int remove_lista_final(Lista* li){
    if(li == NULL)
        return 0;
    if((*li) == NULL)//lista vazia
        return 0;

    Elem *no = *li;
    while(no->prox != NULL)
        no = no->prox;

    if(no->ant == NULL)//remover o primeiro e �nico
        *li = no->prox;
    else
        no->ant->prox = NULL;

    free(no);
    return 1;
}

int tamanho_lista(Lista* li){
    if(li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_cheia(Lista* li){
    return 0;
}

int lista_vazia(Lista* li){
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}

void imprime_lista(Lista* li){
    if(li == NULL)
        return;
    Elem* no = *li;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");

        no = no->prox;
    }
}

/* 
    Passo a passo:

    - Caso especial: A lista está vazia:
     - Os ponteiros do meu nó serão nulos, pois não há outros elementos
     - O ponteiro da lista apontará para o novo nó


    - Percorrer a lista até encontrar a posição correta para inserir o novo nó (encontrar o nó que tem a matrícula maior que a matrícula do novo nó)

    - Caso 1: É o primeiro elemento:
     - O ponteiro anterior do novo nó será nulo
     - O ponteiro próximo do novo nó será o atual primeiro elemento da lista
    
    - Caso 2: É o último elemento:
     - Percorrer a lista até encontrar o último elemento (Preciso percorrer de novo porque a primeira vez que percorri o nó auxiliar ficou nulo)
     - O ponteiro anterior do novo nó será o último elemento da lista
     - O ponteiro próximo do novo nó será nulo
    
    - Caso 3: É um elemento intermediário:
     - O ponteiro prox do novo nó será o nó atual
     - O ponteiro ant do novo nó será o nó anterior ao atual
     - O ponteiro prox do nó anterior ao atual será o novo nó
     - O ponteiro ant do nó atual será o novo nó

*/
int insere_lista_ordenada(Lista* li, struct aluno al) {
    if(li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));

    if(no == NULL)
        return 0;

    no->dados = al;

    if ((*li) == NULL) { // Caso especial: A lista está vazia
        no->prox == NULL;
        no->ant = NULL;
        *li = no;
        return 1;
    }

    Elem* atual = *li;

    while (atual != NULL && atual->dados.matricula < al.matricula) {
        atual = atual->prox;
    }

    if (atual == *li) { // Inserir no início
        no->ant = NULL;
        no->prox = *li;

        (*li)->ant = no;
        *li = no;
    } 

    else if (atual == NULL) { // Inserir no final
        Elem *ultimo = *li;

        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }

        no->ant = ultimo;
        no->prox = NULL;

        ultimo->prox = no;
    } 

    else { // Inserir no meio
        no->prox = atual;
        no->ant = atual->ant;

        if (atual->ant != NULL) {
            atual->ant->prox = no;
        }

        atual->ant = no;
    }
}