/**
 * \file            botoes.h
 * \brief           Header com as funções da biblioteca para controlar os botões
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

#ifndef BOTOES_H
#define BOTOES_H

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>       
#include <sys/mman.h>
#include <unistd.h>  
#define KEY_BASE 0x0
#define LW_BRIDGE_BASE 0xFF200000
#define LW_BRIDGE_SPAN 0x00005000

extern int botao0;
extern int botao1;
extern int botao2;
extern int botao3;

extern volatile int *KEY_ptr;
extern int fd_botoes;
extern void *LW_virtual;

int open_botoes_device();

void read_botoes();

void close_botoes_devide();


#endif // DRAW_SCREEN_H
