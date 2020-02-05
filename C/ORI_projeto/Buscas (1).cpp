#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Documento{	    	//struct que guarda dados sobre o arquivo que a palavra aparece
	int arquivo, quant;		//guarda o arquivo e a frequencia da palavra nesse arquivo
}typedef doc;

struct Dicionario{		//struct que guarda as palavras lidas, uma lista de documentos que essa palavra aparece, a frequencia total da mesma e em quantos documentos a mesma aparece
	char pala[50];
	doc documentos[10];
	int freq;
	int contDoc;
}typedef dic;

struct nomes_dic{
    char nome[50];
    
    struct nomes_dic *prox;
    struct nomes_dic *ant;
}typedef nom_dic;

typedef struct  //struct para guardar a lista de stopwords
{
    char termo[100];

} stopwords ;

dic dicionario_bin[500];// dicionario_bin_complementar[500];
int contp = 0;

doc documentostotal[500];
int contdocs = 0;


////////////////////////inicio parte pré processamento
void retira_plural_palavra(char p1[]){
	dic exce[20];
    FILE *listaExcecao = fopen("listaExcecao.txt", "r");	//abertura do arquivo
    int k=0, j;
    char palav[50];
    while(fscanf(listaExcecao, "%s",&palav)!=EOF){
        strcpy(exce[k].pala, palav);
        k++;
    }
	fclose(listaExcecao);
	
	char pala[20];

    //retirada dos plurais
    //printf("Retirando os Plurais!\n");
    int aux=0;
    int tam = strlen(p1);
    //printf("Tamanho: %d -- Palavra: %s/n",tam,dicionario_bin[w].pala);
    if(p1[tam-1] == 's'){
        for(j=0; j<k; j++){
            if(strcmp(p1,exce[j].pala)==0){
                aux=1;
            }
        }
        if(aux==0){
            if(p1[tam-2] == 'o' || p1[tam-2] == 'a'){
                p1[tam-1] = '\0';
			}
            else if(p1[tam-2] == 'e'){
                p1[tam-1] = '\0';
				if(p1[tam-3] != 'r'){   //por causa da palavra caes
                    p1[tam-2] = 'o';
                }
                else{
                    p1[tam-2] = '\0';
                }
            }
        }
    }
}

void retira_genero_palavra(char p1[]){
	dic exc_palavra[15];
    
    int tam, i, j, k, l;
    
    //printf("Abrindo arquivos e lendo exceções\n\n");

    FILE *ArqExc = fopen("excecoes.txt", "r");

    for(j=0; j<14; j++){
        fscanf(ArqExc, "%s", exc_palavra[j].pala);
    }
	fclose (ArqExc);


	int flag_execao;
	//printf("Iniciando retirada de genero\n\n");
    for(i=0; i<contp; i++){
    	flag_execao = 0;
        for(j=0; j<14; j++){
            if(strcmp(p1, exc_palavra[j].pala)==0){
                flag_execao = 1;
            }
        }

        if(flag_execao == 0){
        	
            tam = strlen(p1);
            if(p1[tam-1] == 'a'){

                if(p1[tam-1] == 'a' && p1[tam-2] == 'r' && tam>3){
                    p1[tam-1] = '\0'; // Coloca '\n' para fechar a palavra pela regra das palavras terminadas em R
                }

                else if(tam>=5 && p1[tam-1] == 'a' && p1[tam-2] == 'm' && p1[tam-3] == 'a' && p1[tam-3] == 'r' && p1[tam-3] == 'g'){
                    // Pela regra palavras terminadas em '-grama' sao sempre masculinas e nao variam
                    //vazio intencional
                }

                else if(p1[tam-1] == 'a' && p1[tam-2] == 'm' && p1[tam-3] == 'a'){
                	//vazio intencional
                }
                
                else{
                    p1[tam-1] = 'o';
                }
            }
        }
    }
}

