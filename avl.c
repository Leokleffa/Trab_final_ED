#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 60
#include "avl.h"

Nodo* inicializa(){
    return NULL;
}
Nodo* rotacao_direita(Nodo* pt){
    rot++;
    Nodo *ptu;
    ptu = pt->esq;
    pt->esq = ptu->dir;
    ptu->dir = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}
Nodo* rotacao_esquerda(Nodo *pt){
    rot++;
    Nodo *ptu;
    ptu = pt->dir;
    pt->dir = ptu->esq;
    ptu->esq = pt;
    pt->FB = 0;
    pt = ptu;
    return pt;
}
Nodo* rotacao_dupla_direita (Nodo* pt){
    rot++;
    Nodo *ptu, *ptv;
    ptu = pt->esq;
    ptv = ptu->dir;
    ptu->dir = ptv->esq;
    ptv->esq = ptu;
    pt->esq = ptv->dir;
    ptv->dir = pt;
    if (ptv->FB == 1)
        pt->FB = -1;
    else
        pt->FB = 0;
    if (ptv->FB == -1)
        ptu->FB = 1;
    else
        ptu->FB = 0;
    pt = ptv;
    return pt;
}
Nodo* rotacao_dupla_esquerda (Nodo *pt){
    rot++;
    Nodo *ptu, *ptv;
    ptu = pt->dir;
    ptv = ptu->esq;
    ptu->esq = ptv->dir;
    ptv->dir = ptu;
    pt->dir = ptv->esq;
    ptv->esq = pt;
    if (ptv->FB == -1)
        pt->FB = 1;
    else
        pt->FB = 0;
    if (ptv->FB == 1)
        ptu->FB = -1;
    else
        ptu->FB = 0;
    pt = ptv;
    return pt;
}
Nodo* InsereArvore (Nodo *raiz, char word[], char syn[], int *ok){
    comp++;
    compINS++;
    if (raiz == NULL) {                         //se achou
        raiz = (Nodo*) malloc(sizeof(Nodo));
        strcpy(raiz->word,word);                //raiz->word recebe a string word
        raiz->esq = NULL;
        raiz->dir = NULL;
        strcpy(raiz->syn,syn);                  //raiz->syn recebe a string syn
        raiz->FB = 0;
        *ok = 1;
    }
    else if (strcmp(raiz->word,word)>0) {               //se a ordem lexicográfica das palavras for menor, insere à esquerda
        raiz->esq = InsereArvore(raiz->esq,word,syn,ok);
        comp++;
        compINS++;
        if (*ok) {
            switch (raiz->FB) {
                case -1: raiz->FB = 0;
                        *ok = 0;
                        break;
                case  0:  raiz->FB = 1; break;
                case  1:  raiz=Caso1(raiz,ok); break;
            }
        }
    }
    else {                                                  //se a ordem lexicográfica das palavras for maior, insere à direita
        raiz->dir = InsereArvore(raiz->dir,word,syn,ok);
        comp++;
        compINS++;
        if (*ok) {
            switch (raiz->FB) {
                case  1:  raiz->FB = 0; *ok = 0; break;
                case  0:  raiz->FB = -1; break;
                case -1:  raiz = Caso2(raiz,ok); break;
            }
        }
    }
    return raiz;
}
Nodo* Caso1 (Nodo *raiz , int *ok) {
    Nodo *ptu;
    ptu = raiz->esq;
    comp++;
    compINS++;
    if (ptu->FB == 1)
        raiz = rotacao_direita(raiz);
    else
        raiz = rotacao_dupla_direita(raiz);
    raiz->FB = 0;
    *ok = 0;
    return raiz;
}
Nodo* Caso2 (Nodo *raiz , int *ok) {
    Nodo *ptu;
    ptu = raiz->dir;
    comp++;
    compINS++;
    if (ptu->FB == -1)
        raiz=rotacao_esquerda(raiz);
    else
        raiz=rotacao_dupla_esquerda(raiz);
    raiz->FB = 0;
    *ok = 0;
    return raiz;
}
int Altura (Nodo *raiz){
    int Alt_Esq, Alt_Dir;
    if (raiz == NULL)
        return 0;
    else{
        Alt_Esq = Altura (raiz->esq);
        Alt_Dir = Altura (raiz->dir);
        if (Alt_Esq > Alt_Dir)
            return (1 + Alt_Esq);
        else
            return (1 + Alt_Dir);
    }
}
int fator(Nodo *raiz){
    return Altura(raiz->esq)-Altura(raiz->dir);
}
Nodo* destruir(Nodo *raiz){
    if(raiz!=NULL){
        destruir(raiz->esq);
        destruir(raiz->dir);
        free(raiz);
    }
    return NULL;
}
Nodo* busca(Nodo *raiz, char word[]){
    comp++;
    compBUSCA++;
    if(raiz!=NULL){
        comp++;
        compBUSCA++;
        if(strcmp(word,raiz->word)==0)
            return raiz;
        else if(strcmp(raiz->word,word)>0)
            return busca(raiz->esq,word);
        else
            return busca(raiz->dir,word);
    }
    return NULL;
}
int contaNodos(Nodo *raiz){
    if(raiz==NULL)
        return 0;
    else
        return 1+contaNodos(raiz->dir)+contaNodos(raiz->esq);
}
