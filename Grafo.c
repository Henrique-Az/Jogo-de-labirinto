#include <stdio.h>
#include <stdlib.h>
#include"Grafo.h"
#define true 1
#define false 0

typedef struct adjacencia {
    int vertice; // vertice de destino 
    TIPOPESO peso; // peso associado a aresta que leva ao vertice de destino
    struct adjacencia *prox; // O próximo elemento da lista de adjacencias
}ADJACENCIA;

typedef struct vertice {
    /* Dados armazenados vão aqui */
	int id;
    ADJACENCIA *cab; //possui apenas a cabeça da lista de adjacencia
}VERTICE;

typedef struct Grafo { //lembrando que cada Grafo possui:
	int fim;
    int vertices; // numero de vertice total do Grafo
    int arestas; // numero de arestas totais do Grafo
    VERTICE *adj; // Arranjo de vertices da estrutura
}Grafo;

typedef struct adjacenciaN {
    int vertice; // vertice de destino 
    struct adjacenciaN *prox; // O próximo elemento da lista de adjacencias
}ADJACENCIAN;

typedef struct verticeN {
    /* Dados armazenados vão aqui */
	int id;
    ADJACENCIAN *cab; //possui apenas a cabeça da lista de adjacencia
}VERTICEN;

typedef struct GrafoN { //lembrando que cada Grafo possui:
	int fim;
    int vertices; // numero de vertice total do Grafo
    int arestas; // numero de arestas totais do Grafo
    VERTICEN *adj; // Arranjo de vertices da estrutura
}GrafoN;

/**função para criar um Grafo**/
Grafo *criaGrafo (int v, int *ids, int fim) {
	int i;
	
	Grafo *g = (Grafo *)malloc(sizeof(Grafo)); //aloca espaço para estrtura Grafo
	g->vertices = v; //atualizo o numero de vertice
	g->arestas = 0;  //atualizo o numero de vertice
	g->adj = (VERTICE *)malloc(v*sizeof(VERTICE)); //ler abaixo
	//Dentro da estrturua tem só o arranjo para o ponteiro de vertice, não o arranjo em si 	
	// então aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<v; i++){ 
		g->adj[i].cab=NULL; //coloco NULL em todas arestas
		g->adj[i].id=ids[i];
	}
	g->fim=fim;
	return(g);
}

int converte(Grafo *gr, int v){ //Uma função que tenta achar o id dentro de um vetor e retorna o índice do vetor que corresponde a esse vértice
	for(int i=0; i<gr->vertices; i++){
		if(gr->adj[i].id==v) return i;
	}
	return -1;
}

bool setFim(Grafo *gr, int id){
	if(converte(gr, id)==-1) return false;
	gr->fim=id;
	return true;
}

int getId(Grafo *gr, int i){
	if(i>=gr->vertices) return -1;
	return gr->adj[i].id;
}

int getMaiorId(Grafo *gr){
	int maior = gr->adj[0].id;
	for(int i=1; i<gr->vertices; i++){
		if(maior<gr->adj[i].id) maior=gr->adj[i].id;
	}
	return maior;
}

int getMaiorIdN(GrafoN *gr){
	int maior = gr->adj[0].id;
	for(int i=1; i<gr->vertices; i++){
		if(maior<gr->adj[i].id) maior=gr->adj[i].id;
	}
	return maior;
}

bool criaVertice(Grafo *gr, int id){
	if(converte(gr, id)!=-1) return false;
	gr->vertices++;
	gr->adj=(VERTICE *)realloc(gr->adj, gr->vertices*sizeof(VERTICE));
	gr->adj[gr->vertices-1].cab=NULL;
	gr->adj[gr->vertices-1].id=id;
	return true;
}

bool existeVertice(Grafo *gr, int id){
	if(converte(gr, id)==-1) return false;
	return true;
}

/**função para adicionar arestas no Grafo**/

ADJACENCIA *criaAdj(int v, int peso){ 
	ADJACENCIA *temp = (ADJACENCIA *) malloc (sizeof(ADJACENCIA)); //aloca espaço para um nó
	temp->vertice =v; //vertice alvo da adjacencia
	temp->peso = peso; //peso da aresta
	temp->prox = NULL; 
	return(temp); //retorno endereço da adjacencia
}

