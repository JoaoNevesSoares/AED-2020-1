/*EXERCICIO SLIDE ADICIONAR, REMOVER, LISTAR NOMES
TODOS OS NOMES ARMAZENADOS EM UM UNICO VETOR*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LOOP 1

void remover(char **string,char *word){

   char *temp = *string;
    char *subs = malloc(strlen(temp)-strlen(word));
    char *x = malloc(strlen(word)+2);
    //x[0]='/';
    strcat(x,word);
    strcat(x,"/");
    if(strstr(*string,word)==NULL){
    printf("Não existe esse nome na lista, tente novamente ou saia do programa\n");
    return;
    }
    while(*temp){
        
        
        char *token = (char *)malloc(20);
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
    *string = subs;
    free(x);
}
void adicionar(char **string){

    char *word = (char *)malloc(50*sizeof(char));
    char *temp=NULL;
    scanf("%s",word);
    int word_len = strlen(word);
    strcat(word,"/");
    
    if(*string==NULL){
        *string=(char *)malloc(word_len*sizeof(char));
        strcat(*string,word);
    }
    else{
        int str_len = strlen(*string);
        //temp = (char*)realloc(*string,str_len+word_len);
        *string = (char*)realloc(*string,str_len+word_len);
        strcat(*string,word);
    }
    free(word);
}
void listar(char *string){

    for(;*string!='\0';string++){
        if(*string !='/'){
        printf("%c",*string);
        }
        else{
            printf("\n");
        }
    }
}
int main(){


    char *string_hold=NULL;
    int s;
    printf("--->MENU DE OPÇÕES<---\nL ---> listar\na ---> Adicionar nome\nr ---> Remover nome (digitar o nome)\ns ---> Sair do programa\n");
    while(LOOP){
        
        
        s = getchar();
        system("clear");
        switch (s)
        {
        case 'z':
            
            listar(string_hold);
            printf("aperte qualquer coisa para sair\n");
            int g = getchar();
            break;
        case 'a':
            adicionar(&string_hold);
            free(string_hold);

            break;

        case 'r':
            printf("digite o nome para remover\n");
            char nome[100];
            scanf("%s",nome);
            remover(&string_hold,nome);
            break;
        case 's':
            return 0;
            break;
        default:
        //printf("Try again");
            break;
        }
         printf("--->MENU DE OPÇÕES<---\nL ---> listar\na ---> Adicionar nome\nr ---> Remover nome (digitar o nome)\ns ---> Sair do programa\n");

    }
    






}
