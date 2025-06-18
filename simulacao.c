#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"
#include "salvar_pacientes.h"
#include "manejo_fila_arvore.h"

void simular(int tempo) {
    printf("\nSimulando...\n\n");
    sleep(tempo);
}

int main() {
    int Vez = 0;
    TadConfigs *tad_configs;
    // Criar TAD e abrir arquivo

    Arvore *raiz = Criar_Arvore(); // Inicializa a árvore
    if (raiz == NULL) {
        printf("Erro ao criar árvore\n");
        return 1;
    }
    tipoFila *filaP1 = raiz->esquerda->fila;
    tipoFila *filaP2 = raiz->esquerda->direita->fila;
    tipoFila *filaP3 = raiz->fila;
    tipoFila *filaP4 = raiz->direita->fila;
    tipoFila *filaP5 = raiz->direita->direita->fila;

    tipoFila *fila = NULL; // Fila para pacientes com prioridade 6 (DEMAIS)

    tad_configs = configs_inicializar();
    if (!tad_configs) {
      printf("Erro ao criar TAD\n");
      return 1;
    }
    printf("Arquivo acessado!");

    // Carregar configurações

    configs_ler(tad_configs);
    configs_mostrar(tad_configs);

    while(tad_configs->configs.status != TERMINAR) {
        Paciente *paciente;
        while ((paciente = ler_paciente_por_numero(Vez)) != NULL) { // Alocar pacientes do arquivo de acordo com a prioridade
            
            if(paciente->prioridade == DEMAIS){ // prioridade 5 
                if(fila == NULL){
                    fila = criarFila();
                    inserirFila(fila, paciente);
                }else{
                inserirFila(fila, paciente);
                }
            }

            else if (paciente->prioridade == DOENCA_CRONICA){ //prioridade 4
                if(filaP5 == NULL){
                    filaP5 = criarFila();
                    inserirFila(filaP5, paciente);
                }else{
                inserirFila(filaP5, paciente); 
                }
            }

            else if (paciente->prioridade == CRIANCA){ //prioridade 3
                if(filaP4 == NULL){
                    filaP4 = criarFila();
                    inserirFila(filaP4, paciente);
                }else{
                inserirFila(filaP4, paciente);
                }
            } 

            else if (paciente->prioridade == PNE){ //prioridade 2
                if(filaP3 == NULL){
                    filaP3 = criarFila();
                    inserirFila(filaP3, paciente);
                }else{
                inserirFila(filaP3, paciente);
                }
            }

            else if (paciente->prioridade == IDOSO){ //prioridade 1
                if(filaP2 == NULL){
                    filaP2 = criarFila();
                    inserirFila(filaP2, paciente);
                }else{
                inserirFila(filaP2, paciente);
                }
            }

            else if (paciente->prioridade == GESTANTE){ //prioridade 0
                if(filaP1 == NULL){
                    filaP1 = criarFila();
                    inserirFila(filaP1, paciente);
                }else{
                inserirFila(filaP1, paciente);
                }
            }
            Vez++; //se paciente = null, vez - 1 é o ultimo paciente da lista (fila.dat)
        }
        
        sleep(1);
        
        switch (tad_configs->configs.status) {
        case SIMULAR:
            int simulacao;
            simular(2);
            printf("\n=======================\n\n");
            if(filaP1 != NULL || filaP2 != NULL || filaP3 != NULL || filaP4 != NULL || filaP5 != NULL) {
                if(filaP1 != NULL){
                    imprimir_e_remover_no(filaP1);
                    if (filaP1->primeiro == NULL) {
                        destruir_fila(filaP1);
                        filaP1 = NULL;
                    }
                } else if(filaP2 != NULL){
                    imprimir_e_remover_no(filaP2);
                    if (filaP2->primeiro == NULL) {
                        destruir_fila(filaP2);
                        filaP2 = NULL;
                    }
                } else if(filaP3 != NULL){
                    imprimir_e_remover_no(filaP3);
                    if (filaP3->primeiro == NULL) {
                        destruir_fila(filaP3);
                        filaP3 = NULL;
                    }
                } else if(filaP4 != NULL){
                    imprimir_e_remover_no(filaP4);
                    if (filaP4->primeiro == NULL) {
                        destruir_fila(filaP4);
                        filaP4 = NULL;
                    }
                } else if(filaP5 != NULL){
                    imprimir_e_remover_no(filaP5);
                    if (filaP5->primeiro == NULL) {
                        destruir_fila(filaP5);
                        filaP5 = NULL;
                    }
                }
            } else if(fila != NULL) {
                imprimir_e_remover_no(fila);
                if(fila->primeiro == NULL) {
                    printf("todas as filas estão vazias!\n");
                    destruir_fila(fila);
                    fila = NULL;
                }
            }

            printf("\nProximo paciente com prioridade:");
            // para mostrar proximo paciente
            if (filaP1 != NULL) { 
                imprimir_numero(filaP1);
            } else if (filaP2 != NULL) {
                imprimir_numero(filaP2);
            } else if (filaP3 != NULL) {
                imprimir_numero(filaP3);
            } else if (filaP4 != NULL) {
                imprimir_numero(filaP4);
            } else if (filaP5 != NULL) {
                imprimir_numero(filaP5);
            } else{
                printf("Nenhum!\n");
            }
            if(fila != NULL) {
                printf("Proximo paciente sem prioridade: ");
                imprimir_numero(fila);
            } else {
                printf("Nenhum paciente na fila sem prioridade!\n");
            }
            printf("\n=======================\n\n");
            break;
        case AGUARDAR:
            printf("Aguardando...\n");
            break;

        case REINICIAR_FILA:
            printf("Reiniciando fila...\n");
            reiniciar_fila();   
            destruir_fila(fila);
            fila == NULL;
            destruir_fila(filaP1);
            filaP1 = NULL;
            destruir_fila(filaP2);
            filaP2 = NULL;
            destruir_fila(filaP3);
            filaP3 = NULL;
            destruir_fila(filaP4);
            filaP4 = NULL;
            destruir_fila(filaP5);
            filaP5 = NULL;

            printf("Fila reiniciada com sucesso!\n");
            Vez = 0; // Reinicia o contador de pacientes
            configs_atualizar(tad_configs, AGUARDAR, 1);
            break;
        }

        // Atualiza as configurações após cada iteração
        configs_ler(tad_configs);
    }

    return 0;
}
