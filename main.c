#include<stdio.h>
#include<stdlib.h>
#include"Labirinto.h"

int main(){
    ArvoreBinaria *arv;
    ranking *rankF=criaRanking(), *rankM=criaRanking(), *rankD=criaRanking();

    int x,y;
    while(x!=5){
        imprimeOpcoes();
        scanf("%d",&x);
        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
        switch(x){
            case 1:
                while(x==1){
                    printf("+------------------------------+\n");
                    printf("|          Escolha nivel       |\n");
                    printf("|                              |\n");
                    printf("| [1] Facil                    |\n");
                    printf("| [2] Medio                    |\n");
                    printf("| [3] Dificil                  |\n");
                    printf("|                              |\n");
                    printf("+------------------------------+\n");
                    scanf("%d",&y);
                    switch(y){
                        case 1:
                            while(x==1){
                                arv=parser(y);
                                jogar(arv, rankF);
                                printf("Deseja jogar novamente?\n1: Sim\n2: Nao\nOpcao: ");
                                scanf("%d",&x);
                            }
                            liberaArvore(arv);
                            break;
                        case 2:
                            while(x==1){
                                arv=parser(y);
                                jogar(arv, rankM);
                                printf("Deseja jogar novamente?\n1: Sim\n2: Nao\nOpcao: ");
                                scanf("%d",&x);
                            }
                            liberaArvore(arv);
                            break;

                        case 3:
                            while(x==1){
                                arv=parser(y);
                                jogar(arv, rankD);
                                printf("Deseja jogar novamente?\n1: Sim\n2: Nao\nOpcao: ");
                                scanf("%d",&x);
                            }
                            liberaArvore(arv);
                            break;
                        default:
                            printf("Opcao invalida\n\n");
                            x = 1;
                    }
                }
                break;

            case 2:
                printf("+------------------------------+\n");
                printf("|     Escolha a dificuldade    |\n");
                printf("|                              |\n");
                printf("| [1] Facil                    |\n");
                printf("| [2] Medio                    |\n");
                printf("| [3] Dificil                  |\n");
                printf("|                              |\n");
                printf("+------------------------------+\n");
                printf("\nOpcao: ");
                scanf("%d",&y);
                printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
                switch(y){
                    case 1:
                        mostraRanking(rankF);
                        break;
                    case 2:
                        mostraRanking(rankM);
                        break;
                    case 3:
                        mostraRanking(rankD);
                        break;
                    default:
                        printf("Dificuldade invalida\n\n");

                }
                break;

            case 3:
                mostraTutorial();
                break;

            case 4:
                mostraVersao();
                break;

            case 5:
                break;

            default:
                printf("Opcao invalida");

        }
    }

    return 0;
}
