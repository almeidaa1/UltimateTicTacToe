/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"

// VERIFICA SE O FICHEIRO PASSADO COMO ARGUMENTO ESTA OU NAO VAZIO
int verificaSeFicheiroVazio(char* nomeF) {
    FILE* f = fopen(nomeF,"rb");
    if(f == NULL) {
        fclose(f);
        return 1;
    }

    fseek (f, 0, SEEK_END); // meto ponteiro no final do ficheiro
    int tam = ftell(f); // Lê o indicador de posição (em bytes)
    
    fclose(f);
    
    int vazio = tam != 0 ? 0 : 1;
    return vazio;
}

// VERIFICA SE O INPUT DA JOGADA, ESTA OU NAO NUM FORMATO VALIDO CONFORME AS REGRAS DEFINIDAS
int verificaInput(int uBloco, int inputs, float coluna, float linha) {
    if(inputs != 2) {
        printf("\t\t\t\t\t\t\t      *Introduza Uma Posicao Valida*");
        return 0;
    }
    if((linha < 0 || linha >= uBloco ) && (coluna < 0 || coluna >= uBloco)) {
        printf("\t\t\t\t\t\t\t*Introduza Uma Linha e Coluna Valida*");
        return 0;
    }
    if((linha < 0 || linha >= uBloco)) {
        printf("\t\t\t\t\t\t\t        *Introduza Uma Linha Valida*");
        return 0;
    }
    if((coluna < 0 || coluna >= uBloco)) {
        printf("\t\t\t\t\t\t\t       *Introduza Uma Coluna Valida*");
        return 0;
    }
    if(linha-(int)linha && coluna-(int)coluna){
        printf("\t\t\t\t\t      *Introduza Uma Linha e Uma Coluna Nao Decimal*");
        return 0;
    }
    if(linha-(int)linha) {
        printf("\t\t\t\t\t\t\t   *Introduza Uma Linha Nao Decimal*");
        return 0;
    }
    if(coluna-(int)coluna){
        printf("\t\t\t\t\t\t\t  *Introduza Uma Coluna Nao Decimal*");
        return 0;
    }
    return 1;
}

// VERIFICA SE A POSIÇAO ESCOLHIDA PELO UTILIZADOR É OU NAO VALIDA
int verificaJogada(bloco* uBoard, int posBloco, int livre, blocoLista* lista, int modo, int jogador, int* indexIni){

    // verifica se ja existe ou nao um vencedor no mini tabuleiro 
    if(verificaVencedorMiniTabuleiro(posBloco, uBoard, jogador, indexIni)){
        if(modo != 2 || jogador != 2) printf("\t\t\t\t\t\t\t\t  *Tabuleiro ja Conquistado*");
        return 0;
    }

    if(verificaSeMiniTabCheio(indexIni,uBoard, posBloco)){
        if(modo != 2 || jogador != 2) printf("\t\t\t\t\t\t\t\t        *Tabuleiro Completo*");
        return 0;
    }

    //verifica se a posiçao ja esta ocupada ou nao
    if(uBoard[posBloco].c != '_') {
        if(modo != 2 || jogador != 2) printf("\t\t\t\t\t\t\t\t        *Posicao ja ocupada*");
        return 0; 
    }

    if(livre) return 1; // se a jogada for livre nao precisa de verificar o codigo abaixo
    
    // verifica se a jogada esta no mini tabuleiro correto, conforme a jogada do adversario anterior
    int proxLinha = lista->linha % 3;           // a linha do mini tabuleiro no qual se tem de jogar
    int proxColuna = lista->coluna % 3;         // a coluna do mini tabuleiro no qual se tem de jogar
    int linhaJ = uBoard[posBloco].linha / 3;    // a linha do mini tabuleiro onde se jogou na jogada anterior
    int colunaJ = uBoard[posBloco].coluna / 3;  // a coluna do mini tabuleiro onde se jogou na jogada anterior

    if(proxLinha == linhaJ && proxColuna == colunaJ)
        return 1;
    else {
        if(modo != 2 || jogador != 2) printf("\t\t\t\t\t\t\t\t       *Tabuleiro Incorreto*");
        return 0;
    }
}

