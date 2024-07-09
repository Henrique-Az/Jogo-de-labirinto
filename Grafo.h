typedef int bool;

typedef int TIPOPESO;

typedef struct adjacencia ADJACENCIA;

typedef struct vertice VERTICE;

typedef struct Grafo Grafo;

typedef struct adjacenciaN ADJACENCIAN;

typedef struct verticeN VERTICEN;

typedef struct GrafoN GrafoN;

/**função para criar um Grafo**/
Grafo *criaGrafo (int v, int *ids, int fim);

bool setFim(Grafo *gr, int id);

bool criaVertice(Grafo *gr, int id);

bool existeVertice(Grafo *gr, int id);

bool criaAresta(Grafo *gr, int vi, int vf, TIPOPESO p);

void liberaLista(ADJACENCIA *a);

void liberaGrafo(Grafo *gr);

void imprime(Grafo *gr);

/**função para criar um Grafo**/
GrafoN *criaGrafoN (int v, int *ids, int fim);

bool setFimN(GrafoN *gr, int id);

bool criaVerticeN(GrafoN *gr, int id);

bool existeVerticeN(GrafoN *gr, int id);

bool criaArestaN(GrafoN *gr, int vi, int vf);

void liberaListaN(ADJACENCIAN *a);

void liberaGrafoN(GrafoN *gr);

void imprimeN(GrafoN *gr);

int processaRaiz(Grafo *gr);

void processaSala(GrafoN *gr);

void imprimeLab(Grafo *gr, int *passou, int tam, int *retrocesso, int tamRet, int atual);

void imprimeLabN(GrafoN *gr, int *passou, int tam, int atual);