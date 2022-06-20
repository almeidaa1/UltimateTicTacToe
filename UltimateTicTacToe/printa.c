/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"

// VAI MOSTRAR NA CONSOLA OS TITULOS
int printaTitulos(char* nomeF) {
    FILE* f = fopen(nomeF, "r");
    if(f == NULL) return 0;
    
    char linha[200];
    int count = 0;
    while(fgets(linha, 200, f) != NULL)
        printf("%s", linha);
    // char c; // caracter
    // while((c = fgetc(f)) != EOF) // enquanto for diferente de "end of file", ou seja, enquanto nao chegar ao fim do ficheiro
    //     putchar(c);

    fclose(f);
    return 1;
}

// MOSTRA NA CONSOLA O TABULEIRO ULTIMATE
void printaTabuleiro(int colunas, bloco* uBoard, int uBloco, int vencedorUlti) {

    int x = 0; // para que se possa percorrer todas as posiçoes do array //
    
    // vai printar o tabuleiro Ultimate com a posicao de cada bloco dos mini tabuleiros V //
    printf("\n");
    for(int i = 0; i < uBloco; i++){
        printf("\t\t\t\t ");
        for(int j = 0; j < uBloco; j++, x++) {
            // printa todo o tabuleiro mini tabuleiro vencedor como o simbolo do jogador ganhador do mesmo
            if(uBoard[x].vencedor == 'x' || uBoard[x].vencedor == 'o')
                printf("  %c   ", uBoard[x].vencedor - ' '); // - ' ', para transformar para UpperCase
            else 
            if(uBoard[x].c == '_' && !vencedorUlti)
                printf("(%d,%d) ", uBoard[x].linha, uBoard[x].coluna);
            else 
            if(uBoard[x].c == '_' && vencedorUlti == 1)
                printf("  -   ", uBoard[x].c);
            else
                printf("  %c   ", uBoard[x].c);
            if(!((x + 1) % colunas) && j != uBloco-1) 
                printf("|| "); // < printa as barras verticais que separam //
        }
    printf("\n");
        // barras horizontais que separam o jogo
        if(!((i + 1) % colunas) && i != uBloco-1){                        
            printf("\t\t\t\t ");
            for(int k = 1; k < 60; k++) // printa as barras horizontais //
                printf("=");
            printf("\n");
        }
    }
}

// MOSTRA NA CONSOLA A SEGUIR DE UMA JOGADA, A JOGADA EFETUADA
void printaJogadaEfetuada(int tab, int l, int c) {
    printf("\n\t\t\t\t  Jogada Efetuada  >>   Tabuleiro [ %d ]     Posicao (%d,%d)  ", tab, l, c);
}

// CASO HAJA UM VENCEDOR NUM MINI TABULEIRO, MOSTRA O MINI TABULEIRO QUE FOI E O SEU CONQUISTADOR
void printaInfoTabConquistado(int nJogadas, int modo, int jog, int nextTab) {
    if(nJogadas >=5) {
        if(modo == 1)
            printf("\n\n\t\t\t\t     -| O Jogador [ %d ] Conquistou o Mini Tabuleiro %d |-", jog, nextTab);
        if(modo == 2 && jog == 1)
            printf("\n\n\t\t\t\t\t     -| Conquistaste o Mini Tabuleiro %d |-             ", nextTab);
        else 
        if(modo == 2 && jog == 2)
            printf("\n\n\t\t\t\t       -| O Computador Conquistou o Mini Tabuleiro %d |-       ", nextTab);
    }
}

