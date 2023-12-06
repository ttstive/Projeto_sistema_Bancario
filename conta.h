#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define MAX_USUARIOS 2

typedef struct {
    char nome[30];
    char cpf[15]; // Alterado para array de char
    int idade;
    float saldo;
    long long numeroConta;
} usuarios;

int validaCPF(const char* cpf) {
    int i, j, digito1 = 0, digito2 = 0;
    int cpf_array[11];

    // Verifica se o formato do CPF está correto
    for (i = 0, j = 0; i < 14; i++) {
        if ((i == 3 || i == 7) && cpf[i] == '.') {
            continue;
        } else if (i == 11 && cpf[i] == '-') {
            continue;
        } else if (cpf[i] >= '0' && cpf[i] <= '9') {
            cpf_array[j] = cpf[i] - '0';
            j++;
        } else {
            return 1;
        }
    }

    // Calcula o primeiro dígito verificador
    for (i = 0, j = 10; i < 9; i++, j--)
        digito1 += cpf_array[i] * j;
    digito1 %= 11;
    if (digito1 < 2)
        digito1 = 0;
    else
        digito1 = 11 - digito1;

    // Calcula o segundo dígito verificador
    for (i = 0, j = 11; i < 10; i++, j--)
        digito2 += cpf_array[i] * j;
    digito2 %= 11;
    if (digito2 < 2)
        digito2 = 0;
    else
        digito2 = 11 - digito2;

    // Verifica se os dígitos verificadores são iguais aos informados
    if (cpf_array[9] == digito1 && cpf_array[10] == digito2)
        return 0;
    else
        return 1;
} 

long long gerarNumeroConta(char* cpf, int idade) {
    char cpf_sem_pontos[12]; // Armazena o CPF sem pontos ou traço
    int j = 0;
    for (int i = 0; i < 15; i++) {
        if (cpf[i] != '.' && cpf[i] != '-') {
            cpf_sem_pontos[j] = cpf[i];
            j++;
        }
    }
    cpf_sem_pontos[j] = '\0'; // Finaliza a string
    long long cpf_as_number = atoll(cpf_sem_pontos); // Converte o CPF para long long
    return cpf_as_number + idade - 17; // Fórmula ajustada para gerar o número da conta
}