// VERIFCA SE JA EXISTE OU NAO UM VENCEDOR ULTIMATE
int verificaVencedorMiniTabuleiro(int posBloco, bloco* uBoard, int jogador, int* indexIni) {
    int linhaMini = uBoard[posBloco].linha / 3;     // linha do mini tabuleiro 
    int colunaMini = uBoard[posBloco].coluna / 3;   // coluna do mini tabuleiro

    int linhaInicial = linhaMini * 3;               // linha inicial do miniTabuleiro no qual se jogou
    int colunaIncial = colunaMini * 3;              // coluna inicial do miniTabuleiro no qual se jogou
    *indexIni = linhaInicial * 9 + colunaIncial;    // index da primeira posiçao no array uBoard, do bloco incial do mini tabuleiro jogado
    
    int auxIL = *indexIni, auxIC = *indexIni;

    if(uBoard[*indexIni].vencedor == 'e') return 0;  // quer dizer o mini tab ja esta completo e nao precisa verificar as confiçoes abaixo 
    if(uBoard[*indexIni].vencedor != 'n') return 1;  // quer dizer que ja tem vencedor e nao precisa verificar as confiçoes abaixo

    // para percorrer o mini array onde se jogou e verificar se o jogador ganhou ou não (Condições Abaixo) V //
    for(int i = 0; i < 3; i++) {
        // verifica as linhas
		if(uBoard[auxIL].c == uBoard[auxIL + 1].c && uBoard[auxIL].c == uBoard[auxIL + 2].c && uBoard[auxIL].c != '_'){ //linhas
            uBoard[*indexIni].vencedor = jogador == 1 ? 'x' : 'o';
			return 1;
        }
        auxIL += 9; // para se puder verificar a linha seguinte caso a condiçao de cima nao se verifique
        // verifica as colunas
		if(uBoard[auxIC].c == uBoard[auxIC + 9].c && uBoard[auxIC].c == uBoard[auxIC + 18].c  && uBoard[auxIC].c != '_'){ //colunas
            uBoard[*indexIni].vencedor = jogador == 1 ? 'x' : 'o';
			return 1;
        }
        auxIC += 1; // para se puder verificar a coluna seguinte caso a condiçao de cima nao se verifique
	}
    //verifica a diagonal esquerda
	if(uBoard[*indexIni].c == uBoard[*indexIni+10].c && uBoard[*indexIni].c == uBoard[*indexIni + 20].c && uBoard[*indexIni].c != '_') {//diagonal esquerda
        uBoard[*indexIni].vencedor = jogador == 1 ? 'x' : 'o';
        return 1;
    }
    //verifica a diagonal direita
	if(uBoard[*indexIni+2].c == uBoard[*indexIni+10].c && uBoard[*indexIni+2].c == uBoard[*indexIni + 18].c && uBoard[*indexIni+2].c != '_'){ //diagonal direita
        uBoard[*indexIni].vencedor = jogador == 1 ? 'x' : 'o';
        return 1;
    }
    return 0; // returna 0 para o caso de nao existir ainda vencedor no tabuleiro jogado
}

// VERIFICAR O NUMERO DE MINI TABULEIROS QUE JA ESTOU CONQUISTADOS OU TOTALMENTE PREENCHIDOS
void verificaEstadoMiniTabs(bloco* uBoard, int* empate) {

    for(int count = 1, auxL = 0; auxL <= 60; count++){
        (*empate) += uBoard[auxL].vencedor != 'n';
        if(count % 3 == 0) auxL += 21; // permite mudar para a proxima linha do Tabuleiro Ultimate
        else auxL += 3;                // permite mudar para o proximo Mini Tab da mesma Linha do Tabuleiro Ultimatez
    }
    
}

// VERIFICA SE O MINI TABULEIRO FOI COMPLETO (TOTALMENTE PREENCHIDO) OU NAO
int verificaSeMiniTabCheio(int* indexIni, bloco* uBoard, int posBloco) {
    int auxIL = *indexIni, count = 0;

    // vai verificar se o tabuleiro ja esta ou nao cheio (basta verificar as linhas OU colunas)
    for(int i = 0; i < 3; i++) {
	    if(uBoard[auxIL].c != '_' && uBoard[auxIL + 1].c != '_' && uBoard[auxIL + 2].c != '_')
            count++;
        auxIL += 9;                                  // para se puder verificar a linha seguinte caso a condiçao de cima nao se verifique
    }
    if(count == 3) {
        uBoard[*indexIni].vencedor = 'e';
        uBoard[posBloco].vencedor = 'e';             // para guardar na lista que a posiçao jogada deu o empate a este tabuleiro
    }

    return count == 3;
}

// VERIFICA SE EXISTE OU NAO UM VENCEDOR ULTIMATE
int verificaVencedorUltimate(bloco* uBoard){

    int indexIni = 0;           // primeiro index do array <=> primeiro bloco do primeiro mini tabueleiro
    int auxIL = 0, auxIC = 0;   // para se puder verificar a linha e coluna seguinte caso a condiçao de cima nao se verifique
        
    for(int i = 0; i < 3; i++) {
        // verifica as linhas
		if(uBoard[auxIL].vencedor == uBoard[auxIL+3].vencedor && uBoard[auxIL].vencedor == uBoard[auxIL+6].vencedor && uBoard[auxIL].vencedor != 'n')
			return 1;
        auxIL += 27; // para se puder verificar a linha seguinte caso a condiçao de cima nao se verifique
        
        // verifica as colunas
		if(uBoard[auxIC].vencedor == uBoard[auxIC+27].vencedor && uBoard[auxIC].vencedor == uBoard[auxIC+54].vencedor  && uBoard[auxIC].vencedor != 'n')
			return 1;
        auxIC += 3; // para se puder verificar a coluna seguinte caso a condiçao de cima nao se verifique
	}

    //verifica a diagonal esquerda
	if(uBoard[indexIni].vencedor == uBoard[indexIni+30].vencedor && uBoard[indexIni].vencedor == uBoard[indexIni+60].vencedor && uBoard[indexIni].vencedor != 'n')
        return 1;
    //verifica a diagonal direita
	if(uBoard[indexIni+6].vencedor == uBoard[indexIni+30].vencedor && uBoard[indexIni+6].vencedor == uBoard[indexIni+54].vencedor && uBoard[indexIni+6].vencedor != 'n')
        return 1;
    return 0;
}