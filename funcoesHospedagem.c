// hospedagem.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesHospedagem.h"

int quantidadeHospedagens() {
    FILE *csv;
    char linha[1000];
    int contadorLinha = 0;
    csv = fopen("Hospedagens.csv", "r");
    if (csv != NULL) {
        fscanf(csv, " %[^\n]s", linha); // lendo o cabeçalho do arquivo
        while (fscanf(csv, " %[^\n]s", linha) != EOF) {
            contadorLinha++;
        }
        fclose(csv);
        return contadorLinha;
    } else {
        return 0; // arquivo não existe
    }
}

void carregarHospedagem(HOSPEDAGEM *lista) {
    FILE *csv;
    char linha[1000];
    char *campos;
    const char s[2] = ";";
    int contadorLinha = 0;
    csv = fopen("Hospedagens.csv", "r");
    if (csv != NULL) {
        fseek(csv, 0, SEEK_SET); // fim dos registros, reabrindo para ler os dados
        fscanf(csv, " %[^\n]s", linha); // lendo o cabeçalho do arquivo

        int i = 0;
        while (fscanf(csv, " %[^\n]s", linha) != EOF) {
            campos = strtok(linha, s); // separando os dados de uma linha
            int campoAtual = 0;
            while (campos != NULL) {
                switch (campoAtual) {
                    case IDRESERVA_HOSPEDAGEM:
                        lista[i].id = atoi(campos);
                        break;
                    case CPF_HOSPEDAGEM:
                        strcpy(lista[i].CPF, campos);
                        break;
                    case CHECKIN_HOSPEDAGEM:
                        StringToData(campos, &lista[i].checkin);
                        break;
                    case CHECKOUT_HOSPEDAGEM:
                        StringToData(campos, &lista[i].checkout);
                        break;
                    case STATUS_HOSPEDAGEM:
                        strcpy(lista[i].status, campos);
                        break;
                    case PRECOTOTAL_HOSPEDAGEM:
                        lista[i].precoTotal = atof(campos);
                        break;
                    default:
                        break;
                }
                campos = strtok(NULL, s);
                campoAtual++;
            }
            i++;
        }
        contadorLinha = i;
        fclose(csv);
    } else {
        printf("Erro - Arquivo Hospedagens.csv não encontrado\n");
    }
}

void exibirHospedagem(HOSPEDAGEM h) {
    char temp[12];
    printf("##################################### \n");
    printf("ID : %d\n", h.id);
    printf("------------------------------------- \n");
    printf("CPF: %s\n", h.CPF);
    printf("------------------------------------- \n");
    DataToString(h.checkin, temp, false);
    printf("Check in: %s\n", temp);
    printf("------------------------------------- \n");
    DataToString(h.checkout, temp, false);
    printf("Check out: %s\n", temp);
    printf("------------------------------------- \n");
    printf("Status: %s\n", h.status);
    printf("------------------------------------- \n");
    printf("Valor total: R$%.2f\n", h.precoTotal);
    printf("------------------------------------- \n");
    printf("##################################### \n");
}

