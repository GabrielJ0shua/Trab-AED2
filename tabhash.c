#include <stdlib.h>
#include <string.h>
#include "tabhash.h"

struct hash{
    int qtd, TABLE_SIZE, TAMANHO_TIPO;
    void **dados;
};

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha !=NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->TAMANHO_TIPO = TAMANHO_TIPO; // guarda o TAMANHO_TIPO em ha para ser utilizado na inserção e busca
        ha->dados = (void**)malloc(TABLE_SIZE *sizeof(void*));
        if(ha->dados == NULL){
            free(ha);
            return NULL;
        }
        ha->qtd = 0;
        for(i=0; i < ha->TABLE_SIZE; i++)
            ha->dados[i] = NULL;
    }
    return ha;
}

void liberaHash(Hash *ha){
    if(ha != NULL){
        int i;
        for(i = 0; i < ha->TABLE_SIZE; i++){
            if(ha->dados[i] != NULL)
                free(ha->dados[i]);
        }
        free(ha->dados);
        free(ha);
    }
}

int chaveDivisao(int chave, int TABLE_SIZE){
    return (chave & 0x7FFFFFFF) % TABLE_SIZE;
}

int sondagemQuadratica(int pos, int i, int TABLE_SIZE){
    pos = pos + 2*i + 5*i*i;
    return (pos & 0x7FFFFFFF) % TABLE_SIZE;
}

int redimensiona(Hash* ha){
    int i, j, antigaChave, pos, newPos;
    void** novaTabela = (void**) malloc(ha->TABLE_SIZE*2*sizeof(void*)); // nova tabela com o dobro do tamanho de ha->dados
    if(novaTabela == NULL)
        return 0;

    for(i=0; i < ha->TABLE_SIZE*2; i++) //limpa a tabela
        novaTabela[i] = NULL;
    
    for(i=0; i < ha->TABLE_SIZE; i++){ //recalcula as posicoes da tabela antiga e insere na nova
        if(ha->dados[i] != NULL){
            memcpy(&antigaChave, ha->dados[i], sizeof(int));  //pega a chave antiga, nesse caso, matrícula dentro de ha->dados[i]
            pos = chaveDivisao(antigaChave, ha->TABLE_SIZE*2);
            
            for(j=0; j<ha->TABLE_SIZE*2; j++){ // nova tabela recebe os dados da antiga
                newPos = sondagemQuadratica(pos,j,ha->TABLE_SIZE*2);
                if(novaTabela[newPos] == NULL){
                    novaTabela[newPos] = ha->dados[i];
                    break;
                }
            }
        }
    }
    free(ha->dados);
    ha->dados = novaTabela;
    ha->TABLE_SIZE = ha->TABLE_SIZE*2;
    return 1;
}

int insereHash(Hash* ha,int chave, void *dados){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    if ((float)ha->qtd / (float)ha->TABLE_SIZE > 0.75){
        redimensiona(ha);
    }
    // verifica se mais de 75% das posicoes da tabela estao ocupadas
    // se estiverem, dobra o tamanho da tabela

    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    
    for (i = 0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemQuadratica(pos,i,ha->TABLE_SIZE);
        if(ha->dados[newPos] == NULL){
            void *novo;
            novo = (void*) malloc(ha->TAMANHO_TIPO);
            if(novo == NULL)
                return 0;

            memcpy(novo, dados, ha->TAMANHO_TIPO);
            // copia os dados de "void* dados" para "void* novo", sendo os dois de tamanho ha->TAMANHO_TIPO
            
            ha->dados[newPos] = novo;
            ha->qtd++;
            return 1;
        }
    }
    return 0;
}

int buscaHash(Hash* ha, int chave , void *dados){
    if(ha == NULL)
        return 0;

    int i, pos, newPos, vchave;
    pos =  chaveDivisao(chave, ha->TABLE_SIZE);
    for(i=0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemQuadratica(pos, i, ha->TABLE_SIZE);
        if(ha->dados[newPos] == NULL)
            return 0;
        
        memcpy(&vchave, ha->dados[newPos], sizeof(int));
        // copia os bits do tamanho de um inteiro DE ha->dados[newPos] PARA vchave
        // restricao: errado se o inteiro (que tambem eh a chave) nao for o primeiro tipo de dado em ha->dados[newPos]
        
        if(vchave == chave){
            memcpy(dados, ha->dados[newPos], ha->TAMANHO_TIPO);
            return 1;
        }
    }
    return 0;
}
