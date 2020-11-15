#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_structure.h"

/* -- Percorre uma lista encadeada de forma linear retornando um novo Nodo de acordo
com o parametro de ordenação definido pelo Argumento "chose", este novo nodo retornado é criado
contendo as informações de um Nodo da lista que será desalocado ao termino da função*/
struct Node* pop_sort(struct List* ref,int *chose){

    struct Node* tmp;
    struct Node *traverse;
    tmp = ref->head_ref;
    traverse = tmp->next;

    if(*chose == 2){
        
        //Busca linear e retorna o elemento de menor valor sintático (ordem alfabética)
        while(traverse!=NULL){
            if(strcmp(tmp->nome,traverse->nome)>= 0){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    else if(*chose == 3){
        
        //Busca linear e retorna o elemento de maior valor sintático (ordem alfabética inversa)
        while(traverse!=NULL){
            if(strcmp(tmp->nome,traverse->nome)<= 0){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    else if(*chose == 4){

        //Busca linear e retorna o elemento de menor tamanho (palavra com menor numero de caracteres)
        while(traverse!=NULL){
            if(strlen(tmp->nome) >= strlen(traverse->nome)){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    traverse = tmp;
    tmp = new_node(tmp->nome); //cria-se um novo Nodo com as informações do Nodo "escolhido"
    
    /*Estrutura Condicional para Reendereçar os ponteiros da Lista encadeada em que o Nodo foi removido*/
    
    if(traverse == ref->head_ref){ //Se o Nodo escolhido for a cabeça da Fila
        
        if(ref->head_ref != ref->last_ref){

            ref->head_ref = ref->head_ref->next;
            ref->head_ref->prev = NULL;
        }
        else{
            ref->head_ref = ref->last_ref = NULL;
        }
    }
    else if(traverse == ref->last_ref && ref->last_ref !=ref->head_ref){ //Se o Nodo escolhido for o ultimo e não for o único presente na lista
        traverse->prev->next = NULL;
        ref->last_ref = ref->last_ref->prev;
        ref->last_ref->next = NULL;
    }
    else{
        traverse->prev->next = traverse->next;
        traverse->next->prev = traverse->prev;
    }
    free(traverse);
    return tmp;
}

/*Função que gerencia a ordenação da fila de impressão, convertendo a estrutura de dados da Lista em uma fila
para realizar a impressão e depois retornando a fila para estrutura de dados da Lista*/
void Queue_sort(struct List* ref, struct List* queue, int *chose){

    if(ref->head_ref == NULL){
        printf("Is empty\n");
        return;
    }
    queue = create_list();
    while(ref->head_ref !=NULL){
        struct Node* aux = pop_sort(ref,chose);
        enqueue(queue,aux);

    }
    print_Queue(queue);
    ref->head_ref = queue->head_ref;
    ref->last_ref = queue->last_ref;
    free(queue);
}
//Menu que engloba as funções de impressão e ordenação
void sort_menu(struct Agenda* agenda){

    printf("MENU DE ORDENAÇÃO\n");
    printf("1-Não ordernar\n");
    printf("2-Ordenar em ordem alfabética\n");
    printf("3-Ordem alfabética inversa\n");
    printf("4-Ordenar por quantidade de letras (crescente)\n");
    scanf("%d",&agenda->int_holder_2);
    getchar();
    switch (agenda->int_holder_2)
    {
    case 1:
        if(agenda->lista_sentinel->head_ref == NULL)break;
        print_Queue(agenda->lista_sentinel);
        break;
    case 2:
        Queue_sort(agenda->lista_sentinel,agenda->queue_sentinel,&agenda->int_holder_2);
        break;
    case 3:
        Queue_sort(agenda->lista_sentinel,agenda->queue_sentinel,&agenda->int_holder_2);
        break;
    case 4:
        Queue_sort(agenda->lista_sentinel,agenda->queue_sentinel,&agenda->int_holder_2);
        break;
    default:
        break;
    }
}
