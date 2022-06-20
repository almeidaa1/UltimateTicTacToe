/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"
#include <string.h>

// PARA O UTILIZADOR ESCOLHER SE QUER FAZER UM NOVO JOGO OU CONTINUAR A SESSAO ANTERIOR CASO ESTA EXISTA
int obtemNovoJogoOuAnterior(int vazio) {
    int modo, tErrada = 0;

    printf("\n\n\t\t\t\t      >  [     Novo Jogo     ] - Tecla | 1 |\n\n");
    if(!vazio)
    printf("\t\t\t\t      >  [     Continuar     ] - Tecla | 2 |    \n\n");
    do{
        fflush(stdin);
        if(tErrada++) printf("\t\t\t\t       *Escolha um modo existente* \n");
        printf("\t\t\t\t       Tecla: ");
        scanf("%d", &modo);
    }while(modo != 1 && modo != 2 || (modo == 2 && vazio));
    return modo;
}

// PARA O UTILIZADOR ESCOLHER O MODO DE JOGO ( JOGOADOR1 VS JOGAGADOR2 ) OU ( JOGADOR VS AI )
int escolheModo() {
    int modo, tErrada = 0;
    printf("\n\n\t\t\t\t      > [ Jogador 1 VS Jogador 2  ] - Tecla | 1 |\n\n");
    printf("\t\t\t\t      > [ Jogador 1 VS Computador ] - Tecla | 2 |\n\n");
    do{
        fflush(stdin);
        if(tErrada++) printf("\t\t\t\t       *Escolha um modo existente* \n");
        printf("\t\t\t\t       Tecla: ");
        scanf("%d", &modo);
    }while(modo != 1 && modo != 2);
    return modo;
}

// VAI ESCOLHER ALEATORIAMENTE O JOGADOR QUE COMEÇA CASO SEJA ESCOLHIDO ( JOGOADOR1 VS JOGAGADOR2 )
int escolheJogador() {
    srand(time(NULL));
    return rand()%2 ? 1 : 2;
}

// PARA O UTILIZADOR ESCOLHER SE QUER JOGAR, VER JOGADAS ANTERIORES OU SAIR DO JOGO
int obtemOpcaoJogo(int jogador, char cJogador) {
    int opcao, tErrada = 0;
    int extra = 2; // vai ser a opçao extra, num tem no outro nao
    if(jogador) {
        printf("\n\t\t\t\t====================== %c| Jogador %d |%c =====================\n", cJogador+32, jogador, cJogador+32);
        printf("\t\t\t\t                                                 SAIR [ 0 ]      \n");
        printf("\t\t\t\t    >              { Jogar }  -  Tecla | 1 |            <      \n\n");
        printf("\t\t\t\t    >        Ver Jogadas Anteriores - Tecla | 2 |       <      \n\n");
        printf("\t\t\t\t=============================================================    \n");
    }else {
        printf("\t\t\t\t====================== | =========== | ======================  \n\n");
        printf("\t\t\t\t    >          { Ver Resumo }  -  Tecla | 1 |           <        \n");
        printf("\t\t\t\t    SAIR [ 0 ]                                                   \n");
        printf("\t\t\t\t=============================================================    \n");
        extra = 0;
    }
    int input;
    do{
        fflush(stdin);
        if(tErrada++) printf("\t\t\t\t\t\t*Escolha uma opcao existente* \n");
        printf("\t\t\t\t\t\t\t  Tecla : ");  
        input = scanf("%d", &opcao);
    }while(opcao != 1 && opcao != extra && opcao != 0 || input != 1);
    if(opcao == 1) 
        printf("\n");
    return opcao;
}

// PARA O UTILIZADOR ESCOLHER O NUMERO DE JOGADAS ANTERIORES A VISUALIZAR ENTRE 1 A 10
int obtemKjogadasAnteriores(int nJogadas) {
    int jAnteriores; // jogadas anteriores solicitadas a visualizar
    
    if(nJogadas > 1) 
        printf("\n\t\t\t\t    || Existem [ %d ] Jogadas Ate Ao Momento ||\n", nJogadas);
    else 
        printf("\n\t\t\t\t    || Existe [ %d ] Jogada Ate Ao Momento ||  \n", nJogadas);

    int input;
    do{
        fflush(stdin);
        printf("\n\t\t\t\t    > Numero de Jogadas Anteriores a Visualizar : ");
        input = scanf("%d", &jAnteriores);
        if(input != 1)
            printf("\t\t\t\t\t         *Nao Digite Caracteres*");
        else
        if(jAnteriores <= 0 || jAnteriores > 10 ) 
            printf("\t\t\t\t\t  *Escolha entre 1 a 10 jogadas*");
        else 
        if(jAnteriores > nJogadas && nJogadas > 1)
            printf("\t\t\t\t    *So existem %d jogadas disponiveis ate ao momento*", nJogadas);
        else 
        if(jAnteriores > nJogadas && nJogadas == 1)
            printf("\t\t\t\t    *So existe %d jogada disponivel ate ao momento*", nJogadas);
    }while(jAnteriores < 0 || jAnteriores > 10 || jAnteriores > nJogadas || input != 1);

    return jAnteriores;
}

