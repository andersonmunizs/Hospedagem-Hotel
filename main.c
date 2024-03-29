//main.c
#include <stdio.h>
#include "funcoesQuartos.h"
#include "funcoesClientes.h"
#include "funcoesReservas.h"
#include "funcoesHospedagem.h"
#include "funcoesMenu.h"
#include <locale.h>


int main() {
    carregarQuartos(); //Carrega os quartos do arquivo CSV
    carregarClientes(); //Carrega os clientes do arquivo CSV
    carregarReservas(); //Carrega as reservas do arquivo CSV
    carregarHospedagens(); //Carrega as hospedagens do arquivo CSV
    setlocale(LC_ALL, "pt_BR.UTF-8");

    int opcao;
    do {
        printf("\nMenu Principal\n");
        printf("1. Reservas\n");
        printf("2. Clientes\n");
        printf("3. Hospedagem\n");
        printf("4. Quartos\n");
        printf("9. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                menuReservas();
                break;
            case 2:
                menuClientes();
                break;
            case 3:
                menuHospedagem();
                break;
            case 4:
                menuQuartos();
                break;
            case 9:
                printf("Saindo do programa...\n");
                break;
            default:
                printf("Opção inválida. Por favor, escolha uma opção válida.\n");
        }
    } while (opcao != 9);

    return 0;
}
