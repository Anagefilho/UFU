#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Lei de Heaps
//Lei de Zipf
/*
fwrite(&Ndicionario, sizeof(ndicionario),arq);
fwrite(&dicionario, sizeof(palavra),arq);
Salvar
*/

struct Documento{	    	//struct que guarda dados sobre o arquivo que a palavra aparece
	int arquivo, quant;		//guarda o arquivo e a frequencia da palavra nesse arquivo
}typedef doc;

struct Dicionario{		//struct que guarda as palavras lidas, uma lista de documentos que essa palavra aparece, a frequencia total da mesma e em quantos documentos a mesma aparece
	char pala[50];
	doc documentos[10];
	int freq;
	int contDoc;
}typedef dic;


int main(){
	dic dicionario[155], dicionario_bin[155];	//vetor do dicionnario
	int contp=0;			//contador de palavras do dicionario

	for(int c=0; c<155; c++){
        dicionario[c].freq = 0;
        dicionario[c].contDoc = 1;
	}

	int i, j;

	FILE *nomeArq;			//ponteiro para abrir arquivo

	char temp[50];			//variáveis temporarias
	int docTemp, freqTemp;	//para retirar as palavras do txt

	nomeArq = fopen("palavras.txt", "r");	//abertura do arquivo

	while(fscanf(nomeArq, "%s %d %d", temp, &docTemp, &freqTemp) != EOF){	//ler o arquivo ate o final e coloca as informações nas variáveis temporarias

		int flag=0;														//variável auxiliar que fica '1' caso a nova palavra já esteja no dicionario
		for(i = 0; i < contp; i++){									//caso tenha palavras no dicionario o for percorre todas as palavras antes de adicionar uma nova
			if(strcmp(temp, dicionario[i].pala) == 0){					//verifica se a palavra a ser adicionada é igual a alguma palavra previamente adicionada
				dicionario[i].documentos[dicionario[i].contDoc].arquivo = docTemp;	//caso já exista a palavra no dicionário
				dicionario[i].documentos[dicionario[i].contDoc].quant = freqTemp;	//adicina um novo documento e sua frequencia
				dicionario[i].freq += freqTemp;										//a lista de documentos dessa palavra
				dicionario[i].contDoc++;											//almenta o contador de documentos dessa palavra
				flag++;																//a flag idica que essa palavra não vai ser adicionada em um novo espaço do dicionário
				i = contp;															//faz o for ser finalizado, evitando ter que comprar essa palavra com todo o resto
			}
		}
		if(flag==0){													//caso a flag fique '0' é porque a palavra ainda não está no dicionário
			strcpy(dicionario[contp].pala, temp);						//então adiciona a palavra ao dicionário
			dicionario[contp].documentos[0].arquivo = docTemp;			//e as informações de documento e frequencia dessa palavra
			dicionario[contp].documentos[0].quant = freqTemp;			//
			dicionario[contp].freq += freqTemp;							//
			contp++;													//aumenta o contador de palavras do dicionário
		}
	}

	///////////////////ordenação por numero do documento
	for(i=0; i<contp; i++){											//passar por todas as palavras
		if(dicionario[i].contDoc > 1){								//verificar se a palavra aparece em mais de 1 documento
			int auxArq, auxQuant, auxTroca=0;						//variáveis auxiliares para transferir valores

			do{
				auxTroca=0;
				for(j=0; j < dicionario[i].contDoc-1; j++){													//passar por todos os documentos que a palavra aparece
					if(dicionario[i].documentos[j].arquivo > dicionario[i].documentos[j+1].arquivo){		//verificar se a arquivo atual é maior que o arquivo j+1
						auxQuant = dicionario[i].documentos[j].quant;										//trocar
						auxArq = dicionario[i].documentos[j].arquivo;										//as

						dicionario[i].documentos[j].quant = dicionario[i].documentos[j+1].quant;			//informações
						dicionario[i].documentos[j].arquivo = dicionario[i].documentos[j+1].arquivo;		//entre

						dicionario[i].documentos[j+1].quant = auxQuant;										//os
						dicionario[i].documentos[j+1].arquivo = auxArq;										//arquivos

						auxTroca++;
					}
				}
			}while(auxTroca!=0);
		}
	}
	///////////////////fim da ordenação por numero do documento

	// salvando em arquivo

    FILE *outfile;

    // Abre um arquivo para salvar em binário
    outfile = fopen ("palavras.dat", "wb"); // Modo de escrita para salvar em arquivo binário
    if (outfile == NULL)
    {
        fprintf(stderr, "\nErro ao abrir arquivo\n"); // Casp houver algum erro ira mostrar a mensagem de erro
        exit (1);
    }

    // Salvando uma struct no arquivo binario
    fwrite (&dicionario, sizeof(struct Dicionario), contp, outfile); // 155 o tamanho do vetor, outfile o nome do arquivo

    if(fwrite != 0)
        printf("Palavras foram salvas em arquivo com sucesso !\n"); // se der tudo certo vai ser salvo
    else
        printf("Erro na hora de salvar palavras!\n");

    // fecha o arquivo
    fclose (outfile);

    FILE *openfile = fopen ("palavras.dat", "rb"); // Modo de leitura para o arquivo binário
    if (openfile == NULL)
    {
        fprintf(stderr, "\nErro ao abrir arquivo\n"); // Se houve erro ao ler um arquivo binário
        exit (1);
    }

    fread (&dicionario_bin, sizeof(struct Dicionario), contp, openfile);

    if(fopen!= 0)
        printf("Palavras foram lidas em arquivo com sucesso !\n"); // se der tudo certo a struct sera lida do arquivo binário
    else
        printf("Erro na hora de ler as palavras!\n");

	for(i=0; i<contp; i++){
		printf("Palavra: %s - ", dicionario_bin[i].pala); //Print da struct
		for(j=0; j<dicionario_bin[i].contDoc; j++){
			printf("doc: %d - freq: %d    ", dicionario_bin[i].documentos[j].arquivo, dicionario_bin[i].documentos[j].quant);
		}
		printf("\n");
	}

	fclose (openfile);

}
