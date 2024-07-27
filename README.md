<div align="center">
<h1>Conversas entre Hardware e Software</h1>
</div>

# Catch The Cheese

```py
1. Clone esse repositório para sua máquina [git clone URL]
2. Faça conexão com a placa [ssh aluno@IP]
3. Faça uma cópia do arquivo para a placa por meio do scp:
   scp [ opcoes ] < usuario_fonte@endereco_IP >:/ < diretorio_do_arquivo_fonte/ arquivo_fonte > < usuario_destino@endereco_IP >:
   /<diretorio_do_arquivo_destino / arquivo_destino >
5. Navegue até o arquivo
6. Execute make
7. carregue o múdulo: sudo insmod gpu_driver.ko
6.  execute: gcc -o exec main.c gpu_lib.c

```

# Introdução

Os jogos digitais começaram como simples passatempos e se transformaram em verdadeiras obras de arte interativas, influenciando a cultura atual e mudando a forma como nos divertimos. Desde os dias dos jogos de arcade até os títulos modernos com gráficos incríveis e histórias envolventes, a indústria de games nunca parou de surpreender. Criar um jogo digital é uma jornada emocionante e complexa que envolve uma mistura de programação, design, arte e música.

Neste trabalho, vamos mergulhar no desenvolvimento de Catch the Cheese, explorando cada fase do processo, desde a ideia inicial até o produto final. Vamos ver como nossa equipe superou desafios e usou as tecnologias para dar vida ao jogo. Ao nos aprofundarmos na criação de Catch the Cheese, queremos mostrar todo o esforço e a criatividade envolvidos em transformar uma ideia em uma experiência de jogo inesquecível.

# Requisitos do sistema

- [x] O código deve ser escrito em linguagem C;
- [x] O sistema só poderá utilizar os componentes disponíveis na placa;
- [x] Um novo sprite deve ser colocado na memória e utilizado no jogo;
- [x] As ações do ator do jogo (pulo, tiro, etc.) devem ser comandadas pelos botões do mouse;
- [x] A variação da velocidade no movimento do mouse deve ser refletida na ação do ator do jogo. Por exemplo, no jogo breakout a barra se move com velocidade maior se o movimento do mouse for brusco;

# Descrição das ferramentas utilizadas

- ### Nano:
  O GNU Nano é um editor de texto minimalista, integrado de forma nativa em sistemas operacionais Linux e operado diretamente no terminal do sistema. Este software foi um dos utilitários de edição de texto empregados durante a codificação do projeto.
- ### Linguagem C:
  Foi utilizado linguagem C para codificar o projeto devido à sua capacidade de ser executada em computadores com recursos limitados, que não suportam softwares mais robustos. Além disso, sua proximidade com a arquitetura de máquina e a disponibilidade de bibliotecas-padrão facilitam a interação com o sistema operacional, tornando mais eficiente a manipulação dos drivers dos dispositivos utilizados no sistema.
- ### GNU

  O GNU Compiler Collection (GCC) é uma ferramenta de compilação de código aberto amplamente utilizada, oferecida gratuitamente para diversas linguagens de programação. Foi instalado e empregado no sistema operacional da plataforma De1-SoC para compilar os códigos escritos em C pelo grupo de desenvolvimento.

- ### Makefile

  Um arquivo Makefile é um script especial usado em ambientes de desenvolvimento de software para automatizar o processo de compilação, vinculação e execução de programas. Ele define as regras e dependências entre os arquivos do seu projeto, facilitando a construção e a manutenção do software.

- ### SSH

  O SSH (Secure Shell) é um protocolo de rede usado para comunicação segura e controle remoto de dispositivos através de uma conexão criptografada. Ele é amplamente utilizado para acessar servidores e dispositivos remotos pela internet, garantindo a proteção das informações transmitidas por meio de criptografia forte.