bool criaAresta(Grafo *gr, int vi, int vf, TIPOPESO p) { //vai de vi a vf
	if(!gr) return (false);  //validações se o Grafo existe
	vi=converte(gr, vi);
	vf=converte(gr, vf);
	if((vf<0)||(vf >= gr->vertices))return(false); //validações se os valores não são neg
	if((vi<0)||(vf >= gr->vertices))return(false); //ou maiores que o numero de vértice do Grafo
	
	ADJACENCIA *novo = criaAdj(vf,p); //crio adjacencia com o vértice final e o peso
	//coloco a adjacencia na lista do vértice inicial
	novo->prox = gr->adj[vi].cab; //o campo prox da adjacencia vai receber a cabeça da lista
	gr->adj[vi].cab=novo; // e a cabeça da lista passa a ser o novo elemento
	gr->arestas++; // atualizo o numero de aresta no Grafo
	return (true);
}

void liberaLista(ADJACENCIA *a){
	if(a!=NULL){
		liberaLista(a->prox);
		free(a);
	}
}

void liberaGrafo(Grafo *gr){
	for(int i=0; i<gr->vertices; i++){
		liberaLista(gr->adj[i].cab);
	}
	free(gr->adj);
	free(gr);
}

int getPeso(Grafo *gr, int ind1, int ind2){
	ADJACENCIA *aresta=gr->adj[ind1].cab;
	while(aresta!=NULL){
		if(aresta->vertice==ind2) return aresta->peso;
		aresta=aresta->prox;
	}
	return -1;
}

/**função para criar um Grafo**/
GrafoN *criaGrafoN (int v, int *ids, int fim) {
	int i;
	
	GrafoN *g = (GrafoN *)malloc(sizeof(GrafoN)); //aloca espaço para estrtura Grafo
	g->vertices = v; //atualizo o numero de vertice
	g->arestas = 0;  //atualizo o numero de vertice
	g->adj = (VERTICEN *)malloc(v*sizeof(VERTICEN)); //ler abaixo
	//Dentro da estrturua tem só o arranjo para o ponteiro de vertice, não o arranjo em si 	
	// então aloco o arranjo com (v) o numero de vertice desejado
	for (i=0; i<v; i++){ 
		g->adj[i].cab=NULL; //coloco NULL em todas arestas
		g->adj[i].id=ids[i];
	}
	g->fim=fim;
	return(g);
}

int converteN(GrafoN *gr, int v){
	for(int i=0; i<gr->vertices; i++){
		if(gr->adj[i].id==v) return i;
	}
	return -1;
}

bool existeVerticeN(GrafoN *gr, int id){
	if(converteN(gr, id)==-1) return false;
	return true;
}

bool setFimN(GrafoN *gr, int id){
	if(converteN(gr, id)==-1) return false;
	gr->fim=id;
	return true;
}

int getIdN(GrafoN *gr, int i){
	if(i>=gr->vertices) return -1;
	return gr->adj[i].id;
}

bool criaVerticeN(GrafoN *gr, int id){
	if(converteN(gr, id)!=-1) return false;
	gr->vertices++;
	gr->adj=(VERTICEN *)realloc(gr->adj, gr->vertices*sizeof(VERTICEN));
	gr->adj[gr->vertices-1].cab=NULL;
	gr->adj[gr->vertices-1].id=id;
	return true;
}

ADJACENCIAN *criaAdjN(int v){ 
	ADJACENCIAN *temp = (ADJACENCIAN *) malloc (sizeof(ADJACENCIAN)); //aloca espaço para um nó
	temp->vertice =v; //vertice alvo da adjacencia
	temp->prox = NULL; 
	return(temp); //retorno endereço da adjacencia
}


bool criaArestaN(GrafoN *gr, int vi, int vf) { //vai de vi a vf
	if(!gr) return (false);  //validações se o Grafo existe
	vi=converteN(gr, vi);
	vf=converteN(gr, vf);
	if((vf<0)||(vf >= gr->vertices))return(false); //validações se os valores não são neg
	if((vi<0)||(vf >= gr->vertices))return(false); //ou maiores que o numero de vértice do Grafo
	
	ADJACENCIAN *novo = criaAdjN(vf); //crio adjacencia com o vértice final e o peso
	//coloco a adjacencia na lista do vértice inicial
	novo->prox = gr->adj[vi].cab; //o campo prox da adjacencia vai receber a cabeça da lista
	gr->adj[vi].cab=novo; // e a cabeça da lista passa a ser o novo elemento
	gr->arestas++; // atualizo o numero de aresta no Grafo
	return (true);
}

void liberaListaN(ADJACENCIAN *a){
	if(a!=NULL){
		liberaListaN(a->prox);
		free(a);
	}
}

void liberaGrafoN(GrafoN *gr){
	for(int i=0; i<gr->vertices; i++){
		liberaListaN(gr->adj[i].cab);
	}
	free(gr->adj);
	free(gr);
}

