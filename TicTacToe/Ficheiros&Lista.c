/* Rui Pedro Costa Almeida - 2021140560 */

#include "funcoes.h"
#include <string.h>

// ADICIONA AO FIM DE CADA JOGADA UM NO A UMA LISTA LIGADA
// inserçao do nó no inicio da lista
blocoLista* addLista(blocoLista* lista, int posBloco, bloco* uBoard, int tabJogado) {

    blocoLista* novo = malloc(sizeof(blocoLista));
    if(novo == NULL) {
        libertaLista(lista);
        return NULL;
    }

    // atribui ao novo bloco da lista a informaçao da jogada efetuada
    novo->linha = uBoard[posBloco].linha;
    novo->coluna = uBoard[posBloco].coluna;
    novo->jogador = uBoard[posBloco].jogador;
    novo->tabuleiro = tabJogado;
    novo->vencedor = uBoard[posBloco].vencedor;

    blocoLista* aux = NULL;
    if(lista == NULL)
        novo->prox = NULL;
    else
        novo->prox = lista;
    return novo;
}

// GRAVA TODOS OS NOS DA LISTA NUM FICHEIRO BINARIO
int gravaLista(blocoLista* lista, char* nomeF, int modo, int nJogadas){

    FILE* f = fopen(nomeF, "ab+");           // +, para o caso de nao existir o ficheiro, este mesmo é criado
    if(f == NULL) {
        fclose(f);
        printf("\t\t\t\t\t *Erro Ao Abrir Ficheiro*\n");
        return 0;
    }
    if(nJogadas == 1)
        fwrite(&modo, sizeof(int), 1, f);    // escreve no logo no inicio do ficheiro o modo de jogo, caso seja a primeira jogada
    fwrite(lista, sizeof(blocoLista), 1, f); // vai passar para o ficheiro a informaçao da lista passada como parametro

    fclose(f);
    return 1;
}

// RECUPERA A LISTA LIGADA DA SESSAO ANTERIOR
blocoLista* recuperaLista(char* nomeF, int* nJogadas, int* modo) {
    blocoLista* lista = NULL, *novo, *aux;
    blocoLista novoAux;

    FILE* f = fopen(nomeF, "rb");
    if(f == NULL) {
        fclose(f);
        printf("\t\t\t\t\t *Erro Ao Abrir Ficheiro*\n");
        return NULL;
    }
    
    fread(modo, sizeof(int), 1, f);
    while(fread(&novoAux, sizeof(blocoLista), 1, f)){
        novo = malloc(sizeof(blocoLista));
        if(novo == NULL)
            return NULL;
            
        *novo = novoAux;
        
        if(lista == NULL) {
            lista = novo;
            novo->prox = NULL;
        }else {
            novo->prox = lista;
            lista = novo;
        }
        (*nJogadas)++;
    }
    fclose(f);
    return lista;
}

// INVERTE A LISTA LIGADA SIMPLES
blocoLista* inverteLista(blocoLista* lista) {
    
    blocoLista* esqLista = NULL, *dirLista = lista->prox; // esqLista : ponteiro a esquerda do ponteiro Lista, dirLista : ponteiro a direita do ponteiro lista

    // metodo de 3 ponteiros (vai incrementa as suas posiçoes)
    lista->prox = NULL;   // coloca a primeira posiçao da lista a com o seu prox a NULL, pois este ao inverter a lista, vai ser o ultimo nó
    while(dirLista != NULL) {
        esqLista = lista;
        lista = dirLista;
        dirLista = dirLista->prox;
        lista->prox = esqLista;
    }

    return lista;
}

