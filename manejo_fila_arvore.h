#ifndef MANEJO_FILA_ARVORE_H
#define MANEJO_FILA_ARVORE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvar_pacientes.h"


//definindo structs de fila e nó

typedef struct no {
   Paciente dados_paciente; // Dados do paciente
   struct no *proximo; // Correção: Usar "struct no" aqui
} No;

typedef struct tipoFila {
   No *primeiro;
   No *ultimo;
 } tipoFila;

 // Definindo a estrutura da árvore binária de busca

typedef struct Arvore {
    tipoFila *fila;
    int prioridade; // (chave)
    struct Arvore *esquerda;
    struct Arvore *direita;
} Arvore;

// Funções para manipulação da fila

tipoFila *criarFila();

No *inserirFila(tipoFila *fila, Paciente *paciente);

int imprimir_e_remover_no(tipoFila *fila);

void destruir_fila(tipoFila *fila);

No* adicionarPacienteFila_Vez(tipoFila *fila_ptr, int vez_paciente);



#endif // MANEJO_FILA_ARVORE_H