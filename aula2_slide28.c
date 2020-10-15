#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define INITIAL_MEM 2
struct pessoa{

    char *nome;
    int idade;
    float altura;
};
struct pessoa * add_pessoa(void){

    struct pessoa *fulano = (struct pessoa *)malloc(1*sizeof(struct pessoa));
    char *nome = (char *)malloc(100);
    printf("nome:\n");
    scanf("%s",nome);
    fulano->nome = (char *)malloc(strlen(nome));
    strcpy(fulano->nome,nome);
    printf("idade\n");
    scanf("%d",&fulano->idade);
    printf("altura\n");
    scanf("%f",&fulano->altura);
    getchar(); // usado para capturar a tecla "enter" do scanf acima
    free(nome);
    return fulano;
}
void limpa_struct(struct pessoa **instancia,int quantidade){

    for(int i=0;i<quantidade;i++){
        free(instancia[i]->nome);//desaloca a memoria usada para os nomes
        free(instancia[i]);

    }

}
int main(){
    int extra=0;
    struct pessoa **lista = (struct pessoa **)malloc(INITIAL_MEM*sizeof(struct pessoa *));
    int flow_control =0;
    int escape;
    printf("digite Y para adicionar nomes ou 'N' para sair\n");
    while(1){

        escape = getchar();
        if(escape == 'N')break;
        else{
            if(flow_control<INITIAL_MEM+extra){
                lista[flow_control++] = add_pessoa();
            }
            else{
                lista = (struct pessoa **)realloc(lista,(INITIAL_MEM+100)*sizeof(struct pessoa *));
                extra = 100;
                lista[flow_control++]=add_pessoa();
            }
        }
        printf("digite Y para adicionar nomes ou 'N' para sair\n");
        
    }
    for(int i=0;i<flow_control;i++){

        printf("%s\n",lista[i]->nome);
        printf("%d\n",lista[i]->idade);
        printf("%.2f\n",lista[i]->altura);
        printf("************\n");
    }
    limpa_struct(&*lista,flow_control);
    free(lista);
}