// EXPORTA PARA UM FICHEIRO NO FINAL DO JOGO UM RESUMO DO MESMO
int exportaJogoParaFicheiro(blocoLista *lista, int vencedorUlti, int modo) {

    if(vencedorUlti == 1 && (modo != 2 || lista->jogador != 2)){
        printf("\t\t\t\t                       ! FANTASTICO !                    \n");
        printf("\t\t\t\t     -Crie Um Resumo Do Jogo Para Relembrar Mais Tarde-\n\n");
    }
    else {
        printf("\t\t\t\t                 ! Melhor Para a Proxima !               \n");
        printf("\t\t\t\t     -Crie Um Resumo Do Jogo para Rever Todos Os Erros-\n\n");
    }

    lista = inverteLista(lista); // inverte a lista a lista ligada para se puder colocar as jogadas da primeira para a ultima

    // criamos o ficheiro com este nome temporario para o caso de acontecer algum erro (o computador vai abaixo) antes do utilizador escolher o nome, guardar o resumo na mesma
    char* temp = "temporario.txt";
    int tamTemp = strlen(temp);

    int tam = 0;

    FILE* f = fopen(temp, "w+");
    if(f == NULL) {
        printf("\t\t\t\t Erro Na Criacao Do Resumo");
        return 0;
    }

    gravaNomeFicheiroTXT(temp, tamTemp);

    if(modo == 1) 
        f = preencheFicheiro_Modo_1(lista, temp, f);
    else 
        f = preencheFicheiro_Modo_2(lista, temp, f);
    fclose(f);

    // para o caso de nao acontecer nenhum erro, o ficheiro e vai entao, ter o nome escolhido pelo utilizador
    char* nomeF = malloc(sizeof(char) * 16);
    if(nomeF == NULL) {
        printf("\t\t\t\t *Erro Ao Alocar Memoria Para o Nome*");
        return 0;
    }
    int existe;
    do{
        nomeF = obtemNomeDoFicheiro(nomeF, &tam); // vai obter o nome (escolhido pelo utilizar) do ficheiro de texto
        nomeF = addExtensaoFicheiroTexto(nomeF, &tam); // vai adicionar a extensao .txt ao ficheiro, para se saber que e de texto
        nomeF = addFicheiroParaDir(nomeF, &tam); // vai adicionar o caminho para a pasta onde vao ser colocados os resumos

        existe = !verificaSeFicheiroVazio(nomeF); // verifica se este resumo ja existe ou nao, nao deixando avançar enquanto passar um nome Igual

        if(existe)
            printf("\t\t\t\t *O Nome Do Resumo Ja Existe*\n"); 

    }while(existe);

    gravaNomeFicheiroTXT(nomeF, tam);
    rename(temp, nomeF);

    free(nomeF); // liberta na memoria a string do nome do ficheiro apos nao ser mais necessaria

    return 1;
}

// ADICIONA A EXTENSAO .txt AO NOME PARA ESTE SER UM FICHEIRO DE TEXTO
char* addExtensaoFicheiroTexto(char* nomeF, int* tam) {
    
    int extra = *tam % 4 + 1;  // para o caso de ja nao haver mais espaço disponivel na string para adicionar o .txt

    if(*tam > 11) { // pois somente e necessario acrescentar espaço na memorio para o txt caso o nome passado tenha 15 caracteres
        nomeF = realloc(nomeF, sizeof(char) * (16 + extra)); // adiciona a string somente o espaço necessario para se puder colocar a string toda
        if(nomeF == NULL) {
            printf("\t\t\t\t *Erro ao Adicionar Extensao*");
            return NULL;
        }
    }
    strcat(nomeF, ".txt");
    *tam = strlen(nomeF);
    nomeF[*tam] = '\0';

    return nomeF;
}

// ADICIONA O FICHEIRO PARA A PASTA ONDE VAO ESTAR OS RESUMOS DOS JOGOS REALIZADOS
char* addFicheiroParaDir(char* nomeF, int* tam) {
    char* pasta = "./ResumoJogos/";
    int tamPasta = strlen(pasta);
    int tamPath = tamPasta + *tam;

    char* path = malloc(sizeof(char) * (tamPath + 1));
    if(path == NULL) {
        printf("\t\t\t\t *Erro Ao Adicionar O ficheiro Para a Pasta*");
        free(path);
        return nomeF;
    }

    *tam = tamPath;
    path[tamPath] = '\0';

    strcpy(path, pasta);
    strcat(path, nomeF);

    return path;
}

