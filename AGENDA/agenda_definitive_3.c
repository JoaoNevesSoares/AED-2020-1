#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Node{

    char nome[50];
    struct Node* next;
    struct Node* prev;

};

//Doubly Linked list
struct List{
    struct Node* head_ref;
    struct Node* last_ref;

};

struct Agenda{

    char nome_holder[50];
    struct Node* traverse;
    struct Node* tmp;
    struct List* reference;
    struct List* aux;
    int int_holder;
    int int_holder_2;
};

void append_sort_alfa(struct List* list,struct Node* new_node);
struct List* sort_list(struct Agenda* agenda);
void sort_menu_sort(struct Agenda* agenda);

struct List* create_list(){

    struct List* tmp = (struct List*)malloc(1*sizeof(struct List));
    return tmp;
}
struct Node* new_node(char* nome){

    struct Node* tmp = (struct Node*)malloc(1*sizeof(struct Node));
    stpcpy(tmp->nome,nome);
    tmp->next = tmp->prev = NULL;
    return tmp;
}

void append(struct Agenda* agenda,struct Node* new_node){

    agenda->traverse = agenda->reference->head_ref;
    if(agenda->reference->head_ref == NULL){
        agenda->reference->head_ref = new_node;
        return;
    }
    while(agenda->traverse->next !=NULL){
        agenda->traverse = agenda->traverse->next;
    }
    new_node->prev = agenda->traverse;
    agenda->traverse->next = new_node;
    agenda->reference->last_ref = agenda->traverse->next;
    return;
}
//ALTERAR
void show_list(struct Node* traverse){

    if(traverse == NULL){
        printf("A lista está vazia\n");
        return; 
    }
    for( ;traverse !=NULL; traverse = traverse->next ){
        printf("%s\n",traverse->nome);
    }
}

struct Node* search(struct Agenda* agenda, char nome[]){ 
    agenda->traverse = agenda->reference->head_ref;

        while(agenda->traverse!=NULL && strcmp(agenda->traverse->nome,nome)!=0)
        agenda->traverse = agenda->traverse->next;
        return agenda->traverse;
}
void remove_nome(struct Agenda* agenda,char nome[]){
    if(agenda->reference->head_ref == NULL){
        printf("A lista está vazia\n");
        return;
    }
    agenda->tmp = search(agenda,nome);
    if(agenda->tmp == agenda->reference->head_ref){
        agenda->reference->head_ref = agenda->reference->head_ref->next;
    }
    else if(agenda->tmp == agenda->reference->last_ref){
        agenda->reference->last_ref = agenda->reference->last_ref->prev;
        agenda->reference->last_ref->next = NULL;
    }
    else if(agenda->tmp == NULL){
        printf("Nome inserido não existe no Banco de dados da Agenda\n");
        return;
    }
    else{
        agenda->tmp->prev->next = agenda->tmp->next;
        agenda->tmp->next->prev = agenda->tmp->prev;
    }
    printf("Nome removido com sucesso\n");
    free(agenda->tmp);
}
int menu(struct Agenda* agenda){
    printf("digite a operação que deseje:\n");
        printf("0-Sair da Agenda\n");
        printf("1-adicionar nome na agenda\n");
        printf("2-listar\n");
        printf("3-Remover nome\n");
        printf("4-buscar nome na agenda\n");
        scanf("%d",&agenda->int_holder);
        getchar();
        system("clear"); //remover depois
        return agenda->int_holder;
}
void sort_menu(){

    printf("MENU DE ORDENAÇÃO\n");
    printf("1-Não ordernar\n");
    printf("2-Ordenar em ordem alfabética\n");
    printf("3-Ordenar por quantidade de letras (crescente)\n\n");
    printf("4-Ordenar trocando posição de 2 nomes da agenda\n");
    printf("5-Ordem alfabética inversa\n");
}
void free_list(struct Agenda* agenda){

    while(agenda->reference->head_ref !=NULL){
        agenda->tmp = agenda->reference->head_ref;
        agenda->reference->head_ref = agenda->reference->head_ref->next;
        free(agenda->tmp);
    }
    free(agenda->reference);
}
int main(){

    void *pBuffer = (struct Agenda*)malloc(1*sizeof(struct Agenda));
    struct Agenda* agenda;
    agenda = pBuffer;
    agenda->reference = create_list();
    agenda->int_holder=10;
    //-------MENU----
    while(agenda->int_holder != 0){

        switch(menu(agenda))
        {

            case 0:
                break;
            case 1:

                printf("digite o nome para inserir na Agenda\n");
                scanf("%[^\n]s",agenda->nome_holder);
                append(agenda,new_node(agenda->nome_holder));
                system("clear");
               break;
            case 2:
                //show_list(agenda);
                sort_menu_sort(agenda);
                getchar();
                system("clear");
                break;
            case 3:
                printf("Digite o nome para ser removido\n");
                scanf("%[^\n]s",agenda->nome_holder);
                remove_nome(agenda,agenda->nome_holder);
                getchar();getchar();
                system("clear");
                break;
            case 4:
                printf("digite um nome para buscar\n");
                scanf("%[^\n]s",agenda->nome_holder);
                search(agenda,agenda->nome_holder);
                if(agenda->traverse == NULL){
                    printf("Nome não encotrado E/OU lista vazia\n");
                }
                else{
                    printf("Nome:%s encontrado!\n",agenda->traverse->nome);
                }
                break;
            default:
                printf("comando inválido, tente novamente\n");
                break;
        }

    }
    free_list(agenda);
    free(agenda);
}