void getAdjacenteN(GrafoN *gr, int vet[3], int ind){
	ADJACENCIAN *aux=gr->adj[ind].cab;
	for(int i=0; i<3; i++){
		if(aux==NULL){
			vet[i]=-1;
			return;
		}
		vet[i]=aux->vertice;
		aux=aux->prox;
	}
}

int getDimensaoN(GrafoN *gr){
	int vet[3], i, j, id, aux;
	for(i=0; i<gr->vertices; i++){
		id=getIdN(gr, i);
		getAdjacenteN(gr, vet, i);
		for(j=0; j<3; j++){
			if(vet[j]==-1) break;
			aux=id-getIdN(gr, vet[j]);
			if(aux<0) aux*=-1;
			if(aux!=1) return aux;
		}
	}
	return 1;
}

int getLinhasN(GrafoN *gr){
	int vet=getMaiorIdN(gr), dim=getDimensaoN(gr);
	if(vet%dim==0){
		return vet/dim;
	}
	return vet/dim+1;
}

void getAdjacente(Grafo *gr, int vet[3], int ind){
	ADJACENCIA *aux=gr->adj[ind].cab;
	for(int i=0; i<3; i++){
		if(aux==NULL){
			vet[i]=-1;
			return;
		}
		vet[i]=aux->vertice;
		aux=aux->prox;
	}
}

int getDimensao(Grafo *gr){
	int vet[3], i, j, id, aux;
	for(i=0; i<gr->vertices; i++){
		id=getId(gr, i);
		getAdjacente(gr, vet, i);
		for(j=0; j<3; j++){
			if(vet[j]==-1) break;
			aux=id-getId(gr, vet[j]);
			if(aux<0) aux*=-1;
			if(aux!=1) return aux;
		}
	}
	return 1;
}

int getLinhas(Grafo *gr){
	int vet=getMaiorId(gr), dim=getDimensao(gr);
	if(vet%dim==0){
		return vet/dim;
	}
	return vet/dim+1;
}

int contem(int *v, int n, int busca){
	if(busca<0) return 0;
	for(int i=0; i<n; i++){
		if(v[i]==-1) return 0;
		if(busca==v[i]){
			return 1;
		}
	}
	return 0;
}

void imprimeLabN(GrafoN *gr, int *passou, int tam, int atual){
	int possivel[3], dim=getDimensaoN(gr), total=dim*getLinhasN(gr)+1, aux;
	getAdjacenteN(gr, possivel, atual);
	for(aux=-2; aux<dim; aux++) printf("::");
	printf("\n::");
	for(int i=1; i<total; i++){
		aux=converteN(gr,i);
		if(aux==atual) printf("()");
		else if(contem(possivel, 3, aux)) printf("><");
		else if(contem(passou, tam, aux)) printf("  ");
		else printf("[]");

		if(i%dim==0) printf("::\n::");
	}
	for(aux=-1; aux<dim; aux++) printf("::");
}

void imprimeLab(Grafo *gr, int *passou, int tam, int *retrocesso, int tamRet, int atual){
	int possivel[3], dim=getDimensao(gr), total=dim*getLinhas(gr)+1, aux;
	getAdjacente(gr, possivel, atual);
	for(aux=-2; aux<dim; aux++) printf("::");
	printf("\n::");
	for(int i=1; i<total; i++){
		aux=converte(gr,i);
		if(aux==atual) printf("()");
		else if(contem(possivel, 3, aux)&&!contem(retrocesso, tamRet, aux)) printf("+%d", getPeso(gr, atual, aux));
		else if(contem(passou, tam, aux)) printf("  ");
		else printf("[]");

		if(i%dim==0) printf("::\n::");
	}
	for(aux=-1; aux<dim; aux++) printf("::");
}

int getOpcao(char a){
	switch(a){
		case 'd':
			return 1;
		case 'a':
			return 2;
		case 'w':
			return 3;
		case 's':
			return 4;
		case 'v':
			return 5; 
	}
	return -1;
}

