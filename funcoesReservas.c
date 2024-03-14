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
    printf("2. [INDISPONIVEL] Utilizando o CPF do cliente e a data de check-in\n");
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
            scanf("%s", cpf);
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

void cancelarReservaPorClienteEData() {
    char cpf[15];
    int dia_checkin, mes_checkin, ano_checkin;
    printf("Digite o CPF do cliente: ");
    scanf("%14s", cpf);
    printf("Digite a data de Check-in (dd mm aaaa): ");
    scanf("%d %d %d", &dia_checkin, &mes_checkin, &ano_checkin);

    DATA data_checkin;
    data_checkin.dia = dia_checkin;
    data_checkin.mes = mes_checkin;
    data_checkin.ano = ano_checkin;
    data_checkin.hora = 0;
    data_checkin.minuto = 0;
    data_checkin.segundo = 0;

    DATA data_checkout;
    data_checkout.dia = 0;
    data_checkout.mes = 0;
    data_checkout.ano = 0;
    data_checkout.hora = 0;
    data_checkout.minuto = 0;
    data_checkout.segundo = 0;

    // Buscar reserva pelo cliente e data de check-in
    cancelarReservaPorClienteEDataF(cpf, dia_checkin, mes_checkin, ano_checkin);
}

void consultarReservasCliente(char *cpf) {
    FILE *file = fopen("reservas.csv", "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo de reservas.\n");
        return;
    }

    char linha[100];
    bool encontrou = false;

    // Ignora o cabeçalho do arquivo CSV
    fgets(linha, sizeof(linha), file);

    printf("Reservas associadas ao cliente com CPF %s:\n", cpf);
    while (fgets(linha, sizeof(linha), file)) {
        char idReserva[10], cpfCliente[15], checkIn[11], checkOut[11], tipoQuarto[20], idQuarto[10];
        sscanf(linha, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^\n]", idReserva, cpfCliente, checkIn, checkOut, tipoQuarto, idQuarto);

        if (strcmp(cpfCliente, cpf) == 0) {
            printf("ID da Reserva: %s\n", idReserva);
            printf("Check-in: %s\n", checkIn);
            printf("Check-out: %s\n", checkOut);
            printf("Tipo de Quarto: %s\n", tipoQuarto);
            printf("ID do Quarto: %s\n", idQuarto);
            encontrou = true;
        }
    }

    if (!encontrou) {
        printf("Nenhuma reserva encontrada para o cliente com CPF %s.\n", cpf);
    }

    fclose(file);
}


Reserva *buscarReservaPorClienteEData(const char *cpf, DATA checkin) {
    for (int i = 0; i < quantidade_reservas; i++) {
        // Verifica se o CPF do cliente e a data de check-in correspondem à reserva atual
        if (strcmp(reservas[i].cpf_cliente, cpf) == 0 &&
            compararDatas(reservas[i].checkin, checkin) == 0) {
            return &reservas[i]; // Retorna o endereço da reserva encontrada
        }
    }
    return NULL; // Retorna NULL se a reserva não for encontrada
}

void cancelarReserva(Reserva *reserva) {
    if (reserva == NULL) {
        printf("Erro: reserva inválida.\n");
        return;
    }

    for (int i = 0; i < quantidade_reservas; i++) {
        if (&reservas[i] == reserva) {
            // Move as reservas após a reserva a ser cancelada para preencher o espaço
            for (int j = i; j < quantidade_reservas - 1; j++) {
                reservas[j] = reservas[j + 1];
            }
            quantidade_reservas--; // Atualiza a quantidade de reservas
            salvarReservas(); // Salva as alterações no arquivo
            printf("Reserva cancelada com sucesso.\n");
            return;
        }
    }
    printf("Erro: reserva não encontrada.\n");
}

int compararDatas(DATA data1, DATA data2) {
    if (data1.ano != data2.ano) {
        return data1.ano - data2.ano;
    }
    if (data1.mes != data2.mes) {
        return data1.mes - data2.mes;
    }
    return data1.dia - data2.dia;
}