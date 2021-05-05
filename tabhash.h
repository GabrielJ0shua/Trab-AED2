#define M 1601

struct aluno{
    int matricula,n1,n2,n3;
    char nome[30];
};
typedef struct hash Hash;
typedef struct aluno Aluno;

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO);
void liberaHash(Hash *ha);
int insereHash(Hash* ha,int chave, void *dados);
int buscaHash(Hash* ha, int chave , void *dados);