void preprocessamento(char p1[], char p2[], char p3[]){
	int i, not1, not2=0, not3=0;
	char aux[50];
	/////////////////////////////////////////////////////inicio palavra 1
	aux[0] = '\0';
	not1=0;
	if(p1[0]=='-'){
		not1++;
		for(i=0; i<strlen(p1); i++){
			p1[i]=p1[i+1];
		}
	}
	retira_plural_palavra(p1);
	retira_genero_palavra(p1);
	if(not1!=0){
		strcat(aux, "-");
		strcat(aux, p1);
		strcpy(p1, aux);
	}
	/////////////////////////////////////////////////////final palavra 1
	/////////////////////////////////////////////////////inicio palavra 2
	aux[0] = '\0';
	not1=0;
	if(p2[0]=='-'){
		not1++;
		for(i=0; i<strlen(p2); i++){
			p2[i]=p2[i+1];
		}
	}
	retira_plural_palavra(p2);
	retira_genero_palavra(p2);
	if(not1!=0){
		strcat(aux, "-");
		strcat(aux, p2);
		strcpy(p2, aux);
	}
	/////////////////////////////////////////////////////final palavra 2
	/////////////////////////////////////////////////////inicio palavra 3
	aux[0] = '\0';
	not1=0;
	if(p3[0]=='-'){
		not1++;
		for(i=0; i<strlen(p3); i++){
			p3[i]=p3[i+1];
		}
	}
	retira_plural_palavra(p3);
	retira_genero_palavra(p3);
	if(not1!=0){
		strcat(aux, "-");
		strcat(aux, p3);
		strcpy(p3, aux);
	}
	/////////////////////////////////////////////////////final palavra 3
	
	
}
////////////////////////final parte pré processamento

////////////////////////inicio parte vetorial
void vetorial(char p1[50], char p2[50], char p3[50]){
	
}
////////////////////////final parte vetorial

////////////////////////inicio parte lógico
void junta_and(doc retorno1[200], doc retorno2[200], doc retorno3[200], int contretorno1, int contretorno2, int contretorno3){
	doc retorno1_2[200];
	int contretorno1_2=0;
	
	doc retorno1_2_3[200];
	int contretorno1_2_3=0;
	
	int i, j, flag;
	
	if(contretorno1 == 0 || contretorno2 == 0 || contretorno3 == 0){
		printf("Não há documentos a ser retornados para esta pesquisa (Conectivo AND)\n");
	}
	else{
		for(i=0; i<contretorno1; i++){
			flag=0;
			for(j=0; j<contretorno2 && flag==0; j++){
				if(retorno1[i].arquivo == retorno2[j].arquivo){
					flag++;
				}
			}
			if(flag!=0){
				retorno1_2[contretorno1_2].arquivo = retorno1[i].arquivo;
				contretorno1_2++;
			}
		}
		if(contretorno1_2 == 0){
			printf("Não há documentos a ser retornados para esta pesquisa (Conectivo AND)\n");
		}
		else{
			for(i=0; i<contretorno1_2; i++){
				flag=0;
				for(j=0; j<contretorno3 && flag==0; j++){
					if(retorno1[i].arquivo == retorno2[j].arquivo){
						flag++;
					}
				}
				if(flag!=0){
					retorno1_2_3[contretorno1_2_3].arquivo = retorno1[i].arquivo;
					contretorno1_2_3++;
				}
			}
			if(contretorno1_2_3 == 0){
				printf("Não há documentos a ser retornados para esta pesquisa (Conectivo AND)\n");
			}
			else{
				printf("A pesquisa retornou os seguintes documentos (Conectivo AND)\n");
				for(i=0; i<contretorno1_2_3; i++){
					printf("Doc: ", retorno1_2_3[i].arquivo);
				}
			}
		}
	}
}

