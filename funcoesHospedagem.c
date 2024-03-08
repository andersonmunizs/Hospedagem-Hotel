#include <stdio.h>
#include "funcoesHospedagem.h"
#include "funcoesReservas.h"

void iniciarHospedagem() {
    int id_reserva;
    printf("Digite o ID da reserva para iniciar a hospedagem: ");
    scanf("%d", &id_reserva);

    int posicao = -1;
    for (int i = 0; i < quantidade_reservas; i++) {
        if (reservas[i].id_reserva == id_reserva) {
            posicao = i;
            break;
        }
    }

    //Se a reserva for encontrada
    if (posicao != -1) {
        printf("Hospedagem iniciada com sucesso para o cliente com CPF %s.\n", reservas[posicao].cpf_cliente);

    } else {
        printf("Reserva com o ID %d não encontrada.\n", id_reserva);
    }
}

void encerrarHospedagem() {

    printf("Hospedagem encerrada com sucesso.\n");
}
