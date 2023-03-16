/*
UNIVERSIDADE FEDERAL DO RIO GRANDE DO SUL
INSTITUTO DE INFORMÁTICA
INF 01203 – Estruturas de Dados
TRABALHO FINAL
Gerador de Paráfrases

Objetivo
O objetivo do trabalho é comparar o desempenho das Árvores Binárias de Pesquisa e de um tipo de
árvore balanceada a ser escolhida pela dupla (AVL, Rubro-Negra, ou Splay) em uma aplicação de
geração de paráfrases.

Integrantes do grupo:
    Carlos Negri - 00333174
    Leonardo Kauer Leffa - 00333399

Turma:
    A

Professora:
    Viviane Moreira

Arvores escolhidas:
    ABP e AVL

Linguagem:
    C

Conteúdo:
    main.c  avl.c   avl.h   abp.c   abp.h

Arquivo atual:
    main.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#define MAX 60

int main(int argc, char *argv[]){

    setlocale(LC_ALL,""); //para imprimir corretamente na tela os caracteres acentuados

    clock_t start, end; //para contar o tempo decorrido

    Nodo *raiz;

    FILE *entrada;
    FILE *saida;
    FILE *dicionario;
     //zera as variaveis globais
    rot=0;
    comp=0;
    compINS=0;
    compBUSCA=0;
    trocas=0;

    if (argc!=4){  //o numero de parametros esperado é 3: nome do programa (argv[0]), nome do dicionario(argv[1]), nome do arq de entrada(argv[2]), nome do arquivo de saida(argv[3])
        printf ("Número incorreto de parâmetros.\n Para chamar o programa digite: <nome_programa> <dicionario> <arq_entrada> <arq_saida>\n");
        return 1;
    }
    else{
        if(!(dicionario = fopen(argv[1], "r"))){//abre o dicionario em modo de leitura
            printf("Erro ao abrir o dicionario (%s)\n", argv[1]);
            fclose (dicionario);
            return 1;
        }
        else{    //arquivo de dicionario ok
            if(!(entrada = fopen(argv[2], "r"))){//abre o arquivo de entrada
                printf("Erro ao abrir o arquivo de entrada (%s)", argv[2]);
                fclose (dicionario);
                fclose (entrada);
                return 1;
            }
            else{
                if(!(saida = fopen(argv[3], "w"))){//abre e cria o arquivo de saida
                    printf("Erro ao abrir o arquivo de entrada (%s)", argv[2]);
                    fclose (dicionario);
                    fclose (entrada);
                    fclose (saida);
                    return 1;
                }

                raiz=inicializa();

                start = clock();    //inicia a contagem de tempo
/*---------------------------------------------------------------------------------------------------*/
                raiz=ReadWriteDic(dicionario, raiz);    //lê o dicionário e insere na árvore a palavra e seu respectivo sinônimo
                parafrase(entrada, saida, raiz);        //lê o arquivo de entrada, busca a palavra na árvore, se encontrar, troca pelo sinônimo, senão mantém a palavra
/*---------------------------------------------------------------------------------------------------*/
                end = clock();  //finaliza a contagem de tempo

                printf("\n=========================== AVL ===========================\n");
                printf("\nArquivo %s gerado com sucesso.\n", argv[3]);

                float milsec = (float)(end - start) / CLOCKS_PER_SEC * 1000;    //calcula o tempo decorrido

                printf("\nTempo de processamento = %.5f ms\n", milsec);

                printf("\nQuantidade de rotações realizadas = %d\n", rot);

                printf("\nQuantidade de comparações realizadas = %d\n", comp);

                printf("\nQuantidade de comparações realizadas na função insere = %d\n", compINS);

                printf("\nQuantidade de comparações realizadas na função busca = %d\n", compBUSCA);

                printf("\nQuantidade de nodos = %d\n", contaNodos(raiz));

                printf("\nAltura = %d\n", Altura(raiz));

                printf("\nQuantidade de trocas de palavras por sinônimos realizadas = %d\n", trocas);

            }
            //finalizando o programa
            raiz=destruir(raiz);
            fclose (dicionario);
            fclose (entrada);
            fclose (saida);
        }
    }
    return 0;
}
