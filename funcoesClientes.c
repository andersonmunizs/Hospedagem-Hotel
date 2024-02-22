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
        fprintf(arquivo, "%s, %s, %02d %02d %04d, %d, %s, %s, %s\n",
                clientes[i].cpf, clientes[i].nome, clientes[i].dia_nascimento,
                clientes[i].mes_nascimento, clientes[i].ano_nascimento, clientes[i].idade,
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
        sscanf(linha, "%13[^,], %50[^,], %d %d %d, %d, %100[^,], %100[^,], %3s",
               clientes[quantidade_clientes].cpf, clientes[quantidade_clientes].nome,
               &clientes[quantidade_clientes].dia_nascimento, &clientes[quantidade_clientes].mes_nascimento,
               &clientes[quantidade_clientes].ano_nascimento, &clientes[quantidade_clientes].idade,
               clientes[quantidade_clientes].endereco, clientes[quantidade_clientes].cidade,
               clientes[quantidade_clientes].estado);
        quantidade_clientes++;
    }

    fclose(arquivo);
}

void cadastrarCliente() {
    if (quantidade_clientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido. Não é possível cadastrar mais clientes.\n");
        return;
    }

    Cliente novo_cliente;
    printf("CPF do cliente (formato xxx.xxx.xxx-xx): ");
    scanf("%13s", novo_cliente.cpf);
    printf("Nome do cliente: ");
    scanf("%50s", novo_cliente.nome);
    printf("Data de Nascimento (dd mm aaaa): ");
    scanf("%d %d %d", &novo_cliente.dia_nascimento, &novo_cliente.mes_nascimento,
          &novo_cliente.ano_nascimento);
    printf("Idade do cliente: ");
    scanf("%d", &novo_cliente.idade);
    printf("Endereço do cliente: ");
    scanf("%100s", novo_cliente.endereco);
    printf("Cidade do cliente: ");
    scanf("%100s", novo_cliente.cidade);
    printf("Estado do cliente (sigla de 2 caracteres): ");
    scanf("%3s", novo_cliente.estado);

    clientes[quantidade_clientes] = novo_cliente;
    quantidade_clientes++;

    salvarClientes();
}

void alterarCliente() {
    char cpf[14];
    int posicao = -1;

    printf("Digite o CPF do cliente que deseja alterar (formato xxx.xxx.xxx-xx): ");
    scanf("%13s", cpf);

    // Encontra a posição do cliente com o CPF especificado
    for (int i = 0; i < quantidade_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            posicao = i;
            break;
        }
    }

    // Se o cliente for encontrado
    if (posicao != -1) {
        printf("Novo nome do cliente: ");
        scanf("%50s", clientes[posicao].nome);
        printf("Nova data de nascimento (dd mm aaaa): ");
        scanf("%d %d %d", &clientes[posicao].dia_nascimento, &clientes[posicao].mes_nascimento,
              &clientes[posicao].ano_nascimento);
        printf("Nova idade do cliente: ");
        scanf("%d", &clientes[posicao].idade);
        printf("Novo endereço do cliente: ");
        scanf("%100s", clientes[posicao].endereco);
        printf("Nova cidade do cliente: ");
        scanf("%100s", clientes[posicao].cidade);
        printf("Novo estado do cliente (sigla de 2 caracteres): ");
        scanf("%3s", clientes[posicao].estado);

        salvarClientes();
        printf("Cliente alterado com sucesso.\n");
    } else {
        printf("Cliente com o CPF %s não encontrado.\n", cpf);
    }
}

void excluirCliente() {
    char cpf[14];
    int posicao = -1;

    printf("Digite o CPF do cliente que deseja excluir (formato xxx.xxx.xxx-xx): ");
    scanf("%13s", cpf);

    // Encontra a posição do cliente com o CPF especificado
    for (int i = 0; i < quantidade_clientes; i++) {
        if (strcmp(clientes[i].cpf, cpf) == 0) {
            posicao = i;
            break;
        }
    }

    // Se o cliente for encontrado
    if (posicao != -1) {
        // Move os elementos subsequentes para o índice atual
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
