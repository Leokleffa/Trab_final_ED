#define MAX 60
//vari�veis globais
int rot;            //n�m. de rota��es
int comp;           //n�m. de compara��es totais
int compINS;        //n�m. de compara��es na funcao insere
int compBUSCA;      //n�m. de compara��es na funcao busca
int trocas;         //n�m. de trocas de palavras

typedef struct NO{
    char word[MAX]; //palavra
    char syn[MAX];  //sinonimo
    int FB;         //fator de balanceamento
    struct NO *esq; //ponteiro para o nodo esquerdo
    struct NO *dir; //ponteiro para o nodo direito
}Nodo;

Nodo* inicializa();                                     //inicializa a �rvore
Nodo* rotacao_direita(Nodo* pt);                        //rota��o a direita
Nodo* rotacao_esquerda(Nodo *pt);                       //rota��o a esquerda
Nodo* rotacao_dupla_direita (Nodo* pt);                 //rota��o dupla a direita
Nodo* rotacao_dupla_esquerda (Nodo *pt);                //rota��o dupla a esquerda
Nodo* InsereArvore (Nodo *raiz, char word[], char syn[], int *ok);      //insere um nodo na �rvore
Nodo* Caso1 (Nodo *raiz , int *ok);                     //auxiliar 1 para inserir
Nodo* Caso2 (Nodo *raiz , int *ok);                     //auxiliar 2 para inserir
int Altura (Nodo *raiz);                                //retorna a altura da �rvore
int fator(Nodo *raiz);                                  //retorna o fator de balanceamento da �rvore
Nodo* busca(Nodo *raiz, char word[]);                   //busca um nodo na �rvore
Nodo* destruir(Nodo *raiz);                             //destroi a �rvore
int contaNodos(Nodo *raiz);                             //conta o n�mero de nodos

Nodo* ReadWriteDic(FILE *dicionario, Nodo *raiz);       //l� o dicion�rio e insere na �rvore a palavra e seu respectivo sin�nimo
void parafrase(FILE *entrada, FILE *saida, Nodo *raiz); //l� o dicion�rio e insere na �rvore a palavra e seu respectivo sin�nimo