void append_sort_alfa(struct List* list,struct Node* new_node){

    struct Node* current;
    new_node->prev = new_node->next = NULL;
    if(list->head_ref ==NULL){
        list->head_ref = list->last_ref = new_node;
        return;
    }
    else if(strcmp(list->head_ref->nome,new_node->nome)>= 0){

        new_node->next = list->head_ref;
        new_node->next->prev = new_node;
        list->head_ref = new_node;
    }
    else{
        current = list->head_ref;
        while(current->next !=NULL && strcmp(current->next->nome,new_node->nome)<0){
                current = current->next;
        }
        new_node->next = current->next;
        if(current->next !=NULL)
            new_node->next->prev = new_node;
        current->next = new_node;
        new_node->prev = current;
    }
    struct Node *traverse = list->head_ref;
    for( ;traverse->next !=NULL;traverse=traverse->next);
    list->last_ref = traverse;
}
void append_sort_length(struct List* list,struct Node* new_node){

    struct Node* current;
    if(list->head_ref ==NULL){
        list->head_ref = new_node;
    }
    else if(strlen(list->head_ref->nome)>= strlen(new_node->nome)){

        new_node->next = list->head_ref;
        new_node->next->prev = new_node;
        list->head_ref = new_node;
    }
    else{
        current = list->head_ref;
        while(current->next !=NULL && strlen(current->next->nome)<strlen(new_node->nome)){
                current = current->next;
        }
        new_node->next = current->next;
        if(current->next !=NULL)
            new_node->next->prev = new_node;
        current->next = new_node;
        new_node->prev = current;
    }
    struct Node *traverse = list->head_ref;
    for( ;traverse->next !=NULL;traverse=traverse->next);
    list->last_ref = traverse;
}
void insertion_sort(struct Agenda* agenda, int i){
    agenda->aux = create_list();
        agenda->traverse = agenda->reference->head_ref;
        while(agenda->traverse !=NULL){
            struct Node* next = agenda->traverse->next;
            if(i==2) append_sort_alfa(agenda->aux,agenda->traverse);
            else if (i ==3) append_sort_length(agenda->aux,agenda->traverse);
            agenda->traverse = next;
        }
        agenda->reference = agenda->aux;
}
void sort_menu_sort(struct Agenda* agenda){

    sort_menu();
    scanf("%d",&agenda->int_holder_2);
    getchar();
    switch (agenda->int_holder_2)
    {
    case 1:
        agenda->traverse = agenda->reference->head_ref;
        show_list(agenda->traverse);
        break;
    case 2:
        insertion_sort(agenda,2);
        show_list(agenda->reference->head_ref);
        break;
    
    case 3:
        insertion_sort(agenda,2);
        show_list(agenda->reference->head_ref);
        break;
    case 4:
        show_list(agenda->reference->head_ref);
        printf("escolha 2 nomes para para muda-los de posição\n");
        scanf("%[^\n]s",agenda->nome_holder);
        getchar();
        agenda->traverse = agenda->reference->head_ref;
        agenda->tmp = search(agenda,agenda->nome_holder);
        if(agenda->tmp==NULL){
            printf("nome inválido\n");
            break;
        }
        scanf("%[^\n]s",agenda->nome_holder);
        getchar();
        agenda->traverse = search(agenda,agenda->nome_holder);
        if(agenda->traverse == NULL){
            printf("nome inválido\n");
            break;
        }
        else if(strcmp(agenda->tmp->nome,agenda->traverse->nome)==0){
            printf("você escolheu nomes iguais -_-\n");
        }
        else{

            struct Node* keep_tmp_prev;
            struct Node* keep_tmp_next;
            struct Node* keep_trv_prev;
            struct Node* keep_trv_next;
            keep_tmp_prev = agenda->tmp->prev;
            keep_tmp_next = agenda->tmp->next;
            keep_trv_prev = agenda->traverse->prev;
            keep_trv_next = agenda->traverse->next;
            
            if(strcmp(keep_tmp_next->nome,agenda->traverse->nome) == 0){
                
                agenda->traverse->next = agenda->tmp;
                agenda->tmp->prev= agenda->traverse;
                agenda->tmp->next = keep_trv_next;
                agenda->traverse->prev = keep_tmp_prev;
                if(agenda->tmp->prev == NULL){
                    agenda->reference->head_ref = agenda->tmp;
                }
                else if(agenda->traverse->prev == NULL){
                    agenda->reference->head_ref = agenda->traverse;
                }
                if(agenda->tmp->next == NULL){
                agenda->reference->last_ref = agenda->tmp;
                }
                else if(agenda->traverse->next == NULL){
                agenda->reference->last_ref = agenda->traverse;
                }

                

            }
            else if(strcmp(keep_trv_next->nome,agenda->tmp->nome) == 0){
                 agenda->tmp->next = agenda->traverse;
                 agenda->traverse->prev = agenda->tmp;
                 agenda->traverse->next = keep_tmp_next;
                 agenda->tmp->prev = keep_trv_prev;
                
                if(agenda->tmp->prev == NULL){
                    agenda->reference->head_ref = agenda->tmp;
                }
                else if(agenda->traverse->prev == NULL){
                    agenda->reference->head_ref = agenda->traverse;
                }
                if(agenda->tmp->next == NULL){
                agenda->reference->last_ref = agenda->tmp;
                }
                else if(agenda->traverse->next == NULL){
                agenda->reference->last_ref = agenda->traverse;
                }

            }
            else{
                agenda->traverse->prev = keep_tmp_prev;if(agenda->tmp->next == NULL){
                agenda->reference->last_ref = agenda->tmp;
                }
                else{
                    agenda->tmp->next->prev = agenda->tmp;
                }
                agenda->traverse->next = keep_tmp_next;
                agenda->tmp->prev = keep_trv_prev;
                agenda->tmp->next = keep_trv_next;
                if(agenda->tmp->prev == NULL){
                    agenda->reference->head_ref = agenda->tmp;
                }
                else{
                    keep_trv_prev->next = agenda->tmp;
                }
                if(agenda->tmp->next == NULL){
                agenda->reference->last_ref = agenda->tmp;
                }
                else{
                    agenda->tmp->next->prev = agenda->tmp;
                }
                
                if(agenda->traverse->prev == NULL){
                    agenda->reference->head_ref = agenda->traverse;
                }
                else{
                    agenda->traverse->prev->next = agenda->traverse;
                }
                if(agenda->traverse->next == NULL){
                agenda->reference->last_ref = agenda->traverse;
                }
                else{
                    agenda->traverse->next->prev = agenda->traverse;
                }

             
             }
            
            /*
            if(agenda->tmp->prev == NULL){
                agenda->reference->head_ref = agenda->tmp;
            }
            else{
                keep_trv_prev->next = agenda->tmp;
            }
            if(agenda->tmp->next == NULL){
                agenda->reference->last_ref = agenda->tmp;
            }
            /*else{
                agenda->tmp->next->prev = agenda->tmp;
            }
            if(agenda->traverse->prev == NULL){
                agenda->reference->head_ref = agenda->traverse;
            }
            /*else{
                agenda->traverse->prev->next = agenda->traverse;
            }
            if(agenda->traverse->next == NULL){
                agenda->reference->last_ref = agenda->traverse;
            }
            else{
                agenda->traverse->next->prev = agenda->traverse;
            }

            //tmp anterior agora aponta para traverse anterior e traverse anterior próximo aponta para tmp
            agenda->tmp->prev = agenda->traverse->prev;
            if( agenda->traverse->prev !=NULL){
            agenda->tmp->prev->next = agenda->tmp;
            }
            else{
                agenda->reference->head_ref = agenda->tmp;
            }
            //troca realizada

            //traverse anterior aponta para keep(nodo anterior de prev antes da troca)
            //keep próximo aponta para traverse
            agenda->traverse->prev = keep;
            if(keep!=NULL){
            keep->next = agenda->traverse;
            }
            else{
                agenda->reference->head_ref = agenda->traverse;
            }
            //troca realizada
            
            //swap tmp next && traverse next
            keep = agenda->tmp->next;
            if(agenda->traverse->next == NULL){
                agenda->tmp->next = NULL;
                agenda->reference->last_ref = agenda->tmp;
            }
            else{
            agenda->tmp->next = agenda->traverse->next;
            agenda->traverse->next->prev = agenda->tmp;
            agenda->traverse->next = keep;
            if(keep !=NULL){
                keep->prev = agenda->traverse;
            }
            else{
                agenda->reference->last_ref = agenda->traverse;
            }
            
            }*/
            
        }
        system("clear");
        show_list(agenda->reference->head_ref);
        break;
    default:
        break;
    }
}
