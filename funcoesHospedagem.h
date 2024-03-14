#ifndef FUNCOESHOSPEDAGEM_H
#define FUNCOESHOSPEDAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura de dados para representar uma hospedagem
typedef struct {
    int codigo_reserva;
    char cpf_cliente[15];
    char data_checkin[11];
    char data_checkout[11]; // Adicionado o membro data_checkout
    char tipo_quarto[10]; // Adicionado o membro tipo_quarto
    int id_quarto;
    char quarto[10];
    char status[20];
} Hospedagem;


void iniciar_hospedagem();
void carregarHospedagens();
void finalizar_hospedagem();
float calcular_valor_total_hospedagem(char *tipo_quarto, char *data_checkin);

#endif /* FUNCOESHOSPEDAGEM_H */
