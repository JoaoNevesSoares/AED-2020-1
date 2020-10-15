#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *realocar(void *pont,size_t new_size){

       void *aux = malloc(new_size);
       memcpy(aux,pont,new_size);
       free(pont);
       return aux;                                                                                                                                                                                                                             

}
int main(){}
