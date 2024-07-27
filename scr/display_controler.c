/**
 * \file            display_controler.c
 * \brief           Biblioteca que implementa as funções da biblioteca display_controler.h para manipular os numeros que serão exibidos no display de 7 segmentos
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

#include "display_controler.h"

volatile int *HEX0_BASE_ptr, *HEX1_BASE_ptr, *HEX2_BASE_ptr, *HEX3_BASE_ptr, *HEX4_BASE_ptr, *HEX5_BASE_ptr;
int fd_display = -1;
void *LW_virtual;

/**
 * \brief           Usada para converter numeros em binarios
 *
 * \param[in]       C: Numero que sera convertido em binario
 * \return          Retorna o numero em binario
 */
int numbers(int c) {
    switch (c) {
        case 0: return 0b01000000;
        case 1: return 0b11111001;
        case 2: return 0b10100100;
        case 3: return 0b10110000;
        case 4: return 0b10011001;
        case 5: return 0b10010010;
        case 6: return 0b10000010;
        case 7: return 0b11111000;
        case 8: return 0b10000000;
        case 9: return 0b10010000;
    }
}

/**
 * \brief           Usada para abrir o arquivo de mapeamento de memoria do display de 7 segmentos
 *  \return         Retorna 1 caso o arquivo foi aberto ou retorna 0 caso não seja possivel abrir o arquivo
 */
int open_display_device() {
     if ((fd_display = open("/dev/mem", (O_RDWR | O_SYNC))) == -1) {
        printf("ERRO: não foi possível abrir \"/dev/mem\"...\n");
        return 0;
    }
    LW_virtual = mmap(NULL, LW_BRIDGE_SPAN, PROT_READ | PROT_WRITE, MAP_SHARED, fd_display, LW_BRIDGE_BASE);
    if (LW_virtual == MAP_FAILED) {
        printf("ERRO: mmap() falhou...\n");
        close(fd_display);
        return 0;
    }

    HEX0_BASE_ptr = (volatile int *)(LW_virtual + HEX0_BASE);
    HEX1_BASE_ptr = (volatile int *)(LW_virtual + HEX1_BASE);
    HEX2_BASE_ptr = (volatile int *)(LW_virtual + HEX2_BASE);
    HEX3_BASE_ptr = (volatile int *)(LW_virtual + HEX3_BASE);
    HEX4_BASE_ptr = (volatile int *)(LW_virtual + HEX4_BASE);
    HEX5_BASE_ptr = (volatile int *)(LW_virtual + HEX5_BASE);

    return 1;
}

/**
 * \brief           Usada desenhar um numero em um dos digitod do displayy de 7 segmentos
 *
 * \param[in]       display_digit: Digito ao qual deve ser desenhado o numero
 * \param[in]       number: Numero a ser desenhado
 */
void write_number_display(int display_digit, int number) {
    
    if (display_digit == 0) {
        *HEX0_BASE_ptr = numbers(number);
    } else if (display_digit == 1) {
        *HEX1_BASE_ptr = numbers(number);
    } else if (display_digit == 2) {
        *HEX2_BASE_ptr = numbers(number);
    } else if (display_digit == 3) {
        *HEX3_BASE_ptr = numbers(number);
    } else if (display_digit == 4) {
        *HEX4_BASE_ptr = numbers(number);
    } else if (display_digit == 5) {
        *HEX5_BASE_ptr = numbers(number);
    } 

}

/**
 * \brief           Usada desenhar o numero das pontos obtidos pelo jogador nos digitos 0 e 1 do display de 7 segmentos
 *
 * \param[in]       score: Pontos atuais do jogador
 */
void write_score (int score) {
    int dezena = score/10;
    int unidade = score % 10;

    write_number_display(1, dezena);
    write_number_display(0, unidade);

}

/**
 * \brief           Usada desenhar o numero das vidas restantes do jogador nos digitos 4 e 5 do display de 7 segmentos
 *
 * \param[in]       vidas: Vidas restantes do jogador
 */
void write_lifes (int vidas) {
    int dezena = vidas/10;
    int unidade = vidas % 10;

    write_number_display(5, dezena);
    write_number_display(4, unidade);
}


/**
 * \brief           Usada para iniciar o numero 0 em todos os digitos do display
 */
void write_start_display() {
    write_number_display(0, 0);
    write_number_display(1, 0);
    write_number_display(2, 0);
    write_number_display(3, 0);
    write_number_display(4, 0);
    write_number_display(5, 0);
    
}


/**
 * \brief           Usada para fechar o arquivo de mapeamento de memoria do display de 7 segmentos
 */
void close_display_device() {
    munmap(LW_virtual, LW_BRIDGE_SPAN);
    close(fd_display);
}
