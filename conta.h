#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 1

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

    printf("Insira seu nome: ");
    scanf(" %s", user->nome);
    printf("Digite sua idade: ");
    scanf("%d", &(user->idade));
    printf("Digite seu cpf: ");
    scanf("%lld", &(user->cpf));
    user->saldo = 0;

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
    user->saldo += deposito;
    printf("Valor depositado foi de: R$ %.2f\n", deposito);
    printf("Seu saldo atual é: R$ %.2f\n", user->saldo);

    FILE *fp = fopen("C:/Users/User/Documents/.vscode/C/contas.txt", "r+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char linhas[MAX_USUARIOS][100];
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
        if (strcmp(user->nome, linhas[j]) == 0) {
            fprintf(fp, "Nome: %s, Idade: %d, CPF: %lld, Numero da Conta: %lld, Saldo: %.2f\n", user->nome, user->idade, user->cpf, user->numeroConta, user->saldo);
        } else {
            fprintf(fp, "%s", linhas[j]);
        }
    }
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

    char linhas[MAX_USUARIOS][100];
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
}
