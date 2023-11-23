#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define MAX_USUARIOS 2 // Define o número máximo de usuários

typedef struct 
{
    char nome[30];
    long long cpf;
    int idade;
    float saldo; // Adiciona um campo saldo à estrutura usuarios
} usuarios;

long long gerarNumeroConta(long long cpf, int idade) {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    int random = rand(); // Gera um número aleatório
    return cpf * 10000 + idade * 1000 + random % 1000; // Mescla o CPF, a idade e o número aleatório para formar o número da conta
}

void criaConta(usuarios* user){
    printf("insira seu nome");
    scanf("%s", user->nome);
    printf("digite sua idade");
    scanf("%d", &(user->idade));
    printf("digite seu cpf");
    scanf("%lld", &(user->cpf));
    user->saldo = 0; // Inicializa o saldo com 0
    printf("sua conta foi criada, guarde seu numero\n" );
    printf("O número da conta gerado é: %lld\n", gerarNumeroConta(user->cpf, user->idade));
}

void depositaValor(usuarios* user){
    float deposito;
    printf("insira um valor que deseja depositar");
    scanf("%f", &deposito);
    user->saldo += deposito; // Adiciona o valor depositado ao saldo
    printf("valor depositado foi de : R$ %.2f\n", deposito);
    printf("Seu saldo atual é: R$ %.2f\n", user->saldo);
}
