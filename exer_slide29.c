/*EXERCICIO SLIDE ADICIONAR, REMOVER, LISTAR NOMES
TODOS OS NOMES ARMAZENADOS EM UM UNICO VETOR*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOOP 1

char *string_hold=NULL;
void remover(char *word){

   char *temp = string_hold;
    char *subs = (char *)calloc(strlen(temp)-strlen(word),sizeof(char));
    if(subs == NULL){
        printf("Problema de alocação de memoria, tente novamente\n");
        return;
    }
    char *x = (char *)calloc(strlen(word)+2,sizeof(char));
    if(x == NULL){
        printf("problema de alocação de memoria, tente novamente");
        return;
    }
    //x[0]='/';
    strcat(x,word);
    strcat(x,"/");
    if(strstr(string_hold,word)==NULL){
    printf("Não existe esse nome na lista, tente novamente ou saia do programa\n");
    return;
    }
    while(*temp){
        
        
        char *token = (char *)calloc(100,sizeof(char));
        if(token == NULL){
            printf("Problema de alocação de memoria tente novamente \n");
            return;
        }
        char *head=token;
        for(;*temp!='/';temp++){
            *token = *temp;
            token++;

        }
        *token= *temp++;
        if( strcmp(head,x) != 0){
            strcat(subs,head);
        };
        token = head;
        free(token);
    }
    free(string_hold);
    string_hold = subs;
    free(x);
}
void adicionar(){

    char *word = (char *)malloc(50*sizeof(char));
    if(word == NULL){
        printf("Problema de alocação de memoria tente novamente\n");
        return;
    }
    scanf("%s",word);
    int word_len = strlen(word);
    strcat(word,"/");
    
    if(string_hold==NULL){
        string_hold=(char *)malloc(word_len*sizeof(char));
        if(string_hold==NULL){
            printf("Problema de alocação de memoria, tente novamente\n");
            return;
        }
        strcat(string_hold,word);
    }
    else{
        int str_len = strlen(string_hold);
        //temp = (char*)realloc(*string,str_len+word_len);
        string_hold = (char*)realloc(string_hold,str_len+word_len);
        if(string_hold ==NULL){
            printf("Problema de alocação de memoria, tente novamente\n");
        }
        strcat(string_hold,word);
    }
    free(word);
}
void listar(){
    char *temp = string_hold;
    if(temp == NULL){
        printf("A lista está vazia\n");
        return;
    }
    for(;*temp!='\0';temp++){
        if(*temp !='/'){
        printf("%c",*temp);
        }
        else{
            printf("\n");
        }
    }
}
int main(){


    int s;
    printf("--->MENU DE OPÇÕES<---\nz ---> listar\na ---> Adicionar nome\nr ---> Remover nome (digitar o nome)\ns ---> Sair do programa\n");
    while(LOOP){
        
        
        s = getchar();
        system("clear");
        switch (s)
        {
        case 'z':
            
            listar();
            printf("aperte qualquer coisa para sair\n");
            int g = getchar();
            break;
        case 'a':
            adicionar();

            break;

        case 'r':
            printf("digite o nome para remover\n");
            char nome[100];
            scanf("%s",nome);
            remover(nome);
            break;
        case 's':
            free(string_hold);
            return 0;
            break;
        default:
        //printf("Try again");
            break;
        }
         printf("--->MENU DE OPÇÕES<---\nL ---> listar\na ---> Adicionar nome\nr ---> Remover nome (digitar o nome)\ns ---> Sair do programa\n");

    }
    return 0;
    


}
