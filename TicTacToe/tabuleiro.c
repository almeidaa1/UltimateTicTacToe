/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"

// CRIAR UM ARRAY COM 81 BLOCOS (9Linhas X 9Colunas), QUE VAI SER O NOSSO TABULEIRO ULTIMATE
bloco* criaTabuleiro(int tam) {

    bloco* uBoard = malloc(sizeof(bloco) * (tam * 9)); //Cria os mini tabuleiros (cada bloco do array equivale a um bloco dos mini tabuleiros) //
    if(uBoard == NULL) {                               //Retorna NULL caso occora um erro na alocaçao //
        printf("\n\n\t\t\t\t*Erro de Alocaçao*\n");
        libertaTabuleiro(uBoard);
        return NULL;
    }

    int x = 0;                                         // x vai ser o contador de blocos para que se possa percorrer o array //
    for(int i = 0; i < tam; i++)                       // atribui a cada bloco do mini tabuleiro a sua posiçao, para que futuramente //
        for(int j = 0; j < tam; j++, x++){
            uBoard[x].linha = i;
            uBoard[x].coluna = j;
            uBoard[x].c = '_';
            uBoard[x].jogador = 0;
            uBoard[x].vencedor = 'n';                  //para facilitar a verificaçao de vencedor final
        }
    return uBoard;
}

// OBTEM O MINI TABULEIRO NO QUAL SE VAI JOGAR NA SEGUINTE JOGADA
int proximoTabuleiro(int* proxLinha, int* proxColuna, blocoLista* lista) {

    *proxLinha = lista->linha % 3;                      // a linha do mini tabuleiro no qual se tem de jogar
    *proxColuna = lista->coluna % 3;                    // a coluna do mini tabuleiro no qual se tem de jogar
    return ((*proxLinha * 3) + (*proxColuna % 3)) + 1;  // mini tabuleiro no qual se vai ter de jogar na seguinte jogada
}

// OBTEM A PRIMEIRA POSICAO (EM INDEX DO ARRAY) DO MINI TABULEIRO
int primeiraPosMiniTabuleiro(int linha, int coluna) {

    int linhaInicial = linha * 3;                       // linha inicial do miniTabuleiro no qual se jogou
    int colunaIncial = coluna * 3;                      // coluna inicial do miniTabuleiro no qual se jogou
    return linhaInicial * 9 + colunaIncial;             // index da primeira posiçao no array uBoard, do bloco incial do mini tabuleiro jogado
}

// PREENCHE O TABULEIRO CONQUISTADO NO CAMPO VENCEDOR DE CADA POSIÇAO COM O SIMBOLO DO JOGADOR VENCEDOR
void preencheTabVencedor(int indexIni, bloco* uBoard) {
    int auxL = indexIni;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++) {
            uBoard[auxL+j].vencedor = uBoard[indexIni].vencedor;
        }
        auxL += 9;
    }
}

// RECUPERA O TABULEIRO DA SESSAO ANTERIOR CASO ESTA EXISTA
void recuperaTabuleiro(blocoLista* lista, bloco* uBoard){
    int posBloco;
    int linhaMiniTab, colunaMiniTab;
    int indexIniTab;
    int flag = 0;

    for(blocoLista* aux = lista; aux != NULL; aux = aux->prox) { // atribui ao tabuleiro a informaçao da sessao anterior
        posBloco = aux->linha * 9 + aux->coluna;
        uBoard[posBloco].linha = aux->linha;
        uBoard[posBloco].coluna = aux->coluna;
        uBoard[posBloco].c = aux->jogador == 1 ? 'X' : 'O';
        uBoard[posBloco].jogador = aux->jogador;
        
        // vai obter a linha e coluna do mini tabuleiro conforme a jogada que estiver na lista, e tmb o index inicial da primeira posiçao desse mini Tab
        linhaMiniTab = (aux->tabuleiro-1) / 3;        // -1 para dar o index do tabuleiro e nao a sua posiçao real (ex:. Mini tab 9 = index 8) 
        colunaMiniTab = (aux->tabuleiro - 1) % 3;    
        indexIniTab = primeiraPosMiniTabuleiro(linhaMiniTab, colunaMiniTab);

        if(aux->vencedor != 'n'){
            uBoard[indexIniTab].vencedor = aux->vencedor; // vai colocar o estado do tabuleiro na primeira posiçao, conforme estava na sessao anterior
            preencheTabVencedor(indexIniTab,uBoard);
        }
    }
}

// LIBERTA NA MEMORIA O ARRAY DE 81 BLOCOS, QUE FAZ O TABULEIRO ULTIMATE
void libertaTabuleiro(bloco* uBoard) {
    free(uBoard); // liverta o array do Tabuleiro
}