void junta_or(doc retorno1[200], doc retorno2[200], doc retorno3[200], int contretorno1, int contretorno2, int contretorno3){
	doc retorno1_2_3[200];
	int contretorno1_2_3=0;
	
	int i, j, flag;
	
	if(contretorno1 == 0 && contretorno2 == 0 && contretorno3 == 0){
		printf("Não há documentos a ser retornados para esta pesquisa (Conectivo OR)");
	}
	else{
		for(i=0; i<contretorno1; i++){
			retorno1_2_3[contretorno1_2_3].arquivo = retorno1[i].arquivo;
			contretorno1_2_3++;
		}
		for(i=0; i<contretorno2; i++){
			flag=0;
			for(j=0; j<contretorno1_2_3 && flag==0; j++){
				if(retorno2[i].arquivo == retorno1_2_3[j].arquivo){
					flag++;
				}
			}
			if(flag==0){
				retorno1_2_3[contretorno1_2_3].arquivo = retorno2[i].arquivo;
				contretorno1_2_3++;
			}
		}
		for(i=0; i<contretorno3; i++){
			flag=0;
			for(j=0; j<contretorno1_2_3 && flag==0; j++){
				if(retorno3[i].arquivo == retorno1_2_3[j].arquivo){
					flag++;
				}
			}
			if(flag==0){
				retorno1_2_3[contretorno1_2_3].arquivo = retorno3[i].arquivo;
				contretorno1_2_3++;
			}
		}
		printf("A pesquisa retornou os seguintes documentos (Conectivo OR)\n");
		for(i=0; i<contretorno1_2_3; i++){
			printf("Doc: %d\n", retorno1_2_3[i].arquivo);
		}
	}
}

void logico(char p1[50], char p2[50], char p3[50], int conectivo){
	int not1=0, not2=0, not3=0;
	int i, j, k, l, flag_achar_palavra, flag_doc;
	doc aux[200];
	int contaux=0;
	
	doc retorno1[200];
	int contretorno1=0;
	
	doc retorno2[200];
	int contretorno2=0;
	
	doc retorno3[200];
	int contretorno3=0;
	
	if(p1[0]=='-'){
		not1++;
		for(i=0; i<strlen(p1); i++){
			p1[i]=p1[i+1];
		}
		// for para procurar todos os documentos que não tem a palavra 1 e gerar seu complemento em dicionario_bin_complemento
		//
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p1,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					aux[j].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contaux++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
		
		if(flag_achar_palavra!=0){
			for(i=0;i<contp;i++){		//passando por todas as palavras
				for(j=0;j<dicionario_bin[i].contDoc;j++){	//passando por todos os documentos dessas palavras
					flag_doc=0;
					for(k=0; k<contaux && flag_doc==0; k++){ //passando por todos os documentos que foram pegos anteriormente
						if(dicionario_bin[i].documentos[j].arquivo == aux[k].arquivo){
							flag_doc++;
						}
					}
					if(flag_doc==0){
						for(k=0; k<contretorno1; k++){
							if(retorno1[k].arquivo == dicionario_bin[i].documentos[j].arquivo){
								flag_doc++;
							}
						}
						if(flag_doc == 0){
							retorno1[contretorno1].arquivo = dicionario_bin[i].documentos[j].arquivo;
							contretorno1++;
						}
					}
				}
			}
		}	
	}
	else{
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p1,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					retorno1[contretorno1].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contretorno1++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
	}
	////////////////////////////////////////////////
	if(p2[0]=='-'){
		not2++;
		for(i=0; i<strlen(p2); i++){
			p2[i]=p2[i+1];
		}
		// for para procurar todos os documentos que não tem a palavra 2 e gerar seu complemento em dicionario_bin_complemento	
		//
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p2,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					aux[j].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contaux++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
		
		if(flag_achar_palavra!=0){
			for(i=0;i<contp;i++){		//passando por todas as palavras
				for(j=0;j<dicionario_bin[i].contDoc;j++){	//passando por todos os documentos dessas palavras
					flag_doc=0;
					for(k=0; k<contaux && flag_doc==0; k++){ //passando por todos os documentos que foram pegos anteriormente
						if(dicionario_bin[i].documentos[j].arquivo == aux[k].arquivo){
							flag_doc++;
						}
					}
					if(flag_doc==0){
						for(k=0; k<contretorno2; k++){
							if(retorno2[k].arquivo == dicionario_bin[i].documentos[j].arquivo){
								flag_doc++;
							}
						}
						if(flag_doc == 0){
							retorno2[contretorno2].arquivo = dicionario_bin[i].documentos[j].arquivo;
							contretorno2++;
						}
					}
				}
			}
		}	
	}
	else{
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p2,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					retorno2[contretorno2].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contretorno2++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
	}
	////////////////////////////////////////////////
	if(p3[0]=='-'){
		not3++;
		for(i=0; i<strlen(p3); i++){
			p3[i]=p3[i+1];
		}
		// for para procurar todos os documentos que não tem a palavra 3 e gerar seu complemento em dicionario_bin_complemento
		//
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p3,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					aux[j].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contaux++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
		
		if(flag_achar_palavra!=0){
			for(i=0;i<contp;i++){		//passando por todas as palavras
				for(j=0;j<dicionario_bin[i].contDoc;j++){	//passando por todos os documentos dessas palavras
					flag_doc=0;
					for(k=0; k<contaux && flag_doc==0; k++){ //passando por todos os documentos que foram pegos anteriormente
						if(dicionario_bin[i].documentos[j].arquivo == aux[k].arquivo){
							flag_doc++;
						}
					}
					if(flag_doc==0){
						for(k=0; k<contretorno3; k++){
							if(retorno3[k].arquivo == dicionario_bin[i].documentos[j].arquivo){
								flag_doc++;
							}
						}
						if(flag_doc == 0){
							retorno3[contretorno3].arquivo = dicionario_bin[i].documentos[j].arquivo;
							contretorno3++;
						}
					}
				}
			}
		}	
	}
	else{
		flag_achar_palavra=0;
		for(i=0;i<contp && flag_achar_palavra==0;i++){		//não esta achando a palavra
			if(strcmp(p3,dicionario_bin[i].pala)==0){
				flag_achar_palavra++;
				for(j=0; j<dicionario_bin[i].contDoc; j++){
					retorno3[contretorno3].arquivo = dicionario_bin[i].documentos[j].arquivo;
					contretorno3++;
				}//nesse momento aux tem todos os documentos que a palavra aparece, agora precisamos pegar todos que ela não aparece
			}
		}
	}
	
	if(conectivo==1){		//AND
		junta_and(retorno1, retorno2, retorno3, contretorno1, contretorno2, contretorno3);
	}
	else{					//OR
		junta_or(retorno1, retorno2, retorno3, contretorno1, contretorno2, contretorno3);
	}
	printf("\n");
	system("pause");
}
////////////////////////final parte lógico

