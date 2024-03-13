//funcoesClientes.c
#include <stdio.h>
#include "stdlib.h"
#include <string.h>
#include "stdbool.h"
#include "funcoesClientes.h"


#define MAX_CLIENTES 100

Cliente clientes[MAX_CLIENTES];
int quantidade_clientes = 0;

void salvarClientes() {
    FILE *arquivo = fopen("Clientes.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    // Verifica se o arquivo já existe e está vazio
    bool arquivoVazio = false;
    fseek(arquivo, 0, SEEK_END);
    if (ftell(arquivo) == 0) {
        arquivoVazio = true;
    }

    // Escreve o cabeçalho apenas se o arquivo estiver vazio
    if (arquivoVazio) {
        fprintf(arquivo, "CPF, Nome, Data de Nascimento, Endereço, Cidade, Estado\n");
    }

    // Escreve os dados dos clientes
    for (int i = 0; i < quantidade_clientes; i++) {
        fprintf(arquivo, "%s, %s, %02d/%02d/%04d, %s, %s, %s\n",
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
    fgets(linha, sizeof(linha), arquivo); // Ignorar o cabeçalho
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
    FILE *arquivo = fopen("Clientes.csv", "a");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    Cliente novoCliente;

    printf("Digite o CPF do cliente: ");
    scanf(" %[^\n]s", novoCliente.cpf);

    while (getchar() != '\n');

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

    // Escrever os dados do novo cliente no arquivo CSV
    fprintf(arquivo, "%s, %s, %02d/%02d/%04d, %s, %s, %s\n",
            novoCliente.cpf, novoCliente.nome,
            novoCliente.dataNascimento.dia, novoCliente.dataNascimento.mes, novoCliente.dataNascimento.ano,
            novoCliente.endereco, novoCliente.cidade, novoCliente.estado);

    fclose(arquivo);
}


void alterarCliente() {
    FILE *arquivo = fopen("Clientes.csv", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de clientes.\n");
        return;
    }

    FILE *temp = fopen("temp.csv", "w");
    if (temp == NULL) {
        printf("Erro ao criar o arquivo temporário.\n");
        fclose(arquivo);
        return;
    }

    Cliente clienteExistente;
    char cpf[14];
    printf("Digite o CPF do cliente que deseja alterar: ");
    scanf("%s", cpf);

    char linha[256];
    while (fgets(linha, sizeof(linha), arquivo)) {
        char tempCpf[14];
        sscanf(linha, "%[^,],", tempCpf);
        if (strcmp(tempCpf, cpf) == 0) {
            // Encontrou o cliente que deseja alterar

            // Receber novos dados do usuário
            printf("Digite o novo nome do cliente: ");
            scanf(" %[^\n]", clienteExistente.nome);

            printf("Digite a nova data de nascimento do cliente (formato: DD/MM/AAAA): ");
            char dataNascimentoStr[11];
            scanf("%s", dataNascimentoStr);
            StringToData(dataNascimentoStr, &clienteExistente.dataNascimento);

            printf("Digite o novo endereco do cliente: ");
            scanf(" %[^\n]", clienteExistente.endereco);

            printf("Digite a nova cidade do cliente: ");
            scanf(" %[^\n]", clienteExistente.cidade);

            printf("Digite o novo estado do cliente: ");
            scanf("%s", clienteExistente.estado);

            // Escrever os novos dados no arquivo temporário
            fprintf(temp, "%s, %s, %02d/%02d/%04d, %s, %s, %s\n", cpf, clienteExistente.nome,
                    clienteExistente.dataNascimento.dia, clienteExistente.dataNascimento.mes, clienteExistente.dataNascimento.ano,
                    clienteExistente.endereco, clienteExistente.cidade, clienteExistente.estado);
        } else {
            // Escrever a linha original no arquivo temporário
            fputs(linha, temp);
        }
    }

    fclose(arquivo);
    fclose(temp);

    // Substituir o arquivo original pelo temporário
    remove("Clientes.csv");
    rename("temp.csv", "Clientes.csv");
}

void excluirCliente() {
    char cpf[14];
    int posicao = -1;

    printf("Digite o CPF do cliente que deseja excluir (formato xxx.xxx.xxx-xx): ");
    scanf(" %[^\n]s", cpf);

    //Encontra a posição do cliente com o CPF especificado
    for (int i = 0; i < quantidade_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            posicao = i;
            break;
        }
    }

    //Se o cliente for encontrado
    if (posicao != -1) {
        for (int i = posicao; i < quantidade_clientes - 1; i++) {
            clientes[i] = clientes[i + 1];
        }
        quantidade_clientes--;

        salvarClientes();
        printf("Cliente excluído com sucesso.\n");
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpf);
    }
}