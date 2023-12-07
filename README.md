# Sistema Bancário em C

Este é um projeto de um sistema bancário simples desenvolvido em linguagem C. O sistema gerencia contas bancárias, permitindo a criação, remoção e outras operações básicas.

## Estrutura do Projeto

O projeto é dividido em dois principais arquivos:

### `contas.h`

O arquivo `contas.h` contém a declaração das funções principais para manipulação de contas bancárias. Ele inclui definições de estruturas de dados, protótipos de funções e constantes utilizadas no sistema.

Funcionalidades implementadas:
- Criação de conta bancária
- Remoção de conta bancária
- Outras operações bancárias (depósito, saque, consulta de saldo etc.)

### `main.c`

O arquivo `main.c` contém a lógica principal do sistema bancário. Ele utiliza as funções definidas em `contas.h` para realizar operações bancárias com base nas interações do usuário.

Funcionalidades implementadas:
- Menu interativo para operações bancárias
- Utiliza as funções definidas em `contas.h` para executar as operações

## Como Usar

Para compilar e executar o sistema bancário, siga os passos abaixo:

1. Abra o terminal na pasta do projeto.
2. Compile os arquivos usando um compilador C (por exemplo, C++ ou Ccompiler):
    ```
    gcc main.c -o sistema_bancario
    ```
3. Execute o programa gerado:
    ```
    ./sistema_bancario
    ```

O sistema exibirá um menu interpretativo com opções para interagir com as contas bancárias.

## Contribuições

Contribuições para melhorias, correções de bugs ou adição de novas funcionalidades são bem-vindas. Se desejar contribuir, siga estes passos:

1. Faça um fork do repositório.
2. Crie uma branch para suas modificações:
    ```
    git checkout -b minha-modificacao
    ```
3. Faça suas alterações e commit:
    ```
    git commit -m "Minha modificação"
    ```
4. Envie suas alterações para o repositório:
    ```
    git push origin minha-modificacao
    ```
5. Abra um pull request descrevendo suas alterações.

## Autores

[Estevão Lins, Matheus, Rafael Dornelas, Caio Caetano, Filipe] [https://www.linkedin.com/in/estevaolins/]

