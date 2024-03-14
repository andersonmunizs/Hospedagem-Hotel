#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "funcoesClientes.h"

#define MAX_CLIENTES 100

Cliente clientes[MAX_CLIENTES];
int quantidade_clientes = 0;

void salvarClientes() {
    FILE *arquivo = fopen("Clientes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    // Escreve os dados dos clientes
    for (int i = 0; i < quantidade_clientes; i++) {
        fprintf(arquivo, "%s,%s,%02d/%02d/%04d,%s,%s,%s\n",
                clientes[i].cpf, clientes[i].nome, clientes[i].dataNascimento.dia,
                clientes[i].dataNascimento.mes, clientes[i].dataNascimento.ano,
                clientes[i].endereco, clientes[i].cidade, clientes[i].estado);
    }

    fclose(arquivo);
}

void carregarClientes() {
    FILE *arquivo = fopen("Clientes.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo Clientes.csv não encontrado. Criando novo arquivo.\n");
        return;
    }

    char linha[256];
    //fgets(linha, sizeof(linha), arquivo); // Ignorar o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        char *campos;
        const char delimiter[2] = ","; // Delimitador utilizado no arquivo CSV
        campos = strtok(linha, delimiter);

        int campoAtual = 0;
        Cliente novoCliente;

        while (campos != NULL) {
            // Remover espaços extras antes e depois de cada campo
            char campoTrim[strlen(campos) + 1];
            sscanf(campos, " %s ", campoTrim);

            switch (campoAtual) {
                case CPF_CLI:
                    strcpy(novoCliente.cpf, campoTrim);
                    break;
                case NOME_CLI:
                    strcpy(novoCliente.nome, campoTrim);
                    break;
                case DATA_NASC_CLI:
                    sscanf(campoTrim, "%d/%d/%d", &novoCliente.dataNascimento.dia, &novoCliente.dataNascimento.mes, &novoCliente.dataNascimento.ano);
                    break;
                case ENDERECO_CLI:
                    strcpy(novoCliente.endereco, campoTrim);
                    break;
                case CIDADE_CLI:
                    strcpy(novoCliente.cidade, campoTrim);
                    break;
                case ESTADO_CLI:
                    strcpy(novoCliente.estado, campoTrim);
                    break;
                default:
                    break;
            }
            campos = strtok(NULL, delimiter);
            campoAtual++;
        }
        clientes[quantidade_clientes] = novoCliente;
        quantidade_clientes++;
    }

    fclose(arquivo);
}

void cadastrarCliente() {
    if (quantidade_clientes >= MAX_CLIENTES) {
        printf("Limite máximo de clientes atingido.\n");
        return;
    }

    Cliente novoCliente;

    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]s", novoCliente.cpf);

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novoCliente.nome);

    printf("Digite a data de nascimento do cliente (formato: DD/MM/AAAA): ");
    scanf("%d/%d/%d", &novoCliente.dataNascimento.dia, &novoCliente.dataNascimento.mes, &novoCliente.dataNascimento.ano);

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", novoCliente.endereco);

    printf("Digite a cidade do cliente: ");
    scanf(" %[^\n]", novoCliente.cidade);

    printf("Digite o estado do cliente: ");
    scanf("%s", novoCliente.estado);

    clientes[quantidade_clientes] = novoCliente;
    quantidade_clientes++;

    salvarClientes();
}

void alterarCliente() {
    char cpf[20];
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf("%s", cpf);

    // Remove pontos e traços do CPF digitado
    char cpfLimpo[20];
    int j = 0;
    for (int i = 0; cpf[i] != '\0'; i++) {
        if (cpf[i] >= '0' && cpf[i] <= '9') {
            cpfLimpo[j++] = cpf[i];
        }
    }
    cpfLimpo[j] = '\0';

    for (int i = 0; i < quantidade_clientes; i++) {
        // Remove pontos e traços do CPF armazenado
        char cpfClienteLimpo[20];
        int k = 0;
        for (int l = 0; clientes[i].cpf[l] != '\0'; l++) {
            if (clientes[i].cpf[l] >= '0' && clientes[i].cpf[l] <= '9') {
                cpfClienteLimpo[k++] = clientes[i].cpf[l];
            }
        }
        cpfClienteLimpo[k] = '\0';

        if (strcmp(cpfClienteLimpo, cpfLimpo) == 0) {
            printf("Digite o novo nome do cliente: ");
            scanf(" %[^\n]", clientes[i].nome);

            printf("Digite a nova data de nascimento do cliente (formato: DD/MM/AAAA): ");
            scanf("%d/%d/%d", &clientes[i].dataNascimento.dia, &clientes[i].dataNascimento.mes, &clientes[i].dataNascimento.ano);

            printf("Digite o novo endereco do cliente: ");
            scanf(" %[^\n]", clientes[i].endereco);

            printf("Digite a nova cidade do cliente: ");
            scanf(" %[^\n]", clientes[i].cidade);

            printf("Digite o novo estado do cliente: ");
            scanf("%s", clientes[i].estado);

            salvarClientes();
            printf("Cliente alterado com sucesso.\n");
            return;
        }
    }
    printf("Cliente com CPF %s não encontrado.\n", cpf);
}

void excluirCliente() {
    char cpf[20];
    printf("Digite o CPF do cliente que deseja excluir: ");
    scanf("%s", cpf);

    for (int i = 0; i < quantidade_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            for (int j = i; j < quantidade_clientes - 1; j++) {
                clientes[j] = clientes[j + 1];
            }
            quantidade_clientes--;

            salvarClientes();
            printf("Cliente excluído com sucesso.\n");
            return;
        }
    }
    printf("Cliente com CPF %s não encontrado.\n", cpf);
}