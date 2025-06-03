#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "aluno.h"


Aluno* criarAluno(char* nome, char* email) {
    Aluno* novoAluno = (Aluno*) malloc(sizeof(Aluno));
    if (novoAluno == NULL) {
        printf("Erro ao alocar memoria para aluno.\n");
        return NULL;
    }
    strcpy(novoAluno->nome, nome);
    strcpy(novoAluno->email, email);
    novoAluno->prox = NULL; 
    return novoAluno;
}


void imprimirAluno(Aluno* aluno) {
    if (aluno != NULL) {
        printf("Nome: %s, Email: %s\n", aluno->nome, aluno->email);
    } else {
        printf("Aluno nulo.\n");
    }
}