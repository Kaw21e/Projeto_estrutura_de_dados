#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"
#include "salvar_pacientes.h" 
#include "manejo_fila_arvore.h"

int menu() {
    printf("1. Aguardar\n2. Simular\n3. Terminar\n4. Reiniciar Fila\n5. Inserir Novo Paciente\n0. Sair\n");
    printf("Informe a opção desejada: ");
    int aux;
    scanf("%d", &aux);
    return aux;
}
int main() {
  int Vez = 0;
  TadConfigs *tad_configs;
  int op;
  // Criar TAD e abrir arquivo
  tad_configs = configs_inicializar();
  if (!tad_configs) {
    printf("Erro ao criar TAD\n");
    return 1;
  }

  // Criar arquivo de pacientes e abrir fila
  FILE *fila = fila_abrir();

  do {
      op = menu();
      switch(op) {
          case 1: {
              configs_atualizar(tad_configs, AGUARDAR, 1);
              break;
          }
          case 2: {
              configs_atualizar(tad_configs, SIMULAR, 1);
              break;
          }
          case 3: {
              configs_atualizar(tad_configs, TERMINAR, 1);
              break;
          }
          case 4: {
              fila = reiniciar_fila();
              printf("Fila reiniciada com sucesso!\n");
              Vez = 0; // Reinicia o contador de pacientes
             // fila = fila_abrir(); // Reabre o arquivo de pacientes
              configs_atualizar(tad_configs, REINICIAR_FILA, 1);
              break;
          }
          case 5: {
            int idade, prioridade;
            char nome_paciente[100];
            printf("Informe a idade do paciente: ");
            scanf("%d", &idade);
            printf("Informe o primeiro nome do paciente: ");
            scanf(" %s", nome_paciente);
            printf("Informe a prioridade do paciente do paciente:\n1. GESTANTE\n2. IDOSO\n3. PNE\n4. CRIANCA\n5. DOENCA_CRONICA\n6. DEMAIS\n");
            scanf("%d", &prioridade);
            Paciente *paciente = criar_paciente(Vez, nome_paciente, idade, prioridade);
            salvar_pacientes(paciente);
            Vez++;
            printf("Paciente %s adicionado com sucesso!\n", nome_paciente);
            break;
          }
          case 0: {
              configs_destruir(tad_configs);
              printf("Até a próxima!\n");
              break;
          }
          default: {
              printf("Opção inválida!\n");
          }
      }
  } while (op != 0);
  return 0;
}