////////////////////////inicio parte jerar, ver e atualizar dicionario
void passar_etapas_antigas(dic dicionario[], int tamanho){
	
	stopwords stop[1000];


    FILE *arqStop;
    arqStop=fopen("listaStopwords.txt","r");  //abrindo a lista de stopwords
    char t[100];
    int z=0,x;


//--------Palavras de stopwords sendo carregada na struct -------------


    if(arqStop == NULL)
        printf("Erro, nao foi possivel abrir o arquivo\n");
    else
    {
        while( (fscanf(arqStop,"%s\n", &t))!=EOF )
        {
            strcpy (stop[z].termo , t);   //copiando as stopwords na struct stop

            z++; //contando quantos termos tem na struct
        }

    }
    
    
    int w,y;
    for (w=0; w<=tamanho; w++)  //for que percorre a struct de entrada que tem tamanho i
    {
        for(y=0; y<=z; y++) //for que percorre a struct de stopwords que tem tamanho z
        {
            if(strcmp(dicionario[w].pala, stop[y].termo) == 0)  //compara se a palavra contem na lista de stopwords
                //se estiver na lista de stopwords, é apagada esta palavra e colocado os valores 0 no numero de documento e na frequencia
            {
                strcpy(dicionario[w].pala, "\n");
                dicionario[w].contDoc = 0;
                dicionario[w].freq = 0;
            }
        }
    }
    //////////////////////////////////////aqui acima tira as stop word
    int aux_novo, i, j;
    for(aux_novo = 0; aux_novo<tamanho; aux_novo++){	//ler o arquivo ate o final e coloca as informações nas variáveis temporarias
		
		retira_plural_palavra(dicionario[aux_novo].pala);
		retira_genero_palavra(dicionario[aux_novo].pala);
		
		int flag=0;														//variável auxiliar que fica '1' caso a nova palavra já esteja no dicionario
		for(i = 0; i < contp; i++){									//caso tenha palavras no dicionario o for percorre todas as palavras antes de adicionar uma nova
			if(strcmp(dicionario[aux_novo].pala, dicionario_bin[i].pala) == 0){					//verifica se a palavra a ser adicionada é igual a alguma palavra previamente adicionada
				dicionario_bin[i].documentos[dicionario_bin[i].contDoc].arquivo = dicionario[aux_novo].documentos[0].arquivo;	//caso já exista a palavra no dicionário
				dicionario_bin[i].documentos[dicionario_bin[i].contDoc].quant = dicionario[aux_novo].freq;	//adicina um novo documento e sua frequencia
				dicionario_bin[i].freq += dicionario[aux_novo].freq;										//a lista de documentos dessa palavra
				dicionario_bin[i].contDoc++;											//almenta o contador de documentos dessa palavra
				flag++;																//a flag idica que essa palavra não vai ser adicionada em um novo espaço do dicionário
				i = contp;															//faz o for ser finalizado, evitando ter que comprar essa palavra com todo o resto
			}
		}
		if(flag==0){													//caso a flag fique '0' é porque a palavra ainda não está no dicionário
			strcpy(dicionario_bin[contp].pala, dicionario[aux_novo].pala);						//então adiciona a palavra ao dicionário
			dicionario_bin[contp].documentos[0].arquivo = dicionario[aux_novo].documentos[0].arquivo;			//e as informações de documento e frequencia dessa palavra
			dicionario_bin[contp].documentos[0].quant = dicionario[aux_novo].freq;			//
			dicionario_bin[contp].freq = dicionario[aux_novo].freq;							//
			dicionario_bin[contp].contDoc = 1;
			contp++;													//aumenta o contador de palavras do dicionário
		}
	}

	///////////////////ordenação por numero do documento
	for(i=0; i<contp; i++){											//passar por todas as palavras
		if(dicionario_bin[i].contDoc > 1){								//verificar se a palavra aparece em mais de 1 documento
			int auxArq, auxQuant, auxTroca=0;						//variáveis auxiliares para transferir valores

			do{
				auxTroca=0;
				for(j=0; j < dicionario_bin[i].contDoc-1; j++){													//passar por todos os documentos que a palavra aparece
					if(dicionario_bin[i].documentos[j].arquivo > dicionario_bin[i].documentos[j+1].arquivo){		//verificar se a arquivo atual é maior que o arquivo j+1
						auxQuant = dicionario_bin[i].documentos[j].quant;										//trocar
						auxArq = dicionario_bin[i].documentos[j].arquivo;										//as

						dicionario_bin[i].documentos[j].quant = dicionario[i].documentos[j+1].quant;			//informações
						dicionario_bin[i].documentos[j].arquivo = dicionario[i].documentos[j+1].arquivo;		//entre

						dicionario_bin[i].documentos[j+1].quant = auxQuant;										//os
						dicionario_bin[i].documentos[j+1].arquivo = auxArq;										//arquivos

						auxTroca++;
					}
				}
			}while(auxTroca!=0);
		}
	}
	///////////////////fim da ordenação por numero do documento
}


