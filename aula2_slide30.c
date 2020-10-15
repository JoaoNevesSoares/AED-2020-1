#include <stdio.h>
#include <stdlib.h>

int **cria_matriz(int lines,int columns){


    int **matriz = (int **)malloc(sizeof(int *)*lines);
    for(int i=0;i<columns;i++){
        matriz[i] = (int *)malloc(sizeof(int)*columns);
    }
    return matriz;
}
void le_matriz(int **matriz,int lines,int columns){

    for(int i=0;i<lines;i++){

        for(int j=0;j<columns;j++){
            scanf("%d",&matriz[i][j]);
        }
    }
}
int soma_matriz(int **matriz,int lines, int columns){

    int count=0;
    for(int i=0;i<columns;i++){

        for(int j=0;j<columns;j++){
            count+=matriz[i][j];
        }
    }
    return count;
}
void imprime_matriz(int **matriz,int lines,int columns){
    for(int i=0;i<lines;i++){

        for(int j=0;j<columns;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}
void limpa_matriz(int **matriz,int lines){
    for(int i=0;i<lines;i++){
        free(matriz[i]);
    }
    free(matriz);
}
int *coluna_matriz(int **matriz,int lines,int columns){
    int *temp = (int *)malloc(columns*sizeof(int));
    for(int i=0;i<lines;i++){
        temp[i] = matriz[i][columns-1];
    }
    return temp;
}
void imprimevet(int *vet, int size){
    for(int i=0;i<size;i++){
        printf("%d ",vet[i]);
    }
    printf("\n");
    free(vet);
}
int main(){
    int linha=2,coluna=2;
    int **ptr = cria_matriz(linha,coluna);
    le_matriz(ptr,linha,coluna);
    imprime_matriz(ptr,linha,coluna);
    printf("valor total armazenado na matriz = %d\n",soma_matriz(ptr,linha,coluna));
    imprimevet(coluna_matriz(ptr,linha,coluna),linha);
    limpa_matriz(ptr,linha);
}