#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"Grafo.h"
#include"ArvBin.h"

typedef struct no{
    Tipo val;
    Apontador esq, dir;
} No;

ArvoreBinaria *criar(){
    ArvoreBinaria *a=(ArvoreBinaria*)malloc(sizeof(ArvoreBinaria));
    (*a)=NULL;
    return a;
}

void Insercao(ArvoreBinaria *arv, Tipo it){
    if(arv==NULL) return;
    No *no=(No *)malloc(sizeof(No));
    no->val=it;
    no->esq=NULL;
    no->dir=NULL;
    if(*arv==NULL){
        *arv=no;
    }
    else{
      Apontador aux=*arv;
      if(Altura(arv)<2){
        while(aux->esq!=NULL) aux = aux->esq;
        aux->esq = no;
      }else{
        aux = (*arv)->dir;
        if(aux==NULL){
            (*arv)->dir= no;
        }
        else{
          if(aux->esq==NULL){
            aux->esq = no;
          }
          else{
            aux->dir = no;
          }
        }
      }
    }
}

void liberaArvoreAux(Apontador a){
  if(a==NULL) return;
  liberaArvoreAux(a->esq);
  liberaArvoreAux(a->dir);
  liberaGrafoN(a->val);
  free(a);
}

void liberaArvore(ArvoreBinaria *arv){
  if(*arv==NULL) return;
  liberaArvoreAux((*arv)->esq);
  liberaArvoreAux((*arv)->dir);
  liberaGrafo((*arv)->val);
  free(*arv);
  arv=NULL;
}

void percursoAux(Apontador a, double tempo[6], int n){
    if(a==NULL) return;
    percursoAux(a->dir, tempo, n+2);
    percursoAux(a->esq, tempo, n+1);
    clock_t ini, fim;
    printf("Mapa das fases percorridas: ");
    for(int i=5; i>n; i--){
      if(i==n+1)
        printf("Fase %d", 6-i);
      else
        printf("Fase %d -> ", 6-i);
    }
    printf("\nComecando a fase %d:\n\n", 6-n);
    ini=clock();
    processaSala((GrafoN *)a->val);
    fim=clock();
    tempo[n]=(double)(fim-ini);
    if(CLOCKS_PER_SEC==1000000){ //Corrige pra um bug dentro do replit, clocks_per_sec foi definido como 1000000,  mas roda em apenas 1000 clocks por segundo, isso faz com o que o programa não funcione para sistemas que definem clocks_per_sec como 1000000 e realmente rodem a 1000000, mas funciona nos terminais do windows, que tem clocks_per_sec definido como 1000
        tempo[n]/=1000;
    } else{
        tempo[n]/=CLOCKS_PER_SEC;
    }
    printf("\nParabens, voce concluiu a fase em %.2f seg (aperte enter para passar para a proxima fase)", tempo[n]);
    setbuf(stdin, NULL);
    getchar();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

int percurso(ArvoreBinaria *arv, double *tempo){
    if(arv==NULL) return -1;
    int pontos;
    percursoAux((*arv)->dir, tempo, 3);
    percursoAux((*arv)->esq, tempo, 1);
    clock_t ini, fim;
    printf("Mapa das fases percorridas: Fase 1 -> Fase 2 -> Fase 3 -> Fase 4 -> Fase 5\n");
    printf("Voce chegou na area central! Seus movimentos valem pontos, e voce pode gastar um ponto para retornar um espaco\n\n");
    ini=clock();
    pontos=processaRaiz((Grafo *)(*arv)->val);
    fim=clock();
    tempo[0]=(double)(fim-ini);
    if(CLOCKS_PER_SEC==1000000){ //Corrige pra um bug dentro do replit, clocks_per_sec foi definido como 1000000,  mas roda em apenas 1000 clocks por segundo, isso faz com o que o programa não funcione para sistemas que definem clocks_per_sec como 1000000 e realmente rodem a 1000000, mas funciona nos terminais do windows, que tem clocks_per_sec definido como 1000
        tempo[0]/=1000;
    } else{
        tempo[0]/=CLOCKS_PER_SEC;
    }
    printf("\nParabens, voce concluiu a area central em %.2f seg", tempo[0]);
    printf("\n");
    return pontos;
}

int alturaaux(Apontador apontador){
    if(apontador->dir==NULL&&apontador->esq==NULL) return 0;
    int esq, dir;
    if(apontador->esq==NULL) esq=0;
    else esq=1+alturaaux(apontador->esq);
    if(apontador->dir==NULL) dir=0;
    else dir=1+alturaaux(apontador->dir);
    if(dir>esq) return dir;
    return esq;
}

int Altura(ArvoreBinaria *arv){
    if(arv==NULL) return -1;
    return alturaaux(*arv);
}

void imprimeAux(Apontador a){
    if(a==NULL) return;
    printf("%p\n", a->val);
    imprimeAux(a->esq);
    imprimeAux(a->dir);
}

void imprimeArv(ArvoreBinaria *arv){
    imprimeAux(*arv);
}