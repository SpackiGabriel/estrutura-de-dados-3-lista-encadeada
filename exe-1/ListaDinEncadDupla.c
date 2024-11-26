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
    Passo a passo para remover:

    - Percorrer a lista até encontrar o elemento com a matrícula igual a mat ou até o nó ser nulo (fim da lista sem encontrar o elemento)
    - Ajustar o ponteiro do elemento anterior para o próximo elemento do elemento a ser removido

    Aqui consigo pensar em alguns

    - Caso especial: A lista tem mais de 1 elemento e a matrícula pertence ao primeiro elemento da lista
     - Ajustar o cabeçalho para o próximo elemento depois do nó encontrado
     - Ajustar o ponteiro do próximo elemento para NULL 
    
    - Caso especial: A lista tem mais de 1 elemento e a matrícula pertence ao último elemento da lista
     - Ajustar o ponteiro do elemento anterior para NULL

    - Caso especial: A lista só tem 1 elemento:
     - Remover esse elemento e ajustar o ponteiro da lista para NULL

    - Liberar o espaço de memória do elemento a ser removido
*/

int remover_lista_matricula(Lista* li, int mat) {
    if(li == NULL)
        return 0;

    Elem *no = *li;

    while(no != NULL && no->dados.matricula != mat) {
        no = no->prox;
    }

    if (no == NULL) { // Não encontrou o elemento com a matrícula
        return 0;
    }

    if (no->ant == NULL) { // Caso especial: A matrícula pertence ao primeiro elemento
        *li = no->prox; // Caso a lista só tenha 1 elemento, agora ele será NULL por conta dessa linha

        if (no->prox != NULL) { // Aqui eu valido que se a lista tem mais de 1 elemento, eu ajusto o ponteiro do próximo elemento para NULL
            no->prox->ant = NULL;
        }

    } 
    
    else if (no->prox == NULL) { // Caso especial: A matrícula pertence ao último elemento
        no->ant->prox = NULL;
    } 
    
    else { // Caso base: A matrícula pertence a um elemento no meio da lista
        no->ant->prox = no->prox;
        no->prox->ant = no->ant;
    }

    free(no);
    return 1;
}
