# Sistema de Gestão de Estudantes

Este projeto é um sistema simples para gerenciar informações de estudantes, incluindo cadastro, atualização, remoção e listagem de dados. Ele utiliza uma lista ligada para armazenar e manipular os dados dos estudantes. O sistema lê e escreve em um arquivo de texto para persistência de dados.

## Estrutura do Projeto

O projeto é dividido em três principais arquivos de código:

1. **`estudantes.h`** - Define a estrutura de dados e as funções para manipulação dos estudantes.
2. **`estudantes.c`** - Implementa as funções definidas em `estudantes.h`.
3. **`main.c`** - Contém a função principal (`main`) que oferece uma interface de linha de comando para o usuário interagir com o sistema.

## Estrutura de Dados

O projeto utiliza uma estrutura de lista ligada para armazenar as informações dos estudantes. Cada estudante é representado pela estrutura `Estudante`:

```c
typedef struct Estudante {
    char *nome;
    char *matricula;
    char *curso;
    int idade;
    int periodo;
    float mge;
    struct Estudante *next;
} Estudante;
