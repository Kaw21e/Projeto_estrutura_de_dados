#include "manejo_fila_arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvar_pacientes.h"



tipoFila *criarFila(){ 
   tipoFila *fila = (tipoFila *) malloc(sizeof(tipoFila));
   if (fila == NULL){
    return NULL;
   }
   fila->primeiro = NULL;
   fila->ultimo = NULL;
   return fila;
}

No *inserirFila(tipoFila *fila, Paciente *paciente){ 
	if (fila == NULL){
        printf("Fila não inicializada!\n");
        return NULL;
    }
   No *novo = (No *) malloc(sizeof(No));
   if (novo == NULL){
   	return NULL;
   }
   novo->dados_paciente = *paciente;
   novo->proximo = NULL;

   if(fila->primeiro == NULL){
   	fila->primeiro = novo;
   	fila->ultimo = novo;
   } else{
   	fila->ultimo->proximo = novo;
   	fila->ultimo = novo;
   }
   return novo;
}

void imprimir_e_remover_no(tipoFila *fila){
	if (fila == NULL){
        printf("Fila não inicializada!\n");
        return;
    }
    if(fila->primeiro == NULL){
		printf("Lista vazia!\n");
		return;
	}
	No *atual = fila->primeiro;
	printf("Nome do Paciente %d: %s\nIdade:%d\nPrioridade:%d\n", atual->dados_paciente.numero, atual->dados_paciente.nome, atual->dados_paciente.idade, atual->dados_paciente.prioridade);
    if(fila->ultimo == atual){
        fila->primeiro = NULL;
        fila->ultimo = NULL;
    } else {
        fila->primeiro = atual->proximo;
    }
    free(atual);
	printf("\n");
}

void destruir_fila(tipoFila *fila) {
    	if (fila == NULL){
        printf("Fila não inicializada!\n");
        return;
    }
	if(fila->primeiro == NULL){
		return;
	}
	No *atual = fila->primeiro;
	No *anterior;
	while (atual != NULL){
	anterior = atual;
	atual = atual->proximo;
	free(anterior);
	}	
	fila->primeiro = NULL;
	fila->ultimo = NULL;
}


