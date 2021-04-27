struct aluno{
    int matricula;
    char nome[30];
    float n1,n2,n3;
};
typedef struct hash Hash;

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO);
void liberaHash(Hash *ha);
int chaveDivisao(int chave, int TABLE_SIZE);
int sondagemLinear(int pos, int i, int TABLE_SIZE);
int insereHash(Hash* ha,int chave, void *dados);
int buscaHash(Hash* ha, int chave , void *dados);