void carrega_lista_palavras(char nome[50]){
    printf("Carregando as palavras!\n");
    FILE *arq = fopen (nome, "rb"); // Modo de leitura para o arquivo binário
    if (arq == NULL)
    {
        fprintf(stderr, "\nErro ao abrir arquivo\n"); // Se houve erro ao ler um arquivo binário
        exit (1);
    }
    
    fread (&contp, sizeof(contp), 1, arq);
    fread (&dicionario_bin, sizeof(struct Dicionario), contp, arq);
    //fread (&dicionario_bin_complementar, sizeof(struct Dicionario), contp, arq);

    if(fopen!= 0){
    	printf("Palavras carregadas com sucesso!\n"); // se der tudo certo a struct sera lida do arquivo binário
	}
    else{
    	printf("Erro na hora de ler as palavras!\n");
	}
    
}

void carrega_lista_palavras_em_txt(char nome[50]){
	int i, j;
	FILE *nomeArq;			//ponteiro para abrir arquivo
	char temp[50];			//variáveis temporarias
	int docTemp, freqTemp;	//para retirar as palavras do txt

	nomeArq = fopen(nome, "r");	//abertura do arquivo
	dic dicionario[155];
	
	int contp_carrega_lista = 0;
	
	while(fscanf(nomeArq, "%s %d %d", temp, &docTemp, &freqTemp) != EOF){	//ler o arquivo ate o final e coloca as informações nas variáveis temporarias

		int flag=0;														//variável auxiliar que fica '1' caso a nova palavra já esteja no dicionario
		for(i = 0; i < contp_carrega_lista; i++){									//caso tenha palavras no dicionario o for percorre todas as palavras antes de adicionar uma nova
			if(strcmp(temp, dicionario[i].pala) == 0){					//verifica se a palavra a ser adicionada é igual a alguma palavra previamente adicionada
				dicionario[i].documentos[dicionario[i].contDoc].arquivo = docTemp;	//caso já exista a palavra no dicionário
				dicionario[i].documentos[dicionario[i].contDoc].quant = freqTemp;	//adicina um novo documento e sua frequencia
				dicionario[i].freq += freqTemp;										//a lista de documentos dessa palavra
				dicionario[i].contDoc++;											//almenta o contador de documentos dessa palavra
				flag++;																//a flag idica que essa palavra não vai ser adicionada em um novo espaço do dicionário
				i = contp_carrega_lista;															//faz o for ser finalizado, evitando ter que comprar essa palavra com todo o resto
			}
		}
		if(flag==0){													//caso a flag fique '0' é porque a palavra ainda não está no dicionário
			strcpy(dicionario[contp_carrega_lista].pala, temp);						//então adiciona a palavra ao dicionário
			dicionario[contp_carrega_lista].documentos[0].arquivo = docTemp;			//e as informações de documento e frequencia dessa palavra
			dicionario[contp_carrega_lista].documentos[0].quant = freqTemp;			//
			dicionario[contp_carrega_lista].freq = freqTemp;							//
			dicionario[contp_carrega_lista].contDoc = 1;
			contp_carrega_lista++;													//aumenta o contador de palavras do dicionário
		}
	}
	passar_etapas_antigas(dicionario, contp_carrega_lista);
}

