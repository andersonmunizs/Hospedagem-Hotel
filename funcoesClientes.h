//funcoesClientes.h
#ifndef FUNCOES_CLIENTES_H
#define FUNCOES_CLIENTES_H

#include "tempo.h"

typedef struct {
    char cpf[14];
    char nome[51];
    DATA dataNascimento;
    int idade;
    char endereco[101];
    char cidade[101];
    char estado[3];
} Cliente;

void cadastrarCliente();
void alterarCliente();
void excluirCliente();
void carregarClientes();
void salvarClientes();

#endif
