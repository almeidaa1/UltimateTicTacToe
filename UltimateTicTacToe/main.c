/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"

int main(void)
{
    system("cls");
    int titulo = printaTitulos("./Titulos/tituloJogo.txt"); // printa o Nome Do Jogo
    if(!titulo){
        printf("\n\t\t\t\t\tO Ficheiro de Texto do Titulo Nao Existe\n");
    }

    int colunas = 3;                // numero de colunas do Tabuleiro Ultimate <=> numero de linhas do Tab Ultimate
    int uBloco = colunas*colunas;   // Coluna do ultimo bloco uBloco <=> Numero De Blocos do Tabuleiro Ultimate <=> numero de blocos de cada linha dos mini tabuleiros juntos

    bloco* UltiBoard = criaTabuleiro(uBloco);
    if(UltiBoard == NULL) {
        printf("\n\t\t\t\t *Erro Na Criacao Do Tabuleiro*");
        return 0;
    }

    blocoLista* lista = NULL;       // lista ligada para guardas as jogadas efetuadas

    char* nomeBinF = "jogo.bin";    // nome do ficheiro binarion que vai guardar as jogadas
    int countJogadas = 0;           // conta o numero de jogada efetuadas

    int vazio;
    int novo;
    int modo = 0;

    titulo = printaTitulos("./Titulos/inicio.txt"); // printa a Palavra Inicio
    if(!titulo){
        printf("\n\t\t\t\t\tO Ficheiro de Texto Inicio Nao Existe\n");
    }
    
    vazio = verificaSeFicheiroVazio(nomeBinF); // verifica se o ficheiro esta ou nao vazio, ou se sequer existe
    novo = obtemNovoJogoOuAnterior(vazio);     // Pergunta ao Utilizador se deseja um Novo Jogo ou Continuar a Sessao Anterior caso esta exista
    if(novo == 2 && !vazio){
        lista = recuperaLista(nomeBinF, &countJogadas, &modo); // vai recuparar a sessao de jogo anterior caso desejado pelo Utilizador
        if(lista != NULL)
            recuperaTabuleiro(lista, UltiBoard);
    }
          
    if(novo == 1){
        titulo = printaTitulos("./Titulos/modo.txt");
        if(!titulo){
            printf("\n\t\t\t\t\tO Ficheiro de Texto Inicio Nao Existe\n");
        }
        modo = escolheModo(); 

        if(!vazio) apagaUltimaSessao(nomeBinF); // para caso o utilizador escolher um novo jogo, a informaçao da sessao anterior é apagada, caso esta exista

        printf("\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
        printf("\t\t\t\t\t         Tabuleiro Ultimate [ %d x %d ]      \n", colunas, colunas);
    }
    int vencedorUlti = 0; // vencedorUlti (1 se houver vencedor, 0 se ainda nao ha, -1 se o jogo empatou)
    if(novo == 2) {
        printf("\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
        printf("\n\t\t\t\t\t(!)  Tabuleiro Ultimate da Ultima Sessao  (!)              \n\n");
        printf("\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = \n");

        vencedorUlti = verificaVencedorUltimate(UltiBoard); // para verificar se na sessao anterior ja tinha ou nao um vencedor Ultimate, e puder printar a tabela
    }
    printaTabuleiro(colunas, UltiBoard, uBloco, vencedorUlti);
    if(novo == 2 && !vencedorUlti) printf("\n");

    int jogador = 0;
    if(novo == 1){
        if(modo == 1) jogador = escolheJogador();
        else jogador = 1;
        if(modo == 1)
            printf("\n\t\t\t\t\t            > Jogador %d Comeca <              \n", jogador);
        else
            printf("\n\t\t\t\t\t         > Jogador 1 (Voce) Comeca <                    \n");
    }else
        jogador = lista->jogador == 1 ? 2 : 1; // para mandar o jogador ia jogar na sessao anterior

    int game = 1; // 0, caso alguem erro, 1 se correu tudo bem e o jogo ja acabou, -1 se for para sair

    if(!vencedorUlti)
        game = ticTacToe(countJogadas, jogador, UltiBoard, colunas, uBloco, modo, lista, nomeBinF);
    else{
        jogador = jogador == 1 ? 2 : 1;
        printaVencedor(vencedorUlti, jogador, modo);
        printf("\n");
    }

    int opcao;
    char* nomeTxtF = NULL;
    if(game == 1){
        opcao = obtemOpcaoJogo(0, 0); // no final pergunta se quer ler o Resumo do Jogo Ou quer sair 

        if(opcao == 1) {

            nomeTxtF = recuperaNomeFicheiroTxt();
            vazio = verificaSeFicheiroVazio(nomeTxtF);

            if(vazio == 1 || nomeTxtF == NULL) printf("\t\t\t\t *O Resumo Nao Existe*");

            else{
                printaTitulos("./Titulos/resumo.txt");
                printaTitulos(nomeTxtF);
                printf("\n\n========================================================================================================================");
            }
            printf("\n\n\t            Prima Qualquer Tecla Para Terminar ...");
            getch();
        }
        system("cls");
        printaTitulos("./Titulos/ateBreve.txt");
    }

    free(nomeTxtF);
    libertaTabuleiro(UltiBoard);        // Liberta todo o array do Tabuleiro Ultimate 
    libertaLista(lista);                // Liberta todos os nos de Lista Criados
}