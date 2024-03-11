#include <stdio.h>
#include "string.h"
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

    // Ignorar o cabeçalho
    fscanf(arquivo, " %*[^\n]\n");

    while (fscanf(arquivo, "%d, %d, %d, %9[^,], %lf, %2s",
                  &quartos[quantidade_quartos].id_quarto, &quartos[quantidade_quartos].camas_solteiro,
                  &quartos[quantidade_quartos].camas_casal, quartos[quantidade_quartos].tipo_quarto,
                  &quartos[quantidade_quartos].preco_diaria, quartos[quantidade_quartos].status) == 6) {
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
    scanf(" %[^\n]", novo_quarto.tipo_quarto);
    printf("Preço da diária: ");
    scanf("%lf", &novo_quarto.preco_diaria);
    printf("Status: D = Disponivel, I = Indisponível): ");
    scanf(" %[^\n]", novo_quarto.status);

    quartos[quantidade_quartos] = novo_quarto;
    quantidade_quartos++;

    salvarQuartos();
}

void alterarQuarto() {
    int id;
    int posicao = -1;

    printf("Digite o ID do quarto que deseja alterar: ");
    scanf("%d", &id);

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
        scanf(" %[^\n]", quartos[posicao].tipo_quarto);
        printf("Novo preço da diária: ");
        scanf("%lf", &quartos[posicao].preco_diaria);
        printf("Novo status: D = Disponivel ou I = Indisponível): ");
        scanf(" %[^\n]", quartos[posicao].status);

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

    for (int i = 0; i < quantidade_quartos; i++) {
        if (quartos[i].id_quarto == id) {
            posicao = i;
            break;
        }
    }

    if (posicao != -1) {
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