void criaConta(usuarios* user, int* totalUsers) {
    if (user == NULL) {
    printf("Usuário inválido.\n");
    return;
    }

    FILE *fp = fopen("contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    user->saldo = 0.0;

    printf("Insira seu nome: ");
    scanf(" %s", user->nome);

    printf("Digite sua idade: ");
    scanf("%d", &(user->idade));

    if (user->idade < 17 || user->idade > 100) {
        printf("Você não tem permissão para criar uma conta remotamente. Por favor, vá em uma de nossas agências acompanhado de seu responsável e você será atendido.\n");
        fclose(fp);
        return;
    }

    printf("Digite seu cpf: ");
    scanf("%s", user->cpf);

    // Verifica se o CPF tem o formato correto
    if (strlen(user->cpf) != 14 || user->cpf[3] != '.' || user->cpf[7] != '.' || user->cpf[11] != '-') {
        printf("Formato de CPF inválido. Insira o CPF no formato correto (000.000.000-00).\n");
        fclose(fp);
        return;
    }

    user->numeroConta = gerarNumeroConta(user->cpf, user->idade);
    printf("Sua conta foi criada, guarde seu número.\n");
    printf("O número da conta gerado é: %lld\n", user->numeroConta);

    fprintf(fp, "Nome: %s, Idade: %d, CPF: %s, Numero da Conta: %lld, Saldo: %.2f\n", user->nome, user->idade, user->cpf, user->numeroConta, user->saldo); // Alterado %lld para %s para cpf
    fclose(fp);
}

void depositaValor(usuarios* user, usuarios* allUsers, int totalUsers) {
    float deposito;
    long long num_conta_deposita;

    printf("Informe o número da conta: ");
    scanf("%lld", &num_conta_deposita);

    int deposito_index = -1;

    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_deposita) {
            deposito_index = i;
            break;
        }
    }

    if (deposito_index == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Informe o valor do deposito: ");
    scanf("%f", &deposito);

    allUsers[deposito_index].saldo += deposito;

    printf("Valor depositado foi de: R$ %.2f\n", deposito);
    printf("Seu saldo atual é: R$ %.2f\n", allUsers[deposito_index].saldo);

    FILE *fp = fopen("contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fp, "Nome :%s , Depósito: %.2f, Saldo: %.2f, Conta: %lld\n", allUsers[deposito_index].nome, deposito, allUsers[deposito_index].saldo, allUsers[deposito_index].numeroConta);
    fclose(fp);
}

void sacaValor(usuarios* user, usuarios* allUsers, int totalUsers){
    if (user == NULL) {
        printf("Usuário inválido.\n");
        return;
    }

    float saque;
    long long num_conta_saque;

    printf("Informe o número da conta: ");
    scanf("%lld", &num_conta_saque);

    int saque_index = -1;

    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_saque) {
            saque_index = i;
            break;
        }
    }

    if (saque_index == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Insira um valor que deseja sacar: ");
    scanf("%f", &saque);

    if (allUsers[saque_index].saldo < saque) {
        printf("Seu saldo não é suficiente para realizar essa transferência.\n");
        return;
    }

    allUsers[saque_index].saldo -= saque;

    printf("Valor sacado foi de : R$ %.2f\n", saque);
    printf("Seu saldo atual é: R$ %.2f\n", allUsers[saque_index].saldo);

    FILE *fp = fopen("contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fp, "Nome :%s , Saque: %.2f, Saldo: %.2f, Conta: %lld \n", allUsers[saque_index].nome, saque, allUsers[saque_index].saldo, allUsers[saque_index].numeroConta);
    fclose(fp);
}


void editarInformacoes(usuarios* user, usuarios* allUsers, int totalUsers) {
    long long num_conta_edita;
    printf("Informe o número da conta: ");
    scanf("%lld", &num_conta_edita);

    int edita_index = -1;

    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_edita) {
            edita_index = i;
            break;
        }
    }

    if (edita_index == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Digite o novo nome do titular: ");
    scanf(" %[^\n]", allUsers[edita_index].nome);  // Use scanf para ler até a nova linha
    getchar();  // Limpar o caractere de nova linha

    printf("Digite a nova idade: ");
    scanf("%d", &(allUsers[edita_index].idade));

    char new_cpf[15];
    printf("Digite o novo CPF: ");
    scanf("%s", new_cpf);

    // Se o CPF for válido, atualiza o CPF
    strcpy(allUsers[edita_index].cpf, new_cpf);

    printf("Informações do titular da conta atualizadas com sucesso!\n");

    // Restante do código para atualizar o arquivo...
    FILE *fp = fopen("contas.txt", "r+");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    char **linhas = malloc(MAX_USUARIOS *sizeof(char * ));
    for(int i = 0; i < MAX_USUARIOS; i++) {
        linhas[i] = malloc(100 *sizeof(char));
    }

    int i = 0;
    while (fgets(linhas[i], 100, fp) != NULL && i < MAX_USUARIOS) {
        i++;
    }
    fclose(fp);

    fp = fopen("contas.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int j = 0; j < MAX_USUARIOS; j++) {
        if (j == edita_index) {
            fprintf(fp, "Nome: %s, Idade: %d, CPF: %s, Numero da Conta: %lld, Saldo: %.2f\n", allUsers[edita_index].nome, allUsers[edita_index].idade, allUsers[edita_index].cpf, allUsers[edita_index].numeroConta, allUsers[edita_index].saldo);
        } else {
            // Check if the line ends with a newline character
            int len = strlen(linhas[j]);
            if (linhas[j][len - 1] != '\n') {
                // If not, add a newline character
                linhas[j][len] = '\n';
                linhas[j][len + 1] = '\0';
            }
            fprintf(fp, "%s", linhas[j]);
        }
    }
    fclose(fp);

    for(int i = 0; i < MAX_USUARIOS; i++) {
        free(linhas[i]);
    }
    free(linhas);
}

