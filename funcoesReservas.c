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
        fprintf(arquivo, "%d, %s, %02d/%02d/%04d, %02d/%02d/%04d, %s, %d\n",
                reservas[i].id_reserva, reservas[i].cpf_cliente,
                reservas[i].checkin.dia, reservas[i].checkin.mes, reservas[i].checkin.ano,
                reservas[i].checkout.dia, reservas[i].checkout.mes, reservas[i].checkout.ano,
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
    fgets(linha, sizeof(linha), arquivo); //Ignorar o cabeçalho
    while (fgets(linha, sizeof(linha), arquivo)) {
        sscanf(linha, "%d, %13[^,], %d/%d/%d, %d/%d/%d, %9[^,], %d",
               &reservas[quantidade_reservas].id_reserva, reservas[quantidade_reservas].cpf_cliente,
               &reservas[quantidade_reservas].checkin.dia, &reservas[quantidade_reservas].checkin.mes,
               &reservas[quantidade_reservas].checkin.ano, &reservas[quantidade_reservas].checkout.dia,
               &reservas[quantidade_reservas].checkout.mes, &reservas[quantidade_reservas].checkout.ano,
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
    scanf(" %d", &nova_reserva.id_reserva);
    printf("CPF do cliente (formato xxx.xxx.xxx-xx): ");
    scanf(" %[^\n]s", nova_reserva.cpf_cliente);
    printf("Data de Check-in (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", &nova_reserva.checkin.dia, &nova_reserva.checkin.mes, &nova_reserva.checkin.ano);
    printf("Data de Check-out (dd/mm/aaaa): ");
    scanf(" %d/%d/%d", &nova_reserva.checkout.dia, &nova_reserva.checkout.mes, &nova_reserva.checkout.ano);
    printf("Tipo de quarto (Single, Duplo, Triplo): ");
    scanf(" %[^\n]s", nova_reserva.tipo_quarto);
    printf("ID do quarto: ");
    scanf(" %d", &nova_reserva.id_quarto);

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

    //Se a reserva for encontrada
    if (posicao != -1) {
        printf("Novo CPF do cliente (formato xxx.xxx.xxx-xx): ");
        scanf(" %[^\n]s", reservas[posicao].cpf_cliente);
        printf("Nova data de Check-in (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &reservas[posicao].checkin.dia, &reservas[posicao].checkin.mes,
              &reservas[posicao].checkin.ano);
        printf("Nova data de Check-out (dd/mm/aaaa): ");
        scanf("%d/%d/%d", &reservas[posicao].checkout.dia, &reservas[posicao].checkout.mes,
              &reservas[posicao].checkout.ano);
        printf("Novo tipo de quarto (Single, Duplo, Triplo): ");
        scanf(" %[^\n]s", reservas[posicao].tipo_quarto);
        printf("Novo ID do quarto: ");
        scanf("%d", &reservas[posicao].id_quarto);

        salvarReservas();
        printf("Reserva alterada com sucesso.\n");
    } else {
        printf("Reserva com o ID %d não encontrada.\n", id);
    }
}

void cancelarReservaPorId(int id);
void cancelarReservaPorClienteEDataF(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin) {
    DATA checkin;
    checkin.dia = dia_checkin;
    checkin.mes = mes_checkin;
    checkin.ano = ano_checkin;

    cancelarReservaPorClienteEData(cpf, checkin);
}

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
            DATA checkin;
            printf("Digite o CPF do cliente: ");
            scanf(" %[^\n]s", cpf);
            printf("Digite a data de Check-in (dd mm aaaa): ");
            scanf("%d %d %d", &checkin.dia, &checkin.mes, &checkin.ano);
            cancelarReservaPorClienteEDataF(cpf, checkin.dia, checkin.mes, checkin.ano);
            break;
        }
        default:
            printf("Opção inválida.\n");
            break;
    }
}

void cancelarReservaPorId(int id) {
    int posicao = -1;

    for (int i = 0; i < quantidade_reservas; i++) {
        if (reservas[i].id_reserva == id) {
            posicao = i;
            break;
        }
    }

    //Se a reserva for encontrada
    if (posicao != -1) {
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

void cancelarReservaPorClienteEData(const char *cpf, DATA checkin) {
    int posicao = -1;

    // Encontra a posição da reserva com o CPF do cliente e a data de check-in especificados
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].cpf_cliente, cpf) == 0 &&
            DataCmp(reservas[i].checkin, checkin) == 0) {
            posicao = i;
            break;
        }
    }

    // Se a reserva for encontrada
    if (posicao != -1) {
        for (int i = posicao; i < quantidade_reservas - 1; i++) {
            reservas[i] = reservas[i + 1];
        }
        quantidade_reservas--;

        salvarReservas();
        printf("Reserva do cliente com CPF %s para a data de check-in %02d/%02d/%04d excluída com sucesso.\n", cpf, checkin.dia, checkin.mes, checkin.ano);
    } else {
        printf("Reserva do cliente com CPF %s para a data de check-in %02d/%02d/%04d não encontrada.\n", cpf, checkin.dia, checkin.mes, checkin.ano);
    }
}

void consultarReservasCliente(const char *cpf) {
    printf("Reservas associadas ao cliente com CPF %s:\n", cpf);
    int encontradas = 0;
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].cpf_cliente, cpf) == 0) {
            printf("ID da Reserva: %d\n", reservas[i].id_reserva);
            printf("Check-in: %02d/%02d/%04d\n", reservas[i].checkin.dia, reservas[i].checkin.mes, reservas[i].checkin.ano);
            printf("Check-out: %02d/%02d/%04d\n", reservas[i].checkout.dia, reservas[i].checkout.mes, reservas[i].checkout.ano);
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

void verificarDisponibilidadeQuarto(const char *tipo_quarto, DATA checkin, DATA checkout) {
    printf("Verificando disponibilidade de quartos do tipo %s para o período de %02d/%02d/%04d a %02d/%02d/%04d:\n", tipo_quarto, checkin.dia, checkin.mes, checkin.ano, checkout.dia, checkout.mes, checkout.ano);
    int disponiveis = 0;
    for (int i = 0; i < quantidade_reservas; i++) {
        if (strcmp(reservas[i].tipo_quarto, tipo_quarto) == 0) {
            if (DataCmp(reservas[i].checkout, checkin) < 0 ||
                DataCmp(reservas[i].checkin, checkout) > 0) {
                printf("Quarto disponível: ID %d\n", reservas[i].id_quarto);
                disponiveis++;
            }
        }
    }
    if (disponiveis == 0) {
        printf("Nenhum quarto do tipo %s disponível para o período especificado.\n", tipo_quarto);
    }
}

int proximoCodigoReserva = 1;