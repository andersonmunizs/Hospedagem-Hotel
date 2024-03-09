//funcoesClientes.c
#include <stdio.h>
#include "string.h"
#include "funcoesClientes.h"


#define MAX_CLIENTES 100

Cliente clientes[MAX_CLIENTES];
int quantidade_clientes = 0;

void salvarClientes() {
    FILE *arquivo = fopen("Clientes.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "CPF, Nome, Data de Nascimento (dd mm aaaa), Idade, Endereço, Cidade, Estado\n");
    for (int i = 0; i < quantidade_clientes; i++) {
        fprintf(arquivo, "%s, %s, %02d/%02d/%04d, %d, %s, %s, %s\n",
                clientes[i].cpf, clientes[i].nome, clientes[i].dataNascimento.dia,
                clientes[i].dataNascimento.mes, clientes[i].dataNascimento.ano, clientes[i].idade,
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
        sscanf(linha, "%13[^,], %50[^,], %d/%d/%d, %d, %100[^,], %100[^,], %3s",
               clientes[quantidade_clientes].cpf, clientes[quantidade_clientes].nome,
               &clientes[quantidade_clientes].dataNascimento.dia, &clientes[quantidade_clientes].dataNascimento.mes,
               &clientes[quantidade_clientes].dataNascimento.ano, &clientes[quantidade_clientes].idade,
               clientes[quantidade_clientes].endereco, clientes[quantidade_clientes].cidade,
               clientes[quantidade_clientes].estado);
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

    // Receber dados do usuário para o novo cliente
    printf("Digite o CPF do cliente: ");
    scanf("%13s", novoCliente.cpf); // Usando %13s para limitar o número de caracteres

    // Limpar o buffer de entrada para remover o caractere de nova linha
    while (getchar() != '\n');

    printf("Digite o nome do cliente: ");
    scanf(" %[^\n]", novoCliente.nome);

    printf("Digite a data de nascimento do cliente (formato: DD/MM/AAAA): ");
    scanf("%d/%d/%d", &novoCliente.dataNascimento.dia, &novoCliente.dataNascimento.mes, &novoCliente.dataNascimento.ano);

    // Calcular a idade com base na data de nascimento fornecida
    DATA hojeData = hoje();
    novoCliente.idade = hojeData.ano - novoCliente.dataNascimento.ano;
    if (hojeData.mes < novoCliente.dataNascimento.mes || (hojeData.mes == novoCliente.dataNascimento.mes && hojeData.dia < novoCliente.dataNascimento.dia)) {
        novoCliente.idade--; // Ainda não fez aniversário este ano
    }

    printf("Digite o endereco do cliente: ");
    scanf(" %[^\n]", novoCliente.endereco);

    printf("Digite a cidade do cliente: ");
    scanf(" %[^\n]", novoCliente.cidade);

    printf("Digite o estado do cliente: ");
    scanf("%s", novoCliente.estado);

    // Escrever os dados do novo cliente no arquivo CSV
    fprintf(arquivo, "%s, %s, %02d/%02d/%04d, %d, %s, %s, %s\n",
            novoCliente.cpf, novoCliente.nome,
            novoCliente.dataNascimento.dia, novoCliente.dataNascimento.mes, novoCliente.dataNascimento.ano,
            novoCliente.idade,
            novoCliente.endereco, novoCliente.cidade, novoCliente.estado);

    fclose(arquivo);
}


void alterarCliente() {
    FILE *arquivo = fopen("clientes.csv", "r");
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
            scanf("%s", clienteExistente.nome);

            printf("Digite a nova data de nascimento do cliente (formato: DD/MM/AAAA): ");
            char dataNascimentoStr[11];
            scanf("%s", dataNascimentoStr);
            StringToData(dataNascimentoStr, &clienteExistente.dataNascimento);

            printf("Digite o novo endereco do cliente: ");
            scanf("%s", clienteExistente.endereco);

            printf("Digite a nova cidade do cliente: ");
            scanf("%s", clienteExistente.cidade);

            printf("Digite o novo estado do cliente: ");
            scanf("%s", clienteExistente.estado);

            // Escrever os novos dados no arquivo temporário
            fprintf(temp, "%s,%s,%d/%d/%d,%s,%s,%s\n", cpf, clienteExistente.nome,
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

    // Encontra a posição do cliente com o CPF especificado
    for (int i = 0; i < quantidade_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            posicao = i;
            break;
        }
    }

    // Se o cliente for encontrado
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