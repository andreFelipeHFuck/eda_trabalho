#include "multi-LDDE.h"

Descritor* inicializaDescritor(){
    Descritor * descritor = (Descritor*) malloc(sizeof(Descritor));

    if(descritor){
        descritor->primeiraLinha = NULL;
        descritor->numLinhas = 0;
    }

    return descritor;
}

int insereLinhaPrimeiro(Descritor *desc){
    Linha * temporario;
    int retorno = FRACASSO;

    temporario = (Linha*) malloc(sizeof(Linha));

    if(temporario){
       temporario->num_palavras = 0;
       temporario->emcima = NULL;
       temporario->inicio = NULL;
       temporario->abaixo = NULL;

       (desc->numLinhas)++;
       if(desc->primeiraLinha != NULL){
            desc->primeiraLinha->abaixo = temporario;
       }
       desc->primeiraLinha = temporario;
       retorno = SUCESSO;
    }
    return retorno;
}

int insereLinhaUltimo(Descritor *desc){
    Linha *temporario = NULL, *aux;
    int retorno = FRACASSO;

    temporario = (Linha*) malloc(sizeof(Linha));

    if(desc->primeiraLinha == NULL){
        retorno = insereLinhaPrimeiro(desc);     
    }else{
        aux = desc->primeiraLinha;

        while (aux->abaixo != NULL){
            aux = aux->abaixo;
        }

        if(temporario != NULL){
            (desc->numLinhas)++;
            temporario->inicio = NULL;
            aux->abaixo = temporario;
            temporario->abaixo = NULL;
            temporario->emcima = aux;
            retorno = SUCESSO;
        }else{
            retorno = FRACASSO;
        }
    }
    return retorno;
}

int insereNoLinha(Descritor *desc, int numLinha, Palavra palavra){
    No *temporario;
    Linha *aux = (Linha*) malloc(sizeof(Linha));
    temporario = (No*) malloc(sizeof(No));
    int retorno = FRACASSO, contador = 1;
    
   if(desc->numLinhas > 0){
      aux = desc->primeiraLinha;

      while (aux != NULL)
      {
        if(contador == numLinha){
            break;
        }else{
            aux = aux->abaixo;
            contador++;
        }
      }
     
      if(temporario){
        memcpy(&(temporario->palavra), &palavra, sizeof(Palavra));
        temporario->anterior = NULL;
        if(aux->inicio != NULL){
            aux->inicio->anterior = temporario;
        }
        aux->inicio = temporario;
        retorno = SUCESSO;
      }
   }
   return retorno;
}

int insereNoLinhaUltimo(Descritor *desc, int numLinha, Palavra palavra){
    No *temporario = NULL, *auxNo;
    Linha *aux = (Linha*) malloc(sizeof(Linha));
    int retorno = FRACASSO, contador = 1;

    temporario = (No*) malloc(sizeof(No));
    
   if(numLinha <= desc->numLinhas && desc->numLinhas > 0){
      aux = desc->primeiraLinha;

      while (aux != NULL)
      {
        if(contador == numLinha){
            break;
        }else{
            aux = aux->abaixo;
            contador++;
        }
      }
      if(aux->inicio == NULL){
        retorno = insereNoLinha(desc, numLinha, palavra);
      }else{
        auxNo = aux->inicio;
        while (auxNo->proximo != NULL)
        {
            auxNo = auxNo->proximo;
        }
       
        if(temporario){
            memcpy(&(temporario->palavra), &palavra, sizeof(Palavra));
            auxNo->proximo = temporario;
            temporario->proximo = NULL;
            temporario->anterior = auxNo;
            retorno = SUCESSO;
        }else{
            retorno = FRACASSO;
        }
      }
   }
   return retorno;
}

void leituraDaLista(Descritor *desc){
    Linha *auxLinha = desc->primeiraLinha;
    No *auxNo;
    int contador = 1;

    printf(" ");
    while (auxLinha != NULL)
    {
        printf("%d ", contador);
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            printf("%s ", auxNo->palavra.palavra);
            auxNo = auxNo->proximo;
        }
        
        contador++;
        auxLinha = auxLinha->abaixo;
    }
    printf("\n");
    
}

void buscaPalavra(Descritor *desc, char palavra[30]){
    Linha *auxLinha = desc->primeiraLinha;
    No *auxNo;
    int palavrasIguais;

    while (auxLinha != NULL)
    {
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            palavrasIguais = strcmp(palavra, auxNo->palavra.palavra);
            if(palavrasIguais == 0){
                printf("Linha: %d Coluna: %d\n", auxNo->palavra.linha, auxNo->palavra.posicaoLetraInicial);
            }
            auxNo = auxNo->proximo;
        }
        auxLinha = auxLinha->abaixo;
    }   
}

