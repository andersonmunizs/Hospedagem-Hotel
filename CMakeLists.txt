cmake_minimum_required(VERSION 3.27)
project(Projeto2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Projeto2 main.c
        funcoesQuartos.c
        funcoesClientes.c
        funcoesMenu.c
        funcoesReservas.h
        funcoesReservas.c
        funcoesHospedagem.h
        funcoesHospedagem.c
        tempo.c)
