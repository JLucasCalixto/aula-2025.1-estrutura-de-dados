#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "aluno.h"


Curso* cadastrarCursoLista(Curso* lista, char* titulo, char* area, int maxVagas);
Curso* removerCursoLista(Curso* lista, char* titulo);
void listarCursos(Curso* lista);
Curso* buscarCursoPorTitulo(Curso* lista, char* titulo);
void ordenarCursosPorTitulo(Curso** lista);
void ordenarCursosPorArea(Curso** lista);
void inscreverAlunoNoCursoPorTitulo(Curso* lista);
void liberarVagaCursoPorTitulo(Curso* lista);

void exibirMenu() {
    printf("\n===== SISTEMA DE CURSOS ONLINE =====\n");
    printf("1. Cadastrar novo curso\n");
    printf("2. Remover curso\n");
    printf("3. Listar todos os cursos\n");
    printf("4. Inscrever aluno em curso\n");
    printf("5. Liberar vaga no curso\n");
    printf("6. Buscar curso por titulo\n");
    printf("7. Ordenar cursos por titulo\n");
    printf("8. Ordenar cursos por area\n");
    printf("0. Sair\n");
    printf("Escolha uma opcao: ");
}

int main() {
    Curso* listaCursos = NULL;
    int opcao;
    char titulo[100], area[50];
    int maxVagas;

    do {
        exibirMenu();
        scanf("%d", &opcao);
        getchar(); 

        switch (opcao) {
            case 1:
                printf("Digite o titulo do curso: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                printf("Digite a area do curso: ");
                fgets(area, 50, stdin);
                area[strcspn(area, "\n")] = 0;

                printf("Digite o maximo de vagas: ");
                scanf("%d", &maxVagas);
                getchar();

                listaCursos = cadastrarCursoLista(listaCursos, titulo, area, maxVagas);
                printf("Curso cadastrado com sucesso.\n");
                break;

            case 2:
                printf("Digite o titulo do curso a remover: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                listaCursos = removerCursoLista(listaCursos, titulo);
                break;

            case 3:
                listarCursos(listaCursos);
                break;

            case 4:
                inscreverAlunoNoCursoPorTitulo(listaCursos);
                break;

            case 5:
                liberarVagaCursoPorTitulo(listaCursos);
                break;

            case 6:
                printf("Digite o titulo do curso para buscar: ");
                fgets(titulo, 100, stdin);
                titulo[strcspn(titulo, "\n")] = 0;

                Curso* c = buscarCursoPorTitulo(listaCursos, titulo);
                if (c) {
                    printf("Curso encontrado:\nTitulo: %s\nArea: %s\nMax vagas: %d\nVagas preenchidas: %d\n", 
                        c->titulo, c->area, c->maxVagas, c->vagasPreenchidas);
                } else {
                    printf("Curso nao encontrado.\n");
                }
                break;

            case 7:
                ordenarCursosPorTitulo(&listaCursos);
                printf("Cursos ordenados por titulo.\n");
                break;

            case 8:
                ordenarCursosPorArea(&listaCursos);
                printf("Cursos ordenados por area.\n");
                break;

            case 0:
                printf("Saindo do programa...\n");
                break;

            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

 
    Curso* atual = listaCursos;
    while (atual != NULL) {
        Curso* temp = atual;
        atual = atual->prox;
        
        free(temp);
    }

    return 0;
}




Curso* cadastrarCursoLista(Curso* lista, char* titulo, char* area, int maxVagas) {
    Curso* novo = criarCurso(titulo, area, maxVagas);
    if (!novo) return lista;

    novo->prox = lista;
    return novo;
}

Curso* removerCursoLista(Curso* lista, char* titulo) {
    Curso* atual = lista;
    Curso* anterior = NULL;

    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            if (anterior == NULL) {
                lista = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            
            free(atual);
            printf("Curso removido com sucesso.\n");
            return lista;
        }
        anterior = atual;
        atual = atual->prox;
    }
    printf("Curso nao encontrado.\n");
    return lista;
}

void listarCursos(Curso* lista) {
    if (lista == NULL) {
        printf("Nenhum curso cadastrado.\n");
        return;
    }
    Curso* atual = lista;
    printf("Lista de cursos:\n");
    while (atual != NULL) {
        printf("Titulo: %s | Area: %s | Max Vagas: %d | Vagas preenchidas: %d\n", 
            atual->titulo, atual->area, atual->maxVagas, atual->vagasPreenchidas);
        atual = atual->prox;
    }
}

Curso* buscarCursoPorTitulo(Curso* lista, char* titulo) {
    Curso* atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->titulo, titulo) == 0) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

void inscreverAlunoNoCursoPorTitulo(Curso* lista) {
    char titulo[100];
    char nome[100];
    char email[100];

    printf("Digite o titulo do curso para inscrever o aluno: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    Curso* curso = buscarCursoPorTitulo(lista, titulo);
    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
        return;
    }

    printf("Digite o nome do aluno: ");
    fgets(nome, 100, stdin);
    nome[strcspn(nome, "\n")] = 0;

    printf("Digite o email do aluno: ");
    fgets(email, 100, stdin);
    email[strcspn(email, "\n")] = 0;

    Aluno* aluno = criarAluno(nome, email);
    if (!aluno) {
        printf("Erro ao criar aluno.\n");
        return;
    }

    inscreverAlunoNoCurso(curso, aluno);
}

void liberarVagaCursoPorTitulo(Curso* lista) {
    char titulo[100];
    printf("Digite o titulo do curso para liberar vaga: ");
    fgets(titulo, 100, stdin);
    titulo[strcspn(titulo, "\n")] = 0;

    Curso* curso = buscarCursoPorTitulo(lista, titulo);
    if (curso == NULL) {
        printf("Curso nao encontrado.\n");
        return;
    }

    liberarVagaCurso(curso);
}


void ordenarCursosPorTitulo(Curso** lista) {
    if (*lista == NULL) return;

    int trocou;
    Curso* ptr1;
    Curso* lptr = NULL;

    do {
        trocou = 0;
        ptr1 = *lista;

        while (ptr1->prox != lptr) {
            if (strcmp(ptr1->titulo, ptr1->prox->titulo) > 0) {
               
                Curso temp = *ptr1;
                *ptr1 = *(ptr1->prox);
                *(ptr1->prox) = temp;

                
                Curso* aux = ptr1->prox->prox;
                ptr1->prox->prox = ptr1->prox;
                ptr1->prox = aux;

                trocou = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    } while (trocou);
}

void ordenarCursosPorArea(Curso** lista) {
    if (*lista == NULL) return;

    int trocou;
    Curso* ptr1;
    Curso* lptr = NULL;

    do {
        trocou = 0;
        ptr1 = *lista;

        while (ptr1->prox != lptr) {
            if (strcmp(ptr1->area, ptr1->prox->area) > 0) {
                Curso temp = *ptr1;
                *ptr1 = *(ptr1->prox);
                *(ptr1->prox) = temp;

                Curso* aux = ptr1->prox->prox;
                ptr1->prox->prox = ptr1->prox;
                ptr1->prox = aux;

                trocou = 1;
            }
            ptr1 = ptr1->prox;
        }
        lptr = ptr1;
    } while (trocou);
}