void somarPosicaoLetraInicial(Linha *linha, char palavra[30], int num){
    No *auxNo = linha->inicio;
    int flag = 0;

    while (auxNo != NULL){
        if(strcmp(palavra, auxNo->palavra.palavra) == 0){
            flag = 1;
        }
        if(flag == 1){
            auxNo->palavra.posicaoLetraInicial += num;
        }
        auxNo = auxNo->proximo;
    }
}

void subtrairPosicaoLetraInicial(Linha *linha, char palavra[30], int num){
    No *auxNo = linha->inicio;
    int flag = 0;

    while (auxNo != NULL){
        if(strcmp(palavra, auxNo->palavra.palavra) == 0){
            flag = 1;
        }
        if(flag == 1 && !(auxNo->palavra.posicaoLetraInicial - num < 0)){
            auxNo->palavra.posicaoLetraInicial -= num;
        }
        auxNo = auxNo->proximo;
    }
}

int removePalavraInicio(Linha *linha){
    int ret = FRACASSO;

    if(linha->inicio != NULL){
        if(linha->inicio->proximo == NULL){
            free(linha->inicio);
            linha->inicio = NULL;
        }else{
            subtrairPosicaoLetraInicial(linha, linha->inicio->palavra.palavra, strlen(linha->inicio->palavra.palavra) + 1);
            linha->inicio = linha->inicio->proximo;
            free(linha->inicio->anterior);
            linha->inicio->anterior = NULL;
        }
        ret = SUCESSO;
    }
    return ret;
}

int removePalavra(Descritor *desc, char palavra[30]){
    int palavrasIguais;
    int contLinha = 1, ret = FRACASSO;

    Linha *auxLinha;
    No *auxNo, *pos;

    auxLinha = desc->primeiraLinha;
    while (auxLinha != NULL)
    {
        if(strcmp(palavra, auxLinha->inicio->palavra.palavra) == 0){
            ret = removePalavraInicio(auxLinha);
        }else{
            pos = auxLinha->inicio->proximo;
            if(pos != NULL){
                subtrairPosicaoLetraInicial(auxLinha, palavra, strlen(palavra));
                while ((strcmp(palavra, pos->palavra.palavra) != 0) && pos->proximo != NULL){
                    pos = pos->proximo;
                }
                if(strcmp(palavra, pos->palavra.palavra) == 0){
                    if(pos->proximo != NULL){
                        pos->proximo->anterior = pos->anterior;
                    }
                    pos->anterior->proximo = pos->proximo;
                    free(pos);
                    ret = SUCESSO;
                }
                
            }
        }
        contLinha++;
        auxLinha = auxLinha->abaixo;
    }
    return ret;  
}

int removerPalavraLinhaColuna(Descritor *desc, int linha, int coluna){
    Linha *auxLinha;
    No *pos;

    int contLinha = 1;
    int ret = FRACASSO;

    char palavra[30];

    auxLinha = desc->primeiraLinha;
    while (auxLinha != NULL){
        if(contLinha == linha){
            if(auxLinha->inicio->palavra.posicaoLetraInicial == coluna){
                ret = removePalavraInicio(auxLinha);
            }else{
                while (pos->palavra.posicaoLetraInicial != coluna && pos->proximo != NULL){
                    pos = pos->proximo;
                }
                strcpy(palavra, pos->proximo->palavra.palavra);
                subtrairPosicaoLetraInicial(auxLinha, palavra, strlen(palavra));

                if(pos->palavra.posicaoLetraInicial == coluna){
                    if(pos->proximo != NULL){
                        pos->proximo->anterior = pos->anterior;
                    }
                    pos->anterior->proximo = pos->proximo;
                    free(pos);
                    ret = SUCESSO;
                }
                
            }
        }
        contLinha++;
        auxLinha = auxLinha->abaixo;
    }
    return ret;
}

int numeroDeUmaPalvra(Descritor *desc, char palavra[30]){
    Linha *auxLinha = desc->primeiraLinha;
    No *auxNo;
    int palavrasIguais;
    int contador = 0;

    while (auxLinha != NULL)
    {
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            palavrasIguais = strcmp(palavra, auxNo->palavra.palavra);
            if(palavrasIguais == 0){
                contador++;
            }
            auxNo = auxNo->proximo;
        }
        auxLinha = auxLinha->abaixo;
    }   
    return contador;
}

