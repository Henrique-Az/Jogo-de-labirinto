#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"Grafo.h"
#include"ArvBin.h"
#include"Labirinto.h"

typedef struct{
    char nome[30];
    double tempos[6];
    int pontos;
}partida;

typedef struct ranking{
    partida vet[10];
    int atual;
    char cheio; //booleano indicando se o resto do vetor é lixo ou partidas validas
}ranking;

ranking *criaRanking(){
    ranking *a=(ranking *)malloc(sizeof(ranking));
    a->atual=0;
    a->cheio=0;
    return a;
}

double calculaTempoTotal(partida part){
    double tempoTotal=0;
    for(int j=0;j<6;j++) tempoTotal += part.tempos[j];
    return tempoTotal;
}

void ordenaTempo(ranking *rank){
    int i,j;
    float tempoAux,tempoTotal;
    partida tmp;
    if(rank->cheio==1){
        for (i=1 ; i < 10 ; i++) {
            tmp = rank->vet[i];
            tempoTotal = calculaTempoTotal(rank->vet[i]);
            tempoAux = calculaTempoTotal(rank->vet[i-1]);

            for (j = i-1 ; j >= 0 &&  tempoAux > tempoTotal ; j--)
                rank->vet[j+1] = rank->vet[j];

            rank->vet[j+1] = tmp;
            if(j-1>=0) tempoAux = calculaTempoTotal(rank->vet[j-1]);
        }
    }else{
        for (i=1 ; i < rank->atual ; i++) {
            tmp = rank->vet[i];
            tempoTotal = calculaTempoTotal(tmp);
            tempoAux = calculaTempoTotal(rank->vet[i-1]);

            for (j = i-1 ; j >= 0 && tempoAux > tempoTotal ; j--){
                rank->vet[j+1] = rank->vet[j];
                if(j-1>=0) tempoAux = calculaTempoTotal(rank->vet[j-1]);
            }
            rank->vet[j+1] = tmp;
        }
    }

}

void ordenaPontos(ranking *rank){
    partida tmp;
    int i,j;
    if(rank->cheio==1){
        for (i=1 ; i < 10 ; i++) {
            tmp = rank->vet[i];
            for (j = i-1 ; j >= 0 && rank->vet[j].pontos < tmp.pontos ; j--)
                rank->vet[j+1] = rank->vet[j];

            rank->vet[j+1] = tmp;
        }
    }else{
        for (i=1 ; i < rank->atual ; i++) {
            tmp = rank->vet[i];
            for (j = i-1 ; j >= 0 && rank->vet[j].pontos < tmp.pontos ; j--)
                rank->vet[j+1] = rank->vet[j];

            rank->vet[j+1] = tmp;
        }
    }
}

