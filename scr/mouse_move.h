/**
 * \file            mouse_move.h
 * \brief           Header com as funções da biblioteca do mouse device
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


#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <math.h>

#define MICE_PATH "/dev/input/mice"

int fd_mouse;
int16_t pos_x;
int16_t pos_y;
uint8_t left;
uint8_t middle;
uint8_t right;
int8_t data[3];

int open_mouse_device();

int power (int base);

void close_mouse_device();

void mouse_movement(int *action, int *power_amount);

int left_click();