// MOSTRA ANTES DA JOGADA, O JOGADOR QUE A VAI REALIZAR E RESPETIVO SIMBOLO E EM QUE TABULEIRO VAI SER PARA JOGAR
void printaInformacaoDaJogada(int livre, int nextTab, int modo, int jog, char cJog) {
    
    printf("\n\t\t\t\t ###############");
    if(livre == 1) printf("\t\t\t  |+ Jogada Livre +|");
    else 
    if(modo != 2 || jog != 2) printf("\t\t  |+ Jogar no Tabuleiro %d +|", nextTab);
    else 
    if(modo == 2) printf("\t\t           |+ Tabuleiro %d +|", nextTab);
    if(modo == 1)
        printf("\n\t\t\t\t #| Jogador %d |#", jog);
    if(modo == 2 && jog == 1)
        printf("\n\t\t\t\t #|  Sua Vez  |#", jog);
    if(modo == 2 && jog == 2)
        printf("\n\t\t\t\t #|    A.I    |#", jog);
    printf("\n\t\t\t\t ###############");
    if(modo != 2 || jog != 2) {
        if(livre == 1) printf("\t\t\t  Simbolo [ %c ]\n", cJog);
        else printf("\t\t  Simbolo [ %c ]\n", cJog);
    }else
        printf("\t\t\t       Simbolo [ %c ]\n", cJog);
}

// MOSTRA AS JOGADAS ANTERIORES, CONSOANTE O NUMERO PEDIDO A VISUALIZAR
void printaJogadasAnteriores(blocoLista* lista, int jAnt, int nJogadas, int modo, int opcao){
    int i = 0;
    int jogada = nJogadas; // para possibilitar o numeraçao das jogadas conforme a jogada corresponte

    printf("\n\t\t\t\t               ==============================                   ");
    if(jAnt > 1)
        printf("\n\t\t\t\t               ||     Ultimas %d Jogadas    ||        ", jAnt);
    else 
        printf("\n\t\t\t\t               ||       Ultima Jogada      ||         ", jAnt);
    printf("\n\t\t\t\t$===========================================================$\n");

    for(blocoLista* aux = lista; i < jAnt && aux != NULL; aux = aux->prox, i++){
        if(opcao == 2){
            if(i == 0) 
                printf("\n\t\t\t\t\t\t  - Ultima Jogada ( %d ) -", jogada);
            else 
                printf("\n\t\t\t\t\t\t       - Jogada %d -", jogada);
        } 
        if(modo == 2 && aux->jogador == 2) 
            printf("\n\t\t\t\t||  Computador        Posicao : (%d,%d)      Tabuleiro [ %d ] ||\n", aux->linha, aux->coluna, aux->tabuleiro);
        else 
            printf("\n\t\t\t\t||  Jogador [ %d ]     Posicao : (%d,%d)      Tabuleiro [ %d ] ||\n", aux->jogador, aux->linha, aux->coluna, aux->tabuleiro);
        jogada--;
    }
    printf("\n\t\t\t\t$===========================================================$");
    if(opcao == 2){
        printf("\n\n\t\t\t\tPrima Qualquer Tecla Para Jogar ...");
        getch();
    }
    printf("\n");
}

// MOSTRA QUEM FOI O VENCEDOR, CASO HAJA UM VENCEDOR ULTIMATE
void printaVencedor(int vencedor, int jog, int modo){
    if(vencedor == -1) {
            printf("\n\t\t\t\t $---------------------------------------------------------$");
            printf("\n\t\t\t\t$                           EMPATE                          $");
            printf("\n\t\t\t\t $---------------------------------------------------------$\n");  
    }else {
        if(modo == 1){
            printf("\n\t\t\t\t $---------------------------------------------------------$");
            printf("\n\t\t\t\t$                  O JOGADOR [ %d ] GANHOU                   $", jog);
            printf("\n\t\t\t\t $---------------------------------------------------------$\n");
        }
        if(modo == 2 && jog == 1){
            printf("\n\t\t\t\t $---------------------------------------------------------$");
            printf("\n\t\t\t\t$                          GANHASTE                         $");
            printf("\n\t\t\t\t $---------------------------------------------------------$\n");
        } else 
        if(modo == 2 && jog == 2){ // se o computador ganhar
            printf("\n\t\t\t\t $---------------------------------------------------------$");
            printf("\n\t\t\t\t$                          PERDESTE                         $");
            printf("\n\t\t\t\t $---------------------------------------------------------$\n");
        }
    }
}