- ### Visual Studio Code

  O Visual Studio Code, mais conhecido como VSCode, é um editor de código-fonte poderoso e gratuito desenvolvido pela Microsoft. Ele se destaca por ser leve, mas extremamente versátil, sendo amplamente utilizado por desenvolvedores de todo o mundo. Com suporte para uma vasta gama de linguagens de programação, o VSCode oferece uma experiência de desenvolvimento intuitiva e eficiente.

# Kit de Desenvolvimento De1-Soc

A Plataforma De1-SoC é uma solução de hardware robusta que integra os poderosos núcleos Cortex-A9 com a flexibilidade de um FPGA. Isso permite aos usuários criar sistemas altamente adaptáveis, combinando desempenho de processamento com capacidade de personalização. Além disso, o SoC inclui um sistema de processador (HPS) baseado em ARM, conectado ao FPGA, facilitando a comunicação eficiente entre o processador e a lógica programável. Com recursos como memória DDR3, capacidades de vídeo e áudio e conectividade Ethernet, a placa DE1 SoC é ideal para uma variedade de aplicações.

</br>
<div align="center">
<img src="https://github.com/mtheuz/Problema-1--Sistemas-Digitais/assets/77650601/18d11607-03e9-4068-8bd0-31e46bd1895c" width="700">
</div>
</br>

O diagrama de blocos da placa mostra como os componentes estão interconectados. Todas as conexões são feitas por meio do dispositivo Cyclone V SoC FPGA para oferecer aos usuários a maior flexibilidade possível. Isso significa que os usuários têm a liberdade de configurar o FPGA de acordo com suas necessidades específicas, permitindo a implementação de uma ampla variedade de designs de sistemas.
</br>

<div align="center">
<img src="https://github.com/mtheuz/Problema-1--Sistemas-Digitais/assets/77650601/b623ebde-9feb-4b2f-a57f-4e8153df9faf" width="700">
</div>
</br>

# 🖥️ Arquitetura do processador ARM Cortex-A9

O processador Cortex-A9 800MHz MPCore é um design de CPU baseado na arquitetura ARMv7 , seguindo a Instruction Set Architecture (ISA) específico dessa arquitetura. Com um clock de 800MHz, este processador é dual-core, significando que possui dois núcleos de CPU idênticos. Cada núcleo possui sua própria hierarquia de cache, incluindo caches L1 (instrução e dados) e um cache L2 compartilhado entre os núcleos. Além disso, o Cortex-A9 é projetado com uma pipeline moderadamente profunda, aproveitando unidades funcionais especializadas, como unidades de execução aritmética e lógica, unidades de acesso à memória e unidades de controle de fluxo, para otimizar a execução de instruções e maximizar o desempenho geral da CPU.

# Arquitetura do processador gráfico

A arquitetura apresentada na imagem abaixo mostra um sistema de processamento gráfico integrado, composto por várias unidades funcionais conectadas.

