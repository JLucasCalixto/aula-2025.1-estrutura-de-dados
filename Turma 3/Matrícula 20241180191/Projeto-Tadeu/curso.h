#ifndef CURSO_H
#define CURSO_H

#include "aluno.h"

typedef struct curso {
    char titulo[100];
    char area[50];
    int maxVagas;
    int vagasPreenchidas;
    Aluno* filaEspera;
    struct curso* prox; 
} Curso;


Curso* criarCurso(char* titulo, char* area, int maxVagas);
void inscreverAlunoNoCurso(Curso* curso, Aluno* aluno);
void liberarVagaCurso(Curso* curso);

#endif