/* Rui Pedro Costa Almeida - 2021140560 */

#ifndef TICTACTOE_FUNCOES_H
#define TICTACTOE_FUNCOES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct jogada { 
    int linha;
    int coluna;
    char c;        // caracter
    int jogador;   // atribui a jogada a um jogador (1 ou 2);
    char vencedor; // atribui a cada posiçao de cada mini tabuleiro o estado do seu tabuleiro (para facilitar a verificaçao de vencedor final e nao so)
}bloco;

typedef struct jogadaLista { 
    int linha;
    int coluna;
    int jogador;
    int tabuleiro;
    char vencedor; // para depois ao se pedir a recuperaçao da sessao anterior se voltar a colocar os estados dos mini tab
    struct jogadaLista* prox;
}blocoLista;

int obtemNovoJogoOuAnterior(int vazio); /*DONE*/
// pergunta ao utilizador se deseja um novo jogo ou continuar o da ultima sessao

int printaTitulos(char* nomeF); /*DONE*/
// vai printar o nome do Jogo buscando a informaçao ao ficheiro de texto "titulo.txt". E passado como argumento o nome do ficheiro

int escolheModo(); /*DONE*/
// possibilita ao jogador a possibilidade de jogar contra um AI ou um outro jogador

bloco* criaTabuleiro(int tam); /*DONE*/
// inicializa o tabuleiro com dando a posição de cada cada posição ao bloco

void recuperaTabuleiro(blocoLista* lista, bloco* uBoard); /*DONE*/
// funçao que vai recuperar as posiçoes do jogo anterior

void printaTabuleiro(int tam, bloco* uBoard, int uBloco, int vencedorUlti); /*DONE*/
// printa o tabuleiro

void printaJogadaEfetuada(int tab, int l, int c); /*DONE*/
// printa a informaçao da jogada efetuada pelo jogador

void printaInformacaoDaJogada(int livre, int nextTab, int modo, int jog, char cJog); /*DONE*/
// printa a informaçao da jogada antes de se jogar (tabuleiro onde tem de jogar, jogador e simbolo correspondente)

void printaJogadasAnteriores(blocoLista* lista, int jAnt, int nJogadas, int modo, int opcao); /*DONE*/
// printa o numero de jogadas anteriores solicitadas pelo jogador em questao

void printaInfoTabConquistado(int nJogadas, int modo, int jog, int nextTab); /*DONE*/
// caso um jogador tenha conquistado um tabuleiro, esta funçao printa quem foi esse jogador e o tabuleiro conquistado

blocoLista* recuperaLista(char* nomeF, int* nJogadas, int* modo); /*DONE*/
// vai recuperar o jogo da sessao anterior caso o Utilizador Deseje e caso haja uma sessão anterior

blocoLista* addLista(blocoLista* lista, int posBloco, bloco* uBoard, int tabJogado); /*DONE*/
// vai adicionando as jogadas a lista

int gravaLista(blocoLista* lista, char* nomeF, int modo, int nJogadas); /*DONE*/
// grava as jogadas feitas, faz inserçao do nó no inicio da lista para facilitar a escolha

int escolheJogador(); /*DONE*/
// vai devolver um 0 ou 1 aleatoriamente sempre que chamada

int ticTacToe(int countJogadas, int jogador, bloco* uBoard, int tam, int uBloco, int modo, blocoLista* lista, char* nomeBinF); /*DONE*/
// jogar jogador VS jogador

int obtemOpcaoJogo(int jogador, char cJogador); /*DONE*/
// returna 1 se opçao for jogar e 2 se for ver jogadas anteriores

int obtemKjogadasAnteriores(int nJogadas); /*DONE*/
// obtem o numero de jogadas anterior solicitadas a visualizar

int obtemPosicaoAI(bloco* uBoard, int* linhaMiniTab, int* colunaMiniTab, int livre); /* DONE */
// Vai obter a posicao do computador  

int obtemPosicaoJogador(int uBloco, int* linhaMini, int* colunaMini); /* DONE */
// Vai obter a posicao caso se verifique que foram colocadas as duas posiçoes  

