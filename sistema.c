#include "multi-LDDE.h"

Descritor* construirSistema(char arquivo[30]){
    Descritor *desc = inicializaDescritor();

    int numPalavras = numeroPalavras("arquivo.txt");

    int numLinhas = numeroDeLinhas("arquivo.txt");

    int *numLetraInicial = numeroPosicaoLetraInicial("arquivo.txt", numPalavras);

    Palavra *palavras = geraPalavras("arquivo.txt",numLetraInicial, numPalavras);

     for(int i=0; i<numLinhas;i++){
        insereLinhaUltimo(desc);
    }
    
    for(int i=0; i<numPalavras; i++){
       int teste =  insereNoLinhaUltimo(desc, palavras[i].linha, palavras[i]);
    }

    return desc;
}

void salvarArquivo(Descritor *desc){
    Palavra *palavras = geraPalavrasMulti(desc);
    int numPalavras = numeroTotalPalavras(desc);
    escreverArquivo(palavras, numPalavras);
}
