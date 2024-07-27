/**
 * \file            display_controller.h
 * \brief           Header com as funções da biblioteca para controlar o display de 7 segmentos
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

#ifndef DISPLAY_CONTROLER_H
#define DISPLAY_CONTROLER_H

#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#define LW_BRIDGE_BASE 0xFF200000
#define LW_BRIDGE_SPAN 0x00005000
#define HEX5_BASE 0x10
#define HEX4_BASE 0x20
#define HEX3_BASE 0x30
#define HEX2_BASE 0x40
#define HEX1_BASE 0x50
#define HEX0_BASE 0x60

extern volatile int *HEX0_BASE_ptr, *HEX1_BASE_ptr, *HEX2_BASE_ptr, *HEX3_BASE_ptr, *HEX4_BASE_ptr, *HEX5_BASE_ptr;
extern int fd_display;
extern void *LW_virtual;

int numbers(int c);

int open_display_device();

void write_score (int score);
void write_lifes (int vidas);
void write_start_display();

void write_number_display(int display_digit, int number);

void close_display_device();

#endif // DRAW_SCREEN_H
