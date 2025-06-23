#include <stdio.h>
#include <unistd.h>
#include "tad_configs.h"
#include "salvar_pacientes.h" 
#include "manejo_fila_arvore.h"

int menu() {
    printf("1. Aguardar\n2. Simular\n3. Terminar\n4. Reiniciar Fila\n5. Inserir Novo Paciente\n6. Imprimir relatorio de especialidades\n0. Sair\n");
    printf("Informe a opção desejada: ");
    int aux;
    scanf("%d", &aux);
    return aux;
}
int main() {

  //iniciando variáveis
  int Vez = 1; // Vez é o contador de pacientes, usado para atribuir um número único a cada
  TadConfigs *tad_configs;
  int op;
  int cardiologista = 0, oftalmologista = 0, alergista = 0, dermatologista = 0; // Especialidades médicas

  // Criar TAD e abrir arquivo
  tad_configs = configs_inicializar();
  if (!tad_configs) {
    printf("Erro ao criar TAD\n");
    return 1;
  }

  // Criar arquivo de pacientes e abrir fila
  FILE *fila = fila_abrir();

  //reiniciar fila
  fila = reiniciar_fila();
  configs_atualizar(tad_configs, REINICIAR_FILA, 1);

  do {
      op = menu();
      if (op < 0 || op > 6) {
          printf("Opção inválida!\n");
          continue;
      }

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
              Vez = 1; // Reinicia o contador de pacientes
              configs_atualizar(tad_configs, REINICIAR_FILA, 1);
              break;

          }
          case 5: {

            int idade, prioridade;
            char nome_paciente[100];
            int medico;

            printf("=======================\n\n");
            printf("Informe o nome do paciente: ");
            int c;
            while ((c = getchar()) != '\n' && c != EOF); // Limpa buffer antes do fgets
            fgets(nome_paciente, sizeof(nome_paciente), stdin);
            printf("Informe a idade do paciente: ");
            scanf("%d", &idade);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Informe a prioridade do paciente do paciente:\n0. GESTANTE\n1. IDOSO\n2. PNE\n3. CRIANCA\n4. DOENCA_CRONICA\n5. DEMAIS\n");
            scanf("%d", &prioridade);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Informe o número da especialidade do médico:\n0. Cardiologista\n1. Oftalmologista\n2. Alergista\n3. Dermatologista\n");
            scanf("%d", &medico);
            while ((c = getchar()) != '\n' && c != EOF);
            printf("\n=======================\n\n");

            switch(medico) {
            case 0: cardiologista++; break;
            case 1: oftalmologista++; break;
            case 2: alergista++; break;
            case 3: dermatologista++; break;
            default: {
                printf("Especialidade inválida!\n");
                break;
            }
            }

            Paciente *paciente = criar_paciente(Vez, nome_paciente, idade, prioridade, medico);
            if(paciente == NULL) {
                printf("Erro ao criar paciente!\n");
                break;
            }

            salvar_pacientes(paciente);
            printf("Paciente %s numero %d adicionado com sucesso!\n", nome_paciente, Vez);

            Vez++;
            break;
          }
          case 6: {
              printf("\nRelatório de Especialidades:\n");
              printf("\n=======================\n\n");
              printf("Cardiologista: %d\n", cardiologista);
              printf("Oftalmologista: %d\n", oftalmologista);
              printf("Alergista: %d\n", alergista);
              printf("Dermatologista: %d\n", dermatologista);
              printf("\n=======================\n\n");
              break;
          }
          case 0: {
              configs_destruir(tad_configs);
              fechar_fila(fila);
              printf("Até a próxima!\n");
              break;
          }
          default: {
              printf("Opção inválida!\n");
              break;
          }
      }
  } while (op != 0);
  return 0;
}
