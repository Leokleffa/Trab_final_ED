#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "avl.h"
#define MAX 60

Nodo* ReadWriteDic(FILE *dicionario, Nodo *raiz){   //l� o dicion�rio e insere na �rvore a palavra e seu respectivo sin�nimo
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
                default: word[i]=ch;    //sen�o, acrescenta o caractere lido na string word
                i++;    //atualiza para colocar o pr�ximo caractere
            }
        }while(ch!='\t');   //fa�o isso, enquanto n�o achar o '\t'
        i=0;     //volta para o inicio da string
        do{
            ch=getc(dicionario);
            switch(ch){
                case '\n':      //se achar '\n' ou EOF, acrescenta '\0' no final da string syn
                case EOF:
                    syn[i]='\0';
                    break;
                default: syn[i]=ch; //sen�o, acrescenta o caractere lido na string syn
                i++;    //atualiza para colocar o pr�ximo caractere
            }
        }while(ch!=EOF && ch!='\n');    //fa�a isso. enquanto n�o achar '\n' ou EOF
        raiz=InsereArvore(raiz,strlwr(word),strlwr(syn),&ok);   //insere na �rvores as string word e syn na �rvore
    }while(ch!=EOF);    //enquanto n�o chegar no fim do dicion�rio
    return raiz;    //retorna a raiz da �rvore
}
void parafrase(FILE *entrada, FILE *saida, Nodo *raiz){     //l� o arquivo de entrada, busca a palavra na �rvore, se encontrar, troca pelo sin�nimo, sen�o mant�m a palavra
    Nodo *aux;
    char *palavra, linha[1000];
    char separador[]= {" ,.&*%\?!;/'@\"$#=><()][}{:\t"};
    while (fgets(linha,1000,entrada)){
        palavra = strtok (linha, separador); //considera qquer caractere nao alfabetico como separador
        do{
            if(linha!=NULL){
                if(aux=busca(raiz,strlwr(palavra))){    //se a palavra for encontrada, ent�o troque-a pelo seu sin�nimo
                    palavra=aux->syn;
                    trocas++;
                }

                if(strlwr(palavra)[strlen(palavra)-1]!='\n')//strlwr e a funcao que converte palavras para minusculo
                    fprintf(saida,"%s ", strlwr(palavra)); //escreve no arquivo de sa�da com espa�o
                else
                    fprintf(saida,"%s", strlwr(palavra));//escreve no arquivo de sa�da com espa�o
                palavra = strtok (NULL, separador);
            }
        } while(palavra!=NULL);     //fa�a isso, enquanto n�o acabar o arquivo
    }
}
