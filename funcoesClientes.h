//funcoesClientes.h
#ifndef FUNCOES_CLIENTES_H
#define FUNCOES_CLIENTES_H

#include "tempo.h"

enum CAMPOS_CLIENTE {CPF_CLI=0, NOME_CLI, DATA_NASC_CLI, IDADE_CLI, ENDERECO_CLI, CIDADE_CLI, ESTADO_CLI};

typedef struct {
    char cpf[20];
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
