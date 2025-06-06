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
        sleep(1);
        switch (tad_configs->configs.status) 
        {
            
        case SIMULAR:
            simular(2);
            Paciente *paciente = ler_paciente_por_numero(Vez);
            if (paciente != NULL) {
                Vez++;
                printf("Paciente %d: %s, Idade: %d, Prioridade: %d\n", paciente->numero, paciente->nome, paciente->idade, paciente->prioridade);
                free(paciente);
            } else {
                printf("Nenhum paciente na fila.\n");
            }
            break;

        case AGUARDAR:
            printf("Aguardando...\n");
            break;

        case REINICIAR_FILA:
            printf("Reiniciando fila...\n");
            reiniciar_fila();
            Vez = 0; // Reinicia o contador de pacientes
            configs_atualizar(tad_configs, AGUARDAR, 1);
            break;
        }

        // Atualiza as configurações após cada iteração
        configs_ler(tad_configs);
    }

    return 0;
}
