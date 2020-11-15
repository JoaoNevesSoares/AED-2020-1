#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "data_structure.h"
#include "sort_algo.h"

//Padroniza todas as  1ªs letras dos nomes para maiúsculo
void capitalize(char nome[]){

    if(nome[0] >'Z'){
        nome[0] = nome[0]-32;
    }
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
        //system("clear");   !Recomendável descomentar esssa linha para melhor leitura dos dados no terminal
        return agenda->int_holder;
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
            //system("clear"); !Recomendável descomentar esssa linha para melhor leitura dos dados no terminal
            break;
        case 2:
            if(agenda->lista_sentinel->head_ref == NULL){
                printf("A lista está vazia! Adicione pessoas antes de poder remove-los\n");
            }
            else{
            printf("Digite o nome para ser removido\n");
            scanf("%[^\n]s",agenda->nome_holder);
            getchar();
            capitalize(agenda->nome_holder);
            remove_nome(agenda->lista_sentinel,agenda->nome_holder);
            }
            printf("\nPressione para qualquer tecla para sair\n");
            getchar();
            //system("clear"); !Recomendável descomentar esssa linha para melhor leitura dos dados no terminal
            break;
        case 3:
            printf("digite um nome para buscar\n");
                scanf("%[^\n]s",agenda->nome_holder);
                getchar();
                capitalize(agenda->nome_holder);
                tmp = search(agenda->lista_sentinel,agenda->nome_holder);
                if(tmp == NULL){
                    printf("Nome não encotrado E/OU lista vazia\n");
                }
                else{
                    printf("Nome:%s encontrado!\n",tmp->nome);
                }
                printf("\npresione qualquer tecla para sair\n");
                getchar();
                //system("clear");!Recomendável descomentar esssa linha para melhor leitura dos dados no terminal

            break;
        case 4:
            sort_menu(agenda);
            printf("\npresione qualquer tecla para sair\n");
            getchar();
            //system("clear"); !Recomendável descomentar esssa linha para melhor leitura dos dados no terminal
        default:
            break;
        }
    }
    return 0;
}
