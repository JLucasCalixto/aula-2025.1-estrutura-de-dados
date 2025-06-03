#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "curso.h"
#include "aluno.h"


Curso* criarCurso(char* titulo, char* area, int maxVagas) {
    Curso* novoCurso = (Curso*) malloc(sizeof(Curso));
    if (novoCurso == NULL) {
        printf("Erro ao alocar memoria para curso.\n");
        return NULL;
    }
    strcpy(novoCurso->titulo, titulo);
    strcpy(novoCurso->area, area);
    novoCurso->maxVagas = maxVagas;
    novoCurso->vagasPreenchidas = 0;
    novoCurso->filaEspera = NULL;
    novoCurso->prox = NULL;
    return novoCurso;
}


void inscreverAlunoNoCurso(Curso* curso, Aluno* aluno) {
    if (curso == NULL || aluno == NULL) {
        printf("Curso ou aluno invalidos.\n");
        return;
    }

    
    if (curso->vagasPreenchidas < curso->maxVagas) {
        curso->vagasPreenchidas++;
        printf("Aluno %s inscrito no curso %s diretamente (vaga disponivel).\n", aluno->nome, curso->titulo);
    } else {
        
        aluno->prox = NULL;
        if (curso->filaEspera == NULL) {
            
            curso->filaEspera = aluno;
        } else {
            
            Aluno* temp = curso->filaEspera;
            while (temp->prox != NULL) {
                temp = temp->prox;
            }
            temp->prox = aluno;
        }
        printf("Curso cheio! Aluno %s colocado na fila de espera do curso %s.\n", aluno->nome, curso->titulo);
    }
}


void liberarVagaCurso(Curso* curso) {
    if (curso == NULL) return;

    if (curso->vagasPreenchidas > 0) {
        curso->vagasPreenchidas--;
        printf("Vaga liberada no curso %s.\n", curso->titulo);

        if (curso->filaEspera != NULL) {
            
            Aluno* alunoChamado = curso->filaEspera;
            curso->filaEspera = alunoChamado->prox;
            alunoChamado->prox = NULL;
            curso->vagasPreenchidas++;
            printf("Aluno %s saiu da fila e foi inscrito no curso %s.\n", alunoChamado->nome, curso->titulo);
            free(alunoChamado);  
        }
    } else {
        printf("Nenhuma vaga ocupada para liberar no curso %s.\n", curso->titulo);
    }
}