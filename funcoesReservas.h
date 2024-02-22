//funcoesReservas.h
#ifndef FUNCOES_RESERVAS_H
#define FUNCOES_RESERVAS_H

typedef struct {
    int id_reserva;
    char cpf_cliente[14];
    int dia_checkin;
    int mes_checkin;
    int ano_checkin;
    int dia_checkout;
    int mes_checkout;
    int ano_checkout;
    char tipo_quarto[10]; // Corrigido para tamanho 10
    int id_quarto;
} Reserva;

void cadastrarReserva();
void alterarReserva();
void excluirReserva();
void carregarReservas();
void salvarReservas();
void consultarReservasCliente(const char *cpf);
void verificarDisponibilidadeQuarto(const char *tipo_quarto, int dia_checkin, int mes_checkin, int ano_checkin, int dia_checkout, int mes_checkout, int ano_checkout);
void cancelarReservaPorId(int id);
void cancelarReservaPorClienteEData(const char *cpf, int dia_checkin, int mes_checkin, int ano_checkin);

#endif
