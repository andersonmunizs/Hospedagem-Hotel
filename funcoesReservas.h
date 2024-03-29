// funcoesReservas.h
#ifndef FUNCOES_RESERVAS_H
#define FUNCOES_RESERVAS_H

#include "string.h"
#include "tempo.h"

#define MAX_RESERVAS 100

enum CAMPOS_HOSPEDAGEM {IDRESERVA_HOSPEDAGEM=0, CPF_HOSPEDAGEM,CHECKIN_HOSPEDAGEM,CHECKOUT_HOSPEDAGEM, STATUS_HOSPEDAGEM, PRECOTOTAL_HOSPEDAGEM};

typedef struct {
    int id_reserva;
    char cpf_cliente[14];
    DATA checkin;
    DATA checkout;
    char tipo_quarto[10];
    int id_quarto;
    char status;
} Reserva;

extern Reserva reservas[MAX_RESERVAS];
extern int quantidade_reservas;

Reserva *buscarReservaPorClienteEData(const char *cpf, DATA checkin);
void cancelarReserva(Reserva *reserva);

// Protótipo das funções
void salvarReservas();
void carregarReservas();
void cadastrarReserva();
void alterarReserva();
void excluirReserva();
void cancelarReservaPorClienteEData();
void verificarDisponibilidadeQuarto(const char *tipo_quarto, DATA checkin, DATA checkout);
void cancelarReservaPorClienteEDataF(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin);
void consultarReservasCliente(char *cpf);
int compararDatas(DATA data1, DATA data2);
#endif /* FUNCOES_RESERVAS_H */
