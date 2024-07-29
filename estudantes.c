#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudantes.h"

Estudante* criar_estudante(const char *nome, int idade, const char *matricula, const char *curso, int periodo, float mge)
{
    Estudante *novo_estudante = (Estudante*)malloc(sizeof(Estudante));
    if (novo_estudante == NULL)
    {
        fprintf(stderr, "[ERROR] Falha ao alocar memória.\n");
        exit(1);
    }

    novo_estudante->nome = strdup(nome);
    novo_estudante->idade = idade;
    novo_estudante->matricula = strdup(matricula);
    novo_estudante->curso = strdup(curso);
    novo_estudante->periodo = periodo;
    novo_estudante->mge = mge;
    novo_estudante->next = NULL;

    return novo_estudante;
}

Estudante* inicializar_lista(const char *nome_arquivo)
{
    FILE *file = fopen(nome_arquivo, "r");
    if (file == NULL)
    {
        fprintf(stderr, "[ERROR] Falha ao tentar abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    Estudante *lista = NULL;
    Estudante *ultimo = NULL;
    char linha[256];
    char nome[100], matricula[10], curso[100];
    int idade, periodo;
    float mge;

    while (fgets(linha, sizeof(linha), file))
    {
        if (sscanf(linha, "Nome: %[^\n]", nome) == 1)
        {
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Idade: %i", &idade);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Matrícula: %[^\n]", matricula);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Curso: %[^\n]", curso);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "Período: %i", &periodo);
            fgets(linha, sizeof(linha), file);
            sscanf(linha, "MGE: %f", &mge);
            fgets(linha, sizeof(linha), file);

            Estudante *novo_estudante = criar_estudante(nome, idade, matricula, curso, periodo, mge);
            if (lista == NULL)
            {
                lista = novo_estudante;
            }
            else
            {
                ultimo->next = novo_estudante;
            }
            ultimo = novo_estudante;
        }
    }

    fclose(file);
    return lista;
}

void listar_estudantes(Estudante *lista)
{
    Estudante *atual = lista;
    while (atual != NULL)
    {
        printf("Nome: %s\n", atual->nome);
        printf("Idade: %i\n", atual->idade);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Curso: %s\n", atual->curso);
        printf("Período: %i\n", atual->periodo);
        printf("Média Global do Estudante: %.1f\n", atual->mge);
        printf("\n");
        atual = atual->next;
    }
}

void alterar_estudante(Estudante *lista, const char *matricula, const char *novo_nome, int nova_idade, const char *novo_curso, int novo_periodo, float nova_mge)
{
    Estudante *atual = lista;
    while (atual != NULL)
    {
        if (strcmp(atual->matricula, matricula) == 0)
        {
            free(atual->nome);
            free(atual->curso);

            atual->nome = strdup(novo_nome);
            atual->idade = nova_idade;
            atual->curso = strdup(novo_curso);
            atual->periodo = novo_periodo;
            atual->mge = nova_mge;
            return;
        }
        atual = atual->next;
    }

    printf("Estudante com matrícula %s não encontrado.\n", matricula);
}

void adicionar_estudante(Estudante **lista, const char *nome, int idade, const char *matricula, const char *curso, int periodo, float mge)
{
    Estudante *novo_estudante = criar_estudante(nome, idade, matricula, curso, periodo, mge);

    if (*lista == NULL)
    {
        *lista = novo_estudante;
    }
    else
    {
        Estudante *atual = *lista;
        while (atual->next != NULL)
        {
            atual = atual->next;
        }
        atual->next = novo_estudante;
    }
}

void remover_estudante(Estudante **lista, const char *matricula)
{
    Estudante *atual = *lista;
    Estudante *anterior = NULL;

    while (atual != NULL && strcmp(atual->matricula, matricula) != 0)
    {
        anterior = atual;
        atual = atual->next;
    }

    if (atual == NULL)
    {
        printf("Estudante com matrícula %s não encontrado.\n", matricula);
        return;
    }

    if (anterior == NULL)
    {
        *lista = atual->next;
    }
    else
    {
        anterior->next = atual->next;
    }

    free(atual->nome);
    free(atual->matricula);
    free(atual->curso);
    free(atual);
}

void salvar_modificacoes(Estudante *lista, const char *nome_arquivo)
{
    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL)
    {
        fprintf(stderr, "[ERROR] Falha ao tentar abrir o arquivo %s.\n", nome_arquivo);
        return;
    }

    Estudante *atual = lista;
    while (atual != NULL)
    {
        fprintf(arquivo, "Nome: %s\n", atual->nome);
        fprintf(arquivo, "Idade: %i\n", atual->idade);
        fprintf(arquivo, "Matrícula: %s\n", atual->matricula);
        fprintf(arquivo, "Curso: %s\n", atual->curso);
        fprintf(arquivo, "Período: %i\n", atual->periodo);
        fprintf(arquivo, "MGE: %.1f\n", atual->mge);
        fprintf(arquivo, "\n");
        atual = atual->next;
    }

    fclose(arquivo);
}