int verificaSeFicheiroVazio(char* nomeF); /*DONE*/
// verifica se ficheiro esta ou nao vazio, ou se sequer existe

int verificaInput(int uBloco, int inputs, float coluna, float linha); /*DONE*/
// Verifica se o input esta correto

int verificaJogada(bloco* uBoard, int posBloco, int livre, blocoLista* lista, int modo, int jogador, int* indexIni); /*DONE*/
// verifica se a jogada efetuada é valida, dentro das regras do jogo

int proximoTabuleiro(int* proxLinha, int* proxColuna, blocoLista* lista); /*DONE*/
// obtem o index real do proximo tabuleiro

void preencheTabVencedor(int indexIni, bloco* uBoard); /*DONE*/
// vai preencher as posiçoes vencedor das estruturas desse mini tab com o vencedor desse mini tabuleiro 

int primeiraPosMiniTabuleiro(int proxLinha, int proxColuna); /*DONE*/
// obtem a posiçao em index do array da primeira posiçao Mini tabuleiro

void verificaEstadoMiniTabs(bloco* uBoard, int* empate); /*DONE*/
// vai verificar o estado dos tabuleiros, se houver 9 tabuleiros com estado vencedor/empatado entao empate == 9, e ainda nao ...
// ... houver vencedor Ultimate entao e porque o jogo empatou

int verificaVencedorMiniTabuleiro(int posBloco, bloco* uBoard, int jogador, int* indexIni); /* DONE */
// verifica se o mini tabuleiro ja tem um vencedor ou nao

int verificaSeMiniTabCheio(int* indexIni, bloco* uBoard, int posBloco); /* DONE */
// verifica se o mini tabuleiro ja esta cheio ou nao

int verificaVencedorUltimate(bloco* uBoard); /*DONE*/
// verifica se ja existe um vencedor final ou nao

char* addExtensaoFicheiroTexto(char* nomeF, int* tam); /*DONE*/
// vai verificar se o ficheiro é o nome colocado ja tem .txt ou nao, ou se tem outra extensao nao permitida

char* addFicheiroParaDir(char* nomeF, int* tam);
// vai adicionar o ficheiro para a pasta onde vao estar os resumos dos jogos feitos

void printaVencedor(int vencedor, int jog, int modo); /*DONE*/
// printa o resultado final, ou seja quem foi o vencedor

void libertaTabuleiro(bloco* uBoard); /*DONE*/

void apagaUltimaSessao(char* nomeF); /*DONE*/
// para caso o utilizador escolher um novo jogo, a informaçao da sessao anterior e apagada, caso esta exista ...
// ... (devido ao facto do ficheiro estar a escrever no modo append, ou seja vai estar sempre com o ponteiro no posiçao final do file)

int exportaJogoParaFicheiro(blocoLista *lista, int vencedorUlti, int modo); /*DONE*/
// vai exportar para um ficheiro de texto o resumo de todo o jogo

FILE* preencheFicheiro_Modo_1(blocoLista* lista, char* nomeF, FILE* f); /*DONE*/
// Vai preencher o ficheiro de texto caso seja o modo 1

FILE* preencheFicheiro_Modo_2(blocoLista* lista, char* nomeF, FILE* f); /*DONE*/
// Vai preencher o ficheiro de texto caso seja o modo 2

char* obtemNomeDoFicheiro(char* nomeF, int* tam); /*DONE*/
// vai obter o nome do ficheiro para o qual o utilizador vai querer guardar o nome das jogadas

blocoLista* inverteLista(blocoLista* lista); /*DONE*/
// vai inverter a lista ligada simples, colocando a ultima jogada efetuada como ultimo nó da lista, e a primeira como primeiro ... 
// ... para se puder colocar as jogadas no ficheiro de texto por ordem 

int gravaNomeFicheiroTXT(char* nomeF, int tam);
// vai gravar o nome do ficheiro TXT pedido ao ultizador, para dar para ver o relatorio

char* recuperaNomeFicheiroTxt();
// recupera o nome do ficheiro de texto que contem o resumo do jogo da sessao anterior

void libertaLista(blocoLista* lista); /*DONE*/

#endif /*TICTACTOE_FUNCOES_H*/