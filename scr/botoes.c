/**
 * \file            botoes.c
 * \brief           Biblioteca que implementa as funções da biblioteca botoes.h para ler os inputes dos 4 botões da placa
 */

/*
 * Copyright (c) 2024 Pedro Henrique Araujo Almeida, Dermeval Neves de Oliveira Filho, Matheus
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE
 * AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * This file is part of library_name.
 *
 * Author:          Pedro Henrique ARAUJO ALMEIDA <phaalmeida1\gmail.com>
 *                  Dermeval Neves de Oliveira Filho <dermevalneves\gmail.com>
 *                  Matheus Mota Santos<matheuzwork\gmail.com>
 */

#include "botoes.h"

volatile int *KEY_ptr;
int fd_botoes = 0;
void *LW_virtual;

int botao0;
int botao1;
int botao2;
int botao3;

/**
 * \brief           Usada para abrir o arquivo de mapeamento de memoria dos botões
 *  \return         Retorna 1 caso o arquivo foi aberto ou retorna 0 caso não seja possivel abrir o arquivo
 */
int open_botoes_device() {
    if ((fd_botoes = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERRO: não foi possível abrir \"/dev/mem\"...\n");
        return 0;
    }

    // Mapeia a memória
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd_botoes, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERRO: mmap() falhou...\n");
        close(fd_botoes);
        return 0;
    }

    KEY_ptr = (volatile int *)(LW_virtual + KEY_BASE);

    return 1;

}

/**
 * \brief           Altera as variaveis botao0, botao1, botao2, botao3 com base nos inputes dos botões da placa
 */
void read_botoes() {
    botao0 = (*KEY_ptr & 0b1);
    botao1 = (*KEY_ptr & 0b10) >> 1;
    botao2 = (*KEY_ptr & 0b100) >> 2;
    botao3 = (*KEY_ptr & 0b1000) >> 3;
}


/**
 * \brief           Usada para fechar o arquivo de mapeamento de memoria dos botões
 */
void close_botoes_devide() {
    // Desmapeia a memória e fecha o arquivo
    munmap(LW_virtual, LW_BRIDGE_SPAN);
    close(fd_botoes);
}