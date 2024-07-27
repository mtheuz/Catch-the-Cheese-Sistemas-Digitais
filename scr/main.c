/**
 * \file            main.c
 * \brief           Codigo que quando compilado e executado vai rodar o jogo Catch The Cheese
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
#include <unistd.h>
#include <stdint.h>
#include "gpu_lib.h"
#include <stdlib.h>
#include <fcntl.h>       
#include <sys/mman.h>
#include "draw_screens.h"
#include "draw_sprites.h" 
#include "mouse_move.h"
#include <pthread.h>
#include "botoes.h"
#include "display_controler.h"

/* VARIAVEIS GLOBAIS */
uint8_t game_state = 1;
uint8_t start = 0;
uint32_t contador = 0;
int coin_collumn = 0;
int coin_line = 0;
int is_game_state_on = 0;
int disable_sprite_player = 0;
int is_imortal = 0;
int action = 0;
int power_amount = 1;
int ativar_pisca = 0;

/**
 * \brief           Usada detectar colisão do jogador com os inimigos na tela
 *
 * \param[in]       sp1: Ponteiro para o sprite do jogador
 * \param[in]       sp2: Ponteiro para o sprite do inimigo
 * \param[in]       invuneravel: Ponteiro para o estado de quando o jogador esta invuneravel a danos
 * \param[in]       vidas: Ponteiro para as vidas restantes do jogador
 * \param[in]       offset_imortal: Numero a ser desenhado
 * \return          Retorna 1 para quando a colisão foi detectada e -1 caso contrario
 */
int collisao_inimigos(Sprite *sp1, Sprite *sp2, int *invuneravel, int *vidas, int offset_imortal) {
    if (collision(sp1, sp2) && (*invuneravel) == 0) {
        if (action == 1) {
            action = 0;
            ativar_pisca = 1;
            create_sprite(1, 1, pos_x, pos_y, 23, 0, 0, 0, 0);
            (*invuneravel) = 1;
            return -1;
        } else {
            if (*vidas > 0) {
                printf("VIDAS: %d\n", *vidas);
                *vidas -= 1;
                write_lifes(*vidas);
                create_sprite(1, 1, pos_x, pos_y, offset_imortal, 0, 0, 0, 1);
                *invuneravel = 1;
                return 0;
            } else {
                game_state = 4;
                contador = 0;
                is_game_state_on = 0;
                printf("COLISÃO: %d\n", sprites_array[1].collision);
                usleep(500000);
                return 1;
            }
        }
    }
    return -1;
}

/**
 * \brief           Usada gerar um numero aleatorio que não seja igual ao ultimo

 * \return          Retorna o novo numero aleatorio gerado
 */
int no_repeat_random (int last, int line) {
    int random_num = last;
    while (last == random_num) {
        if (line == 1) {
            random_num = rand() % 23;
        }
        else {
            random_num = rand() % 31;
        }
    }
    return random_num;
}

/**
 * \brief           Usada gerar um numero aleatorio que não seja igual ao ultimo e igual aos das armadilhas/objetivo
 *
 * \param[in]       last: Numero anteriormente gerado ao qual o novo deve ser diferente
 * \param[in]       line: Bit que indica se o numero deve ser gerado para uma linha ou uma coluna da matriz
 * \param[in]       difficulty: Nivel de dificuldade que se o numero deve ser gerado novamente quando ele já for igual a o de uma das armadilhas ou do objetivo
 * \return          Retorna o novo numero aleatorio gerado
 */
int no_repeat_random_and_other (int last, int line, int difficulty) {
    int random_num = last;
    int ok = 1;
    int i = 3;
    if (difficulty == 3) {
        if (line == 1) {
            while (random_num*20 == sprites_array[2].pos_y || random_num*20 == sprites_array[3].pos_y) {
                random_num = rand() % 23;
            }
        } else {
            while (random_num*20 == sprites_array[2].pos_x || random_num*20 == sprites_array[3].pos_x) {
                random_num = rand() % 31;
            }
        }
    } else if (difficulty == 4) {
        if (line == 1) {
            while (random_num*20 == sprites_array[2].pos_y || random_num*20 == sprites_array[3].pos_y || random_num*20 == sprites_array[4].pos_y || 
                   random_num*20 == sprites_array[5].pos_y || random_num*20 == sprites_array[6].pos_y) {
                random_num = rand() % 23;
            }
        } else {
            while (random_num*20 == sprites_array[2].pos_x || random_num*20 == sprites_array[3].pos_x || random_num*20 == sprites_array[4].pos_x || 
                   random_num*20 == sprites_array[5].pos_x || random_num*20 == sprites_array[6].pos_x) {
                random_num = rand() % 31;
            }
        }
    }
    return random_num;
}

