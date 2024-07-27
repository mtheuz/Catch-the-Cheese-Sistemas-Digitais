/**
 * \file            mouse_move.c
 * \brief           Biblioteca que implementa as funções do header mouse_move.h para uso da mouse device
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


#include "mouse_move.h"
#include <math.h>


int fd_mouse = 0;
int16_t pos_x = 0;
int16_t pos_y = 0;
uint8_t left = 0;
uint8_t middle = 0;
uint8_t right = 0;

/**
 * \brief           Usada para abrir o arquivo de drive do mouse
 *  \return         Retorna 1 caso o arquivo foi aberto ou retorna 0 caso não seja possivel abrir o arquivo
 */
int open_mouse_device()
{
    fd_mouse = open(MICE_PATH, O_RDWR);

    if (fd_mouse < 0)
    {
        perror("Failed to open the device");
        return 0;
    }
    return 1;
}

/**
 * \brief           Usada para fechar o arquivo de drive do mouse
 */
void close_mouse_device()
{
    close(fd_mouse);
}

/**
 * \brief           Usada ler os inputs do mouse
 * 
 * \param[in]       action: Ponteiro para o inteiro que indica se a habilidade esta ativada ou não
 * \param[in]       power_amount: Ponteiro para o inteiro que indica a quantidade de vezes que ahabilidade ainda pode ser ativada
 * \return         Retorna 1 caso o arquivo foi aberto ou retorna 0 caso não seja possivel abrir o arquivo
 */
void mouse_movement(int *action, int *power_amount)
{
    int bytes = read(fd_mouse, data, sizeof(data)); /* Abre o arquivo MICE para leitura dos eventos de input que o mouse esta enviando */

    left = data[0] & 0x1;   /* Lê o 1º LSB e se for igual a 1 significa que o botão esquerdo foi pressionado então left = 1 tambem */
    right = data[0] & 0x2;  /* Lê o 2º LSB e se for igual a 1 significa que o botão direito foi pressionado então right = 1 tambem */
    middle = data[0] & 0x4; /* Lê o 4º LSB e se for igual a 1 significa que o botão do meio foi pressionado então middle = 1 tambem */
    if (left == 1 && *power_amount > 0) {
        *action = 1;
        *power_amount -= 1;
    }

    pos_x += (data[1]/2);
    pos_y -= (data[2]/2);
    if (pos_x < 0)
    {
        pos_x = 0;
    }
    if (pos_x > 620)
    {
        pos_x = 620;
    }

    if (pos_y < 0)
    {
        pos_y = 0;
    }
    if (pos_y > 460)
    {
        pos_y = 460;
    }
}

