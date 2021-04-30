#include <stdio.h>
#include "tabhash.h"
#define M 1601

int main(void){
    //variáveis auxiliares e lista apontando para NULL.
    int opc;
    Hash* ha;
    Aluno estudante;
    FILE *dados;
    char auxTexto[50];
    //Menu
    do{
        printf("\nEscolha uma opcao:\n1 - Inicializar o Hash\n2-Inserir a base de dados\n3-Consultar a posicao\n4-Sair do sistema\n");
        scanf("%d",&opc);
        switch(opc){
            
            case(1):
                ha = criaHash(M, sizeof(struct aluno));
                printf("\nPronto");   
            break;
            //Le e insere os dados e verificando se deu certo
            case(2):
                dados = fopen("alunos.txt", "a");
                if (dados == NULL){
                    printf("Erro ao abrir o arquivo!");
                    return 1;
                }
                while(fgets(auxTexto, sizeof(auxTexto), dados) != NULL){
                    fscanf((FILE*)auxTexto, "%d %s %f %f %f", &estudante.matricula, estudante.nome, &estudante.n1, &estudante.n2, &estudante.n3);
                    insereHash(ha,estudante.matricula, &estudante);
                }
                printf("Dados inseridos");
                fclose(dados);
            break;
            //Consultar a lista
            case(3):
                printf("\nQual a matrícula do aluno: ");
                scanf("%d",&estudante.matricula);
                int codigo = buscaHash(ha, estudante.matricula, &estudante);
                if (codigo == 1)
                    printf("\n %d %s %f %f %f", estudante.matricula, estudante.nome, estudante.n1, estudante.n2, estudante.n3); 
                else printf("\n%d Não encontrado...",codigo);
            break;
            //libera a lista por completo e fecha o programa
            case(5):
               liberaHash(ha);
               fclose(dados);
               return 0;
            break;

            default:
                printf("\nOpção Invalida...");
            break;
        } 
    }while (1);
    liberaHash(ha);
    fclose(dados);
    return 1; //programa saiu dos casos então é erro, melhor encerrar por aqui
}