/**
 * \brief           Usada criar as armadilhas na tela
 *
 * \param[in]       difficult: Nivel de dificuldade que determina quantas armadilhas vão aparecer na tela
 */
void spawn_bomb(int difficult) {
    int bomb_collumn = rand() % 31;
    int bomb_line = rand() % 23;
    bomb_collumn = no_repeat_random_and_other(bomb_collumn, 0, difficult);
    bomb_line = no_repeat_random_and_other(bomb_line, 1, difficult);
    create_sprite(3, 3, bomb_collumn*20, bomb_line*20, 2, 0, 0, 0, 1);
    printf("BOMB1 X: %d, BOMB2 Y: %d\n", bomb_collumn*20, bomb_line*20);
    bomb_collumn = no_repeat_random_and_other(bomb_collumn, 0, difficult);
    bomb_line = no_repeat_random_and_other(bomb_line, 1, difficult);
    printf("BOMB2 X: %d, BOMB2 Y: %d\n", bomb_collumn*20, bomb_line*20);
    create_sprite(4, 4, bomb_collumn*20, bomb_line*20, 2, 0, 0, 0, 1);

    if (difficult == 4) {
        bomb_collumn = no_repeat_random_and_other(bomb_collumn, 0, difficult);
        bomb_line = no_repeat_random_and_other(bomb_line, 1, difficult);
        printf("BOMB3 X: %d, BOMB3 Y: %d\n", bomb_collumn*20, bomb_line*20);
        create_sprite(5, 5, bomb_collumn*20, bomb_line*20, 2, 0, 0, 0, 1);
        
        bomb_collumn = no_repeat_random_and_other(bomb_collumn, 0, difficult);
        bomb_line = no_repeat_random_and_other(bomb_line, 1, difficult);
        printf("BOMB4 X: %d, BOMB4 Y: %d\n", bomb_collumn*20, bomb_line*20);
        create_sprite(6, 6, bomb_collumn*20, bomb_line*20, 2, 0, 0, 0, 1);
    }
}

/**
 * \brief           Usada criar o obejtivo que o jogador deve coletar
 */
void spawn_coin() {
    int i = 0;
    coin_collumn = no_repeat_random(coin_collumn, 0);
    coin_line = no_repeat_random(coin_line, 1);
    
    for (i; i < 100; i++) {
        create_sprite(2, 2, coin_collumn*20, coin_line*20, 5, 0, 0, 0, 1);
        
    }
    


}

/**
 * \brief           Usada detectar colisão do jogador com o objetivo na tela
 *
 * \param[in]       sp1: Ponteiro para o sprite do jogador
 * \param[in]       sp2: Ponteiro para o sprite do objetivo
 * \param[in]       score: Ponteiro para os pontos acumulados do jogador
 * \param[in]       difficulty: Ponteiro para a dificuldade/fase atual que o jogador esta
 * \param[in]       difficulty_completed: Ponteiro para o estado de jogo de fase completa
 * \return          Retorna 1 para quando a colisão foi detectada e -1 caso contrario
 */
int collisao_queijo(Sprite *sp1, Sprite *sp2, int *score, int *difficulty, int *difficulty_completed) {
    if (collision(sp1, sp2)) {
        *score += 1;
        printf("COIN: %d\n", *score);
        printf("PEGOU A MOEDA!\n");
        spawn_coin();
        write_score(*score);
        if (*score == (((*difficulty) + 1) * 5)) {
            printf("AUSDHI");
            *difficulty_completed = 0;
            game_state = 2;
            usleep(500000);
            return 1;
        }
    }
    return -1;
}

