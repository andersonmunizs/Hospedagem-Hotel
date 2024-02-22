//funcoesReservas.c
#include <stdio.h>
#include "string.h"
#include "funcoesReservas.h"

#define MAX_RESERVAS 100

Reserva reservas[MAX_RESERVAS];
int quantidade_reservas = 0;

void salvarReservas() {
    FILE *arquivo = fopen("reservas.csv", "w");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        return;
    }

    fprintf(arquivo, "ID Reserva, CPF Cliente, Check-in (dd mm aaaa), Check-out (dd mm aaaa), Tipo Quarto, ID Quarto\n");
    for (int i = 0; i < quantidade_reservas; i++) {
        fprintf(arquivo, "%d, %s, %02d %02d %04d, %02d %02d %04d, %s, %d\n",
                reservas[i].id_reserva, reservas[i].cpf_cliente,
                reservas[i].dia_checkin, reservas[i].mes_checkin, reservas[i].ano_checkin,
                reservas[i].dia_checkout, reservas[i].mes_checkout, reservas[i].ano_checkout,
                reservas[i].tipo_quarto, reservas[i].id_quarto);
    }

    fclose(arquivo);
}

void carregarReservas() {
    FILE *arquivo = fopen("reservas.csv", "r");
    if (arquivo == NULL) {
        printf("Arquivo de reservas não encontrado. Criando novo arquivo.\n");
        return;
    }

    char linha[256];
    fgets(linha, sizeof(linha), arquivo); // Ignorar o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d, %13[^,], %d %d %d, %d %d %d, %9[^,], %d",
               &reservas[quantidade_reservas].id_reserva, reservas[quantidade_reservas].cpf_cliente,
               &reservas[quantidade_reservas].dia_checkin, &reservas[quantidade_reservas].mes_checkin,
               &reservas[quantidade_reservas].ano_checkin, &reservas[quantidade_reservas].dia_checkout,
               &reservas[quantidade_reservas].mes_checkout, &reservas[quantidade_reservas].ano_checkout,
               reservas[quantidade_reservas].tipo_quarto, &reservas[quantidade_reservas].id_quarto);
        quantidade_reservas++;
    }

    fclose(arquivo);
}

void cadastrarReserva() {
    if (quantidade_reservas >= MAX_RESERVAS) {
        printf("Limite de reservas atingido. Não é possível cadastrar mais reservas.\n");
        return;
    }

    Reserva nova_reserva;
    printf("ID da reserva: ");
    scanf("%d", &nova_reserva.id_reserva);
    printf("CPF do cliente (formato xxx.xxx.xxx-xx): ");
    scanf("%13s", nova_reserva.cpf_cliente);
    printf("Data de Check-in (dd mm aaaa): ");
    scanf("%d %d %d", &nova_reserva.dia_checkin, &nova_reserva.mes_checkin, &nova_reserva.ano_checkin);
    printf("Data de Check-out (dd mm aaaa): ");
    scanf("%d %d %d", &nova_reserva.dia_checkout, &nova_reserva.mes_checkout, &nova_reserva.ano_checkout);
    printf("Tipo de quarto (Single, Duplo, Triplo): ");
    scanf("%9s", nova_reserva.tipo_quarto);
    printf("ID do quarto: ");
    scanf("%d", &nova_reserva.id_quarto);

    reservas[quantidade_reservas] = nova_reserva;
    quantidade_reservas++;

    salvarReservas();
}

void alterarReserva() {
    int id;
    int posicao = -1;

    printf("Digite o ID da reserva que deseja alterar: ");
    scanf("%d", &id);

    // Encontra a posição da reserva com o ID especificado
    for (int i = 0; i < quantidade_reservas; i++) {
        if (reservas[i].id_reserva == id) {
            posicao = i;
            break;
        }
    }

    // Se a reserva for encontrada
    if (posicao != -1) {
        printf("Novo CPF do cliente (formato xxx.xxx.xxx-xx): ");
        scanf("%13s", reservas[posicao].cpf_cliente);
        printf("Nova data de Check-in (dd mm aaaa): ");
        scanf("%d %d %d", &reservas[posicao].dia_checkin, &reservas[posicao].mes_checkin,
              &reservas[posicao].ano_checkin);
        printf("Nova data de Check-out (dd mm aaaa): ");
        scanf("%d %d %d", &reservas[posicao].dia_checkout, &reservas[posicao].mes_checkout,
              &reservas[posicao].ano_checkout);
        printf("Novo tipo de quarto (Single, Duplo, Triplo): ");
        scanf("%9s", reservas[posicao].tipo_quarto);
        printf("Novo ID do quarto: ");
        scanf("%d", &reservas[posicao].id_quarto);

        salvarReservas();
        printf("Reserva alterada com sucesso.\n");
    } else {
        printf("Reserva com o ID %d não encontrada.\n", id);
    }
}

void cancelarReservaPorId(int id);
void cancelarReservaPorClienteEData(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin);