int numeroTotalPalavras(Descritor *desc){
    Linha *auxLinha = desc->primeiraLinha;
    No *auxNo;
    int palavrasIguais;
    int contador = 0;

    while (auxLinha != NULL)
    {
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            auxNo = auxNo->proximo;
            contador++;
        }
        auxLinha = auxLinha->abaixo;
    }   
    return contador;
}

// TO DO: Reescrever a função como insereNoLinha
int inserePalavraInicio(Descritor *desc, Palavra *palavra){
    Linha *auxLinha;
    No *temp;

    int cont = 1;
    int ret = FRACASSO;

    temp = (No*) malloc(sizeof(No));
    auxLinha = desc->primeiraLinha;

    while (auxLinha != NULL)
    {
        if(cont == palavra->linha){
            memcpy(&(temp->palavra), palavra, sizeof(Palavra));
            temp->proximo = auxLinha->inicio;
            temp->anterior = NULL;
            if(auxLinha->inicio != NULL){
                auxLinha->inicio->anterior = temp;
            }
            auxLinha->inicio = temp;
            somarPosicaoLetraInicial(auxLinha, palavra->palavra, strlen(palavra->palavra));
            ret = SUCESSO;
        }
        cont++;
        auxLinha = auxLinha->abaixo;
    }
    
    return ret;
}

int inserePalavraPoslog(Descritor *desc, Palavra *palavra, int posLog){
    Linha *auxLinha;
    No *temp, *pos, *auxNo;
    int contLinha = 1, contNo, ret = FRACASSO;

    auxLinha = desc->primeiraLinha;
    while (auxLinha != NULL)
    {
        if(contLinha == palavra->linha){
            if(posLog == 1){
                ret = inserePalavraInicio(desc, palavra);
            }else{
                temp = (No*) malloc(sizeof(No));
                pos = auxLinha->inicio->proximo;
                if(pos != NULL){
                    contNo = 2;
                    while (contNo < posLog && pos->proximo != NULL){
                        pos = pos->proximo;
                        contNo++;
                    }
                    if(contNo == posLog){
                        memcpy(&(temp->palavra), palavra, sizeof(Palavra));
                        temp->proximo = pos;
                        temp->anterior = pos->anterior;
                        pos->anterior->proximo = temp;
                        pos->anterior = temp;
                        somarPosicaoLetraInicial(auxLinha, palavra->palavra, strlen(palavra->palavra));
                        ret = SUCESSO;
                    }else{
                        insereNoLinhaUltimo(desc, palavra->linha, *palavra);
                    }
                }
            }
        }
        contLinha++;
        auxLinha = auxLinha->abaixo;
    }
    return ret;
}

int editarPalavra(Descritor *desc, int linha, int coluna){
    Linha *auxLinha;
    No *auxNo;
    int tamPalavra;
    char novaPalavra[30];

    auxLinha = desc->primeiraLinha;
    while (auxLinha != NULL)
    {
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            if(auxNo->palavra.linha == linha && auxNo->palavra.posicaoLetraInicial == coluna){
                printf("Editar palavra: %s\n", auxNo->palavra.palavra);
                printf("> ");
                scanf("%s", novaPalavra);
                strcpy(auxNo->palavra.palavra, novaPalavra);
            }
            auxNo = auxNo->proximo;
        }
        
        auxLinha = auxLinha->abaixo;
    }
    
}

void exibirPalavrasComSubstring(Descritor *desc, char substring[30]){
    Linha *auxLinha;
    No *auxNo;
    char *sub;
    int cont = 0;

    auxLinha = desc->primeiraLinha;
    while (auxLinha != NULL)
    {
        auxNo = auxLinha->inicio;
        while (auxNo != NULL)
        {
            sub = strstr(auxNo->palavra.palavra, substring);
            if(sub){
                printf("(%d, %d): %s\n", auxNo->palavra.linha, auxNo->palavra.posicaoLetraInicial, auxNo->palavra.palavra);
                cont++;
            }
            auxNo = auxNo->proximo;
        }
        
        auxLinha = auxLinha->abaixo;
    
    }
    printf("Total de palvras: %d\n", cont);
    
}

Palavra* geraPalavrasMulti(Descritor *desc){
    Linha *auxLinha;
    No *auxNo;
    Palavra *palavras;
    int i = 0;
    int numeroPalavras = numeroTotalPalavras(desc);

    palavras = (Palavra*) malloc(numeroPalavras * sizeof(Palavra));
    auxLinha = desc->primeiraLinha;

    while (auxLinha != NULL){
        auxNo = auxLinha->inicio;
        while (auxNo != NULL){
            palavras[i] = auxNo->palavra;
            auxNo = auxNo->proximo;
            i++;
        }
        auxLinha = auxLinha->abaixo;
    }
    return palavras;
}