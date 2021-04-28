#include <stdlib.h>
#include <string.h>
#include "tabhash.h"
#define M 1601

struct hash{
    int qtd, TABLE_SIZE, TAMANHO_TIPO;
    void **dados;
};

Hash* criaHash(int TABLE_SIZE, int TAMANHO_TIPO){
    Hash* ha = (Hash*) malloc(sizeof(Hash));
    if(ha !=NULL){
        int i;
        ha->TABLE_SIZE = TABLE_SIZE;
        ha->TAMANHO_TIPO = TAMANHO_TIPO;
        ha->dados = (void*)malloc(TABLE_SIZE *(TAMANHO_TIPO));
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

int sondagemLinear(int pos, int i, int TABLE_SIZE){
    return ((pos + 1) & 0x7FFFFFFF) % TABLE_SIZE;
}

int redimensiona(Hash* ha, int TABLE_SIZE){
    
    ha->TABLE_SIZE = 2* ha->TABLE_SIZE;
    
}

int insereHash(Hash* ha,int chave, void *dados){
    if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

    if ((float)ha->qtd / (float)ha->TABLE_SIZE > 0.75){
        redimensiona(ha, ha->TABLE_SIZE);
    }
    // verifica se mais de 75% das posicoes da tabela estao ocupadas
    // se estiverem, dobra o tamanho da tabela

    int i, pos, newPos;
    pos = chaveDivisao(chave, ha->TABLE_SIZE);
    for (i = 0; i < ha->TABLE_SIZE; i++){
        newPos = sondagemLinear(pos,i,ha->TABLE_SIZE);
        if(ha->dados[newPos] == NULL){
            void *novo;
            novo = (void*) malloc(sizeof(ha->TAMANHO_TIPO));
            if(novo == NULL)
                return 0;

            novo = dados;
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
        newPos = sondagemLinear(pos, i, ha->TABLE_SIZE);
        if(ha->dados[newPos] == NULL)
            return 0;
        
        memcpy(&vchave, ha->dados[newPos], sizeof(int));
        // copia os bits do tamanho de um inteiro DE ha->dados[newPos] PARA vchave
        // restricao: errado se o inteiro (que tambem eh a chave) nao for o primeiro tipo de dado em ha->dados[newPos]

        if(vchave == chave){
            dados = (ha->dados[newPos]);
            return 1;
        }
    }
    return 0;
}