![image](https://github.com/mtheuz/Problema-2---Sistemas-Digitais/assets/77650601/313ebf3a-a4ba-4506-a048-b9c2a85a5fd0)

O Processador de Propósito Geral (GPP) executa instruções gerais. O GPP possui uma Unidade de Memória que inclui Memória de Instruções para armazenar as instruções a serem executadas e Memória de Dados para os dados necessários à execução das instruções. As interfaces do GPP incluem periféricos para comunicação com outras partes do sistema e um barramento (bus) para facilitar a comunicação de dados. Além disso, o GPP utiliza um contador de pulsos e um gerador de pulsos para sincronização e controle de tempo.

A Unidade de Processamento Gráfico (GPU) inclui um buffer de instruções com duas filas FIFO (A e B) para armazenar temporariamente as instruções gráficas antes de serem processadas. O campo de opcode e endereçamento no buffer de instruções armazena os códigos de operação e endereços das instruções. O núcleo da GPU (GPU core) processa as instruções gráficas, acessa as memórias de dados (memória de sprites e memória de background) e gera a saída de vídeo.

A memória de sprites armazena bitmaps de sprites, enquanto a memória de background armazena bitmaps do fundo da tela. A memória de sprites possui 12.800 palavras de 9 bits (3 bits por componente RGB), permitindo o armazenamento de 32 sprites de 20x20 pixels cada, totalizando 400 posições de memória por sprite. A memória de background possui 4.800 palavras de 9 bits para modificar pequenas partes do fundo da tela.

O fluxo de dados começa com o carregamento do código pelo usuário na memória de instruções do GPP. O GPP processa o código, gerencia a comunicação entre as diferentes unidades e gera instruções gráficas que são passadas para o buffer de instruções da GPU. A GPU processa essas instruções, acessa as memórias de dados e gera a saída de vídeo. Finalmente, a saída de vídeo é enviada ao monitor VGA para exibição.

Essa arquitetura permite que um usuário interaja com jogos e aplicativos gráficos, proporcionando uma plataforma eficiente para a execução e exibição de gráficos complexos em tempo real. O sistema é capaz de administrar 31 sprites em um mesmo frame, renderizando imagens em uma taxa de aproximadamente 60 frames por segundo, o que resulta em uma tela impressa a cada 16,768 ms. Além disso, um co-processador gerencia a construção de polígonos convexos, como quadrados e triângulos, que são renderizados na tela junto com os sprites e o background.

# Captura dos dados do mouse

O arquivo `/dev/input/mice` desempenha um papel crucial no registro de eventos do mouse no ambiente Linux. Funcionando como uma interface direta, ele permite que os programas acessem os dados brutos gerados pelos movimentos e cliques do mouse, sem precisar lidar diretamente com os drivers de dispositivo. Quando um usuário move o mouse ou clica em um botão, essas ações são traduzidas em dados brutos pelo driver do mouse e registradas na fila de eventos do sistema operacional. O arquivo `/dev/input/mice` fornece acesso direto a esses eventos. Para interagir com o arquivo `/dev/input/mice`, são utilizadas as funções `open()` e `read()`. Os dados lidos são armazenados em um vetor como bytes, onde cada byte representa um evento de mouse. O primeiro byte corresponde ao evento de clique do mouse, o segundo byte representa o deslocamento no eixo x, e o terceiro byte representa o deslocamento no eixo y.

# Display de 7 Segmentos

A placa DE1-SoC possui seis displays de 7 segmentos, que podem ser combinados para exibir números em diferentes tamanhos. A Figura abaixo ilustra a conexão dos sete segmentos (ânodo comum) com os pinos no FPGA Cyclone V SoC. Cada segmento pode ser ativado ou desativado aplicando, respectivamente, um nível lógico baixo ou alto a partir do FPGA. Em cada display, os segmentos são indexados de 0 a 6, conforme mostrado na abaixo. os displays de 7 segmentos foram utilizados para mostrar status do jogo.

<div align="center">
<img src="https://github.com/user-attachments/assets/79783d02-b9a4-4b08-8afc-31f8bbafdc7d" width="700">
</div>
</br>

# Push-buttons

A placa possui quatro botões conectados ao FPGA, conforme ilustrado na abaixo, que mostra as conexões entre os botões e o FPGA Cyclone V SoC. Um circuito Schmitt trigger é implementado para atuar como debounce dos botões Os quatro botões, nomeados KEY0, KEY1, KEY2 e KEY3, saem do dispositivo Schmitt trigger e são conectados diretamente ao FPGA Cyclone V SoC. Quando pressionado, o botão gera um nível lógico baixo, e quando não pressionado, um nível lógico alto. Devido ao debounce dos botões, eles podem ser utilizados como entradas de clock ou reset em um circuito. Os botões foram utilizados para realizar ações como pausar, finalizar, reiniciar e retomar o jogo.

<div align="center">
<img src="https://github.com/user-attachments/assets/f5927d1c-c792-4ab7-9c1a-2ccf15229373" width="700">
</div>
</br>

# VGA

A placa DE1-SoC possui um conector D-SUB de 15 pinos para saída VGA. Os sinais de sincronização VGA são gerados pelo FPGA Cyclone V SoC, e o conversor digital-analógico ADV7123 transforma os sinais digitais em analógicos para as cores vermelho, verde e azul. Suporta até o padrão SXGA (1280x1024) com sinais transmitidos a 100MHz. A Figura 3-22 mostra as conexões entre o FPGA e a VGA. As especificações de tempo para a sincronização VGA e dados RGB incluem um pulso ativo-baixo de hsync, seguido pelos períodos de back porch, intervalo de exibição e front porch. A sincronização vertical (vsync) é semelhante, com um pulso indicando o fim de um quadro e o início do próximo. A entrada VGA foi utilizada para conectar um monitor e proporcionar uma demonstração visual do jogo.

<div align="center">
<img src="https://github.com/user-attachments/assets/8d0b272d-b36e-4552-9332-7e28dbd9596d" width="700">
</div>
</br>

# Bibioltecas

## gpu_lib.h

A biblioteca gpu_lib.h fornece uma interface para interagir com um driver de GPU, permitindo a manipulação de sprites, polígonos e cores de fundo através de funções específicas. Abaixo está uma explicação detalhada de cada parte da biblioteca:

| Nome da Função            | Parâmetros                                                                                                                                                   | Descrição                                                                                                                   |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------- |
| `open_gpu_device`         | Nenhum                                                                                                                                                       | Abre o arquivo do driver da GPU. Retorna 1 se bem-sucedido, 0 caso contrário.                                               |
| `close_gpu_devide`        | Nenhum                                                                                                                                                       | Fecha o arquivo do driver da GPU.                                                                                           |
| `set_background_color`    | `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                                        | Configura a cor de fundo com valores RGB. Retorna 0 se falhar, 1 se bem-sucedido.                                           |
| `set_sprite`              | `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t sp`                                                                                    | Define um sprite na tela com as coordenadas, deslocamento e ativação especificados. Retorna 0 se falhar, 1 se bem-sucedido. |
| `set_poligono`            | `uint16_t address`, `uint16_t ref_x`, `uint16_t ref_y`, `uint8_t size`, `uint8_t r`, `uint8_t g`, `uint8_t b`, `uint8_t shape`                               | Define um polígono na tela com as características especificadas. Retorna 0 se falhar, 1 se bem-sucedido.                    |
| `set_background_block`    | `uint8_t column`, `uint8_t line`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                      | Preenche um bloco de fundo 8x8 pixels com a cor especificada. Retorna 0 se falhar, 1 se bem-sucedido.                       |
| `set_sprite_pixel_color`  | `uint16_t address`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                    | Muda a cor RGB de um pixel específico em um sprite. Retorna 1 se bem-sucedido, 0 caso contrário.                            |
| `change_coordinate`       | `Sprite *sp`, `uint16_t new_x`, `uint16_t new_y`, `uint8_t mirror`                                                                                           | Atualiza as coordenadas de um sprite e redefine sua posição na tela.                                                        |
| `collision`               | `Sprite *sp1`, `Sprite *sp2`                                                                                                                                 | Verifica se há colisão entre dois sprites. Retorna 1 se há colisão, 0 caso contrário.                                       |
| `clear_background_blocks` | Nenhum                                                                                                                                                       | Define o valor RGB "510" para todos os blocos de fundo, restaurando a cor padrão.                                           |
| `fill_background_blocks`  | `uint8_t line`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                        | Preenche todos os blocos de fundo a partir de uma linha especificada com a cor dada.                                        |
| `create_fixed_sprite`     | `uint8_t array_position`, `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t sp`                                                          | Cria um sprite fixo na posição especificada e retorna 1 se bem-sucedido, 0 caso contrário.                                  |
| `create_sprite`           | `uint8_t array_position`, `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t step_x`, `uint8_t step_y`, `uint8_t direction`, `uint8_t sp` | Cria um sprite móvel na posição especificada e retorna 1 se bem-sucedido, 0 caso contrário.                                 |
| `clear_poligonos`         | Nenhum                                                                                                                                                       | Desativa todos os polígonos configurando seu tamanho para 0.                                                                |
| `clear_sprites`           | Nenhum                                                                                                                                                       | Desativa todos os sprites nos registradores de 1 a 31.                                                                      |
| `static_movement`         | `Sprite *sp`, `uint8_t mirror`                                                                                                                               | Atualiza as coordenadas de um sprite com base na direção e deslocamento, considerando a condição de espelhamento.           |
| `clear_all`               | Nenhum                                                                                                                                                       | Limpa todos os blocos de fundo, polígonos e sprites.                                                                        |
| `reset_sprites`           | Nenhum                                                                                                                                                       | Reativa todos os sprites no array `sprites_array` que estão ativados.                                                       |

## draw_sprites.h e draw_screens.h

Foi criada uma nova estrutura para armazenar as informações dos novos sprites e telas a serem desenhadas no monitor, utilizando os arquivos `draw_sprites.h` e `draw_screens.h`.

### draw_sprites.h

| Nome da Função      | Parâmetros | Descrição                              |
| ------------------- | ---------- | -------------------------------------- |
| `draw_player`       | Nenhum     | Desenha o sprite do jogador.           |
| `draw_enemy`        | Nenhum     | Desenha o sprite do inimigo.           |
| `draw_bomb`         | Nenhum     | Desenha o sprite da ratoeira.          |
| `draw_ghost`        | Nenhum     | Desenha o sprite do fantasma.          |
| `draw_coin`         | Nenhum     | Desenha o sprite do queijo.            |
| `draw_player_shild` | Nenhum     | Desenha o sprite do escudo do jogador. |

### draw_screens.h

| Nome da Função           | Parâmetros                 | Descrição                                      |
| ------------------------ | -------------------------- | ---------------------------------------------- |
| `draw_pause_screen`      | Nenhum                     | Limpa a tela e desenha a tela de pausa.        |
| `draw_win_screen`        | Nenhum                     | Limpa a tela e desenha a tela de vitória.      |
| `draw_fase_screen`       | `int number`, `int repeat` | Desenha a tela da fase de acordo com o número. |
| `draw_restart_screen`    | Nenhum                     | Limpa a tela e desenha a tela de reinício.     |
| `draw_game_over_screen`  | Nenhum                     | Limpa a tela e desenha a tela de game over.    |
| `draw_start_game_screen` | Nenhum                     | Limpa a tela e desenha a tela inicial do jogo. |
| `draw_end_game_screen`   | Nenhum                     | Limpa a tela e desenha a tela de fim de jogo.  |
| `draw_bg_cenario`        | Nenhum                     | Desenha o cenário de fundo.                    |

## botoes_control.h e display_control.h

Duas novas bibliotecas foram criadas para se comunicar com os componentes da placa, botoes_control.h e display_control.h, uma fica encarregada do funcionamento dos botões e a outra do display de 7-segmentos

### botoes_control.h

| Nome da Função        | Parâmetros | Descrição                      |
| --------------------- | ---------- | ------------------------------ |
| `open_botoes_device`  | Nenhum     | Abre o dispositivo de botões.  |
| `read_botoes`         | Nenhum     | Lê o estado dos botões.        |
| `close_botoes_device` | Nenhum     | Fecha o dispositivo de botões. |

### display_control.h

| Nome da Função         | Parâmetros                      | Descrição                                                        |
| ---------------------- | ------------------------------- | ---------------------------------------------------------------- |
| `open_display_device`  | Nenhum                          | Abre o dispositivo de display e mapeia a memória.                |
| `write_number_display` | `int display_digit, int number` | Escreve um número em um dos displays HEX.                        |
| `write_score`          | `int score`                     | Escreve a pontuação no display (2 dígitos).                      |
| `write_lifes`          | `int vidas`                     | Escreve o número de vidas restantes no display (2 dígitos).      |
| `close_display_device` | Nenhum                          | Fecha o dispositivo de display e desfaz o mapeamento da memória. |

# Desenvolvimento do Jogo

### Movimento do mouse

A função `mouse_movement()` tem a tarefa de processar eventos do mouse para atualizar a posição do cursor na tela. Inicialmente, a função lê os dados do mouse, que incluem informações sobre o estado dos botões e o deslocamento do cursor. Em seguida, ela aplica uma forma básica de aceleração ao atualizar as coordenadas do cursor, reduzindo o impacto do movimento ao dividir o deslocamento por 2. Isso ajuda a suavizar o movimento do cursor e a evitar movimentos excessivamente rápidos. Além disso, a função garante que o cursor permaneça dentro de uma área específica da tela, ajustando suas coordenadas para não ultrapassar os limites estabelecidos. Embora essa aceleração seja simples, ela pode ser ajustada para comportamentos mais avançados conforme necessário.

### Verificação de colisão

Para verificar se dois sprites colidem em um jogo, criamos a função `collision`, que recebe as coordenadas X e Y de dois sprites e determina se eles estão se sobrepondo. A função calcula as bordas direita e inferior de ambos os sprites, assumindo que cada sprite tem um tamanho fixo de 20 unidades em largura e altura. Em seguida, ela compara as coordenadas dos sprites para verificar se há alguma interseção entre suas áreas. Se as coordenadas de um sprite estiverem fora dos limites do outro, a função conclui que não há colisão, definindo a propriedade de colisão dos sprites como 0 e retornando 0. Caso contrário, se houver sobreposição, a propriedade de colisão é ajustada para 1 para ambos os sprites e a função retorna 1, indicando que houve uma colisão.

### Aleatoriedade dos objetos

Para tornar o jogo mais interessante e dinâmico, os inimigos (gatos e ratoeiras) e o queijo são posicionados aleatoriamente na tela a cada nova geração. Para realizar essa aleatoriedade, a tela de 640x480 pixels é dividida em uma grade de 20 partes, resultando em células de 32x24 pixels cada. Com essa divisão, obtemos um total de 768 posições válidas onde os objetos podem ser colocados. Dessa forma, a posição de cada objeto é escolhida aleatoriamente dentro dessas células, garantindo que o layout do jogo seja diferente a cada vez que ele é iniciado, o que aumenta a imprevisibilidade e o desafio para o jogador.

### Utilização de Threads

Para evitar conflitos entre a utilização do mouse e os botões da placa, o sistema do jogo utiliza duas threads distintas. A primeira thread é responsável por capturar as informações fornecidas pelo mouse, controlar o sprite do jogador principal e executar as ações correspondentes. Isso permite que o movimento e as interações do jogador sejam processados em tempo real, sem interferir em outras operações do jogo. A segunda thread gerencia o loop principal do jogo e as verificações das ações dos botões da placa. Ela assegura que as entradas dos botões sejam processadas de forma eficiente e que o jogo mantenha seu fluxo contínuo.

# O jogo "Catch the cheese"

No jogo "Catch The Cheese", o jogador controla um rato cujo objetivo é coletar todos os queijos de um local enquanto foge dos gatos. Durante o jogo, ratoeiras surgem para dificultar o objetivo principal. O jogador vence o jogo ao coletar todos os queijos e perde caso os gatos ou as ratoeiras o peguem.

## Objetivo

O jogador assume o papel de um rato esperto, cuja missão é coletar queijos espalhados pelo cenário. A cada 5 queijos coletados, o jogador avança para uma nova fase, devendo coletar mais 5 queijos. A jornada se completa ao atingir um total de 25 queijos.

## Desafios

Gatos aparecerão para complicar a vida do nosso pequeno herói. Eles se movimentam tanto na vertical quanto na horizontal e, se colidirem com o rato, o jogador perderá uma das suas 3 vidas. Além disso, ratoeiras estarão espalhadas pelo caminho, representando mais uma ameaça.

## Poderes e Habilidades

- **Fantasma Temporário:** Ao ser atingido por um gato ou ratoeira, o rato se transforma em um fantasma por um curto período, ficando imune a danos.
- **Escudo Protetor:** Uma vez por jogo, o jogador pode ativar o escudo clicando com o botão esquerdo do mouse. O escudo protege o rato de perder uma vida na próxima vez que for atingido.

## Fim de Jogo

Se o jogador perder todas as 3 vidas, ao próximo impacto o jogo termina com um "Game Over" e ele terá que reiniciar para jogar novamente.

## Progresso


- Fase 1: Coletar 5 queijos / 2 inimigos

<div align="center">
<img src="https://github.com/user-attachments/assets/cba160f2-24b3-46a9-9e82-d7fe03f29a87" width="300">
</div>
</br>

- Fase 2: Coletar 5 queijos / 4 inimigos

<div align="center">
<img src="https://github.com/user-attachments/assets/b143107f-5392-4f85-a2b7-1288aa5b84f7" width="300">
</div>
</br>

- Fase 3: Coletar 5 queijos / 6 inimigos

<div align="center">
<img src="https://github.com/user-attachments/assets/44e88333-2b04-48f3-ab5c-b4054e9da974" width="300">
</div>
</br>

- Fase 4: Coletar 5 queijos / 6 inimigos / 2 ratoeiras

<div align="center">
<img src="https://github.com/user-attachments/assets/ae4f23a3-5407-4e6d-b91b-858f997f595b" width="300">
</div>
</br>

- Fase 5: Coletar 5 queijos /  6 inimgos / 4 ratoeiras

<div align="center">
<img src="https://github.com/user-attachments/assets/236a4d87-8f84-466e-a4ab-f0e1c779e487" width="300">
</div>
</br>

- **Total: 25 queijos**

Foram criadas 5 fases no total, sendo as primeiras fases mais fáceis e as últimas mais difíceis. Das fases 1 a 3, mais gatos são adicionados enquanto nas fases 4 e 5 as ratoeiras começam a aparecer. Cada vez que o jogador passa de fase, a velocidade com que os gatos se movem é aumentada.

A cada nova fase, os desafios aumentam, tornando a jornada mais emocionante e desafiadora. Prepare-se para uma aventura cheia de surpresas e perigos!

# Fluxo do jogo

O fluxograma ilustra a sequência de passos para o funcionamento do jogo, começando com a inicialização da variável `game_state` e a impressão da tela inicial. Em seguida, o sistema lê o botão `KEY0`. Se `KEY0` for pressionado (`KEY0 == 1`), duas threads são iniciadas: `THREAD1` e `THREAD2`. `THREAD1` é responsável pelo movimento e ações do mouse, enquanto `THREAD2` cuida do loop principal do jogo e da ação dos botões. Ambas as threads verificam constantemente o estado do jogo (`game_state`), e se o `game_state` for maior ou igual a 6, o jogo termina e o sistema segue para a saída. Se `KEY0` não for pressionado, o sistema continua verificando até que seja detectada a entrada do usuário.

## Funcionamento dos botões 

O fluxograma detalha o funcionamento do loop principal do jogo (`THREAD2`) e as ações dos botões. Aqui está uma descrição passo a passo de cada seção:

1. **Início:**
   - O processo começa lendo os inputs dos botões `KEY0`, `KEY1`, `KEY2` e `KEY3`.
   - A variável `game_state` é modificada com base nos botões acionados.

2. **Jogando:**
   - **Condição:** `game_state == 0`
   - Se a condição `fase_comp == 0` ou `KEY_PRESS == 1` for verdadeira, o jogo entra no **loop das fases**.

3. **Fase Completa:**
   - **Condição:** `game_state == 1`
   - Gera a próxima fase.

4. **Reiniciando:**
   - **Condição:** `game_state == 3`
   - Reinicia o jogo.

5. **Perdeu:**
   - **Condição:** `game_state == 4`
   - Desenha a tela "Game Over".

6. **Ganhou:**
   - **Condição:** `game_state == 5`
   - Desenha a tela "You Win".

7. **Finalizou:**
   - **Condição:** `game_state == 6`
   - Finaliza o jogo e segue para a saída.

Cada estado do jogo é verificado sequencialmente, e as ações são tomadas com base no valor atual de `game_state`, permitindo uma transição fluida entre diferentes fases e condições de jogo.


## Movimento e Ações do Mouse
Este fluxograma descreve o fluxo de execução da `THREAD1`, responsável por ler e processar os movimentos e ações do mouse em um jogo. 

1. **Início**
   - O processo começa no estado inicial.

2. **Leitura dos Inputs do Mouse**
   - A thread lê os inputs do mouse, que incluem:
     - `POS_X`: Posição X do mouse.
     - `POS_Y`: Posição Y do mouse.
     - `LEFT_CLICK`: Estado do clique esquerdo do mouse.

3. **Verificação do Estado do Jogo**
   - A thread verifica se o `game_state` é igual a 6:
     - Se verdadeiro, o fluxo vai para a saída.
     - Se falso, a thread verifica se o `game_state` é igual a 1.

4. **Incremento da Posição do Sprite**
   - Se o `game_state` é igual a 1, a thread incrementa a posição do sprite do jogador com base nos valores de `POS_X` e `POS_Y`.

5. **Verificação do Clique Esquerdo**
   - A thread verifica se o `LEFT_CLICK` é igual a 1:
     - Se verdadeiro, a habilidade do jogador é ativada (`action = 1`).
     - Se falso, o fluxo retorna à leitura dos inputs do mouse.

6. **Saída**
   - Se o `game_state` é igual a 6, o fluxo vai para a saída e a thread encerra seu processamento.


## Loop das Fases

O fluxograma detalha o funcionamento do loop das fases no jogo. Aqui está uma descrição passo a passo de cada seção:

1. **Início:**
   - Desenha o background.

2. **Geração de Inimigos:**
   - Gera inimigos com base na fase atual.

3. **Leitura dos Inputs dos Botões:**
   - Lê os inputs dos botões `KEY0`, `KEY1` e `KEY3`.
   - Se `KEY0 == 1`, `KEY1 == 1` ou `KEY3 == 1`, sinaliza que um botão foi acionado (`KEY_PRESS == 1`), e muda o estado do jogo para `game_state == 4` (saída).

4. **Movimento dos Inimigos:**
   - Move os inimigos.

5. **Verificação de Colisões:**
   - Verifica se há colisões.

6. **Geração de Novo Objetivo (se necessário):**
   - Gera um novo objetivo se preciso.

7. **Verificação de Vidas:**
   - Se `vidas < 0`, muda o estado do jogo para `game_state == 4` (saída).

8. **Verificação de Pontuação:**
   - Se `score % 5 == 0`, incrementa a variável da fase (`fase + 1`) e `game_state = 2` (saída).

9. **Atualização do Estado do Jogo:**
   - Se `score == 25`, atualiza o estado do jogo para `GANHOU` (`game_state = 5`).

Cada um desses passos é executado em sequência para garantir a mecânica de avanço de fases, verificação de condições de vitória ou derrota, e transições adequadas entre os diferentes estados do jogo.

# Conclusão
Desenvolver "Catch the Cheese" foi uma jornada rica em aprendizado e desafios, envolvendo diversas disciplinas da computação, como programação em C, uso de hardware específico e design de jogos. A experiência proporcionou uma compreensão profunda da integração entre software e hardware, além de aprimorar habilidades em resolução de problemas e trabalho em equipe.