// GUARDA O NOME DO FICHEIRO DE TEXTO QUE VAI CONTER O RESUMO DO JOGO JOGADO
int gravaNomeFicheiroTXT(char* nomeFtxt, int tam) {

    FILE* f = fopen("nomeFicheiro.bin", "wb+");
    if(f == NULL) {
        printf("\t\t\t\t *Erro Ao Guardar o Nome Do Ficheiro De Texto*");
        return 0;
    }
    fwrite(&tam, sizeof(int), 1, f);
    fwrite(nomeFtxt, sizeof(char), tam, f);

    fclose(f);
    return 1;
}

// RECUPERA O NOME DO FICHEIRO DE TEXTO QUE CONTEM O RESUMO DO JOGO DA SESSAO ANTERIOR
char* recuperaNomeFicheiroTxt() {
    FILE* f = fopen("nomeFicheiro.bin", "rb");
    if(f == NULL) {
        printf("\t\t\t\t *Erro Ao Recuperar o Nome Do Ficheiro De Texto Da Sessao Anterior*");
        return 0;
    }

    int tam = 0;
    fread(&tam, sizeof(int), 1, f);
    
    char* nomeF = malloc(sizeof(char) * (tam));
    fread(nomeF, sizeof(char), tam, f);
    nomeF[tam] = '\0';

    fclose(f);
    return nomeF;
}

// APAGA O FICHEIRO DA ULTIMA SESSAO
void apagaUltimaSessao(char* nomeF) {
    remove(nomeF);

    return;
}

