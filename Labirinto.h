#include"Grafo.h"
#include"ArvBin.h"
typedef struct ranking ranking;
ranking *criaRanking();
ArvoreBinaria *parser(int dif);
void jogar(ArvoreBinaria *arv, ranking *rank);
void ordenaPontos(ranking *rank);
void ordenaTempo(ranking *rank);
void imprimeOpcoes();
void mostraRanking(ranking *rank);
void mostraVersao();
void mostraTutorial();