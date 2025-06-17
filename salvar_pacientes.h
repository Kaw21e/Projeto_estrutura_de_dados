#ifndef SALVAR_PACIENTES_H
#define SALVAR_PACIENTES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
    GESTANTE,
    IDOSO,
    PNE,
    CRIANCA,
    DOENCA_CRONICA,
    DEMAIS
} PrioridadePaciente;

typedef enum {
    Cardiologista,
    Oftalmologista,
    Alergista,
    Dermatologista
} especialidade;

typedef struct {
    int numero;
    char nome[100];
    int idade;
    especialidade medico;
    PrioridadePaciente prioridade;
   
} Paciente;


Paciente *criar_paciente(int numero, char nome[], int idade, PrioridadePaciente prioridade, especialidade medico);

int salvar_pacientes(Paciente *paciente);

FILE *fila_abrir();

Paciente *ler_paciente_por_numero(int numero);

FILE *reiniciar_fila();

void fechar_fila();

#endif // SALVAR_PACIENTES_H