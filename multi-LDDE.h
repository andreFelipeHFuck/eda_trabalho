#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio_ext.h>

#define NAO 0
#define SIM 1

#define FRACASSO 0
#define SUCESSO 1

typedef struct palavra{
    int linha;
    int posicaoLetraInicial;
    char palavra[30];
}Palavra;

typedef struct no
{
    struct no* proximo;
    Palavra palavra;
    struct no* anterior;
}No;

typedef struct multi_pilha
{
    struct multi_pilha* emcima;
    int num_palavras;
    No* inicio;
    struct multi_pilha* abaixo;
}Linha;

typedef struct descritor
{
    int numLinhas;
    Linha* primeiraLinha; 
}Descritor;

// Manipula Texto
FILE * abrirArquivo(char nomeArquivo[30]);

int numeroDeLinhas(char nomeArquivo[30]);

int numeroPalavras(char nomeArquivo[30]);

Palavra* geraPalavras(char nomeArquivo[30], int *numLetraInicial,int numeroPalavras);

int* numeroPosicaoLetraInicial(char nomeArquivo[30], int numeroPalavras);

void escreverArquivo(Palavra *palavras, int numPalavras);

// Manipula a lista
Descritor* inicializaDescritor();
Linha* inicializaLinha();

int insereLinhaPrimeiro(Descritor *desc);

int insereLinhaUltimo(Descritor *desc);

int insereNoLinha(Descritor *desc, int numLinha, Palavra palavra);

int insereNoLinhaUltimo(Descritor *desc, int numLinha, Palavra palavra);

void leituraDaLista(Descritor *desc);

void buscaPalavra(Descritor *desc, char palavra[30]);

int removePalavraInicio(Linha *linha);

int removePalavra(Descritor *desc, char palavra[30]);

int removerPalavraLinhaColuna(Descritor *desc, int linha, int coluna);

int numeroDeUmaPalvra(Descritor *desc, char palavra[30]);

int numeroTotalPalavras(Descritor *desc);

int inserePalavraInicio(Descritor *desc, Palavra *palavra);

int inserePalavraPoslog(Descritor *desc, Palavra *palavra, int posLog);

int editarPalavra(Descritor *desc, int linha, int coluna);

void exibirPalavrasComSubstring(Descritor *desc, char substring[30]);

Palavra* geraPalavrasMulti(Descritor *desc);

// Sistema

Descritor* construirSistema(char arquivo[30]);

