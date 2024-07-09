#include"Grafo.h"
typedef struct no No;
typedef No* ArvoreBinaria;
typedef No* Apontador;
typedef void* Tipo;
typedef int Busca;

ArvoreBinaria *criar();
void Insercao(ArvoreBinaria *arv, Tipo it);
void liberaArvore(ArvoreBinaria *arv);
int percurso(ArvoreBinaria *arv, double *tempo);
int Altura(ArvoreBinaria *arv);
void imprimeArv(ArvoreBinaria *arv);