#include <stdio.h>
#include <locale.h>
#include "conta.h"

int main() {
    setlocale(LC_ALL, "Portuguese");
    int opcoes;
    usuarios user[MAX_USUARIOS];
    int indice;

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
                printf("Digite o índice do usuário que você deseja depositar: ");
                scanf("%d", &indice);
                if (indice >= 0 && indice < MAX_USUARIOS) {
                    depositaValor(&user[indice]);
                } else {
                    printf("Índice de usuário inválido.\n");
                }
                break;

            case 3:
                printf("Digite o índice do usuário que você deseja sacar");
                scanf("%d", &indice);
                if (indice >=0 && indice < MAX_USUARIOS)
                {
                     sacaValor(&user[indice]);
                } else{
                    printf("índice de usuário inválido.\n");
                }
                break;

            case 4:
                printf("digite o índice da conta rementente");
                scanf("%d", &indice);
                if (indice<0 || indice >MAX_USUARIOS)
                {
                    printf("indíce usuário invalido\n");                    
                }
                else if (indice>=0 && indice <MAX_USUARIOS)
                {
                    Tranferencia1(&user[indice], indice);

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
                printf("Digite o índice do titular da conta que você deseja editar: ");
                scanf("%d", &indice);
                getchar(); // Limpa o buffer de entrada
                if (indice >= 0 && indice < MAX_USUARIOS) {
                    editarInformacoes(&user[indice], indice);
                } else {
                    printf("Índice de usuário inválido.\n");
                }
                break;
            default:
                break;
        }
    } while (opcoes < 8);

    return 0;
}
