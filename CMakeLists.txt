cmake_minimum_required(VERSION 3.20)
project(TP02_AEDII C)

set(CMAKE_C_STANDARD 99)

add_executable(
        main
        src/main/main.c
        src/main/TAD_arv_AVL.c
        src/main/TAD_arv_bin_pesquisa.c
        src/main/TAD_vetor.c
        src/main/TAD_arv_pacotes.c
        src/main/TAD_arv_pacotes.c
        src/main/TAD_arv_pacotes.h
)