#include "multi-LDDE.h"

void menu(){
    system("clear");
    printf("1 - Ler texto\n");
    printf("2 - Buscar palavra\n");
    printf("3 - Remover palavra\n");
    printf("4 - Remover palavra por linha e coluna\n");
    printf("5 - Numero de ocorrencias de uma palavra\n");
    printf("6 - Numero total de palavras no texto\n");
    printf("7 - Numero de palavras com substring\n");
    printf("8 - Inserir palavra\n");
    printf("0 - Sair\n");
    printf("> ");
}

void leituraTexto(Descritor *desc){
    system("clear");
    char finaliza[10];

    printf("Texto:\n");

    leituraDaLista(desc);

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void buscaPalavraTexto(Descritor *desc){
    system("clear");
    char finaliza[10];
    char palavra[30];

    printf("Buscar palavra no texto\n");
    printf("> ");
    scanf("%s", palavra);

    buscaPalavra(desc, palavra);

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void removerPalavraTexto(Descritor *desc){
    system("clear");
    char finaliza[10];
    char palavra[30];

    printf("Digite a palavra que deseja remover\n");
    printf("> ");
    scanf("%s", palavra);

    int resultado = removePalavra(desc, palavra);

    if(resultado == 1){
        printf("Palavra removida com sucesso\n");
    }else{
        printf("Erro ao remover a palavra");
    }

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void removerPalavraLinhaColunaTexto(Descritor *desc){
    system("clear");
    char finaliza[10];
    int linha, coluna;

    printf("Remover palavra a partir da sua linha e coluna\n");

    printf("Linha:\n");
    printf("> ");
    scanf("%d", &linha);

    printf("Coluna:\n");
    printf("> ");
    scanf("%d", &coluna);

    int resultado = removerPalavraLinhaColuna(desc, linha, coluna);
    
    if(resultado == 1){
        printf("Palavra removida com sucesso\n");
    }else{
        printf("Erro ao remover a palavra");
    }

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void numeroDeUmaPalvraTexto(Descritor *desc){
    system("clear");
    char finaliza[10];
    char palavra[30];

    printf("Numero de ocorrencias de uma palavra no texto\n");
    printf("Palavra:\n");
    printf("> ");
    scanf("%s", palavra);

    int num = numeroDeUmaPalvra(desc, palavra);
    printf("%s ocorre %d vezes no texto", palavra, num);

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void numeroTotalPalavrasTexto(Descritor *desc){
    system("clear");
    char finaliza[10];

    int num = numeroTotalPalavras(desc);
    printf("O texto tem %d palavra(s)", num);

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

int main(){
    Descritor *desc = construirSistema("arquivo.txt");

    int opt;
    
    while (opt != 0){
        menu();
        scanf("%d", &opt);

        switch (opt){

        case 0:
            break;
        case 1:
            leituraTexto(desc);
            break;
        case 2:
            buscaPalavraTexto(desc);
            break;
        case 3:
            removerPalavraTexto(desc);
            break;
        case 4:
            removerPalavraLinhaColunaTexto(desc);
            break;
        case 5:
            numeroDeUmaPalvraTexto(desc);
            break;
        case 6:
            numeroTotalPalavrasTexto(desc);
        default:
            break;
        }
    }
    
}