void Transferencia1(usuarios* user, usuarios* allUsers, int totalUsers){
    if (user == NULL) {
        printf("Usuário inválido.\n");
        return;
    }

    float transfere;
    long long num_conta_destino;
    long long num_conta_remetente;

    printf("Informe o número da conta: ");
    scanf("%lld", &num_conta_remetente);

    int remetente_index = -1;

    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_remetente) {
            remetente_index = i;
            break;
        }
    }

    if (remetente_index == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Informe o valor a transferir: ");
    scanf("%f", &transfere);

    if (allUsers[remetente_index].saldo < transfere) {
        printf("Seu saldo não é suficiente para realizar essa transferência.\n");
        return;
    }

    printf("Informe o número da conta de destino: ");
    scanf("%lld", &num_conta_destino);

    int destinatario_index = -1;

    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_destino) {
            destinatario_index = i;
            break;
        }
    }

    if (destinatario_index == -1) {
        printf("Conta de destino não encontrada.\n");
        return;
    }

    allUsers[remetente_index].saldo -= transfere;
    allUsers[destinatario_index].saldo += transfere;

    printf("Transferência de R$ %.2f realizada com sucesso para %s.\n", transfere, allUsers[destinatario_index].nome);

    FILE *fp = fopen("contas.txt", "a");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(fp, "Nome: %s, Transferência: %.2f, Conta Origem: %lld, Conta Destino: %lld\n", allUsers[remetente_index].nome, transfere, num_conta_remetente, num_conta_destino);
    fclose(fp);
}

void removeConta(usuarios* user) {
    long long int num_conta_remover;
    printf("Digite o número da conta que deseja remover: ");
    scanf("%lld", &num_conta_remover);
    getchar(); 

    int indice = -1;

    for (int i = 0; i < MAX_USUARIOS; i++) {
        if (user[i].numeroConta == num_conta_remover) {
            indice = i;
            break;
        }
    }

    if (indice == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    FILE *fp = fopen("contas.txt", "r");
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

    fp = fopen("contas.txt", "w");
    if (fp == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int j = 0; j < MAX_USUARIOS; j++) {
        if (j != indice && strcmp(user[j].nome, "") != 0) {
            fprintf(fp, "Nome: %s, Idade: %d, CPF: %s, Numero da Conta: %lld, Saldo: %.2f\n", user[j].nome, user[j].idade, user[j].cpf, user[j].numeroConta, user[j].saldo);
        }
    }
    fclose(fp);

    for(int i = 0; i < MAX_USUARIOS; i++) {
        free(linhas[i]);
    }
    free(linhas);

    usuarios vazio = {"", "", 0, 0, 0};
    user[indice] = vazio;

    printf("Conta removida com sucesso!\n");
}

void extrato(usuarios* user, usuarios* allUsers, int totalUsers){
    if (user == NULL) {
        printf("Usuário inválido.\n");
        return;
    }

    int user_index = -1;
    long long int num_conta_extrato;
    printf("informe o numero da conta: ");
    scanf("%lld", &num_conta_extrato);
    for (int i = 0; i < totalUsers; i++) {
        if (allUsers[i].numeroConta == num_conta_extrato) {
            user_index = i;
            break;
        }
    }

    if (user_index == -1) {
        printf("Conta não encontrada.\n");
        return;
    }

    printf("Número da Conta: %lld\n", allUsers[user_index].numeroConta);
    printf("Nome do Titular: %s\n", allUsers[user_index].nome);
    printf("Idade: %d\n", allUsers[user_index].idade);
    printf("Cpf: %s\n", allUsers[user_index].cpf);
    printf("Saldo Atual: R$ %.2f\n", allUsers[user_index].saldo);
    return;
}
