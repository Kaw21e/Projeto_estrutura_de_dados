#include "salvar_pacientes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FILA_FILE "../fila.dat"


Paciente *criar_paciente(int numero, char nome[], int idade, PrioridadePaciente prioridade, especialidade medico){ //função para usar no menu.c
    Paciente *paciente = malloc(sizeof(Paciente));
    if (!paciente) {
        return NULL; // Erro ao alocar memória
    }
    paciente->numero = numero;
    strcpy(paciente->nome, nome);
    paciente->idade = idade;
    paciente->medico = medico;
    paciente->prioridade = prioridade;

    return paciente;
}

int salvar_pacientes(Paciente *paciente){ //função para usar no menu.c
    FILE *arquivo = fila_abrir();
    if (!arquivo) {
        return -1; // Erro ao abrir o arquivo
    }
    // Escreve o paciente no arquivo
    fseek(arquivo, 0, SEEK_END); // Move o ponteiro para o final do arquivo
    fwrite(paciente, sizeof(Paciente), 1, arquivo); // Grava o paciente no arquivo
    
    fclose(arquivo);
    free(paciente); // Libera a memória alocada para o paciente
    return 0; // Sucesso

}

FILE *fila_abrir() {
    FILE *arquivo;
    if( access(FILA_FILE, F_OK ) != -1 ) { // arquivo já existe
        arquivo = fopen(FILA_FILE, "rb+"); // apenas abre o arquivo
    } else {
        arquivo = fopen(FILA_FILE, "wb+"); // cria arquivo novo
    }
    return arquivo;
}

Paciente *ler_paciente_por_numero(int numero) { //função para usar no simulacao.c
    FILE *arquivo = fila_abrir();
    if (!arquivo) {
        return NULL; // Erro ao abrir o arquivo
    }
    // Move o ponteiro para o paciente desejado
    if (fseek(arquivo, numero * sizeof(Paciente), SEEK_SET) != 0) {
        fclose(arquivo);
        return NULL; // Erro ao posicionar
    }
    Paciente *paciente = malloc(sizeof(Paciente));
    if (!paciente) {
        fclose(arquivo);
        return NULL; // Erro de memória
    }
    int debug;
    debug = fread(paciente, sizeof(Paciente), 1, arquivo);
    fclose(arquivo);
    if (debug != 1) {
        free(paciente);
        return NULL; // Não foi possível ler
    }
    return paciente;
}

FILE *reiniciar_fila() {
    FILE *arquivo = fopen(FILA_FILE, "wb+"); // Cria ou limpa o arquivo
    if (!arquivo) {
        return NULL; // Erro ao abrir o arquivo
    }
    return arquivo;
}

void fechar_fila(FILE *arquivo) {
    if (arquivo) {
        fclose(arquivo); // Fecha o arquivo
    }
}