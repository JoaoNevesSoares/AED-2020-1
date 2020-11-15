#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"

//aloca uma lista na memoria e retorna o endereço
struct List* create_list(){

    struct List* tmp = (struct List*)malloc(1*sizeof(struct List));
    tmp->head_ref = NULL;
    tmp->last_ref = NULL;
    return tmp;
}


//Cria um novo node contendo um nome
struct Node* new_node(char* nome){

    struct Node* tmp = (struct Node*)malloc(1*sizeof(struct Node));
    stpcpy(tmp->nome,nome);
    tmp->next = tmp->prev = NULL;
    return tmp;
}
//Adiciona elementos no fim da lista
void append(struct List* ref,struct Node* new_node){

    struct Node* traverse;
    traverse = ref->head_ref;
    if(ref->head_ref == NULL){
        ref->head_ref = ref->last_ref = new_node;
        return;
    }
    while(traverse->next !=NULL){
        traverse = traverse->next;
    }
    new_node->prev = traverse;
    traverse->next = new_node;
    ref->last_ref  = traverse->next;
    return;
}
//Busca Linear na lista
struct Node* search(struct List* reference, char nome[]){ 
    
        struct Node* traverse = reference->head_ref;

        while(traverse!=NULL && strcmp(traverse->nome,nome)!=0)
        traverse = traverse->next;
        return traverse;
}

//remove um nome da estrutura de dados da lista
void remove_nome(struct List* reference,char nome[]){

    struct Node* tmp = search(reference,nome);
    if(tmp == reference->head_ref){
        reference->head_ref = reference->head_ref->next;
    }
    else if(tmp == reference->last_ref){
        reference->last_ref = reference->last_ref->prev;
        reference->last_ref->next = NULL;
    }
    else if(tmp == NULL){
        printf("Nome inserido não existe no Banco de dados da Agenda\n");
        return;
    }
    else{
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
    }
    printf("Nome removido com sucesso\n");
    free(tmp);
}

//  !Função implementada porém não utilizada, (substituída por print_Queue() )
void show_queue(struct List* ref){
    struct Node* traverse = ref->head_ref;
    for(;traverse!=NULL;traverse = traverse->next){
        printf("%s\n",traverse->nome);
    }
}


struct Node* dequeue(struct List* queue_ref){
    struct Node* tmp;
    tmp = queue_ref->head_ref;
    if(queue_ref->head_ref->next == NULL){
        queue_ref->head_ref = NULL;
        queue_ref->last_ref = NULL;
     }
    else{
    queue_ref->head_ref->next->prev = NULL;
    queue_ref->head_ref = queue_ref->head_ref->next;
    }
    return tmp;
}

void enqueue(struct List* queue_ref, struct Node* new_node){
    
        if(queue_ref->head_ref == NULL){
            queue_ref->head_ref = queue_ref->last_ref = new_node;
        }
        else{
        new_node->prev = queue_ref->last_ref;
        queue_ref->last_ref->next = new_node;
        queue_ref->last_ref = new_node;
        queue_ref->last_ref->next = NULL;
        }
}

/*Função que imprime os elementos da lista de forma circular,
os elementos impressos saem do inicio da fila e retornam a fila após a impressão (CIRCULAR)
a função termina de imprimir os elementos quando a fila der 1 volta completa*/
void print_Queue(struct List* queue_ref){

    struct Node* tmp;
    struct Node* aux;
    tmp = queue_ref->head_ref;
    do{
        aux = dequeue(queue_ref);
        printf("%s\n",aux->nome);
        enqueue(queue_ref,aux);
    }while(tmp != queue_ref->head_ref);
}

//Desaloca memoria de uma das estruturas de dados do programa
void free_list(struct List* reference){

    while(reference->head_ref !=NULL){
        struct Node* tmp = reference->head_ref;
        reference->head_ref = reference->head_ref->next;
        free(tmp);
    }
    free(reference);
}