// LIBERTA A LISTA LIGADA SIMPLES 
void libertaLista(blocoLista* lista) {

    blocoLista* aux;
    while(lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

    return;
}

// FUNÇAO PARA PREENCHER A INFORMAÇAO NO FICHEIRO SE O FOR O MODO 1
FILE* preencheFicheiro_Modo_1(blocoLista* lista, char* nomeF, FILE* f) {

    int nJogada = 0, vitorias1 = 0, vitorias2 = 0;
    char vencedor = 'n';

    fprintf(f, "\t      ###########\n");
    fprintf(f, "\t       Jogada N.                     - JOGADOR [ 1 ] vs JOGADOR [ 2 ] -\n");
    fprintf(f, "\t      ###########\n");
    for(blocoLista* aux = lista; aux != NULL; aux = aux->prox) {
        nJogada++;
        fprintf(f, "\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
        fprintf(f, "\t           { %d }", nJogada);
        if(aux->vencedor == 'n') {
            fprintf(f, "\t  O Jogador [ %d ] Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] \n\n", aux->jogador, aux->linha, aux->coluna
                                                                                                                  ,aux->tabuleiro);
        } else 
        if(aux->vencedor == 'e') {
            fprintf(f, " O Jogador [ %d ] Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] Concluindo-o ! %d\n\n",aux->jogador, aux->linha
                                                                                                       , aux->coluna ,aux->tabuleiro);
        }else {
            fprintf(f, " O Jogador [ %d ] Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] e Conquistou-o !!!\n", aux->jogador , 
                                                                                  aux->linha, aux->coluna, aux->tabuleiro);
            fprintf(f, "\t\t\t\t\t\t\tFANTASTICO !!\n");
        fprintf(f, "\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
            
            if(aux->jogador == 1) vitorias1++;
            else vitorias2++;
            fprintf(f, "\t\t\t\t=============================================================\n");
            fprintf(f, "\t\t\t\t||      Mini Tabuleiros Conquistados Ate Ao Momenento      ||\n\n");
            fprintf(f, "\t\t\t\t||     Jogador [ 1 ] - | %d |     Jogador [ 2 ] - | %d |     ||\n", vitorias1, vitorias2);
            fprintf(f, "\t\t\t\t=============================================================\n\n");

            
            if(aux->prox == NULL) // quer dizer que e o ultimo bloco e vai ser neste que contem a informaçao de vencedor final
                vencedor = aux->vencedor;
        }
    }
    
    if(vencedor == 'x')
            fprintf(f, "\t\t\t\t       !!! Parabens Jogador [ 1 ], Ganhaste o Jogo !!!");
    else 
    if(vencedor == 'o')
        fprintf(f, "\t\t\t\t       !!! Parabens Jogador [ 2 ], Ganhaste o Jogo !!!");
    else 
        fprintf(f, "\t\t\t\t        !!! Jogo Bastante Renhido, Foi Um Empate !!!");

    return f;
}

// FUNÇAO PARA PREENCHER A INFORMAÇAO NO FICHEIRO SE O FOR O MODO 2
FILE* preencheFicheiro_Modo_2(blocoLista* lista, char* nomeF, FILE* f) {

    fprintf(f, "\t      ###########\n");
    fprintf(f, "\t       Jogada N.                           - VOCE vs COMPUTADOR -\n");
    fprintf(f, "\t      ###########\n");
    
    int nJogada = 0, vitorias1 = 0, vitorias2 = 0;
    char vencedor = 'n';
    for(blocoLista* aux = lista; aux != NULL; aux = aux->prox) {

        nJogada++;
        fprintf(f, "\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
        fprintf(f, "\t           { %d }", nJogada);
        
        if(aux->vencedor == 'n') {
            if(aux->jogador == 1)
                fprintf(f, "\t\t Jogaste Na Posicao (%d,%d) Do Tabuleiro [ %d ] \n\n", aux->linha, aux->coluna, aux->tabuleiro);
            else 
                fprintf(f, "\t   O Computador Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] \n\n", aux->linha, aux->coluna, aux->tabuleiro);

        } else 

        if(aux->vencedor == 'e') {
            if(aux->jogador == 1)
                fprintf(f, "\tJogaste Na Posição (%d,%d) Do Tabuleiro [ %d ] Concluiste-o ! %d\n\n", aux->linha, aux->coluna ,aux->tabuleiro);
            else 
                fprintf(f, "  O Computador Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] Concluindo-o ! %d\n\n", aux->linha, aux->tabuleiro);

        }else {

            if(aux->jogador == 1){
                fprintf(f, "\tJogaste Na Posicao (%d,%d) Do Tabuleiro [ %d ] e Conquistaste-o !\n", aux->linha, aux->coluna, aux->tabuleiro);
                fprintf(f, "\t\t\t\t\t\t\tFANTASTICO !!\n");
            }
            else 
                fprintf(f, "   O Computador Jogou Na Posicao (%d,%d) Do Tabuleiro [ %d ] Concluindo-o ! %d\n", aux->linha, aux->tabuleiro);
            fprintf(f, "\n\t\t\t\t= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n");
            if(aux->jogador == 1) vitorias1++;
            else vitorias2++;
            fprintf(f, "\t\t\t\t=============================================================\n");
            fprintf(f, "\t\t\t\t||      Mini Tabuleiros Conquistados Ate Ao Momenento      ||\n\n");
            fprintf(f, "\t\t\t\t||       Jogador [ 1 ] - | %d |     Computador - | %d |      ||\n", vitorias1, vitorias2);
            fprintf(f, "\t\t\t\t=============================================================\n\n");
        }
        
        if(aux->prox == NULL) // quer dizer que e o ultimo bloco e vai ser neste que contem a informaçao de vencedor final
            vencedor = aux->vencedor;
    }
    if(vencedor == 'x')
        fprintf(f, "\t\t\t\t\t      !!! Parabens, Ganhaste o Jogo !!!");
    else 
    if(vencedor == 'o')
        fprintf(f, "\t\t\t\t   Que Pena !! Perdeste o Jogo, Corre Melhor Na Proxima");
    else 
        fprintf(f, "\t\t\t\t\t  Que Pena !! O jogo Ficou Empatado");

    return f;
}