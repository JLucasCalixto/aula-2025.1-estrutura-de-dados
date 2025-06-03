#ifndef ALUNO_H
#define ALUNO_H

typedef struct aluno {
    char nome[100];
    char email[100];
    struct aluno* prox; 
} Aluno;


Aluno* criarAluno(char* nome, char* email);
void imprimirAluno(Aluno* aluno);

#endif