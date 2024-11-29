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

void libera_lista(Lista* li) {
    if (li != NULL) {
        Elem* no = *li;
        Elem* temp;
        do {
            temp = no->prox;
            free(no);
            no = temp;
        } while (no != *li);
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

/*
    - Se a lista não estiver vazia, o novo nó é inserido após o último nó.
    - O ponteiro "ant" do novo nó aponta para o último nó da lista.
    - O ponteiro "prox" do último nó é atualizado para o novo nó.
    - O ponteiro "prox" do novo nó aponta para o primeiro nó.
*/

int insere_lista_final(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;

    no->dados = al;
    if (*li == NULL) {
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        Elem* ultimo = (*li)->ant;
        no->prox = *li;
        no->ant = ultimo;
        ultimo->prox = no;
        (*li)->ant = no;
    }

    return 1;
}

/*
    - Se a lista não estiver vazia, o novo nó é inserido antes do primeiro nó.
    - O ponteiro "prox" do novo nó aponta para o primeiro nó da lista.
    - O ponteiro "ant" do primeiro nó é atualizado para o novo nó.
    - O ponteiro da lista agora aponta para o novo nó.
*/

int insere_lista_inicio(Lista* li, struct aluno al) {
    if (li == NULL)
        return 0;

    Elem* no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return 0;

    no->dados = al;
    if (*li == NULL) {
        no->prox = no;
        no->ant = no;
        *li = no;
    } else {
        Elem* primeiro = *li;
        no->prox = primeiro;
        no->ant = primeiro->ant;
        primeiro->ant->prox = no;
        primeiro->ant = no;
        *li = no;
    }

    return 1;
}

/*
    - O primeiro nó é removido e o ponteiro da lista é atualizado para o próximo nó.
    - O ponteiro "ant" do novo primeiro nó é ajustado para o último nó.
*/
int remove_lista_inicio(Lista* li) {
    if (li == NULL)
        return 0;

    Elem* primeiro = *li;
    if (primeiro->prox == primeiro) {
        free(primeiro);
        *li = NULL;
    } else {
        Elem* ultimo = primeiro->ant;
        *li = primeiro->prox;
        primeiro->prox->ant = ultimo;
        ultimo->prox = primeiro->prox;
        free(primeiro);
    }

    return 1;
}

/* 
    - O último nó é removido e o ponteiro "ant" do novo último nó é ajustado para o penúltimo nó.
    - O ponteiro "prox" do novo último nó aponta para o primeiro nó.
*/

int remove_lista_final(Lista* li) {
    if (li == NULL)
        return 0;

    Elem* ultimo = (*li)->ant;
    if (ultimo == *li) {
        free(ultimo);
        *li = NULL;
    } else {
        Elem* penultimo = ultimo->ant;
        penultimo->prox = *li;
        (*li)->ant = penultimo;
        free(ultimo);
    }

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

/* 
    
    - Usamos o do while para imprimir todos os elementos:
        - Começamos pelo primeiro nó e imprimimos suas informações.
        - O laço continua até voltar ao primeiro nó (quando o nó atual for igual ao primeiro).
    
    - O do while é importante porque precisamos garantir que o primeiro nó seja impresso.
    - Dessa maneira podemos fazer nosso while baseado na condição de comparação com o primeiro nó (já que ele já foi impresso).
*/
void imprime_lista(Lista* li) {
    if (li == NULL)
        return;

    Elem* no = *li;
    do {
        printf("Matricula: %d\n", no->dados.matricula);
        printf("Nome: %s\n", no->dados.nome);
        printf("Notas: %f %f %f\n", no->dados.n1, no->dados.n2, no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    } while (no != *li);
}