void removeRank(ranking *rank){
    int i;
    if(rank->cheio==0&&rank->atual==0){
        printf("Nao ha dados para serem removidos\n");
        return;
    }
    printf("---------------------RANKING----------------------\n");
    printf("POSICAO     JOGADOR     PONTOS     TEMPO\n");
    if(rank->cheio==1){
        for(i=0;i<10;i++){
            printf("--------------------------------------------------\n");
            printf("[%d]",i+1);
            printf("%15s",rank->vet[i].nome);
            printf("%9d",rank->vet[i].pontos);
            printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
        }
        printf("--------------------------------------------------\n");
    }else{
        for(i=0;i<rank->atual;i++){
            printf("--------------------------------------------------\n");
            printf("[%d]",i+1);
            printf("%15s",rank->vet[i].nome);
            printf("%9d",rank->vet[i].pontos);
            printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
        }
        printf("--------------------------------------------------\n"); 
    }
    printf("Digite o digito do rank que deve ser apagado\n");
    scanf("%d", &i);
    if(i>0&&i<11){
        if(rank->cheio==0){
            if(i<=rank->atual){ //if impede de remover 1 se usuario digitou invalido
                for(;i<rank->atual; i++){
                    rank->vet[i-1]=rank->vet[i];
                }
                rank->atual--;
            }
        }else{
            partida aux[9];
            int j, s=rank->atual;//Mais velho;
            for(j=0; j<9; j++, s++){
                if(s%10!=i-1)
                    aux[j]=rank->vet[s%10];
                else{
                    j--;
                }
            }
            for(j=0; j<9; j++){
                rank->vet[j]=aux[j];
            }
            rank->atual=9;
            rank->cheio=0;
        }
    }
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void mostraRanking(ranking *rank){
    int x,i;
    printf("+------------------------------+\n");
    printf("|    Visualizar ranking por:   |\n");
    printf("|                              |\n");
    printf("| [1] Pontos                   |\n");
    printf("| [2] Tempo total              |\n");
    printf("| [3] Limpar historico         |\n");
    printf("| [4] Excluir um registro      |\n");
    printf("|                              |\n");
    printf("+------------------------------+\n\n");
    printf("Opcao: ");
    scanf("%d",&x);
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    switch(x){
        case 1:
            if(rank->atual==0&&rank->cheio==0) printf("Nao houveram partidas para serem classificadas\n\n");
            else{
                printf("---------------------RANKING----------------------\n");
                printf("POSICAO     JOGADOR     PONTOS     TEMPO\n");
                ordenaPontos(rank);
                if(rank->cheio==1){
                    for(i=0;i<10;i++){
                        printf("--------------------------------------------------\n");
                        printf("[%d]",i+1);
                        printf("%15s",rank->vet[i].nome);
                        printf("%9d",rank->vet[i].pontos);
                        printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
                    }
                    printf("--------------------------------------------------\n");
                    printf("Pressione enter para continuar\n");
                    setbuf(stdin, NULL);
                    getchar();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }else{
                    for(i=0;i<rank->atual;i++){
                        printf("--------------------------------------------------\n");
                        printf("[%d]",i+1);
                        printf("%15s",rank->vet[i].nome);
                        printf("%9d",rank->vet[i].pontos);
                        printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
                    }
                    printf("--------------------------------------------------\n");
                    printf("Pressione enter para continuar\n");
                    setbuf(stdin, NULL);
                    getchar();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
            }
            break;
        case 2:
            if(rank->atual==0) printf("Nao houveram partidas para serem classificadas\n\n");
            else{
                ordenaTempo(rank);
                printf("---------------------RANKING----------------------\n");
                printf("POSICAO     JOGADOR     PONTOS     TEMPO\n");
                if(rank->cheio==1){
                    for(i=0;i<10;i++){
                        printf("--------------------------------------------------\n");
                        printf("[%d]",i+1);
                        printf("%15s",rank->vet[i].nome);
                        printf("%9d",rank->vet[i].pontos);
                        printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
                    }
                    printf("--------------------------------------------------\n");
                    printf("Pressione enter para continuar\n");
                    setbuf(stdin, NULL);
                    getchar();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }else{
                    for(i=0;i<rank->atual;i++){
                        printf("--------------------------------------------------\n");
                        printf("[%d]",i+1);
                        printf("%15s",rank->vet[i].nome);
                        printf("%9d",rank->vet[i].pontos);
                        printf("%14.3f\n",calculaTempoTotal(rank->vet[i]));
                    }
                    printf("--------------------------------------------------\n");
                    printf("Pressione enter para continuar\n");
                    setbuf(stdin, NULL);
                    getchar();
                    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                }
            }
            break;
        case 3:
            free(rank);
            rank = criaRanking();
            break;
        case 4:
            removeRank(rank);
            break;
    }
}

void mostraVersao(){
    printf("+------------------------------+\n");
    printf("|            Versao            |\n");
    printf("|                              |\n");
    printf("|          Versao 1.0          |\n");
    printf("|                              |\n");
    printf("|        Desenvolvedores:      |\n");
    printf("|        Henrique Azevedo      |\n");
    printf("|        Miguel Tabajara       |\n");
    printf("|                              |\n");
    printf("+------------------------------+\n\n");
    printf("Pressione enter para continuar\n");
    setbuf(stdin, NULL);
    getchar();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void mostraTutorial(){
    printf("+-------------------------------------------------+\n");
    printf("|                  Tutorial                       |\n");
    printf("|                                                 |\n");
    printf("|  Este jogo se trata de um labirinto que trabalha|\n");
    printf("|a memoria e logica do jogador.                   |\n");
    printf("|                                                 |\n");
    printf("| Modo Facil: Contem 6 labirintos de 4 a 9 salas  |\n");
    printf("|cada. A ultima area contabilizara pontos de acor-|\n");
    printf("|do com as escolhas que o usuario tomar.          |\n");
    printf("|                                                 |\n");
    printf("| Modo Medio: Contem 6 labirintos de 6 a 11 salas |\n");
    printf("|cada. A ultima area contabilizara pontos de acor-|\n");
    printf("|do com as escolhas que o usuario tomar.          |\n");
    printf("|                                                 |\n");
    printf("| Modo Dificil Contem 6 labirintos de 9 a 14 salas|\n");
    printf("|cada. A ultima area contabilizara pontos de acor-|\n");
    printf("|do com as escolhas que o usuario tomar.          |\n");
    printf("|                                                 |\n");
    printf("| Icones do tabuleiro:                            |\n");
    printf("| () Representa sua localizacao atual             |\n");
    printf("| <> Representa seus possiveis movimentos         |\n");
    printf("| [] Representa paredes ou salas ainda nao explora|\n");
    printf("| das                                             |\n");
    printf("|                                                 |\n");
    printf("|                  Divirta-se!                    |\n");
    printf("+-------------------------------------------------+\n\n");
    printf("Pressione enter para continuar\n");
    setbuf(stdin, NULL);
    getchar();
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
}

void imprimeOpcoes(){
    printf("+------------------------------+\n");
    printf("|             Menu             |\n");
    printf("|                              |\n");
    printf("| [1] Jogar                    |\n");
    printf("| [2] Ranking                  |\n");
    printf("| [3] Tutorial                 |\n");
    printf("| [4] Versao                   |\n");
    printf("| [5] Sair                     |\n");
    printf("|                              |\n");
    printf("+------------------------------+\n\n");
    printf("Opcao: ");
}

void leCentro(FILE *fp, Grafo *res){
    char buffer[30];
    int sala, dest, peso;
    while(fgets(buffer, 30, fp)){
        if(buffer[0]==13||buffer[0]=='\n') return;
        sscanf(buffer, "%d", &sala);
        if(!existeVertice(res, sala)){
            criaVertice(res, sala);
        }
        int i=0;
        for(;buffer[i]!=13&&buffer[i]!='\n'&&buffer[i]!=' ';i++);
        if(buffer[i]!=13&&buffer[i]!='\n'){
            i++;
            while(1){
                sscanf(buffer+i, "%d %d", &dest, &peso);
                if(!existeVertice(res, dest)){
                    criaVertice(res, dest);
                }
                criaAresta(res, sala, dest, peso);
                for(;buffer[i]!=' ';i++);
                i++;
                for(;buffer[i]!=13&&buffer[i]!='\n'&&buffer[i]!=' ';i++);
                if(buffer[i]==13||buffer[i]=='\n') break;
                i++;
            }
        }
    }
}

void leSala(FILE *fp, GrafoN *res){
    char buffer[30];
    int sala, dest;
    while(fgets(buffer, 30, fp)){
        if(buffer[0]==13||buffer[0]=='\n') return;
        sscanf(buffer, "%d", &sala);
        if(!existeVerticeN(res, sala)){
            criaVerticeN(res, sala);
        }
        int i=0;
        while(1){
            for(;buffer[i]!=13&&buffer[i]!='\n'&&buffer[i]!=' ';i++);
            if(buffer[i]==13||buffer[i]=='\n') break;
            i++;
            sscanf(buffer+i, "%d", &dest);
            if(!existeVerticeN(res, dest)){
                criaVerticeN(res, dest);
            }
            criaArestaN(res, sala, dest);
        }
    }
}

ArvoreBinaria *parser(int dif){
    ArvoreBinaria *arv=criar();
    FILE *fp;
    if(dif==1){
        fp=fopen("facil.txt", "r");
    } else if(dif==2){
        fp=fopen("medio.txt", "r");
    } else{
        fp=fopen("dificil.txt", "r");
    }
    if(fp==NULL){
        exit(1);
    }
    int fim;
    fscanf(fp, "%d\n", &fim);
    Grafo *aux=criaGrafo(0, NULL, fim);
    leCentro(fp,aux);
    Insercao(arv, aux);
    for(int i=0; i<5; i++){
        fscanf(fp, "%d\n", &fim);
        GrafoN *aux1=criaGrafoN(0, NULL, fim);
        leSala(fp, aux1);
        Insercao(arv, aux1);
    }
    fclose(fp);
    return arv;
}

void jogar(ArvoreBinaria *arv, ranking *rank){
    char nome[20];
    printf("Insira o seu nome: ");
    setbuf(stdin, NULL);
    fgets(nome, 20, stdin);
    if(nome[strlen(nome)-1]=='\n') nome[strlen(nome)-1]='\0';
    strcpy(rank->vet[rank->atual].nome, nome);
    rank->vet[rank->atual].pontos=percurso(arv, rank->vet[rank->atual].tempos);
    printf("\n\nVoce ganhou com %d pontos\n\n", rank->vet[rank->atual].pontos);
    double *tempo=rank->vet[rank->atual].tempos;
    double total=tempo[0]+tempo[5];
    printf("O tempo de cada area foi:\n\nFase 1: %.2f seg\n", tempo[5]);
    for(int i=4; i>0; i--){
      total+=tempo[i];
      printf("Fase %d: %.2f seg\n", 6-i,tempo[i]);
    }
    printf("Area central: %.2f seg\n\nTempo total: %.2f seg\n", tempo[0], total);
    rank->atual++;
    if(rank->atual==10){
        rank->atual=0;
        rank->cheio=1;
    }
}
