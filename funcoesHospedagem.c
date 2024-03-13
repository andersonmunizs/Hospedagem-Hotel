//funcoesHospedagem.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesHospedagem.h"
#include "funcoesQuartos.h"
#include "tempo.h"

int codigo_reserva_global = 0;

void iniciar_hospedagem() {
    int codigo_reserva;
    printf("Digite o código da reserva para iniciar a hospedagem: ");
    scanf("%d", &codigo_reserva);
    codigo_reserva_global = codigo_reserva;

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
            // Exibir a hospedagem para fins de depuração
            printf("Reserva encontrada: %d, %s, %s, %s\n", codigo_reserva, data_checkin, quarto, status);
            // Agora você pode fazer o que quiser com os dados da hospedagem, como armazená-los em um array
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
    printf("1. Pelo código do quarto\n");
    printf("2. Pelo código da reserva\n");
    printf("Opção: ");
    scanf("%d", &opcao);

    if (opcao == 1) {
        // Código para finalizar a hospedagem pelo número do quarto

    } else if (opcao == 2) {
        int codigo_reserva;
        printf("Digite o código da reserva: ");
        scanf("%d", &codigo_reserva);

        codigo_reserva_global = codigo_reserva;

        // Procurar hospedagem pelo código da reserva
        Hospedagem hospedagem;
        int encontrou = 0;
        while (fread(&hospedagem, sizeof(Hospedagem), 1, arquivo_hospedagens)) {
            if (hospedagem.codigo_reserva == codigo_reserva && strcmp(hospedagem.status, "Ativa") == 0) {
                encontrou = 1;
                break;
            }
        }

        if (encontrou) {
            Quarto quarto = obterQuartoPorNumero(hospedagem.id_quarto);
            if (quarto.preco_diaria == 0) {
                printf("Valor da diária não encontrado para o quarto especificado.\n");
                return;
            }
            DATA data_checkin_obj;
            sscanf(hospedagem.data_checkin, "%d/%d/%d", &data_checkin_obj.dia, &data_checkin_obj.mes, &data_checkin_obj.ano);
            DATA data_checkout_obj;
            time_t rawtime;
            struct tm *timeinfo;
            time(&rawtime);
            timeinfo = localtime(&rawtime);
            data_checkout_obj.dia = timeinfo->tm_mday;
            data_checkout_obj.mes = timeinfo->tm_mon + 1;
            data_checkout_obj.ano = timeinfo->tm_year + 1900;
            int numero_dias = calcularNumeroDias(data_checkin_obj, data_checkout_obj);
            float valor_total = quarto.preco_diaria * numero_dias;

            //Armazenar a data de check-out na hospedagem
            strftime(hospedagem.data_checkout, sizeof(hospedagem.data_checkout), "%d/%m/%Y", timeinfo);

            //Atualizar o status da hospedagem para "finalizada"
            strcpy(hospedagem.status, "Finalizada");

            //Voltar ao início do registro para sobrescrevê-lo no arquivo
            fseek(arquivo_hospedagens, -sizeof(Hospedagem), SEEK_CUR);
            fwrite(&hospedagem, sizeof(Hospedagem), 1, arquivo_hospedagens);

            printf("Hospedagem finalizada com sucesso. Valor total: %.2f\n", valor_total);
        } else {
            printf("Nenhuma hospedagem ativa encontrada para o código de reserva especificado.\n");
        }
    } else {
        printf("Opção inválida.\n");
    }

    fclose(arquivo_hospedagens);
}