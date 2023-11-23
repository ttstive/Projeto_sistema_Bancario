#include <stdio.h>
#include <locale.h>
#include "conta.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcoes;
    usuarios user[MAX_USUARIOS]; // Cria um array de estruturas usuarios

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
        switch (opcoes) {
            case 1:
                for(int i = 0; i < MAX_USUARIOS; i++) {
                    printf("\nCriando conta para o usuário %d\n", i+1);
                    criaConta(&user[i]);
                }
                break;
            case 2:
                for(int i = 0; i < MAX_USUARIOS; i++) {
                    printf("\nDepositando valor para o usuário %d\n", i+1);
                    depositaValor(&user[i]);
                }
                break;
            case 3:
                printf("saindo da aplicacao");
                break;
            default:
                break;
        }
    } while (opcoes < 8);

    return 0;
}
