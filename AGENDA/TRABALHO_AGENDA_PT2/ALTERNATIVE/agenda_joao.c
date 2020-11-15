#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Lists Nodes
struct Node{

    char nome[50];
    struct Node* next;
    struct Node* prev;

};

//Doubly Linked list // Queue
struct List{
    struct Node* head_ref;
    struct Node* last_ref;

};

//Buffer principal do código
struct Agenda{

    char nome_holder[50];
    int int_holder;
    int int_holder_2;
    struct List* lista_sentinel;
    struct List* queue_sentinel;
};

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

void capitalize(char nome[]){

    if(nome[0] >'Z'){
        nome[0] = nome[0]-32;
    }
}

//Adiciona elementos na lista
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
//busca na lista
struct Node* search(struct List* reference, char nome[]){ 
    
        struct Node* traverse = reference->head_ref;

        while(traverse!=NULL && strcmp(traverse->nome,nome)!=0)
        traverse = traverse->next;
        return traverse;
}

//remove um nome da lista
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
struct Node* pop_sort(struct List* ref,int *chose){

    struct Node* tmp;
    struct Node *traverse;
    tmp = ref->head_ref;
    traverse = tmp->next;
    if(*chose == 2){
        while(traverse!=NULL){
            if(strcmp(tmp->nome,traverse->nome)>= 0){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    else if(*chose == 3){
        while(traverse!=NULL){
            if(strcmp(tmp->nome,traverse->nome)<= 0){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    else if(*chose == 4){
        while(traverse!=NULL){
            if(strlen(tmp->nome) >= strlen(traverse->nome)){
                tmp = traverse;
            }
            traverse = traverse->next;
        }
    }
    traverse = tmp;
    tmp = new_node(tmp->nome);
    if(traverse == ref->head_ref){
        
        if(ref->head_ref != ref->last_ref){

            ref->head_ref = ref->head_ref->next;
            ref->head_ref->prev = NULL;
        }
        else{
            ref->head_ref = ref->last_ref = NULL;
        }
    }
    else if(traverse == ref->last_ref && ref->last_ref !=ref->head_ref){
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
void Queue_sort(struct List* ref, struct List* queue, int *chose){

    if(ref->head_ref == NULL){
        printf("Is empty\n");
        return;
    }
    queue = create_list();
    while(ref->head_ref !=NULL){
        struct Node* aux = pop_sort(ref,chose);
        enqueue(queue,aux);
        //append(queue,aux);//posso usar o enqueue
    }
    print_Queue(queue);
    ref->head_ref = queue->head_ref;
    ref->last_ref = queue->last_ref;
    free(queue);
}
//Menu do Main
int menu(struct Agenda* agenda){
    printf("digite a operação que deseje:\n");
        printf("0-Sair da Agenda\n");
        printf("1-adicionar nome na agenda\n");
        printf("2-Remover nome\n");
        printf("3-Buscar nome na agenda\n");
        printf("4-Listar nomes\n");
        scanf("%d",&agenda->int_holder);
        getchar();
        system("clear"); //remover depois
        return agenda->int_holder;
}
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
//Libera elemento da Lista
void free_list(struct List* reference){

    while(reference->head_ref !=NULL){
        struct Node* tmp = reference->head_ref;
        reference->head_ref = reference->head_ref->next;
        free(tmp);
    }
    free(reference);
}
int main(){

    void *pbuffer = (struct Agenda*)malloc(1*sizeof(struct Agenda));
    struct Agenda* agenda = pbuffer;    
    struct Node* tmp;
    agenda->lista_sentinel = create_list();
    agenda->int_holder = 99; //set int_holder to non 0 random value

    //-------Menu-------
    while(agenda->int_holder != 0){
        switch (menu(agenda))
        {
        case 0:
        free_list(agenda->lista_sentinel);
        if(agenda->queue_sentinel !=NULL){
            free(agenda->lista_sentinel);
        }
        free(agenda);
            break;
        case 1:
            printf("Digite um nome para inserir na agenda\n");
            scanf("%[^\n]s",agenda->nome_holder);
            getchar();
            capitalize(agenda->nome_holder);
            append(agenda->lista_sentinel,new_node(agenda->nome_holder));
            system("clear");
            break;
        case 2:
            if(agenda->lista_sentinel->head_ref == NULL){
                printf("A lista está vazia! Adicione pessoas antes de poder remove-los\n");
            }
            else{
            printf("Digite o nome para ser removido\n");
            scanf("%[^\n]s",agenda->nome_holder);
            getchar();
            remove_nome(agenda->lista_sentinel,agenda->nome_holder);
            }
            printf("\nPressione para qualquer tecla para sair\n");
            getchar();
            system("clear");
            break;
        case 3:
            printf("digite um nome para buscar\n");
                scanf("%[^\n]s",agenda->nome_holder);
                getchar();
                tmp = search(agenda->lista_sentinel,agenda->nome_holder);
                if(tmp == NULL){
                    printf("Nome não encotrado E/OU lista vazia\n");
                }
                else{
                    printf("Nome:%s encontrado!\n",tmp->nome);
                }
                printf("\npresione qualquer tecla para sair\n");
                getchar();
                system("clear");

            break;
        case 4:
            sort_menu(agenda);
            printf("\npresione qualquer tecla para sair\n");
            getchar();
            system("clear");
        default:
            break;
        }
    }
}



