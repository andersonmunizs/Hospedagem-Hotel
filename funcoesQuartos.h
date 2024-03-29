//funcoesQuartos.h
#ifndef FUNCOES_QUARTOS_H
#define FUNCOES_QUARTOS_H

typedef struct {
    int id_quarto;
    int camas_solteiro;
    int camas_casal;
    char tipo_quarto[10];
    double preco_diaria;
    char status[4];
} Quarto;

extern int quantidade_quartos;
extern Quarto quartos[100];

void cadastrarQuarto();
void alterarQuarto();
void excluirQuarto();
void carregarQuartos();
void salvarQuartos();

Quarto obterQuartoPorNumero(int numero);

#endif

