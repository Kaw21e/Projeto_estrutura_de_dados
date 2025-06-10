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

typedef struct {
    int numero;
    char nome[100];
    int idade;
    PrioridadePaciente prioridade;
   
} Paciente;


Paciente *criar_paciente(int numero, char nome[], int idade, PrioridadePaciente prioridade); 
// Função para salvar pacientes em arquivo
int salvar_pacientes(Paciente *paciente);

FILE *fila_abrir();

Paciente *ler_paciente_por_numero(int numero);

FILE *reiniciar_fila();

#endif // SALVAR_PACIENTES_H