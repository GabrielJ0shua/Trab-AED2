#include <stdlib.h>
#include <string.h>
#include "tabelahash.h"

struct hash{
    int qtd; TABLE_SIZE;
    struct aluno **itens;
};
  
  Hash* criaHash(int TABLE_SIZE){
      Hash* ha = (Hash*)malloc(sizeof(Hash));
      if(ha != NULL){
          int i;
          ha->TABLE_SIZE = TABLE_SIZE;
          ha->intes = (struct aluno**) malloc(TABLE_SIZE *sizeof(struct aluno*));
          if(ha->itens == NULL){
              free(ha);
              return NULL;
              }
              ha->qtd = 0;
              for(i=0; i < ha->TABLE_SIZE; i++)
              ha->itens[i] = NULL;
      }
          return ha;
}

    void liberaHash(Hash* ha){
        if(ha != NULL){
            int i;
            for(i=0; i < ha->MAX; i++){
                if(ha->itens[i] != NULL)
                free(ha->itens[i]);
            }
            free(ha->itens);
            free(ha);
            }
        }
    
    int chaveDivisao(int chave, int TABLE_SIZE){
        return (chave & 0x7FFFFFFF) % TABLE_SIZE;
    }

    int chaveMultiplicacao(int chave, int TABLE_SIZE) {
        float A = 0.6180339887; // constante: 0 < A < 1
        float val = chave * A;
        val = val - (int) val;
        return (int) (TABLE_SIZE * val);
    }

    int chaveDobra(int chave, int TABLE_SIZE) {
        int num_bits = 10;
        int parte1 = chave >> num_bits;
        int parte2 = chave & (TABLE_SIZE-1);
        return (parte1 ^ parte2);
    }

    int valorString(char *str){
        
    }



    int insereHash_SemColisao(Hash* ha, struct aluno al){
        if(ha == NULL || ha->qtd == ha->TABLE_SIZE)
        return 0;

        int chave == al.matricula;
        int chave = valorString(al.nome);

        int pos = chaveDivisao (chave, ha->TABLE_SIZE);
        struct aluno* novo;
        novo = (struct aluno*) malloc(sizeof(struct aluno));
        if(novo == NULL)
            return 0;
            *novo = al;
            ha->itens[pos] = novo;
            ha->qtd++;
            return 1;      
    }