int quantdic(nom_dic *nomes){
	if(nomes == NULL){
		return 0;
	}
	else{
		return 1+quantdic(nomes->prox);
	}
}

bool verifica_nome_dic(nom_dic *nomes, char nome[]){
	if(nomes == NULL){
		return true;
	}
	else{
		if(strcmp(nomes->nome, nome) == 0){
			return false;
		}
		else{
			return verifica_nome_dic(nomes->prox, nome);
		}
	}
}

nom_dic* adicionar_lista(nom_dic *nomes, char nome[]){
	if(nomes == NULL){
		nom_dic *novo;
		novo = (nom_dic *)malloc(sizeof(nom_dic));
		novo->prox = NULL;
		strcpy(novo->nome, nome);
		nomes = novo;	
	}
	else{
		nomes->prox = adicionar_lista(nomes->prox, nome);
	}
	return nomes;
}

int menudicionario(){
	printf("Escolha\n");
	printf("1-Adicionar dicionários\n");
	printf("2-Ver nomes dos dicionários adicionados\n");
	printf("3-Ver todas as palavras adicionadas\n");
	printf("0-Sair do menu de dicionários\n");
	int aux;
	scanf("%d", &aux);
	return aux;
}

void nomes_dos_dici(nom_dic *nomes){
	if(nomes != NULL){
		printf("%s    ", nomes->nome);
		nomes_dos_dici(nomes->prox);
	}
}

void mostrar_todas_palavras(){
	int i, j;
	
	for(i=0; i<contp; i++){
		printf("Palavra: %s - ", dicionario_bin[i].pala); //Print da struct
		for(j=0; j<dicionario_bin[i].contDoc; j++){
			printf("doc: %d - freq: %d    ", dicionario_bin[i].documentos[j].arquivo, dicionario_bin[i].documentos[j].quant);
		}
		printf("\n");
	}
}

