#include "tabhash.h"
#include <stdio.h>

int main(void){
    //variáveis auxiliares e lista apontando para NULL.
    int opc;
    Hash* ha;
    Aluno estudante;
    FILE *dados;
    char auxTexto[50];
    //Menu
    do{
        printf("\nEscolha uma opção:\n1 - Inicializar o Hash\n2-Inserir a base de dados\n3-Consultar a posição\n4-Sair do sistema\n");
        scanf("%d",&opc);
        switch(opc){
            
            case(1):
                liberaHash(ha);
                ha = criaHash(M,0);
                printf("\nPronto");   
            break;
            //Lendo os dados e verificando se deu certo
            case(2):
                fclose(dados);
                dados = fopen("alunos.txt", "r");
                if (dados == NULL){
                    printf("Erro ao abrir o arquivo!");
                    exit(1);
                }
            break;
            //Inserir os dados
            case(3):
                while(fgets(auxTexto, 50, dados) != NULL){
                fscanf(auxTexto, "%d %s %f %f %f", &estudante.matricula, estudante.nome, &estudante.n1, &estudante.n2, &estudante.n3);
                insereHash(ha,estudante.matricula, &dados);
            }
            break;
            //Consultar a lista
            case(4):
                printf("\nQual a matrícula do aluno: ");
                scanf("%d",&estudante.matricula);
                if (buscaHash(ha, estudante.matricula, &estudante))
                    printf("\n %d %s %f %f %f", estudante.matricula, estudante.nome, estudante.n1, estudante.n2, estudante.n3); 
                else printf("\nNão encontrado...");
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