/**
 * \brief           Usada criar os inimigos que o jogador deve desviar
 *
 * \param[in]       difficult: Nivel de dificuldade que determina quantos inimigos vão aparecer na tela
 */
void spaw_enemy(int difficult) {
    int random_column = 0;
    int random_line = 0;
    // 0 = DIREITA, 1 = ESQUERDA, 2 = BAIXO, 3 = CIMA

    if (difficult == 0) {
        random_column = rand() % 31;
        random_line = rand() % 23;
        create_sprite(31, 31, random_column*20, random_line*20, 1, 1, 5, 0, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        create_sprite(30, 30, random_column*20, random_line*20, 1, 5, 1, 2, 1);
    }
    else if (difficult == 1) {
        random_column = rand() % 31;
        random_line = rand() % 23;
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(31, 31, random_column*20, random_line*20, 1, 2, 2, 0, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(30, 30, random_column*20, random_line*20, 1, 2, 2, 2, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(29, 29, random_column*20, random_line*20, 1, 2, 2, 1, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1   );
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(28, 28, random_column*20, random_line*20, 1, 2, 2, 3, 1);
    }

    else if (difficult >= 2) {
        random_column = rand() % 31;
        random_line = rand() % 23;
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(31, 31, random_column*20, random_line*20, 1, 2, 2, 0, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(30, 30, random_column*20, random_line*20, 1, 2, 2, 2, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(29, 29, random_column*20, random_line*20, 1, 2, 2, 1, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1   );
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(28, 28, random_column*20, random_line*20, 1, 2, 2, 3, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1);
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(27, 27, random_column*20, random_line*20, 1, 2, 2, 0, 1);
        random_column = no_repeat_random(random_column, 0);
        random_line = no_repeat_random(random_line, 1   );
        //printf("X=%d, Y=%d\n", random_column*19, random_line*19);
        create_sprite(26, 26, random_column*20, random_line*20, 1, 2, 2, 2  , 1);
    } 

}

/**
 * \brief           Loop principal do jogo.
 */
void* loop_principal (void* arg) {
    /* Variaveis locais para controlar estados do jogo*/
    int difficulty = 0;
    int difficulty_completed = 1;
    /* Variaveis locais para controlar caracteristicas do jogador */
    int score = 0;
    int vidas = 3;
    int offset_imortal = 4;
    int contador_pisca = 0;
    int contador_aux_pix = 0;
    int is_imortal_time = 75;

    /* Loop inicial que espera até o KEY0 ser pressionado para assim iniciar o jogo*/
    read_botoes();
    printf("%d\n", botao0);
    set_background_color(0, 0, 0);
    draw_start_game_screen();
    while (botao0) { /* BOTAO MAIS A DIREITA INICIA */
        game_state = 0;
        read_botoes();
        //draw_start_screen(); /* TEM QUE CRIAR*/
    }

    /* Desenha a primeira fase de jogo e inicia o loop*/
    draw_fase_screen(1, 0);
    usleep(2000000);
    game_state = 1;
    int is_paused = 1;
    int contador_aux = 0;
    while (1) {
        /* Verifica se algum dos botões foi pressionado para assim mudar o estado do jogo */
        read_botoes();
        if (botao0 == 0) { /* BOTAO MAIS A DIREITA RESETA */
            game_state = 3;
        } else if (botao2 == 0 && (game_state != 5 && game_state != 4)) { /* CONTINUA O JOGO EM CASO DE PAUSE*/
            game_state = 1;
        } else if (botao3 == 0) { /* BOTAO MAIS A ESQUERDA ENCERRA O JOGO*/
            game_state = 6;
            is_paused = 0;
            clear_poligonos();
            clear_sprites();
        }
        if (game_state == 0) { /* JOGO PAUSADO */
            sprites_array[1].enable = 0;
            if (is_paused == 0) {
                draw_pause_screen();
                is_paused = 1;
            }
        }
        else if (game_state == 1) { /* FASE ROLANDO */
            /* Desenha o background e reinicia os sprites caso o jogo estaja pausado*/
            draw_bg_cenario();
            if (is_paused == 1) {
                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, sprites_array[1].offset, 0, 0, 0, 1);
                create_sprite(2, 2, sprites_array[2].pos_x, sprites_array[2].pos_y, 5, 0, 0, 0, 1);
                if (difficulty == 3) {
                    create_sprite(3, 3, sprites_array[3].pos_x, sprites_array[3].pos_y, sprites_array[3].offset, 0, 0, 0, 1);
                    create_sprite(4, 4, sprites_array[4].pos_x, sprites_array[4].pos_y, sprites_array[4].offset, 0, 0, 0, 1);
                } else if (difficulty == 4) {
                    create_sprite(3, 3, sprites_array[3].pos_x, sprites_array[3].pos_y, sprites_array[3].offset, 0, 0, 0, 1);
                    create_sprite(4, 4, sprites_array[4].pos_x, sprites_array[4].pos_y, sprites_array[4].offset, 0, 0, 0, 1);
                    create_sprite(5, 5, sprites_array[5].pos_x, sprites_array[5].pos_y, sprites_array[5].offset, 0, 0, 0, 1);
                    create_sprite(6, 6, sprites_array[6].pos_x, sprites_array[6].pos_y, sprites_array[6].offset, 0, 0, 0, 1);
                
                }
                
            }
            is_paused = 0;
            /* Quando for a primeira vez entrado nesse loop apos a finalização de uma fase ou o inicio do jogo, a nova fase vai ser gerada*/
            if (start == 0) {
                spaw_enemy(difficulty);
                if (difficulty >= 3) {
                    spawn_bomb(difficulty);
                }
                start = 1;
                spawn_coin();
                contador = 0;
                pos_x = 0;
                pos_y = 0;
                create_sprite(1, 1, 0, 0, sprites_array[1].offset, 0, 0, 0, 1);
                write_lifes(vidas);
            }
            /* Loop da fase onde os inimigos se movimentam e o jogador deve coletar os objetivos pelo mapa */
            while (difficulty_completed) {
                /* Verifica se algum dos botões foi pressionado para assim alterar o estado do jogo */
                read_botoes();
                if (botao0 == 0) {
                    game_state = 3;
                    clear_poligonos();
                    clear_sprites();
                    break;
                } else if (botao1 == 0) {
                    game_state = 0;
                    is_paused = 0;
                    clear_poligonos();
                    clear_sprites();
                    break;
                } else if (botao3 == 0) {
                    game_state = 6;
                    is_paused = 0;
                    clear_poligonos();
                    clear_sprites();
                    break;
                }
                if (difficulty == 0) { /* FASE 1 DO JOGO */
                    /* Verifica as colisões e move os inimigos pelo mapa */
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[31], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[30], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_queijo(&sprites_array[1], &sprites_array[2], &score, &difficulty, &difficulty_completed) == 1) {
                        break;
                    }
                    if (contador == 8000){
                        static_movement(&sprites_array[31], 1);
                        static_movement(&sprites_array[30], 1);
                        if (is_imortal == 1) {
                            contador_aux += 1;
                        }
                        contador = 0;
                    }
                    /* Condicionais de caso o jogador tenha sido atingido então animações do fantasminha ou do pisca são mostradas*/
                    if (ativar_pisca == 1) {
                        contador_pisca += 1;
                    }
                    if (contador_pisca == 100000 && contador_aux_pix < 10) {
                            contador_pisca = 0;
                            if (sprites_array[1].enable == 0) {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 1);
                            } else {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 0);
                            }
                            contador_aux_pix += 1;
                    } else if (contador_aux_pix == 10) {
                        contador_aux_pix = 0;
                        ativar_pisca = 0;
                    }
                    if (contador_aux == is_imortal_time) {
                        ativar_pisca = 0;
                        create_sprite(1, 1, pos_x, pos_y, 0, 0, 0, 0, 1);
                        contador_aux = 0;
                        is_imortal = 0;
                    }
                    contador += 1;
                } else if (difficulty == 1) { /* FASE 2 DO JOGO */
                    /* Verifica as colisões e move os inimigos pelo mapa */
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[31], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[30], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[29], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[28], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_queijo(&sprites_array[1], &sprites_array[2], &score, &difficulty, &difficulty_completed) == 1) {
                        break;
                    }
                    if (contador == 6500){
                        static_movement(&sprites_array[31], 1);
                        static_movement(&sprites_array[30], 1);
                        static_movement(&sprites_array[29], 1);
                        static_movement(&sprites_array[28], 1);
                        if (is_imortal == 1) {
                            contador_aux += 1;
                        }
                        contador = 0;
                    }
                    /* Condicionais de caso o jogador tenha sido atingido então animações do fantasminha ou do pisca são mostradas*/
                    if (ativar_pisca == 1) {
                        contador_pisca += 1;
                    }
                    if (contador_pisca == 100000 && contador_aux_pix < 10) {
                            contador_pisca = 0;
                            if (sprites_array[1].enable == 0) {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 1);
                            } else {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 0);
                            }
                            contador_aux_pix += 1;
                    } else if (contador_aux_pix == 10) {
                        contador_aux_pix = 0;
                        ativar_pisca = 0;
                    }
                    if (contador_aux == is_imortal_time + 20) {
                        ativar_pisca = 0;
                        create_sprite(1, 1, pos_x, pos_y, 0, 0, 0, 0, 1);
                        contador_aux = 0;
                        is_imortal = 0;
                    }
                    contador += 1;
                } else if (difficulty == 2) { /* FASE 3 DO JOGO */
                    /* Verifica as colisões e move os inimigos pelo mapa */
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[31], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[30], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }  
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[29], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[28], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[27], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[26], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_queijo(&sprites_array[1], &sprites_array[2], &score, &difficulty, &difficulty_completed) == 1) {
                        break;
                    }
                    if (contador == 5000){
                        static_movement(&sprites_array[31], 1);
                        static_movement(&sprites_array[30], 1);
                        static_movement(&sprites_array[29], 1);
                        static_movement(&sprites_array[28], 1);
                        static_movement(&sprites_array[27], 1);
                        static_movement(&sprites_array[26], 1);
                        if (is_imortal == 1) {
                            contador_aux += 1;
                        }
                        contador = 0;
                    }
                    /* Condicionais de caso o jogador tenha sido atingido então animações do fantasminha ou do pisca são mostradas*/
                    if (ativar_pisca == 1) {
                        contador_pisca += 1;
                    }
                    if (contador_pisca == 100000 && contador_aux_pix < 10) {
                            contador_pisca = 0;
                            if (sprites_array[1].enable == 0) {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 1);
                            } else {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 0);
                            }
                            contador_aux_pix += 1;
                    } else if (contador_aux_pix == 10) {
                        contador_aux_pix = 0;
                        ativar_pisca = 0;
                    }
                    if (contador_aux == is_imortal_time + 30) {
                        ativar_pisca = 0;
                        create_sprite(1, 1, pos_x, pos_y, 0, 0, 0, 0, 1);
                        contador_aux = 0;
                        is_imortal = 0;
                    }
                    contador += 1;
                } else if (difficulty == 3) { /* FASE 4 DO JOGO */
                    /* Verifica as colisões e move os inimigos pelo mapa */
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[31], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[30], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[29], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[28], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[27], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[26], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[4], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[3], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_queijo(&sprites_array[1], &sprites_array[2], &score, &difficulty, &difficulty_completed) == 1) {
                        break;
                    }
                    if (contador == 4500){
                        static_movement(&sprites_array[31], 1);
                        static_movement(&sprites_array[30], 1);
                        static_movement(&sprites_array[29], 1);
                        static_movement(&sprites_array[28], 1);
                        static_movement(&sprites_array[27], 1);
                        static_movement(&sprites_array[26], 1);
                        if (is_imortal == 1) {
                            contador_aux += 1;
                        }
                        contador = 0;
                    }
                    /* Condicionais de caso o jogador tenha sido atingido então animações do fantasminha ou do pisca são mostradas*/
                    if (ativar_pisca == 1) {
                        contador_pisca += 1;
                    }
                    if (contador_pisca == 100000 && contador_aux_pix < 10) {
                            contador_pisca = 0;
                            if (sprites_array[1].enable == 0) {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 1);
                            } else {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 0);
                            }
                            contador_aux_pix += 1;
                    } else if (contador_aux_pix == 10) {
                        contador_aux_pix = 0;
                        ativar_pisca = 0;
                    }
                    if (contador_aux == is_imortal_time + 40) {
                        ativar_pisca = 0;
                        create_sprite(1, 1, pos_x, pos_y, 0, 0, 0, 0, 1);
                        contador_aux = 0;
                        is_imortal = 0;
                    }
                    contador += 1;
                } else if (difficulty == 4) { /* FASE 5 DO JOGO */
                    /* Verifica as colisões e move os inimigos pelo mapa */
                   if (collisao_inimigos(&sprites_array[1], &sprites_array[31], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[30], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[29], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[28], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[27], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[26], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[6], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[5], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[4], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_inimigos(&sprites_array[1], &sprites_array[3], &is_imortal, &vidas, offset_imortal) == 1) {
                        break;
                    }
                    if (collisao_queijo(&sprites_array[1], &sprites_array[2], &score, &difficulty, &difficulty_completed) == 1) {
                        game_state = 5;
                        is_game_state_on = 0;
                        break;
                    }
                    if (contador == 4000){
                        static_movement(&sprites_array[31], 1);
                        static_movement(&sprites_array[30], 1);
                        static_movement(&sprites_array[29], 1);
                        static_movement(&sprites_array[28], 1);
                        static_movement(&sprites_array[27], 1);
                        static_movement(&sprites_array[26], 1);
                        if (is_imortal == 1) {
                            contador_aux += 1;
                        }
                        contador = 0;
                    }
                    /* Condicionais de caso o jogador tenha sido atingido então animações do fantasminha ou do pisca são mostradas*/
                    if (ativar_pisca == 1) {
                        contador_pisca += 1;
                    }
                    if (contador_pisca == 100000 && contador_aux_pix < 10) {
                            contador_pisca = 0;
                            if (sprites_array[1].enable == 0) {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 1);
                            } else {
                                create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 0, 0, 0, 0, 0);
                            }
                            contador_aux_pix += 1;
                    } else if (contador_aux_pix == 10) {
                        contador_aux_pix = 0;
                        ativar_pisca = 0;
                    }
                    if (contador_aux == is_imortal_time + 50) {
                        ativar_pisca = 0;
                        create_sprite(1, 1, pos_x, pos_y, 0, 0, 0, 0, 1);
                        contador_aux = 0;
                        is_imortal = 0;
                    }
                    contador += 1;
                }
            }
        /* CASO O JOGADOR COMPLETE 5 OBJETIVOS COLETADOS A FASE ATUAL É COMPLETA E ELE IRA PARA A PROXIMA */
        } else if (game_state == 2) { /*FASE COMPLETA*/
            disable_sprite_player = 0;
            is_paused = 0;
            contador = 0;

            difficulty += 1;

            if(difficulty == 1){
                draw_fase_screen(2, 0);
            } else if(difficulty == 2){
                draw_fase_screen(3, 0);
            } else if(difficulty == 3){
                draw_fase_screen(4, 0);
            } else if(difficulty == 4){
                draw_fase_screen(5, 0);
            }
            usleep(2000000);
            game_state = 1;
            difficulty_completed = 1;
            start = 0;
        /* CASO O JOGADOR REINICIE O JOGO TODAS AS VARIAVEIS SÃO RESETADAS */
        } else if (game_state == 3) { /* JOGO REINICIADO */
            clear_all();
            action = 0;
            is_paused = 0;
            contador_aux_pix = 0;
            contador_pisca = 0;
            ativar_pisca = 0;
            disable_sprite_player = 0;
            sprites_array[1].offset = 0;
            vidas = 3;
            score = 0;
            power_amount = 1;
            is_imortal = 0;
            int i = 0;
            for(i; i < 31; i++) {
                sprites_array[i].collision = 0;
                sprites_array[i].enable = 0;
                sprites_array[i].pos_x = 0;
                sprites_array[i].pos_y = 0;
            }
            difficulty = 0;
            difficulty_completed = 1;
            start = 0;
            write_score(score);
            write_lifes(vidas);
            draw_restart_screen();
            usleep(2000000);
            game_state = 1;
        /* CASO O JOGADOR PERCA TODAS AS SUAS VIDAS O JOGO VAI PRA TELA DE GAME OVER E O JOGADOR TERA QUE REINICIAR PARA JOGAR NOVAMENTE */
        } else if (game_state == 4) { /* GAME OVER */
        
            if (is_game_state_on == 0) {
                disable_sprite_player = 0;
                printf("PASSOU AQUI\n");
                draw_game_over_screen();
                is_game_state_on = 1;
            }
        /* CASO O JOGADOR CONSIGA 25 PONTOS O JOGO VAI PARA A TELA DE VITORIA E O JOGADOR TERA QUE REINICIAR PARA JOGAR NOVAMENTE */
        } else if (game_state == 5) { /* WIN */
            if (is_game_state_on == 0) {
                draw_win_screen();
                is_paused = 0;
                int i = 0;
                for(i; i < 31; i++) {
                    sprites_array[i].collision = 0;
                    sprites_array[i].enable = 0;
                    sprites_array[i].pos_x = 0;
                    sprites_array[i].pos_y = 0;
                }
                usleep(2000000);
                start = 0;
                is_game_state_on = 1;
            }
        /* CASO JOGADOR DESEJE ENCERRAR O JOGO A TELA DE ENCERRAMENTO VAI SER DESENHADA E O LOOP VAI SER TERMINADO */
        } else if (game_state == 6) {
            sprites_array[1].enable = 0;
            draw_end_game_screen();
            break;
        }
    }
    return NULL;
}