void main_dicionario(nom_dic **nomes){
	int sair = 0;
	

	char nome[50];
	do{
		system("cls");
		int var_escolha;
		printf("%d Dicionários (de nomes diferentes) inseridos ate o momento\n", quantdic(*nomes));
		var_escolha = menudicionario();
		switch(var_escolha){
			case 1:
				printf("Informe o nome e extensão dos arquivos de dicionario (ex: dici.dat)\n");
				scanf("%s", nome);
				//strcpy(nome, "TermosSemFeminino.dat"); 	//apagar depois
				
				if(verifica_nome_dic(*nomes, nome)){
					if(nome[strlen(nome)-2]=='a'){
						carrega_lista_palavras(nome);
					}
					else{
						carrega_lista_palavras_em_txt(nome);
					}
					printf("Arquivo lido\n");// digite um novo nome para adicionar mais arquivos ou 0 para sair\n");
					*nomes = adicionar_lista(*nomes, nome);
				}
				else{
					printf("\nEste dicionário já foi adicionado, adicionalo novamente vai aumentar as frequências\n");
					printf("das palavras que estão no mesmo, e isso irá interferir na busca vetorial, deseja\n");
					printf("adicionar mesmo assim?\n");
					printf("Escolha:\n1-Adicionar\n2-Não adicionar\n");
					int aux_escolha;
					scanf("%d", &aux_escolha);
					if(aux_escolha == 1){
						if(nome[strlen(nome)-2]=='a'){
							carrega_lista_palavras(nome);
						}
						else{
							carrega_lista_palavras_em_txt(nome);
						}
						//printf("Arquivo lido\n");//, digite um novo nome para adicionar mais arquivos ou 0 para sair\n");
					}
				}
							
			break;
			case 2:
				nomes_dos_dici(*nomes);
				printf("\n");
			break;
			case 3:
				mostrar_todas_palavras();
			break;
			case 0:
				if(quantdic(*nomes) > 0){
					sair++;
				}
				else{
					printf("É preciso ler no mínimo 1 dicionário para continuar\n");
				}
				
			break;
			default:
				printf("Opção inválida\n");
		}
		system("pause");
	}while(sair==0);
}
////////////////////////final parte jerar, ver e atualizar dicionario

int menu_main(){
	system("cls");
	int rep;
	printf("Escolha:\n");
	printf("1-Iniciar uma busca\n");
	printf("2-Voltar ao menu de dicionários\n");
	printf("0-Sair\n");
	scanf("%d", &rep);
	return rep;
}

int main(){
	setlocale(LC_ALL, "Portuguese");
	printf("Trabalho 3 - Buscas\n");
	
	nom_dic *nomes;
	nomes = NULL;
	
	main_dicionario(&nomes);
	
	int op=0, rep;
	char p1[50], p2[50], p3[50];
	do{
		rep = menu_main();
		switch(rep){
			case 1:
				printf("Palavra 1: ");
				scanf("%s", p1);
				printf("Palavra 2: ");
				scanf("%s", p2);
				printf("Palavra 3: ");
				scanf("%s", p3);
			
				preprocessamento(p1, p2, p3);
		
				if(p1[0]=='-' || p2[0]=='-' || p3[0]=='-'){
					op = 2;
				}	
				else{
					printf("Escolha da forma de busca:\n1-Para busca vetorial\n2-Para busca logica\n");
					scanf("%d", &op);
				}
				switch(op){
					case 1:
						vetorial(p1, p2, p3);
					break;
					case 2:
						int conectivo;
						printf("Definir conectvo\n1-AND\n2-OR\n");
						scanf("%d", &conectivo);
						logico(p1, p2, p3, conectivo);
					break;
				}
			break;
			case 2:
				main_dicionario(&nomes);
			break;
			case 0:
				rep=0;
			break;
			default:
				printf("Opção inválida\n");		
		}		
	}while(rep!=0);
	return 0;
}
