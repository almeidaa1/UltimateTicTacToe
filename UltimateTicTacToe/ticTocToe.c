/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"

// FUNÇAO PRINCIPAL DO JOGO
int ticTacToe(int countJogadas, int jogador, bloco* uBoard, int tam, int uBloco, int modo, blocoLista* lista, char* nomeBinF) {
    
    int posBloco = 0;
    int vencedorMini = 0, vencedorUlti = 0;      // vencedorUlti (1 se houver vencedor, 0 se ainda nao ha, -1 se o jogo empatou)
    int inputs, livre = 1;                       // livre = se jogada livre ? 1 : 0;
    int indexIni = 0;                            // indice inicial do tabuleiro atual
    int proxLinha = 0, proxColuna = 0;           // a linha e coluna do mini tabuleiro no qual se tem de jogar

    int nextTabuleiro = -1;                      // posiçao do mini tabuleiro (miniTab 1 = pos 1, miniTab 2 = pos 2, etc...)
    int indexIniProxTab = -1;                    // indice inicial do tabuleiro seguinte face a posiçao da jogada efetuada
    int empate = 0;                              // vai contar o numero de tabuleiros conquistados ou ja completos, caso empate == 9 e ainda nao existir vencedor entao o jogo Empatou 
    if(countJogadas >= 1){                       // <- (if) para o caso de haver uma recuperaçao da sessao anterior
        nextTabuleiro = proximoTabuleiro(&proxLinha, &proxColuna, lista);
        indexIniProxTab = primeiraPosMiniTabuleiro(proxLinha, proxColuna);
        verificaEstadoMiniTabs(uBoard, &empate); // vai verificar o estado dos tabuleiros, se houver 9 tabuleiros com estado vencedor/empatado entao empate == 9, e ainda nao houver vencedor Ultimate entao e porque o jogo empatou
    }
    if(empate == 9) {                            // para o caso de ao recuperar sessao o resultado Estiver com Empate
            vencedorUlti = -1;
            printaVencedor(vencedorUlti, jogador, modo);
            return 1;
    }

    do{
        
        char cJogador = jogador == 1 ? 'X' : 'O';// caracter atribuido ao jogador
        countJogadas++;                          // incrementa o numero de jogada efetuadas
 
        int l, c;                                // eventual linha e coluna da posiçao jogada
        int opcao = 0;                           // opçao escolhida pelo utilizar (1 se for para jogar, 2 se for para ver jogadas anteriores, 0 para sair)
        
        
        if(countJogadas > 1){

            livre = uBoard[indexIniProxTab].vencedor != 'n' ? 1 : 0; // verifica se a jogada vai ser ou nao livre (Jogada a escolha), verificando a primeira se a primeira posiçao do mini tab vai ter ja um estado de vitoria/empate ou nao

            if(modo != 2 || jogador != 2) opcao = obtemOpcaoJogo(jogador, cJogador);
            if((modo != 2 || jogador != 2) && opcao == 0) {

                int titulo = printaTitulos("./Titulos/ateBreve.txt");
                if(!titulo) printf("\t\t\t\tO ficheiro da Mensagem Ate Breve Nao Existe");

                return -1;
            }

            if(opcao == 2) {
                int kJogAnteriores = obtemKjogadasAnteriores(countJogadas-1);
                printaJogadasAnteriores(lista, kJogAnteriores, countJogadas-1, modo, opcao);
            }
        }

        opcao = 1; // para printar a informacao da ultima jogada na jogada seguinte sem aparecer o "Pressionar qualquer tecla..."
        
        if(countJogadas > 1 && (modo != 2 || jogador != 2)) {
            printaJogadasAnteriores(lista, 1, countJogadas-1, modo, opcao); // vai printar a ultima jogada efetuada na vez do jogador
            printaTabuleiro(tam, uBoard, uBloco, vencedorUlti);
        }
        printaInformacaoDaJogada(livre, nextTabuleiro, modo, jogador, cJogador);

        do{
            if(modo == 2 && jogador == 2) {
                l = proxLinha, c = proxColuna;
                posBloco = obtemPosicaoAI(uBoard, &l, &c, livre);
            }else
                posBloco = obtemPosicaoJogador(uBloco, &l, &c);
        }while(!verificaJogada(uBoard, posBloco , livre, lista, modo, jogador, &indexIni));
        
        uBoard[posBloco].jogador = jogador;
        uBoard[posBloco].c = cJogador;

        // para o caso de ser jogada livre, obter tabuleiro jogado e nao o que era suposto jogar
        if(livre){
            int linhaMini = l / 3;
            int colunaMini = c / 3;
            int miniJogado = linhaMini * 3 + colunaMini + 1; // da o tabuleiro jogado
            nextTabuleiro = miniJogado;
        }

        if(countJogadas >= 5){  // Vai verificar so apartir do numero minimo de jogadas ao qual se pode conquistar um mini tabuleiro
            vencedorMini = verificaVencedorMiniTabuleiro(posBloco ,uBoard, jogador, &indexIni); // returna 1 se vencedor, 0 se nao
            empate += vencedorMini;
            if(vencedorMini) preencheTabVencedor(indexIni, uBoard);
        }
        if(countJogadas >= 17 && !vencedorMini)
            empate += verificaSeMiniTabCheio(&indexIni, uBoard, posBloco); // para caso a posiçao colocada deixar o tabuleiro completo (sem que haja ja um vencedor) este e nomeado com 'e'
        if(countJogadas >= 15)                                             // Vai verificar so apartir do numero minimo de jogodas ao qual se pode ganhar o jogo
            vencedorUlti = verificaVencedorUltimate(uBoard);

        if(!vencedorUlti && empate == 9 && countJogadas >= 17) vencedorUlti = -1; // vencedorUlti == -1 se nenhum dos jogadores ganhou o jogo
        
        printaTabuleiro(tam, uBoard, uBloco, vencedorUlti);
        printaJogadaEfetuada(nextTabuleiro, l, c);

        if(vencedorMini) {
            printaInfoTabConquistado(countJogadas, modo, jogador, nextTabuleiro);
            printf("\n");    
        }else 
            printf("\n\n"); //para fins de design
        if(modo == 2 && jogador == 1) 
            printf("\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n");

        lista = addLista(lista, posBloco, uBoard, nextTabuleiro);
        if(lista == NULL) {
            printf("\n\t\t\t\t *Erro Ao Adicionar Jogada Na Lista Ligada*\n");
            return 0;
        }

        int gravou = gravaLista(lista, nomeBinF, modo, countJogadas); // grava a lista no ficheiro "jogo.bin"
        if(!gravou) {
            printf("\n\t\t\t\t *Nao Foi Possivel Gravar a Jogada*\n");
            return 0;
        }

        nextTabuleiro = proximoTabuleiro(&proxLinha, &proxColuna, lista);

        if(!vencedorUlti) {
            indexIniProxTab = primeiraPosMiniTabuleiro(proxLinha, proxColuna); // index da primeira posiçao do bloco do array do proximo ...
                                                                                   // ... mini tabuleiro correspondente face a jogada atual
            jogador = jogador == 1 ? 2 : 1;
        }
    }while(!vencedorUlti);
    
    if((vencedorUlti == 1 && modo == 2 && jogador == 2) || vencedorUlti == -1)
        printaTitulos("./Titulos/medalha.txt");
    else{
        printf("\n");
        printaTitulos("./Titulos/trofeu.txt");
    }

    printaVencedor(vencedorUlti, jogador, modo);
    printaTabuleiro(tam, uBoard, uBloco, vencedorUlti);
    printf("\n\n\t\t\t\t Prima Qualquer Tecla Para Continuar ...");
    getch();
    printf("\n\n");

    int exportado = exportaJogoParaFicheiro(lista, vencedorUlti, modo);     // Exporta no final do jogo para um Ficheiro de textot, a sucessão completa das jogadas realizadas
    if(exportado){
        printf("\t\t\t\t - Resumo Guardado Com Sucesso !\n");
        printaTitulos("./Titulos/fimJogo.txt");
    }
    
    return 1;
    
}