int processaRaiz(Grafo *gr){
  int i = 0, j, dim, pontos=0;
  int v[3], opVal[3], qtOp=0, opSel;
  int caminho[gr->vertices], qtVer=1;
  int retrocesso[gr->vertices], qtRet=0;
  caminho[0]=0;
  dim = getDimensao(gr);
  while(gr->adj[i].id!=gr->fim){
	imprimeLab(gr, caminho, qtVer, retrocesso, qtRet, i);
    getAdjacente(gr,v,i);
	qtOp=0;
    for(int k=0;k<3;k++){
      if(v[k]==-1) break;
	  else if(contem(retrocesso, qtRet, v[k])) continue;
      else if(gr->adj[i].id+1==getId(gr, v[k])){
		opVal[qtOp]=1;
		qtOp++;
	  }
      else if(gr->adj[i].id-1==getId(gr, v[k])){
		opVal[qtOp]=2;
		qtOp++;
	  }
      else if(gr->adj[i].id-dim==getId(gr, v[k])){
		opVal[qtOp]=3;
		qtOp++;
	  }
      else if(gr->adj[i].id+dim==getId(gr, v[k])){
		opVal[qtOp]=4;
		qtOp++;
	  }
    }
	if(qtOp>0){
		printf("\n\n%d pontos\n\nOnde voce deseja ir(wasd para mover e v para voltar): ", pontos);
		while(1){
			setbuf(stdin, NULL);
			opSel=getchar();
            while(getchar()!='\n');
			opSel=getOpcao(opSel);
			if(contem(opVal, qtOp, opSel)||opSel==5){
				switch(opSel){
					case 1:
						j=converte(gr, getId(gr, i)+1);
						break;
					case 2:
						j=converte(gr, getId(gr, i)-1);
						break;
					case 3:
						j=converte(gr, getId(gr, i)-dim);
						break;
					case 4:
						j=converte(gr, getId(gr, i)+dim);
						break;
					case 5:
						if(pontos>0){
							qtVer--;
							i=caminho[qtVer-1];
							retrocesso[qtRet]=caminho[qtVer];
							qtRet++;
							pontos--;
						} else{
							printf("Nao ha pontos suficientes para retroceder:\n");
						}
						break;
				}
				if(opSel!=5){
					pontos+=getPeso(gr, i, j);
					i=j;
					caminho[qtVer]=i;
					qtVer++;
					printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				}
				break;
			} else{
				printf("Opcao invalida, tente novamente:\n");
			}
		}
	} else{
		if(pontos==0){
			printf("\n\nVoce perdeu, reiniciando a fase\n\n");
			i=0;
			qtVer=1;
			qtRet=0;
			pontos=0;
		} else{
			printf("\n\nNao ha caminhos, um ponto foi gasto para retroceder\n\n");
			qtVer--;
			i=caminho[qtVer-1];
			retrocesso[qtRet]=caminho[qtVer];
			qtRet++;
			pontos--;
		}
	}
  }
  imprimeLab(gr, caminho, qtVer, retrocesso, qtRet, i);
  return pontos;
}

void processaSala(GrafoN *gr){
  int i = 0,dim;
  int v[3], opVal[3], qtOp=0, opSel;
  int caminho[gr->vertices], qtVer=1;
  caminho[0]=0;
  dim = getDimensaoN(gr);
  while(gr->adj[i].id!=gr->fim){
	imprimeLabN(gr, caminho, qtVer, i);
    getAdjacenteN(gr,v,i);
	qtOp=0;
    for(int k=0;k<3;k++){
      if(v[k]==-1) break;
      else if(gr->adj[i].id+1==getIdN(gr, v[k])){
		opVal[qtOp]=1;
		qtOp++;
	  }
      else if(gr->adj[i].id-1==getIdN(gr, v[k])){
		opVal[qtOp]=2;
		qtOp++;
	  }
      else if(gr->adj[i].id-dim==getIdN(gr, v[k])){
		opVal[qtOp]=3;
		qtOp++;
	  }
      else if(gr->adj[i].id+dim==getIdN(gr, v[k])){
		opVal[qtOp]=4;
		qtOp++;
	  }
    }
	if(qtOp>0){
		while(1){
			printf("\n\nOnde voce deseja ir(wasd para mover): ");
			setbuf(stdin, NULL);
			opSel=getchar();
            while(getchar()!='\n');
			opSel=getOpcao(opSel);
			if(contem(opVal, qtOp, opSel)){
				switch(opSel){
					case 1:
						i=converteN(gr, getIdN(gr, i)+1);
						break;
					case 2:
						i=converteN(gr, getIdN(gr, i)-1);
						break;
					case 3:
						i=converteN(gr, getIdN(gr, i)-dim);
						break;
					case 4:
						i=converteN(gr, getIdN(gr, i)+dim);
						break;
				}
				caminho[qtVer]=i;
				qtVer++;
				printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
				break;
			} else{
				printf("Opcao invalida, tente novamente:\n");
			}
		}
	} else{
		printf("\n\nVoce perdeu, reiniciando a fase\n\n");
		i=0;
		qtVer=1;
	}
  }
  imprimeLabN(gr, caminho, qtVer, i);
}