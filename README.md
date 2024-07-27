<div align="center">
<h1>Conversas entre Hardware e Software</h1>
</div>

# Como rodar o projeto

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

# 📖 1. Introdução

### Introdução

Os jogos digitais começaram como simples passatempos e se transformaram em verdadeiras obras de arte interativas, influenciando a cultura atual e mudando a forma como nos divertimos. Desde os dias dos jogos de arcade até os títulos modernos com gráficos incríveis e histórias envolventes, a indústria de games nunca parou de surpreender. Criar um jogo digital é uma jornada emocionante e complexa que envolve uma mistura de programação, design, arte e música.

Neste trabalho, vamos mergulhar no desenvolvimento de Catch the Cheese, explorando cada fase do processo, desde a ideia inicial até o produto final. Vamos ver como nossa equipe superou desafios e usou as tecnologias para dar vida ao jogo. Ao nos aprofundarmos na criação de Catch the Cheese, queremos mostrar todo o esforço e a criatividade envolvidos em transformar uma ideia em uma experiência de jogo inesquecível.

# 🎯 2. Requisitos do sistema

- [x] O código deve ser escrito em linguagem C;
- [x] O sistema só poderá utilizar os componentes disponíveis na placa;
- [x] Um novo sprite deve ser colocado na memória e utilizado no jogo;
- [x] As ações do ator do jogo (pulo, tiro, etc.) devem ser comandadas pelos botões do mouse;
- [x] A variação da velocidade no movimento do mouse deve ser refletida na ação do ator do jogo. Por exemplo, no jogo breakout a barra se move com velocidade maior se o movimento do mouse for brusco;

# 📝 3. Descrição das ferramentas utilizadas

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

## gpu_lib.c

A biblioteca gpu_lib.c fornece uma interface para interagir com um driver de GPU, permitindo a manipulação de sprites, polígonos e cores de fundo através de funções específicas. Abaixo está uma explicação detalhada de cada parte da biblioteca:

| Nome da Função            | Parâmetros                                                                                                                                                   | Funcionalidade                                                                                                              |
| ------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------ | --------------------------------------------------------------------------------------------------------------------------- |
| `open_gpu_device`         | Nenhum                                                                                                                                                         | Abre o arquivo do driver da GPU. Retorna 1 se bem-sucedido, 0 caso contrário.                                               |
| `close_gpu_devide`        | Nenhum                                                                                                                                                         | Fecha o arquivo do driver da GPU.                                                                                           |
| `set_background_color`    | `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                                        | Configura a cor de fundo com valores RGB. Retorna 0 se falhar, 1 se bem-sucedido.                                           |
| `set_sprite`              | `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t sp`                                                                                    | Define um sprite na tela com as coordenadas, deslocamento e ativação especificados. Retorna 0 se falhar, 1 se bem-sucedido. |
| `set_poligono`            | `uint16_t address`, `uint16_t ref_x`, `uint16_t ref_y`, `uint8_t size`, `uint8_t r`, `uint8_t g`, `uint8_t b`, `uint8_t shape`                               | Define um polígono na tela com as características especificadas. Retorna 0 se falhar, 1 se bem-sucedido.                    |
| `set_background_block`    | `uint8_t column`, `uint8_t line`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                      | Preenche um bloco de fundo 8x8 pixels com a cor especificada. Retorna 0 se falhar, 1 se bem-sucedido.                       |
| `set_sprite_pixel_color`  | `uint16_t address`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                    | Muda a cor RGB de um pixel específico em um sprite. Retorna 1 se bem-sucedido, 0 caso contrário.                            |
| `change_coordinate`       | `Sprite *sp`, `uint16_t new_x`, `uint16_t new_y`, `uint8_t mirror`                                                                                           | Atualiza as coordenadas de um sprite e redefine sua posição na tela.                                                        |
| `collision`               | `Sprite *sp1`, `Sprite *sp2`                                                                                                                                 | Verifica se há colisão entre dois sprites. Retorna 1 se há colisão, 0 caso contrário.                                       |
| `clear_background_blocks` | Nenhum                                                                                                                                                         | Define o valor RGB "510" para todos os blocos de fundo, restaurando a cor padrão.                                           |
| `fill_background_blocks`  | `uint8_t line`, `uint8_t R`, `uint8_t G`, `uint8_t B`                                                                                                        | Preenche todos os blocos de fundo a partir de uma linha especificada com a cor dada.                                        |
| `create_fixed_sprite`     | `uint8_t array_position`, `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t sp`                                                          | Cria um sprite fixo na posição especificada e retorna 1 se bem-sucedido, 0 caso contrário.                                  |
| `create_sprite`           | `uint8_t array_position`, `uint8_t reg`, `uint16_t x`, `uint16_t y`, `uint8_t offset`, `uint8_t step_x`, `uint8_t step_y`, `uint8_t direction`, `uint8_t sp` | Cria um sprite móvel na posição especificada e retorna 1 se bem-sucedido, 0 caso contrário.                                 |
| `clear_poligonos`         | Nenhum                                                                                                                                                         | Desativa todos os polígonos configurando seu tamanho para 0.                                                                |
| `clear_sprites`           | Nenhum                                                                                                                                                         | Desativa todos os sprites nos registradores de 1 a 31.                                                                      |
| `static_movement`         | `Sprite *sp`, `uint8_t mirror`                                                                                                                               | Atualiza as coordenadas de um sprite com base na direção e deslocamento, considerando a condição de espelhamento.           |
| `clear_all`               | Nenhum                                                                                                                                                         | Limpa todos os blocos de fundo, polígonos e sprites.                                                                        |
| `reset_sprites`           | Nenhum                                                                                                                                                         | Reativa todos os sprites no array `sprites_array` que estão ativados.                                                       |

## draw_sprites.c e draw_screens.c

Foi criada uma nova estrutura para armazenar as informações dos novos sprites e telas a serem desenhadas no monitor, utilizando os arquivos `draw_sprites.h` e `draw_screens.h`.

### draw_sprites.c

| Nome da Função        | Descrição                              | Parâmetros |
| --------------------- | -------------------------------------- | ---------- |
| `draw_player`         | Desenha o sprite do jogador.           | Nenhum     |
| `draw_enemy`          | Desenha o sprite do inimigo.           | Nenhum     |
| `draw_bomb`           | Desenha o sprite da bomba.             | Nenhum     |
| `draw_bomb_animation` | Desenha a animação da bomba.           | Nenhum     |
| `draw_ghost`          | Desenha o sprite do fantasma.          | Nenhum     |
| `draw_coin`           | Desenha o sprite da moeda.             | Nenhum     |
| `draw_player_shild`   | Desenha o sprite do escudo do jogador. | Nenhum     |

### screens.c

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
