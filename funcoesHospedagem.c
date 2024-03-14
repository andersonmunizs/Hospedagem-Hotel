//funcoesHospedagem.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesHospedagem.h"


#define MAX_BUFFER_SIZE 256

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

        if (codigo == codigo_reserva) {
            encontrado = 1;
            break;
        }
    }

    fclose(arquivo_reservas);


    if (!encontrado) {
        printf("Hospedagem com código de reserva %d não encontrada.\n", codigo_reserva);
        return;
    }


    FILE *arquivo_hospedagens = fopen("hospedagens.csv", "a");
    if (arquivo_hospedagens == NULL) {
        printf("Erro ao abrir o arquivo de hospedagens.\n");
        exit(1);
    }

    //Obter a data atual
    time_t tempo_agora;
    time(&tempo_agora);
    struct tm *info_tempo;
    info_tempo = localtime(&tempo_agora);
    char data_checkin[11];
    strftime(data_checkin, sizeof(data_checkin), "%d/%m/%Y", info_tempo);


    fprintf(arquivo_hospedagens, "%d,%s,Ativa\n", codigo_reserva, data_checkin);


    fclose(arquivo_hospedagens);

    printf("Iniciando hospedagem para reserva de código: %d\n", codigo_reserva);
}


void carregarHospedagens() {
    FILE *arquivo = fopen("hospedagens.csv", "r");
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
        char linha[100];
        // Ignorar o cabeçalho
        fgets(linha, sizeof(linha), arquivo);
        // Ler o restante das linhas
        while (fgets(linha, sizeof(linha), arquivo) != NULL) {
            int codigo_reserva;
            char data_checkin[11];
            char quarto[10];
            char status[8];
            // Ler os valores da linha para as variáveis correspondentes
            sscanf(linha, "%d,%10[^,],%10[^,],%7s", &codigo_reserva, data_checkin, quarto, status);
        }
        fclose(arquivo);
        printf("O arquivo hospedagens.csv já existe.\n");
    }
}

void finalizar_hospedagem() {
    FILE *arquivo_hospedagens = fopen("hospedagens.csv", "r+");
    if (arquivo_hospedagens == NULL) {
        printf("Erro ao abrir o arquivo de hospedagens.\n");
        exit(1);
    }

    int opcao;
    printf("Escolha a opção para finalizar a hospedagem:\n");
    printf("1. [INDISPONIVEL]Pelo código do quarto\n");
    printf("2. [INDISPONIVEL]Pelo código da reserva\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        // Implementação para finalizar hospedagem pelo número do quarto
    } else if (opcao == 2) {
        int codigo_reserva;
        printf("Digite o código da reserva: ");
        scanf("%d", &codigo_reserva);

        char linha[MAX_BUFFER_SIZE];
        char temp_data_checkin[11], temp_quarto[10], temp_status[20];
        int temp_codigo_reserva;

        // Procurar hospedagem pelo código da reserva
        while (fgets(linha, sizeof(linha), arquivo_hospedagens) != NULL) {
            sscanf(linha, "%d,%10[^,],%10[^,],%19[^,]", &temp_codigo_reserva, temp_data_checkin, temp_quarto, temp_status);

            if (temp_codigo_reserva == codigo_reserva && strcmp(temp_status, "Ativa") == 0) {
                // Encontrou a hospedagem ativa com o código de reserva especificado
                printf("Hospedagem encontrada para o código de reserva %d.\n", codigo_reserva);

                // Faça o que for necessário com os dados da hospedagem

                break;
            }
        }
    } else {
        printf("Opção inválida.\n");
    }

    fclose(arquivo_hospedagens);
}


float calcular_valor_total_hospedagem(char *tipo_quarto, char *data_checkin) {
    float preco_diaria = 100.0;
    int numero_dias = 5;
    float valor_total = preco_diaria * numero_dias;

    return valor_total;
}