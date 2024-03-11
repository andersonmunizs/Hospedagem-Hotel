// funcoesReservas.h
#ifndef FUNCOES_RESERVAS_H
#define FUNCOES_RESERVAS_H

#include "string.h"
#include "tempo.h"

#define MAX_RESERVAS 100

typedef struct {
    int id_reserva;
    char cpf_cliente[14];
    DATA checkin;
    DATA checkout;
    char tipo_quarto[10];
    int id_quarto;
} Reserva;

extern Reserva reservas[MAX_RESERVAS];
extern int quantidade_reservas;

// Protótipo das funções
void salvarReservas();
void carregarReservas();
void cadastrarReserva();
void alterarReserva();
void excluirReserva();
void cancelarReservaPorClienteEData(const char *cpf, DATA checkin);
void verificarDisponibilidadeQuarto(const char *tipo_quarto, DATA checkin, DATA checkout);
void cancelarReservaPorClienteEDataF(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin);
void consultarReservasCliente(const char *cpf);
#endif /* FUNCOES_RESERVAS_H */
