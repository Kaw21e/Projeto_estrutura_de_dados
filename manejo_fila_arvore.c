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
	printf("Nome do Paciente %d: %s\nIdade:%d\nMedico:%d\n", atual->dados_paciente.numero, atual->dados_paciente.nome, atual->dados_paciente.idade, atual->dados_paciente.medico);

    switch (atual->dados_paciente.medico){
    case 0:
        printf("Especialidade: cardiologista\n");
        break;
    case 1:
        printf("Especialidade: oftalmologista\n");
        break;
    case 2:
        printf("Especialidade: alergista\n");
        break;
    case 3:
        printf("Especialidade: dermatologista\n");
        break;
    default:
        printf("Especialidade desconhecida\n");
        break;
    }

    switch(atual->dados_paciente.prioridade){
    case 0:
        printf("Prioridade: Gestante\n");
        break;
    case 1:
        printf("Prioridade: Idoso\n");
        break;
    case 2:
        printf("Prioridade: PNE\n");
        break;
    case 3:
        printf("Prioridade: Crianca\n");
        break;
    case 4:
        printf("Prioridade: Doenca Cronica\n");
        break;
    case 5:
        printf("Prioridade: DEMAIS\n");
        break;
    default:
        printf("Prioridade desconhecida\n");
        break;
    }
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

    Arvore *raizP2 = (Arvore *) malloc(sizeof(Arvore));
    if (raizP2 == NULL){ //verifica erros
        printf("Erro ao criar raizP2!\n");
        return NULL;
    }
    raizP2->esquerda = NULL;
    raizP2->direita = NULL;
    raizP2->prioridade = 2;
    raizP2->fila = NULL;
    
    //criando filhos raiz

    Arvore *filhoP3 = (Arvore *) malloc(sizeof(Arvore));
    if(filhoP3 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar filhoP3!\n");
        free(raizP2);
        return NULL;
    }
    filhoP3->direita = NULL;
    filhoP3->esquerda = NULL;
    raizP2->direita = filhoP3;
    filhoP3->prioridade = 3;
    filhoP3->fila = NULL; 

    Arvore *filhoP0 = (Arvore *) malloc(sizeof(Arvore));
    if(filhoP0 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar filhoP0!\n");
        free(raizP2);
        free(filhoP3);
        return NULL;
    }
    filhoP0->direita = NULL;
    filhoP0->esquerda = NULL;
    raizP2->esquerda = filhoP0;
    filhoP0->prioridade = 0;
    filhoP0->fila = NULL;

    //criando filhos dos filhos
    
    Arvore *folhaP1 = (Arvore *) malloc(sizeof(Arvore));
    if (folhaP1 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar folhaP1!\n");
        free(raizP2);
        free(filhoP3);
        free(filhoP0);
        return NULL;
    }
    folhaP1->esquerda = NULL;
    folhaP1->direita = NULL;
    filhoP0->direita = folhaP1;
    folhaP1->prioridade = 1;
    folhaP1->fila = NULL;

    Arvore *folhaP4 = (Arvore *) malloc(sizeof(Arvore));
    if(folhaP4 == NULL){ //verifica erros e libera memória
        printf("Erro ao criar folhaP4!\n");
        free(raizP2);
        free(filhoP3);
        free(filhoP0);
        free(folhaP1);
        return NULL;
    }
    folhaP4->esquerda = NULL; 
    folhaP4->direita = NULL;
    folhaP4->fila = NULL;
    filhoP3->direita = folhaP4;
    folhaP4->prioridade = 4; 
    
    return raizP2;
}
