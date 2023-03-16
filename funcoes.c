#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#define MAX 60

Nodo* ReadWriteDic(FILE *dicionario, Nodo *raiz){   //lê o dicionário e insere na árvore a palavra e seu respectivo sinônimo
    int ok;
    int i=0;
    char ch;
    char word[MAX];
    char syn[MAX];
    do{
        i=0;     //volta para o inicio da string
        do{
            ch=getc(dicionario);
            switch(ch){
                case '\t':          //se achar '\t' ou EOF, acrescenta '\0' no final da string word
                case EOF:
                    word[i]='\0';
                    break;
                default: word[i]=ch;    //senão, acrescenta o caractere lido na string word
                i++;    //atualiza para colocar o próximo caractere
            }
        }while(ch!='\t');   //faço isso, enquanto não achar o '\t'
        i=0;     //volta para o inicio da string
        do{
            ch=getc(dicionario);
            switch(ch){
                case '\n':      //se achar '\n' ou EOF, acrescenta '\0' no final da string syn
                case EOF:
                    syn[i]='\0';
                    break;
                default: syn[i]=ch; //senão, acrescenta o caractere lido na string syn
                i++;    //atualiza para colocar o próximo caractere
            }
        }while(ch!=EOF && ch!='\n');    //faça isso. enquanto não achar '\n' ou EOF
        raiz=InsereArvore(raiz,strlwr(word),strlwr(syn),&ok);   //insere na árvores as string word e syn na árvore
    }while(ch!=EOF);    //enquanto não chegar no fim do dicionário
    return raiz;    //retorna a raiz da árvore
}
void parafrase(FILE *entrada, FILE *saida, Nodo *raiz){     //lê o arquivo de entrada, busca a palavra na árvore, se encontrar, troca pelo sinônimo, senão mantém a palavra
    Nodo *aux;
    char *palavra, linha[1000];
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\t"};
    while (fgets(linha,1000,entrada)){
        palavra = strtok (linha, separador); //considera qquer caractere nao alfabetico como separador
        do{
            if(linha!=NULL){
                if(aux=busca(raiz,strlwr(palavra))){    //se a palavra for encontrada, então troque-a pelo seu sinônimo
                    palavra=aux->syn;
                    trocas++;
                }

                if(strlwr(palavra)[strlen(palavra)-1]!='\n')//strlwr e a funcao que converte palavras para minusculo
                    fprintf(saida,"%s ", strlwr(palavra)); //escreve no arquivo de saída com espaço
                else
                    fprintf(saida,"%s", strlwr(palavra));//escreve no arquivo de saída com espaço
                palavra = strtok (NULL, separador);
            }
        } while(palavra!=NULL);     //faça isso, enquanto não acabar o arquivo
    }
}
