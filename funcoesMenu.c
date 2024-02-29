//funcoesMenu.c
#include "stdio.h"
#include "funcoesClientes.h"
#include "funcoesQuartos.h"
#include "funcoesReservas.h"
#include "funcoesHospedagem.h"

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
        printf("5. Verificar Disponibilidade de Quartos\n");
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
                char cpf[14];
                printf("Digite o CPF do cliente para consultar suas reservas (formato xxx.xxx.xxx-xx): ");
                scanf("%13s", cpf);
                consultarReservasCliente(cpf);
            }
                break;
            case 5:
            {
                char tipo_quarto[10];
                int dia_checkin, mes_checkin, ano_checkin;
                int dia_checkout, mes_checkout, ano_checkout;
                printf("Tipo de Quarto (Single, Duplo, Triplo): ");
                scanf("%9s", tipo_quarto);
                printf("Data de Check-in (dd mm aaaa): ");
                scanf("%d %d %d", &dia_checkin, &mes_checkin, &ano_checkin);
                printf("Data de Check-out (dd mm aaaa): ");
                scanf("%d %d %d", &dia_checkout, &mes_checkout, &ano_checkout);
                verificarDisponibilidadeQuarto(tipo_quarto, dia_checkin, mes_checkin, ano_checkin, dia_checkout, mes_checkout, ano_checkout);
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
        printf("2. Encerrar Hospedagem\n");
        printf("9. Voltar ao Menu Principal\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                iniciarHospedagem();
                break;
            case 2:
                encerrarHospedagem();
                break;
            case 9:
                printf("Voltando ao Menu Principal...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);
}
