// funcoesReservas.h
#ifndef FUNCOES_RESERVAS_H
#define FUNCOES_RESERVAS_H

#include "string.h"

#define MAX_RESERVAS 100

typedef struct {
    int id_reserva;
    char cpf_cliente[14];
    int dia_checkin;
    int mes_checkin;
    int ano_checkin;
    int dia_checkout;
    int mes_checkout;
    int ano_checkout;
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
void consultarReservasCliente(const char *cpf);
void verificarDisponibilidadeQuarto(const char *tipo_quarto, int dia_checkin, int mes_checkin, int ano_checkin, int dia_checkout, int mes_checkout, int ano_checkout);

#endif /* FUNCOES_RESERVAS_H */
