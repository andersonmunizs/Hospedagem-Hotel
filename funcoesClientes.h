//funcoesClientes.h
#ifndef FUNCOES_CLIENTES_H
#define FUNCOES_CLIENTES_H

typedef struct {
    char cpf[14];
    char nome[51];
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento;
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
