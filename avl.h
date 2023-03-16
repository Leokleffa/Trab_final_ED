#define MAX 60
//variáveis globais
int rot;            //núm. de rotações
int comp;           //núm. de comparações totais
int compINS;        //núm. de comparações na funcao insere
int compBUSCA;      //núm. de comparações na funcao busca
int trocas;         //núm. de trocas de palavras

typedef struct NO{
    char word[MAX]; //palavra
    char syn[MAX];  //sinonimo
    int FB;         //fator de balanceamento
    struct NO *esq; //ponteiro para o nodo esquerdo
    struct NO *dir; //ponteiro para o nodo direito
}Nodo;

Nodo* inicializa();                                     //inicializa a árvore
Nodo* rotacao_direita(Nodo* pt);                        //rotação a direita
Nodo* rotacao_esquerda(Nodo *pt);                       //rotação a esquerda
Nodo* rotacao_dupla_direita (Nodo* pt);                 //rotação dupla a direita
Nodo* rotacao_dupla_esquerda (Nodo *pt);                //rotação dupla a esquerda
Nodo* InsereArvore (Nodo *raiz, char word[], char syn[], int *ok);      //insere um nodo na árvore
Nodo* Caso1 (Nodo *raiz , int *ok);                     //auxiliar 1 para inserir
Nodo* Caso2 (Nodo *raiz , int *ok);                     //auxiliar 2 para inserir
int Altura (Nodo *raiz);                                //retorna a altura da árvore
int fator(Nodo *raiz);                                  //retorna o fator de balanceamento da árvore
Nodo* busca(Nodo *raiz, char word[]);                   //busca um nodo na árvore
Nodo* destruir(Nodo *raiz);                             //destroi a árvore
int contaNodos(Nodo *raiz);                             //conta o número de nodos

Nodo* ReadWriteDic(FILE *dicionario, Nodo *raiz);       //lê o dicionário e insere na árvore a palavra e seu respectivo sinônimo
void parafrase(FILE *entrada, FILE *saida, Nodo *raiz); //lê o dicionário e insere na árvore a palavra e seu respectivo sinônimo
