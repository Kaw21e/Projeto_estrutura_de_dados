#include "manejo_fila_arvore.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "salvar_pacientes.h"


// Funções para manipulação das filas

tipoFila *criarFila(){ 
   tipoFila *fila = (tipoFila *) malloc(sizeof(tipoFila));
   if (fila == NULL){
    printf("Erro ao criar fila!\n");
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
   	printf("Erro ao criar nó!\n");
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
	printf("Nome do Paciente %d: %s\nIdade:%d\nMedico:%d\nPrioridade:%d\n", atual->dados_paciente.numero, atual->dados_paciente.nome, atual->dados_paciente.idade, atual->dados_paciente.medico, atual->dados_paciente.prioridade);
    
    if(fila->ultimo == atual){
        fila->primeiro = NULL;
        fila->ultimo = NULL;
    } else {
        fila->primeiro = atual->proximo;
    }
    free(atual);
	printf("paciente simulado removido com sucesso!\n");
    return 0; 
}

int imprimir_numero(tipoFila *fila){
    if (fila == NULL){
        printf("Fila não inicializada!\n");
        return -1;
    }
    if(fila->primeiro == NULL){
		printf("Lista vazia!\n");
		return 1;
	}
	No *atual = fila->primeiro;
	printf("Numero %d\n", atual->dados_paciente.numero);
    return 0;
}

void destruir_fila(tipoFila *fila) {
    	if (fila == NULL){
        printf("Fila não inicializada!\n");
        return;
    }
	if(fila->primeiro == NULL){
		free(fila);
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
    free(fila);
    printf("Fila destruída com sucesso!\n");
}


// Função para manipulação da arvore

Arvore *Criar_Arvore(){
    
    //criando raiz

    Arvore *raizP3 = (Arvore *) malloc(sizeof(Arvore));
    if (raizP3 == NULL){ //verifica erros
        printf("Erro ao criar raizP3!\n");
        return NULL;
    }
    raizP3->esquerda = NULL;
    raizP3->direita = NULL;
    raizP3->prioridade = 3;
    raizP3->fila = NULL;
    
    //criando filhos raiz

    Arvore *filhoP4 = (Arvore *) malloc(sizeof(Arvore));
    if(filhoP4 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar filhoP4!\n");
        free(raizP3);
        return NULL;
    }
    filhoP4->direita = NULL;
    filhoP4->esquerda = NULL;
    raizP3->direita = filhoP4;
    filhoP4->prioridade = 4;
    filhoP4->fila = NULL; 

    Arvore *filhoP1 = (Arvore *) malloc(sizeof(Arvore));
    if(filhoP1 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar filhoP1!\n");
        free(raizP3);
        free(filhoP4);
        return NULL;
    }
    filhoP1->direita = NULL;
    filhoP1->esquerda = NULL;
    raizP3->esquerda = filhoP1;
    filhoP1->prioridade = 1;
    filhoP1->fila = NULL;

    //criando filhos dos filhos
    
    Arvore *folhaP2 = (Arvore *) malloc(sizeof(Arvore));
    if (folhaP2 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar folhaP2!\n");
        free(raizP3);
        free(filhoP4);
        free(filhoP1);
        return NULL;
    }
    folhaP2->esquerda = NULL;
    folhaP2->direita = NULL;
    filhoP1->direita = folhaP2;
    folhaP2->prioridade = 2;
    folhaP2->fila = NULL;

    Arvore *folhaP5 = (Arvore *) malloc(sizeof(Arvore));
    if(folhaP5 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar folhaP5!\n");
        free(raizP3);
        free(filhoP4);
        free(filhoP1);
        free(folhaP2);
        return NULL;
    }
    folhaP5->esquerda = NULL; 
    folhaP5->direita = NULL;
    folhaP5->fila = NULL;
    filhoP4->direita = folhaP5;
    folhaP5->prioridade = 5; 
    
    return raizP3;
}
