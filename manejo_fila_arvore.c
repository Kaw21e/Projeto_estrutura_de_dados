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

int imprimir_e_remover_no(tipoFila *fila){
	if (fila == NULL){
        printf("Fila não inicializada!\n");
        return -1;
    }
    if(fila->primeiro == NULL){
		printf("Lista vazia!\n");
		return 1;
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
	printf("paciente removido com sucesso!\n");
    return 0; 
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


No* adicionarPacienteFila_Vez(tipoFila *fila_ptr, int vez_paciente) {
    Paciente *dados_paciente_lido;
    while ((dados_paciente_lido = ler_paciente_por_numero(vez_paciente)) != NULL) {
       No* no_inserido = inserirFila(&fila_ptr, dados_paciente_lido); 
       if (no_inserido == NULL) {
            free(dados_paciente_lido);
            return fila_ptr; // Erro ao inserir na fila
        }
        free(dados_paciente_lido); 
    }
    return fila_ptr;
}