void excluirReserva() {
    int opcao;
    printf("Como deseja encontrar a reserva a ser cancelada?\n");
    printf("1. Utilizando o código da reserva\n");
    printf("2. Utilizando o CPF do cliente e a data de check-in\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int id;
            printf("Digite o ID da reserva que deseja excluir: ");
            scanf("%d", &id);
            cancelarReservaPorId(id);
            break;
        }
        case 2: {
            char cpf[14];
            int dia_checkin, mes_checkin, ano_checkin;
            printf("Digite o CPF do cliente: ");
            scanf("%13s", cpf);
            printf("Digite a data de Check-in (dd mm aaaa): ");
            scanf("%d %d %d", &dia_checkin, &mes_checkin, &ano_checkin);
            cancelarReservaPorClienteEData(cpf, dia_checkin, mes_checkin, ano_checkin);
            break;
        }
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void cancelarReservaPorId(int id) {
    int posicao = -1;

    // Encontra a posição da reserva com o ID especificado
    for (int i = 0; i < quantidade_reservas; i++) {
        if (reservas[i].id_reserva == id) {
            posicao = i;
            break;
        }
    }

    // Se a reserva for encontrada
    if (posicao != -1) {
        // Move os elementos subsequentes para o índice atual
        for (int i = posicao; i < quantidade_reservas - 1; i++) {
            reservas[i] = reservas[i + 1];
        }
        quantidade_reservas--;

        salvarReservas();
        printf("Reserva com o ID %d excluída com sucesso.\n", id);
    } else {
        printf("Reserva com o ID %d não encontrada.\n", id);
    }
}

void cancelarReservaPorClienteEData(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin) {
    int posicao = -1;

    // Encontra a posição da reserva com o CPF do cliente e a data de check-in especificados
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].cpf_cliente, cpf) == 0 &&
            reservas[i].dia_checkin == dia_checkin &&
            reservas[i].mes_checkin == mes_checkin &&
            reservas[i].ano_checkin == ano_checkin) {
            posicao = i;
            break;
        }
    }

    // Se a reserva for encontrada
    if (posicao != -1) {
        // Move os elementos subsequentes para o índice atual
        for (int i = posicao; i < quantidade_reservas - 1; i++) {
            reservas[i] = reservas[i + 1];
        }
        quantidade_reservas--;

        salvarReservas();
        printf("Reserva do cliente com CPF %s para a data de check-in %02d/%02d/%04d excluída com sucesso.\n", cpf, dia_checkin, mes_checkin, ano_checkin);
    } else {
        printf("Reserva do cliente com CPF %s para a data de check-in %02d/%02d/%04d não encontrada.\n", cpf, dia_checkin, mes_checkin, ano_checkin);
    }
}

void consultarReservasCliente(const char *cpf) {
    printf("Reservas associadas ao cliente com CPF %s:\n", cpf);
    int encontradas = 0;
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].cpf_cliente, cpf) == 0) {
            printf("ID da Reserva: %d\n", reservas[i].id_reserva);
            printf("Check-in: %02d/%02d/%04d\n", reservas[i].dia_checkin, reservas[i].mes_checkin, reservas[i].ano_checkin);
            printf("Check-out: %02d/%02d/%04d\n", reservas[i].dia_checkout, reservas[i].mes_checkout, reservas[i].ano_checkout);
            printf("Tipo de Quarto: %s\n", reservas[i].tipo_quarto);
            printf("ID do Quarto: %d\n", reservas[i].id_quarto);
            printf("\n");
            encontradas++;
        }
    }
    if (encontradas == 0) {
        printf("Nenhuma reserva encontrada para o cliente com CPF %s.\n", cpf);
    }
}

void verificarDisponibilidadeQuarto(const char *tipo_quarto, int dia_checkin, int mes_checkin, int ano_checkin, int dia_checkout, int mes_checkout, int ano_checkout) {
    printf("Verificando disponibilidade de quartos do tipo %s para o período de %02d/%02d/%04d a %02d/%02d/%04d:\n", tipo_quarto, dia_checkin, mes_checkin, ano_checkin, dia_checkout, mes_checkout, ano_checkout);
    int disponiveis = 0;
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].tipo_quarto, tipo_quarto) == 0) {
            if (reservas[i].ano_checkout < ano_checkin ||
                (reservas[i].ano_checkout == ano_checkin && reservas[i].mes_checkout < mes_checkin) ||
                (reservas[i].ano_checkout == ano_checkin && reservas[i].mes_checkout == mes_checkin && reservas[i].dia_checkout <= dia_checkin)) {
                printf("Quarto disponível: ID %d\n", reservas[i].id_quarto);
                disponiveis++;
            } else if (reservas[i].ano_checkin > ano_checkout ||
                       (reservas[i].ano_checkin == ano_checkout && reservas[i].mes_checkin > mes_checkout) ||
                       (reservas[i].ano_checkin == ano_checkout && reservas[i].mes_checkin == mes_checkout && reservas[i].dia_checkin >= dia_checkout)) {
                printf("Quarto disponível: ID %d\n", reservas[i].id_quarto);
                disponiveis++;
            }
        }
    }
    if (disponiveis == 0) {
        printf("Nenhum quarto do tipo %s disponível para o período especificado.\n", tipo_quarto);
    }
}

int proximoCodigoReserva = 1; // Variável para controlar o próximo código de reserva
