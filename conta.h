#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 3

typedef struct {
    char nome[30];
    long long cpf;
    int idade;
    float saldo;
    long long numeroConta;
} usuarios;

long long gerarNumeroConta(long long cpf, int idade) {
    srand(time(NULL));
    int random = rand();
    return cpf * 10000 + idade * 1000 + random % 1000;
}

void criaConta(usuarios* user) {
    FILE *fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
if (user->idade < 17)
{
    printf("voce não tem permissão para cria conta remotamente, por favor ,vá em uma de nossas agências acompanhado de seu responsável e você será atendido ");
   
   return;
}
else{


    printf("Insira seu nome: ");
    scanf(" %s", user->nome);
    printf("Digite sua idade: ");
    scanf("%d", &(user->idade));
    printf("Digite seu cpf: ");
    scanf("%lld", &(user->cpf));
    user->saldo = 0;
}

    user->numeroConta = gerarNumeroConta(user->cpf, user->idade);
    printf("Sua conta foi criada, guarde seu número.\n");
    printf("O número da conta gerado é: %lld\n", user->numeroConta);

    fprintf(fp, "Nome: %s, Idade: %d, CPF: %lld, Numero da Conta: %lld, Saldo: %.2f\n", user->nome, user->idade, user->cpf, user->numeroConta, user->saldo);
    fclose(fp);
}

void depositaValor(usuarios* user) {
    float deposito;
    printf("Insira um valor que deseja depositar: ");
    scanf("%f", &deposito);
    user->saldo = user->saldo + deposito;
    printf("Valor depositado foi de: R$ %.2f\n", deposito);
    printf("Seu saldo atual é: R$ %.2f\n", user->saldo);
    

    FILE *fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fp, "Nome :%s , Depósito: %.2f, Saldo: %.2f- Conta: %lld\n", user->nome, deposito, user->saldo, user->numeroConta);
    fclose(fp);
}

void sacaValor(usuarios* user){
    float saque;
    printf("Insira um valor que deseja sacar: ");
    scanf("%f", &saque);
    if (user->saldo < saque)
    {
        printf("Seu saldo não é suficiente.\n");
        return;
    }
    else{
        user->saldo = user->saldo - saque;
        printf("Valor sacado foi de : R$ %.2f\n", saque);
        printf("Seu saldo atual é: R$ %.2f\n", user->saldo);
    }
    
    FILE *fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fp, "Nome :%s , Saque: %.2f, Saldo: %.2f, Conta: %lld \n", user->nome, saque, user->saldo, user->numeroConta);
    fclose(fp);
}

void editarInformacoes(usuarios* user, int indice) {
    printf("Digite o novo nome do titular: ");
    scanf(" %[^\n]", user->nome);  // Use scanf para ler até a nova linha
    getchar();  // Limpar o caractere de nova linha do buffer

    printf("Digite a nova idade: ");
    scanf("%d", &(user->idade));

    printf("Digite o novo CPF: ");
    scanf("%lld", &(user->cpf));

    printf("Informações do titular da conta atualizadas com sucesso!\n");

    FILE *fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "r+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char **linhas = malloc(MAX_USUARIOS * sizeof(char *));
    for(int i = 0; i < MAX_USUARIOS; i++) {
        linhas[i] = malloc(100 * sizeof(char));
    }

    int i = 0;
    while (fgets(linhas[i], 100, fp) != NULL && i < MAX_USUARIOS) {
        i++;
    }
    fclose(fp);

    fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int j = 0; j < MAX_USUARIOS; j++) {
        if (j == indice) {
            fprintf(fp, "Nome: %s, Idade: %d, CPF: %lld, Numero da Conta: %lld, Saldo: %.2f\n", user->nome, user->idade, user->cpf, user->numeroConta, user->saldo);
        } else {
            fprintf(fp, "%s", linhas[j]);
        }
    }
    fclose(fp);

    for(int i = 0; i < MAX_USUARIOS; i++) {
        free(linhas[i]);
    }
    free(linhas);
}