// PARA O UTILIZADOR ESCOLHER A POSIÇAO ONDE QUER JOGAR
int obtemPosicaoJogador(int uBloco, int* linhaMini, int* colunaMini) {
    
    float linha, coluna;
    int inputs, posBloco; 
    do{
        fflush(stdin);
        printf("\n\t\t\t\t Posicao (Linha,Coluna) > ");
        inputs = scanf("%f,%f", &linha, &coluna);          // returna o numero de inputs feitos com sucesso  
    }while(!verificaInput(uBloco, inputs, coluna, linha)); // verifica se os inputs sao de acordo com o formato e regras pedidas

    *linhaMini = linha;
    *colunaMini = coluna;
    posBloco = (int)linha * uBloco + (int)coluna;          // da me a posiçao escolhida do mini tabuleiro, para o bloco equivalente no array
    return posBloco;
}

// ESCOLHE UMA POSIÇAO DO TABUELEIRO PARA O COMPUTADOR
int obtemPosicaoAI(bloco* uBoard, int* linhaMini, int* colunaMini, int livre) {

    srand(time(NULL));
    int linhaInicial = *linhaMini * 3;                                       // linha inicial do miniTabuleiro no qual se jogou
    int linhaFinal = linhaInicial + 2;                                       // ultima linha do miniTabuleiro no qual se jogou

    int colunaIncial = *colunaMini * 3;                                      // coluna inicial do miniTabuleiro no qual se jogou
    int colunaFinal = colunaIncial + 2;                                      // ultima coluna do miniTabuleiro no qual se jogou

    int linha, coluna;
    int posBloco;
    if(!livre){
        // linha = linhaInicial + (int)(voltas / 3);                         // Outra Possibilidade (voltas -> numero de vezes que volta ao ciclo)
        linha = (rand() % (linhaFinal - linhaInicial + 1)) + linhaInicial;   // linha random do mini tabuleiro
        coluna = (rand() % (colunaFinal - colunaIncial + 1)) + colunaIncial; // coluna random do mini tabuleiro
        posBloco = linha * 9 + coluna;                                       // posiçao do bloco (index) no array total
        *linhaMini = linha;                                                  // vai atribuir ao valor do ponteiro a linha obtida para despois dar a jogada efetuada pela AI
        *colunaMini = coluna;                                                // vai atribuir ao valor do ponteiro a coluna obtida para despois dar a jogada efetuada pela AI

    }else {
        posBloco = rand() % 81;                                              // para uma melhor eficiencia
        *linhaMini = posBloco / 9;
        *colunaMini = posBloco % 9;
    }

    return posBloco;
}

// OBTEM O NOME DO FICHEIRO (A ESCOLHER PELO UTILIZADOR)
char* obtemNomeDoFicheiro(char* nomeF, int* tam) {

    int errado;
    do{
        errado = 0;
        printf("\t\t\t\t > Nome Do Resumo : ");
        scanf(" %99[^\n]", nomeF);
        
        *tam = strlen(nomeF);
        if(*tam > 15) printf("\t\t\t\t *Digite um nome com menos de 15 caracteres*\n");
        else {
            // vai verificar no nome se existe alguem caracter nao permitido pelos ficheiros .txt
            for(int i = 0; i < *tam; i++){
                if(nomeF[i] == 92 /* \ */ || nomeF[i] == ':' || nomeF[i] == '*' || nomeF[i] == '?' || nomeF[i] == '"' || nomeF[i] == '<'
                                                                                || nomeF[i] == '/' || nomeF[i] == '>' || nomeF[i] == '|'){
                    errado = 1;
                    printf("\t\t\t\t ** Nao Coloque No Nome    %c / : * %c < > | \n", 92, 34); /* 34 == " */
                    break;
                }
            }            
        }

    }while(*tam > 15 || errado);
    nomeF[*tam] = '\0';
    
    return nomeF;
}