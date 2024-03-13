#ifndef FUNCOESHOSPEDAGEM_H
#define FUNCOESHOSPEDAGEM_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da estrutura de dados para representar uma hospedagem
typedef struct {
    int codigo_reserva;
    char data_checkin[20]; // A data de check-in será armazenada como uma string
    int quarto;
    char status[10]; // "Ativa" ou "Inativa"
} Hospedagem;

// Função para iniciar a hospedagem de um cliente a partir do código da reserva
void iniciar_hospedagem();
void carregarHospedagens();

#endif /* FUNCOESHOSPEDAGEM_H */
