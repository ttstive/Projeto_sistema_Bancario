#include <stdio.h>
#include <locale.h>
#include "conta.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcoes;
    usuarios user[MAX_USUARIOS];
    int indice;
    int totalUsers = 0;

    do {
        printf("Ola, bem vindo ao nosso sistema bancário.\n");
        printf("Temos as opcoes abaixo disponiveis:\n");
        printf("1 : criar conta\n");
        printf("2 : depositar\n");
        printf("3 : sacar\n");
        printf("4 : transferir para outra conta\n");
        printf("5 : mostrar extrato\n");
        printf("6 : remover conta\n");
        printf("7 : editar informacoes conta\n");
        printf("8 : sair\n");

        scanf("%d", &opcoes);
        getchar(); // Limpa o buffer de entrada
        switch (opcoes) {
            case 1:
                for(int i = 0; i < MAX_USUARIOS; i++) {
                    printf("\nCriando conta para o usuário: %d\n", i+1);
                    criaConta(&user[i]);
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
                printf("Digite o índice do usuário que você deseja ver o extrato: ");
                scanf("%d", &indice);
                if (indice >=0 && indice < MAX_USUARIOS)
                {
                    extrato(&user[indice]);
                } else{
                    printf("índice de usuário inválido.\n");
                }
                break;

            case 6:
                printf("Digite o índice do usuário cuja conta você deseja remover: ");
                scanf("%d", &indice);
                getchar(); // Limpa o buffer de entrada
                if (indice >= 0 && indice < MAX_USUARIOS) {
                    removeConta(user, indice);
                } else {
                    printf("Índice de usuário inválido.\n");
                }
                break;

            case 7:

                editarInformacoes(user, user, totalUsers);

                break;

            default:
                break;
        }
    } while (opcoes < 8);

    return 0;
}
