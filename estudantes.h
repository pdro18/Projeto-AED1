#ifndef ESTUDANTES_H
#define ESTUDANTES_H

typedef struct Estudante {
    char *nome;
    char *matricula;
    char *curso;
    int idade;
    int periodo;
    float mge;
    struct Estudante *next;
} Estudante;

Estudante* criar_estudante(const char *nome, int idade, const char *matricula, const char *curso, int periodo, float mge);

Estudante* inicializar_lista(const char *nome_arquivo);

void listar_estudantes(Estudante *lista);

void alterar_estudante(Estudante *lista, const char *matricula, const char *novo_nome, int nova_idade, const char *novo_curso, int novo_periodo, float nova_mge);

void adicionar_estudante(Estudante **lista, const char *nome, int idade, const char *matricula, const char *curso, int periodo, float mge);

void remover_estudante(Estudante **lista, const char *matricula);

void salvar_modificacoes(Estudante *lista, const char *nome_arquivo);

Estudante* buscar_estudante_por_nome(Estudante *lista, const char *nome);

Estudante* buscar_estudante_por_matricula(Estudante *lista, const char *matricula);

Estudante* ordenar_estudantes_por_mge(Estudante *head);

void listar_estudantes_por_curso_e_periodo(Estudante *lista, const char *curso);

void listar_estudantes_com_maior_mge(Estudante *lista);

void liberar_lista(Estudante *lista);

#endif // ESTUDANTES_H
