#include <stdio.h>
#include "funcoesQuartos.h"

#define MAX_QUARTOS 100

Quarto quartos[MAX_QUARTOS];
int quantidade_quartos = 0;

void salvarQuartos() {
    FILE *arquivo = fopen("Quartos.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    fprintf(arquivo, "ID, Camas Solteiro, Camas Casal, Tipo Quarto, Preço Diária, Status\n");
    for (int i = 0; i < quantidade_quartos; i++) {
        fprintf(arquivo, "%d, %d, %d, %s, %.2lf, %s\n",
                quartos[i].id_quarto, quartos[i].camas_solteiro, quartos[i].camas_casal,
                quartos[i].tipo_quarto, quartos[i].preco_diaria, quartos[i].status);
    }

    fclose(arquivo);
}

void carregarQuartos() {
    FILE *arquivo = fopen("Quartos.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo Quartos.csv não encontrado. Criando novo arquivo.\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Ignorar o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d, %d, %d, %9[^,], %lf, %3s",
               &quartos[quantidade_quartos].id_quarto, &quartos[quantidade_quartos].camas_solteiro,
               &quartos[quantidade_quartos].camas_casal, quartos[quantidade_quartos].tipo_quarto,
               &quartos[quantidade_quartos].preco_diaria, quartos[quantidade_quartos].status);
        quantidade_quartos++;
    }

    fclose(arquivo);
}


void cadastrarQuarto() {
    if (quantidade_quartos >= MAX_QUARTOS) {
        printf("Limite de quartos atingido. Não é possível cadastrar mais quartos.\n");
        return;
    }

    Quarto novo_quarto;
    printf("ID do quarto: ");
    scanf("%d", &novo_quarto.id_quarto);
    printf("Número de camas de solteiro: ");
    scanf("%d", &novo_quarto.camas_solteiro);
    printf("Número de camas de casal: ");
    scanf("%d", &novo_quarto.camas_casal);
    printf("Tipo de quarto (Single, Duplo, Triplo): ");
    scanf("%s", novo_quarto.tipo_quarto);
    printf("Preço da diária: ");
    scanf("%lf", &novo_quarto.preco_diaria);
    printf("Status (Disponível ou Indisponível): ");
    scanf("%s", novo_quarto.status);

    quartos[quantidade_quartos] = novo_quarto;
    quantidade_quartos++;

    salvarQuartos();
}

void alterarQuarto() {
    int id;
    int posicao = -1;

    printf("Digite o ID do quarto que deseja alterar: ");
    scanf("%d", &id);

    // Encontra a posição do quarto com o ID especificado
    for (int i = 0; i < quantidade_quartos; i++) {
        if (quartos[i].id_quarto == id) {
            posicao = i;
            break;
        }
    }

    // Se o quarto for encontrado
    if (posicao != -1) {
        printf("Novo número de camas de solteiro: ");
        scanf("%d", &quartos[posicao].camas_solteiro);
        printf("Novo número de camas de casal: ");
        scanf("%d", &quartos[posicao].camas_casal);
        printf("Novo tipo de quarto (Single, Duplo, Triplo): ");
        scanf("%s", quartos[posicao].tipo_quarto);
        printf("Novo preço da diária: ");
        scanf("%lf", &quartos[posicao].preco_diaria);
        printf("Novo status (Disponível ou Indisponível");
        scanf("%s", quartos[posicao].status);

        salvarQuartos();
        printf("Quarto alterado com sucesso.\n");
    } else {
        printf("Quarto com o ID %d não encontrado.\n", id);
    }
}

void excluirQuarto() {
    int id;
    int posicao = -1;

    printf("Digite o ID do quarto que deseja excluir: ");
    scanf("%d", &id);

    // Encontra a posição do quarto com o ID especificado
    for (int i = 0; i < quantidade_quartos; i++) {
        if (quartos[i].id_quarto == id) {
            posicao = i;
            break;
        }
    }

    // Se o quarto for encontrado
    if (posicao != -1) {
        // Move os elementos subsequentes para o índice atual
        for (int i = posicao; i < quantidade_quartos - 1; i++) {
            quartos[i] = quartos[i + 1];
        }
        quantidade_quartos--;

        salvarQuartos();
        printf("Quarto excluído com sucesso.\n");
    } else {
        printf("Quarto com o ID %d não encontrado.\n", id);
    }
}
