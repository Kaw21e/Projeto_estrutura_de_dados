#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"
#include "salvar_pacientes.h"
#include "manejo_fila_arvore.h"

void simular(int tempo) {
    printf("Simulando...\n");
    sleep(tempo);
}



int main() {
    int Vez = 0;
    TadConfigs *tad_configs;
    // Criar TAD e abrir arquivo
    tipoFila *fila = criarFila(); // Inicializa a fila
    if (fila == NULL) {
        printf("Erro ao criar fila\n");
        return 1;
    }
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
        int addPaciente = 0;
        Paciente *paciente;
        while ((paciente = ler_paciente_por_numero(Vez)) =! NULL) {
            inserirFila(fila, paciente);
            Vez++; //se paciente = null, vez - 1 é o ultimo paciente da lista (fila.dat)
        }

        
        sleep(1);
        switch (tad_configs->configs.status) 
        {

        case SIMULAR:
            simular(2);
            int simulacao = imprimir_e_remover_no(fila);
            if (simulacao == 1) {       
                printf("Fila vazia!\n");
            } else {
                printf("Paciente simulado com sucesso!\n");
            }
            break;
        case AGUARDAR:
            printf("Aguardando...\n");
            break;

        case REINICIAR_FILA:
            printf("Reiniciando fila...\n");
            reiniciar_fila();   
            destruir_fila(fila);
            fila = criarFila();
            if (fila == NULL) {
                printf("Erro ao reiniciar fila\n");
                return 1;
            }
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