/**
 * \brief           Loop auxiliar que detecta inputs do mouse.
 */
void* player_movement(void* arg) {
    while (1) {
        if (game_state == 1) {
        mouse_movement(&action, &power_amount);
        if (action == 1) {
            create_sprite(1, 1, sprites_array[1].pos_x, sprites_array[1].pos_y, 6, 0, 0, 0, 1);
        }
        change_coordinate(&sprites_array[1], pos_x, pos_y, 0);
        } else if (game_state == 6) {
            break;
        } else if (disable_sprite_player == 0) {
            usleep(500000);
            create_sprite(1, 1, 0, 0, 0, 0, 0, 0, 0);
            disable_sprite_player = 1;
        }
        //printf("\nX = %d , Y = %d\n", pos_x, pos_y);
    }
    return NULL;
}

int main() {


    /* ABRE TODOS OS ARQUIVOS DOS DRIVES */
    if (open_gpu_device() == 0)
        return 0;
    if (open_mouse_device() == 0){
        return 0;
    }
    if (open_botoes_device() == 0){
        return 0;
    }
    if (open_display_device() == 0){
        return 0;
    }

    /* SETA O GERADOR DE SUMEROS ALEATORIOS COM BASE NO HORARIO */
    srand(time(NULL));
    /* DESENHA TODOS OS SPRITES NA MEMORIA */
    draw_player();
    draw_enemy();
    draw_coin();
    draw_bomb();
    draw_bomb_animation();
    draw_ghost();
    draw_player_shild();

    /* LIMPA TODOS OS ELEMENTOS DA TELA*/
    clear_background_blocks();
    clear_poligonos();
    clear_sprites();
    set_background_color(0, 0, 0);

    /* SETA OS VALORES INICIAIS DO DISPLAY DE 7 SEGMENTOS*/
    write_start_display();

    /* CRIA O SPRITE DO PLAYER */
    create_sprite(1, 1, 0, 0, 0, 0, 0, 0, 0);  /* PLAYER */ 

    /* CRIA AS DUAS THREADS QUE SERÃO USADAS, UMA COM O LOOP PRINCIPAL E A OUTRA COMS OS INPUTOS DO MOUSE*/
    pthread_t thread1, thread2;
    game_state = 0;
    if (pthread_create(&thread1, NULL, loop_principal, NULL) != 0) {
        perror("Failed to create thread1");
        return 1;
    }

    if (pthread_create(&thread2, NULL, player_movement, NULL) != 0) {
        perror("Failed to create thread2");
        return 1;
    }

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    /* FECHA TODOS OS ARQUIVOS DOS DRIVES QUE FORAM ABERTOS*/
    close_gpu_devide();
    close_mouse_device();
    close_botoes_devide();
    close_display_device();

    return 0;
}