#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

typedef struct{
    char P[20];
    int F;
} Palavra;

int main(){
    int TAM;
    FILE *arq;
    arq = fopen("nome.txt", "r");
    if (arq==NULL){
        printf("DEU RUIM");
    }
    Palavra vetor_palavra[100];

    char Px[20];


    fseek(arq,0, SEEK_END);// movimenta a posição corrente de leitura no arquivo para o seu fim

    TAM = ftell(arq);//pega a posição corrente de leitura no arquivo
    rewind(arq); // volta pro começo novamente.
    char texto[TAM+3];
    fread(texto ,1 ,TAM ,arq);
    fclose(arq);
    char *tmp; strcpy(tmp, texto);
    strcpy(texto, " ");
    strcat(texto, tmp);//coloca o espaço no começo do texto
    free(tmp);//libera tmp
    cout<<texto<<endl;
    strcat (texto," ");//coloca o espaço no fim do texto
    cout<<texto;

    int cx=0, c_string=0,cp=0;
    printf("O arquivo tem %d caracteres", TAM);

    while(c_string < (TAM+2)){
        while(texto[c_string] == ' '){
            c_string++;
            while(texto[c_string]!= ' ' || '.' || ';' || ':'){
            Px[cx] = texto[c_string];
            cx++;
            printf("oi");
            }
            c_string++;
        }
        //vetor_palavra[cp].P = Px;
        //vetor_palavra[cp].F = 1;
        //cp++;
        //cout<< vetor_palavra[0].P<<endl;
    }
    return 0;
}
