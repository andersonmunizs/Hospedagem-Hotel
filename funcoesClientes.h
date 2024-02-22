//funcoesClientes.h
#ifndef FUNCOES_CLIENTES_H
#define FUNCOES_CLIENTES_H

typedef struct {
    char cpf[14]; // String de 13 caracteres + terminador nulo
    char nome[51]; // String de 50 caracteres + terminador nulo
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento;
    int idade;
    char endereco[101]; // String de 100 caracteres + terminador nulo
    char cidade[101]; // String de 100 caracteres + terminador nulo
    char estado[3]; // String de 2 caracteres + terminador nulo
} Cliente;

void cadastrarCliente();
void alterarCliente();
void excluirCliente();
void carregarClientes();
void salvarClientes();

#endif
