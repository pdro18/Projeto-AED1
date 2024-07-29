#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estudantes.h"

int main(void) 
{
    Estudante *lista = inicializar_lista("estudantes.txt");
    if (lista == NULL) {
        fprintf(stderr, "Falha ao inicializar a lista de estudantes.\n");
        return 1;
    }

    while (1)
    {
        int opcao;
        printf("Escolha uma opçãoo: \n");
        printf("[ 1 ] Cadastrar estudante\n");
        printf("[ 2 ] Listar estudantes\n");
        printf("[ 3 ] Atualizar estudante\n");
        printf("[ 4 ] Remover estudante\n");
        printf("[ 5 ] Buscar estudante por nome\n");
        printf("[ 6 ] Buscar estudante por matricula\n");
        printf("[ 7 ] Listar estudantes por curso e periodo\n");
        printf("[ 8 ] Listar estudantes com maior MGE\n");
        printf("[ 9 ] Sair\n");
        printf("Opção: ");
        scanf("%i", &opcao);
        getchar();
        
        char nome[100], matricula[10], curso[50];
        int idade, periodo;
        float mge;
        Estudante *estudante;

        switch (opcao)
        {
            case 1:
                printf("Digite o nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite a idade: ");
                scanf("%i", &idade);
                getchar();
                printf("Digite a matrícula: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                printf("Digite o curso: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';
                printf("Digite o período: ");
                scanf("%i", &periodo);
                getchar();
                printf("Digite a Média Global do Estudante (MGE): ");
                scanf("%f", &mge);
                getchar();
                adicionar_estudante(&lista, nome, idade, matricula, curso, periodo, mge);
                salvar_modificacoes(lista, "estudantes.txt");
                break;

            case 2:
                listar_estudantes(lista);
                break;

            case 3:
                printf("Digite a matrícula do estudante que deseja atualizar: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                printf("Digite o novo nome: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                printf("Digite a nova idade: ");
                scanf("%i", &idade);
                getchar();
                printf("Digite o novo curso: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';
                printf("Digite o novo período: ");
                scanf("%i", &periodo);
                getchar();
                printf("Digite a nova Média Global do Estudante (MGE): ");
                scanf("%f", &mge);
                getchar();
                alterar_estudante(lista, matricula, nome, idade, curso, periodo, mge);
                salvar_modificacoes(lista, "estudantes.txt");
                break;

            case 4:
                printf("Digite a matrícula do estudante que deseja remover: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                remover_estudante(&lista, matricula);
                salvar_modificacoes(lista, "estudantes.txt");
                break;

            case 5:
                printf("Digite o nome do estudante que deseja buscar: ");
                fgets(nome, sizeof(nome), stdin);
                nome[strcspn(nome, "\n")] = '\0';
                estudante = buscar_estudante_por_nome(lista, nome);
                if (estudante != NULL) {
                    printf("Nome: %s\n", estudante->nome);
                    printf("Idade: %i\n", estudante->idade);
                    printf("Matrícula: %s\n", estudante->matricula);
                    printf("Curso: %s\n", estudante->curso);
                    printf("Período: %i\n", estudante->periodo);
                    printf("Média Global do Estudante: %.1f\n", estudante->mge);
                } else {
                    printf("Estudante com nome %s não encontrado.\n", nome);
                }
                break;

            case 6:
                printf("Digite a matrícula do estudante que deseja buscar: ");
                fgets(matricula, sizeof(matricula), stdin);
                matricula[strcspn(matricula, "\n")] = '\0';
                estudante = buscar_estudante_por_matricula(lista, matricula);
                if (estudante != NULL) {
                    printf("Nome: %s\n", estudante->nome);
                    printf("Idade: %i\n", estudante->idade);
                    printf("Matrícula: %s\n", estudante->matricula);
                    printf("Curso: %s\n", estudante->curso);
                    printf("Período: %i\n", estudante->periodo);
                    printf("Média Global do Estudante: %.1f\n", estudante->mge);
                } else {
                    printf("Estudante com matrícula %s não encontrado.\n", matricula);
                }
                break;

            case 7:
                printf("Digite o curso que deseja listar os estudantes: ");
                fgets(curso, sizeof(curso), stdin);
                curso[strcspn(curso, "\n")] = '\0';
                listar_estudantes_por_curso_e_periodo(ordenar_estudantes_por_mge(lista), curso);
                break;

            case 8:
                listar_estudantes_com_maior_mge(ordenar_estudantes_por_mge(lista));
                break;

            case 9:
                liberar_lista(lista);
                printf("Saindo...\n");
                exit(0);

            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    }

    return 0;
}
