#include "multi-LDDE.h"

FILE * abrirArquivo(char nomeArquivo[30]){
    FILE *arq = fopen(nomeArquivo, "rt");

    if(arq){
        return arq;
    }else{
        return NULL;
    }
}

int numeroDeLinhas(char nomeaArquivo[30]){
    FILE *arq = abrirArquivo(nomeaArquivo);

    int numLinhas = 0;
    char c;

    if(arq != NULL){
        for(c = getc(arq); c != EOF; c = getc(arq)){
            if(c == '\n'){
                numLinhas++;
            }
        }
    }else{
        printf("Não foi possivel abrir o arquivo");
    }
    fclose(arq);
    return numLinhas;
}

int numeroPalavras(char nomeArquivo[30]){
    FILE *arq = abrirArquivo(nomeArquivo);
    int contador = 0;
    size_t len = 100;
    char * linha = malloc(len);
    char *palavra;

    while (getline(&linha, &len, arq) > 0)
    {
        palavra = strtok(linha, " ");
        while(palavra){
            contador++;
            palavra = strtok(NULL, " ");
        }
    }
    free(palavra);
    free(linha);
    fclose(arq);
    return contador;
}

int* numeroPosicaoLetraInicial(char nomeArquivo[30], int numeroPalavras){
    FILE *arq = abrirArquivo(nomeArquivo);
    char letra;
    int *posicaoInicialLetras = (int*) malloc(numeroPalavras * sizeof(int));
    int i = 0;
    int contador = 0;
    int ehEspaco = NAO;

    while (!feof(arq))
    {
        
        letra = fgetc(arq);
        if(letra == '\n'){
            contador = 0;
            continue;
        }
        if(isalpha(letra) && (ehEspaco == SIM || contador == 0)){
            ehEspaco = NAO;
            posicaoInicialLetras[i] = contador;
            i++;
        }else if(isspace(letra)){
            ehEspaco = SIM;
        }
        contador++;
    }
    fclose(arq);

    return posicaoInicialLetras;
}

Palavra * geraPalavras(char nomeArquivo[30], int *numLetraInicial,  int numeroPalavras){
    FILE *arq = abrirArquivo(nomeArquivo);
    Palavra * palavras = NULL;
    palavras = malloc(numeroPalavras * sizeof(Palavra));

    int numLinha = 1;
    int i = 0;
    size_t len = 100;
    size_t ln;
    char * linha = malloc(len);
    char *palavra;

    while (getline(&linha, &len, arq) > 0)
    {
        palavra = strtok(linha, " ");
        while(palavra){
            palavras[i].linha = numLinha;
            palavras[i].posicaoLetraInicial = numLetraInicial[i];
            ln = strlen(palavra) - 1;
            if(palavra[ln] == '\n'){
                palavra[ln] = '\0';
            }
            strcpy(palavras[i].palavra, palavra);
            palavra = strtok(NULL, " ");
            i++;
        }
        numLinha++;
    }
    free(linha);
    fclose(arq);
    return palavras;
}

void escreverArquivo(Palavra *palavras, int numPalavras){
    FILE *arq;
    arq = fopen("arqTemp.txt", "w");
    int linha = palavras[0].linha;
    
    if(arq == NULL){
        printf("Erro, não foi possivel abrir o arquivo\n");
    }else{
        for(int i = 0; i<numPalavras; i++){
            if(linha != palavras[i].linha){
                linha = palavras[i].linha;
                fprintf(arq, "\n");
                fprintf(arq, "%s ", palavras[i].palavra);
            }else{
                fprintf(arq, "%s ", palavras[i].palavra);
            }
        }
        fprintf(arq, "\n");
        rename("arquivo.txt", "arquivoOLD.txt");
        rename("arqTemp.txt", "arquivo.txt");
    }
   
    fclose(arq);
}
