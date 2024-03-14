//funcoesMenu.c
#include "stdio.h"
#include "funcoesClientes.h"
#include "funcoesQuartos.h"
#include "funcoesReservas.h"
#include "funcoesHospedagem.h"
#include "tempo.h"

void menuQuartos() {
    int opcao;
    do {
        printf("\nMenu Quartos\n");
        printf("1. Novo Quarto\n");
        printf("2. Alterar Quarto\n");
        printf("3. Excluir Quarto\n");
        printf("9. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarQuarto();
                break;
            case 2:
                alterarQuarto();
                break;
            case 3:
                excluirQuarto();
                break;
            case 9:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);
}

void menuClientes() {
    int opcao;
    do {
        printf("\nMenu Clientes\n");
        printf("1. Novo Cliente\n");
        printf("2. Alterar Cliente\n");
        printf("3. Excluir Cliente\n");
        printf("9. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarCliente();
                break;
            case 2:
                alterarCliente();
                break;
            case 3:
                excluirCliente();
                break;
            case 9:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);
}

void menuReservas() {
    int opcao;
    do {
        printf("\nMenu Reservas\n");
        printf("1. Nova Reserva\n");
        printf("2. Alterar Reserva\n");
        printf("3. Excluir Reserva\n");
        printf("4. Consultar Reservas de um Cliente\n");
        printf("9. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarReserva();
                break;
            case 2:
                alterarReserva();
                break;
            case 3:
                excluirReserva();
                break;
            case 4:
            {
                char cpf[15]; // Aumentando o tamanho para incluir o caractere de hífen
                printf("Digite o CPF do cliente para consultar suas reservas (formato xxx.xxx.xxx-xx): ");
                scanf("%14s", cpf); // Ajustando o formato para incluir o hífen
                consultarReservasCliente(cpf);
            }
                break;
            case 9:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);
}

void menuHospedagem() {
    int opcao;
    do {
        printf("\nMenu Hospedagem\n");
        printf("1. Iniciar Hospedagem\n");
        printf("2. [INDISPONIVEL] Finalizar Hospedagem\n");
        printf("9. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                iniciar_hospedagem();
                break;
            case 2:
                finalizar_hospedagem();
                break;
            case 9:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);
}
