/*
Integrantes:
Mateus Rocha Resende - 11921BCC027
Gabriel Joshua Calixto Naves dos Santos - 11911BCC052
Gustavo Melo do Carmo - 11721BCC035
*/

#include <stdio.h>
#include "tabhash.h"

int main(void){
    //variáveis auxiliares e lista apontando para NULL.
    int opc;
    Hash* ha;
    Aluno estudante;
    FILE *dados;
    //Menu
    do{
        printf("\nEscolha uma opcao:\n1 - Inicializar o Hash\n2 - Inserir a base de dados\n3 - Consultar a posicao\n4 - Sair do sistema\n");
        scanf("%d",&opc);
        switch(opc){
            // Inicializa o Hash
            case(1):
                ha = criaHash(M, sizeof(struct aluno));
                printf("\nPronto");
                break;
            //Le e insere os dados e verificando se deu certo
            case(2):
                dados = fopen("alunos.txt", "r");
                if (dados == NULL){
                    printf("Erro ao abrir o arquivo!");
                    return 1;
                }
                while(1){
                    if(feof(dados)) break;
                    fscanf(dados, "%d %s %d %d %d", &estudante.matricula, estudante.nome, &estudante.n1, &estudante.n2, &estudante.n3);
                    insereHash(ha,estudante.matricula, &estudante);
                }
                printf("Dados inseridos");
                fclose(dados);
                break;
            //Consultar a lista
            case(3):
                printf("\nQual a matricula do aluno: ");
                scanf("%d",&estudante.matricula);
                if (buscaHash(ha, estudante.matricula, &estudante))
                    printf("\n%d %s %d %d %d", estudante.matricula, estudante.nome, estudante.n1, estudante.n2, estudante.n3); 
                else
                    printf("\nNao encontrado...");
                break;
            //libera a lista por completo e fecha o programa
            case(4):
                liberaHash(ha);
                fclose(dados);
                return 0;
                break;
            default:
                printf("\nOpcao Invalida...");
                break;
        } 
    }while (1);
    liberaHash(ha);
    fclose(dados);
    return 1; //programa saiu dos casos então é erro, melhor encerrar por aqui
}