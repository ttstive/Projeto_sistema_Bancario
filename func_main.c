#include <stdio.h>
#include <locale.h>
#include "conta.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcoes;
    usuarios user[MAX_USUARIOS];
    int indice;
    int totalUsers = 2;
    int contadorContas = 0;
    
    do {
        printf("Olá, bem vindo ao nosso sistema bancário.\n");
        printf("Temos as opções abaixo disponíveis:\n");
        printf("1 : criar conta\n");
        printf("2 : depositar\n");
        printf("3 : sacar\n");
        printf("4 : transferir para outra conta\n");
        printf("5 : mostrar extrato\n");
        printf("6 : remover conta\n");
        printf("7 : editar informações conta\n");
        printf("8 : sair\n");

        scanf("%d", &opcoes);
        getchar(); // Limpa o buffer de entrada
        switch (opcoes) {
            case 1:
                if (contadorContas < 2) {
                    printf("\nCriando conta para o usuário: %d\n", contadorContas+1);

                    criaConta(&user[contadorContas], totalUsers);
                    if (user[contadorContas].idade >= 17 && user[contadorContas].idade <= 100) {
                        contadorContas ++;
                    }
                    

                    
                } 
                else {
                    printf("Limite de criação de contas atingido.\n");
                }

                break;

            case 2:
            
                depositaValor(&user[indice], user, totalUsers);

                break;
                
            case 3:
                
                sacaValor(&user[indice], user, totalUsers);

                break;
                

            case 4:

                Transferencia1(&user[indice], user, totalUsers);

                break;

            case 5:
             
               extrato(&user[indice], user, totalUsers);

               break;

            case 6:
            
                removeConta(user, &contadorContas);
                contadorContas-1;
                
                break;

            case 7:

                editarInformacoes(&user[indice], user, totalUsers, contadorContas);

                break;

            default:
                break;
        }
    } while (opcoes < 8);

    return 0;
}
