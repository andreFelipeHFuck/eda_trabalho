#include "multi-LDDE.h"

void menu(){
    printf("1 - Buscar palavra\n");
    printf("2 - Remover palavra\n");
    printf("3 - Remover palavra por linha e coluna\n");
    printf("4 - Inserir palavra\n");
    printf("5 - Editar palavra\n");
    printf("6 - Numero de palavras com substring\n");
    printf("7 - Numero de ocorrencias de uma palavra\n");
    printf("8 - Numero total de palavras no texto\n");
   
    printf("0 - Sair\n");
    printf("> ");
}

void leituraTexto(Descritor *desc){
    system("clear");

    printf("Texto:\n");

    leituraDaLista(desc);
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

void numeroDePalavrasSubstring(Descritor *desc){
    system("clear");
    char finaliza[10];
    char palavra[30];

    printf("Numero de palavras com uma substring:\n");
    printf("Digite a substring:\n");
    printf("> ");
    scanf("%s", palavra);

    exibirPalavrasComSubstring(desc, palavra);

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

void inserirPalavra(Descritor *desc){
    system("clear");

    Palavra *palavra = NULL;

    char finaliza[10];
    char p[30];

    int linha = 0, posLog = 0;
    int teste;

    palavra = (Palavra *) malloc(sizeof(Palavra));

    printf("Inserir palavra\n");

    printf("Digite a palavra: \n");
    printf("> ");
    scanf("%s", p);
    strcpy(palavra->palavra, p);

    while (1)
    {
        printf("Digite o numero da linha:\n");
        printf("> ");
        scanf("%d", &linha);

        if(linha > 0 && linha <= desc->numLinhas){
            palavra->linha = linha;
            break;
        }else{
            printf("Linha não existente, por favor tente de novo");
        }
    }

    printf("Posição logica:\n");
    printf("> ");
    scanf("%d", &posLog);

    teste = inserePalavraPoslog(desc, palavra, posLog);

    if(teste == SUCESSO){
        printf("Palavra inserida com sucesso\n");
    }else{
        printf("Não foi possivel inserir a palavra\n");
    }

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin); 
}

void editarPalavraTexto(Descritor *desc){
    system("clear");
    char finaliza[10];
    int linha, coluna;

    printf("Edição de uma palavra\n");

    printf("Linha:\n");
    printf("> ");
    scanf("%d", &linha);

    printf("Coluna:\n");
    printf("> ");
    scanf("%d", &coluna);

    int resultado = editarPalavra(desc, linha, coluna);

    if(resultado == 1){
        printf("Palavra editada com sucesso\n");
    }else{
        printf("Não foi possivel editar a paalvra\n");
    }

    printf("\nAperte qualquer botão para sair: \n");
    printf("> ");
    __fpurge(stdin);
    fgets(finaliza, 10, stdin);
}

int main(){
    Descritor *desc = construirSistema("arquivo.txt");

    int opt;
    
    while (opt != 0){
        leituraTexto(desc);
        menu();
        scanf("%d", &opt);

        switch (opt){
            
        case 1:
            buscaPalavraTexto(desc);
            break;
        case 2:
            removerPalavraTexto(desc);
            break;
        case 3:
            removerPalavraLinhaColunaTexto(desc);
            break;
        case 4:
            inserirPalavra(desc);
            break;
        case 5:
            editarPalavraTexto(desc);
            break;
        case 6:
            numeroDePalavrasSubstring(desc);
            break;
        case 7:
            numeroDeUmaPalvraTexto(desc);
            break;
        case 8:
            numeroTotalPalavrasTexto(desc);
            break;
      
        case 0:
            salvarArquivo(desc);
            break;
        default:
            break;
        }
    }
    
}

