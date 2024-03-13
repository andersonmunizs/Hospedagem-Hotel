// hospedagem.h
#ifndef FUNCOESHOSPEDAGEM_H
#define FUNCOESHOSPEDAGEM_H

#include "tempo.h"
#include "funcoesReservas.h"

typedef struct {
    unsigned int id;
    char CPF[16];
    DATA checkin;
    DATA checkout;
    char status[12];
    float precoTotal;
} HOSPEDAGEM;
/*
int quantidadeHospedagens();
void carregarHospedagem();
void exibirHospedagem(HOSPEDAGEM h);
*/
#endif /* FUNCOESHOSPEDAGEM_H */
