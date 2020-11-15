#include <stdio.h>
#include <stdlib.h>

/*Prototipo das funções*/
int **cria_matriz(int lines,int columns);
void le_matriz(int **matriz,int lines,int columns);
void imprime_matriz(int **matriz,int lines,int columns);
int **redimensiona (int **matriz,int lines,int columns,int old_lines,int old_columns);
int soma_matriz(int **matriz,int lines, int columns);
int *coluna_matriz(int **matriz,int lines,int columns);
void imprimevet(int *vet, int size);
void limpa_matriz(int **matriz,int lines);
void copiar(int **destination,int **source,int i, int columns, int old_columns);
int main(){

    int linha,coluna,soma=0;
    int **matriz=NULL,*vetor_column=NULL;
    printf("digite o numero de linhas e colunas para inicialiar a matriz\n");
    scanf("%d %d",&linha,&coluna);
    matriz = cria_matriz(linha,coluna);
    
    printf("digite os valores inteiros para matriz\n");
    le_matriz(matriz,linha,coluna);
    int option=1;
    while(option){
        
        printf("'1' para ler\n'2' para imprimir\n'3' para redimensionar\n'4' para somar\n'5' retornar vetor\n'6' para imprimir vetor\n'7' para sair\n");
        scanf("%d",&option);
        switch (option)
        {
        case 1:
            le_matriz(matriz,linha,coluna);
            break;
        case 2:
            imprime_matriz(matriz,linha,coluna);
            break;
        case 3:
            printf("digite os novos valores para linha e coluna\n");
            int old_linha = linha;
            int old_coluna = coluna;
            scanf("%d %d",&linha,&coluna);
            matriz = redimensiona(matriz,linha,coluna,old_linha,old_coluna);
            break;
        case 4:
            soma = soma_matriz(matriz,linha,coluna);
            printf("soma = %d\n",soma);
            break;
        case 5:
            if(vetor_column !=NULL) free(vetor_column);
            int col;
            printf("digite uma da coluna da matriz para retornar(Lembre-se as posições vão de 0 até coluna-1)\n");
            scanf("%d",&col);
            if(col>=0 && col <coluna){
            vetor_column = coluna_matriz(matriz,linha,col);
            };
            break;
        case 6:
            if(vetor_column!=NULL)imprimevet(vetor_column,linha);
            else{
                printf("O vetor não foi criado, tente a opção 5!\n");
            }
            break;
        
        case 7:
            option =0;
            break;
        
        default:
             printf("'1' para ler\n'2' para imprimir\n'3' para redimensionar\n4 para somar\n5 retornar vetor\n6 para imprimir vetor\n7 para sair\n");
             //scanf("%d",&option);
            break;
        }
    }
    limpa_matriz(matriz,linha);
    if(vetor_column !=NULL) free(vetor_column);
    return 0;
}

//aloca uma matriz linha*coluna na heap, retorna endereço da matriz
int **cria_matriz(int lines,int columns){


    int **matriz = (int **)malloc(sizeof(int *)*lines);
    for(int i=0;i<lines;i++){
        matriz[i] = (int *)malloc(sizeof(int)*columns);
    }
    return matriz;
}

//lê valores inteiros do usuário e adiciona nos campos da matriz
void le_matriz(int **matriz,int lines,int columns){

    for(int i=0;i<lines;i++){

        for(int j=0;j<columns;j++){
            scanf("%d",&matriz[i][j]);
        }
    }
}
//Imprime os valores contidos na matriz
void imprime_matriz(int **matriz,int lines,int columns){
    for(int i=0;i<lines;i++){

        for(int j=0;j<columns;j++){
            printf("%d ",matriz[i][j]);
        }
        printf("\n");
    }
}
/*Redimensiona o tamanho da matriz alocada na heap, copiando os valores já salvo e adicionando
0 nas novas posições alocadas*/
int **redimensiona (int **matriz,int lines,int columns,int old_lines,int old_columns){

    int **aux = (int **)malloc(sizeof(int *)*lines);
    int i;
    
    /*caso a nova matriz for maior que a anterior ira copiar os valores anteriores e 
    preencher as novas posições usando a func Calloc*/
    if(old_lines<lines){
        for(i=0;i<old_lines;i++){
            aux[i] = (int *)malloc(sizeof(int)*columns);
            copiar(aux,matriz,i,columns,old_columns); //funcao para copiar as linhas da matriz anterior
        }
        for(i;i<lines;i++){
            aux[i] = (int *)calloc(columns,sizeof(int));
        }
    }
    /*caso a nova matriz for menor que a anterior então copiará até o tamanho atual da matriz*/
    else{
        for(i=0;i<lines;i++){
            aux[i] = (int *)malloc(sizeof(int)*columns);
            copiar(aux,matriz,i,columns,old_columns);
        }
    }
    //desaloca a memoria da antiga matriz
    limpa_matriz(matriz,old_lines);
    return aux;
}

//Realisa a soma dos elementos da matriz
int soma_matriz(int **matriz,int lines, int columns){

    int count=0;
    for(int i=0;i<lines;i++){

        for(int j=0;j<columns;j++){
            count+=matriz[i][j];
        }
    }
    return count;
}
//retorna um vetor do tamanho = numero de linhas, com os elementos da coluna selecionada
int *coluna_matriz(int **matriz,int lines,int columns){
    int *temp = (int *)malloc(columns*sizeof(int));
    for(int i=0;i<lines;i++){
        temp[i] = matriz[i][columns-1];
    }
    return temp;
}
//imprime o vetor retornado pela função anterior
void imprimevet(int *vet, int size){
    for(int i=0;i<size;i++){
        printf("%d ",vet[i]);
    }
    printf("\n");
}
//função para desalocar a memoria de uma matriz
void limpa_matriz(int **matriz,int lines){
    for(int i=0;i<lines;i++){
        free(matriz[i]);
    }
    free(matriz);
}
//copia os elementos de determinada posicação de uma matriz para a outra
void copiar(int **destination,int **source,int i, int columns, int old_columns){
    
    int j;
    
    if(old_columns<columns){
        for(j=0;j<old_columns;j++){
            destination[i][j] = source[i][j];
        }
        for(j;j<columns;j++){
            destination[i][j] = 0;
        }
    }
    else{
        for(j=0;j<columns;j++){
            destination[i][j] = source[i][j];
        }
    }
}