Estudante* buscar_estudante_por_nome(Estudante *lista, const char *nome)
{
    Estudante *atual = lista;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

Estudante* buscar_estudante_por_matricula(Estudante *lista, const char *matricula)
{
    Estudante *atual = lista;
    while (atual != NULL)
    {
        if (strcmp(atual->matricula, matricula) == 0)
        {
            return atual;
        }
        atual = atual->next;
    }
    return NULL;
}

Estudante* ordenar_estudantes_por_mge(Estudante *lista)
{
    if (lista == NULL || lista->next == NULL)
    {
        return lista;
    }

    Estudante *sorted = NULL;

    while (lista != NULL)
    {
        Estudante *atual = lista;
        lista = lista->next;

        if (sorted == NULL || sorted->mge <= atual->mge)
        {
            atual->next = sorted;
            sorted = atual;
        }
        else
        {
            Estudante *temp = sorted;
            while (temp->next != NULL && temp->next->mge > atual->mge)
            {
                temp = temp->next;
            }

            atual->next = temp->next;
            temp->next = atual;
        }
    }

    return sorted;
}

void listar_estudantes_por_curso_e_periodo(Estudante *lista_ordenada, const char *curso)
{
    int max_periodo = 0;

    Estudante *atual = lista_ordenada;
    while (atual != NULL)
    {
        if (strcmp(atual->curso, curso) == 0)
        {
            if (atual->periodo > max_periodo)
            {
                max_periodo = atual->periodo;
            }
        }
        atual = atual->next;
    }
    
    for (int periodo = 1; periodo <= max_periodo; periodo++)
    {
        printf("%iº Período:\n", periodo);
        int encontrado = 0;
        
        atual = lista_ordenada;
        while (atual != NULL)
        {
            if (strcmp(atual->curso, curso) == 0 && atual->periodo == periodo)
            {
                printf("Nome: %s\n", atual->nome);
                printf("Idade: %i\n", atual->idade);
                printf("Matrícula: %s\n", atual->matricula);
                printf("Curso: %s\n", atual->curso);
                printf("Média Global do Estudante: %.1f\n", atual->mge);
                printf("\n");
                encontrado = 1;
            }
            atual = atual->next;
        }

        if (!encontrado)
        {
            printf("Nenhum estudante encontrado para este período.\n");
        }
        printf("\n");
    }
}

void listar_estudantes_com_maior_mge(Estudante *lista_ordenada)
{
    if (lista_ordenada == NULL)
    {
        printf("A lista está vazia.\n");
        return;
    }
    
    float max_mge = lista_ordenada->mge;
    printf("Estudante(s) com a maior Média Global (%1.f):\n\n", max_mge);
    
    Estudante *atual = lista_ordenada;
    while (atual != NULL && atual->mge == max_mge)
    {
        printf("Nome: %s\n", atual->nome);
        printf("Idade: %i\n", atual->idade);
        printf("Matrícula: %s\n", atual->matricula);
        printf("Curso: %s\n", atual->curso);
        printf("Média Global do Estudante: %.1f\n", atual->mge);
        printf("\n");
        atual = atual->next;
    }
}

void liberar_lista(Estudante *lista)
{
    Estudante *atual = lista;
    while (atual != NULL)
    {
        Estudante *proximo = atual->next;
        free(atual->nome);
        free(atual->matricula);
        free(atual->curso);
        free(atual);
        atual = proximo;
    }
}
