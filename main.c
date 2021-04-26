#include "tad.h"
#include <stdio.h>
#include <math.h>

int main(void)
{
    //variáveis auxiliares e lista apontando para NULL.
    int opc;
    //Menu
    do{
        printf("\nEscolha uma opção:\n1 - Inicializar o Hash\n2-Inserir a base de dados\n3-Consultar a posição\n4-Sair do sistema\n");
        scanf("%d",&opc);
        switch(opc){
            //Iniciando a lista
            case(1):
                printf("\nPronto");   
            break;
            //Inserindo o valor e verificando se deu certo
            case(2):
                             
            break;
            //verificando se tem valores antes de imprimir e imprimir
            case(3):

            break;
            //Verificando se o valor existe antes de deduzir do auxiliar qnt para não perder quantos elementos tem
            case(4):
                
            break;
            //Limpa a equação por completo mas não libera a lista
            case(5):
               
            break;
            //Calcula toda a função se ela existir
            case (6):
                
            break;
            //libera a lista por completo e fecha o programa
            case (7):    
                return 0;
            break;

            default:
                printf("\nOpção Invalida...");
            break;
        } 
    }while (1);
    return 1; //programa saiu dos casos então é erro, melhor encerrar por aqui
}