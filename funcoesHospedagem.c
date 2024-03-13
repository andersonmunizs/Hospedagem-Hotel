// hospedagem.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesHospedagem.h"

// Função para iniciar a hospedagem de um cliente a partir do código da reserva
void iniciar_hospedagem() {
    int codigo_reserva;
    printf("Digite o código da reserva para iniciar a hospedagem: ");
    scanf("%d", &codigo_reserva);

    // Abrir o arquivo de reservas em modo de leitura
    FILE *arquivo_reservas = fopen("reservas.csv", "r");
    if (arquivo_reservas == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        exit(1);
    }

    // Procurar pelo código de reserva no arquivo de reservas
    int encontrado = 0;
    char linha[100];
    while (fgets(linha, sizeof(linha), arquivo_reservas) != NULL) {
        // Ignorar a primeira linha (cabeçalho)
        if (strstr(linha, "ID Reserva") != NULL) {
            continue;
        }

        // Extrair o código de reserva da linha
        char *token = strtok(linha, ",");
        int codigo = atoi(token);

        // Se o código de reserva encontrado for igual ao código fornecido, marcar como encontrado
        if (codigo == codigo_reserva) {
            encontrado = 1;
            break;
        }
    }

    // Fechar o arquivo de reservas
    fclose(arquivo_reservas);

    // Se o código de reserva não foi encontrado, exibir mensagem de erro e sair da função
    if (!encontrado) {
        printf("Hospedagem com código de reserva %d não encontrada.\n", codigo_reserva);
        return;
    }

    // Abrir o arquivo de hospedagens em modo de leitura e escrita
    FILE *arquivo_hospedagens = fopen("hospedagens.csv", "a");
    if (arquivo_hospedagens == NULL) {
        printf("Erro ao abrir o arquivo de hospedagens.\n");
        exit(1);
    }

    // Obter a data atual
    time_t tempo_agora;
    time(&tempo_agora);
    struct tm *info_tempo;
    info_tempo = localtime(&tempo_agora);
    char data_checkin[11];
    strftime(data_checkin, sizeof(data_checkin), "%d/%m/%Y", info_tempo);

    // Escrever a nova hospedagem no arquivo
    fprintf(arquivo_hospedagens, "%d,%s,Ativa\n", codigo_reserva, data_checkin);

    // Fechar o arquivo de hospedagens
    fclose(arquivo_hospedagens);

    printf("Iniciando hospedagem para reserva de código: %d\n", codigo_reserva);
}


void carregarHospedagens() {
    FILE *arquivo;
    arquivo = fopen("hospedagens.csv", "r");

    if (arquivo == NULL) {
        printf("O arquivo hospedagens.csv não existe. Criando...\n");
        arquivo = fopen("hospedagens.csv", "w");
        if (arquivo == NULL) {
            printf("Erro ao criar o arquivo hospedagens.csv\n");
            exit(1);
        }
        fprintf(arquivo, "codigo_reserva,data_checkin,quarto,status\n");
        fclose(arquivo);
        printf("Arquivo hospedagens.csv criado com sucesso.\n");
    } else {
        fclose(arquivo);
        printf("O arquivo hospedagens.csv já existe.\n");
    }
}
