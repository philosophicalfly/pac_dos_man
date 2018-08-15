# PAC-DOS-MAN

## DEFINIÇÕES:

### Estruturas utilizadas:  

- str_pacman (Pacman):

Contém as posições x e y atuais do pacman, as posições x e y iniciais do pacman e uma flag se o pacman está ou não com o poder ativo.

- str_ghost (Ghost):

Contém as posições x e y atuais de um fantasma, as posições x e y iniciais de um fantasma, uma flag se ele está vivo ou morto, e a última ação realizada pelo mesmo.

### Funções utilizadas: 

- int Find_Ghost_Qtd

Recebe: Ponteiro para a matriz map.

O objetivo dessa função é contar quantos fantasmas estão no labirinto obtido do arquivo. Isso é feito com dois for encadeados, através dos quais a matriz inteira é percorrida procurando pelo caractere "W" e incrementando o contador qnt toda vez que um é encontrado. Esta função retorna o valor final de qnt após percorrer a matriz.

- int Get_Map

Recebe: Ponteiro para a matriz map.

O objetivo dessa função é obter o labirinto usado como mapa. A matriz é preenchida, caractere por caractere obtido do arquivo que foi aberto. Caso haja um erro na abertura do arquivo, retorna 0. Caso o arquivo seja aberto e preenchido sem problemas, retorna 1.

- void Find_Pacman

Recebe: Ponteiro para a matriz map, Ponteiros para as posições x e y do pacman.

A função percorre a matriz através de dois for, atrás do caractere "C", que denomina
a posição inicial do pacman, e atribui as coordenadas desse caractere às posições iniciais
do pacman.

- void Find_Ghost

Recebe: Ponteiro para a matriz map, Ponteiros para as posições x e y de um fantasma, Índice do fantasma atual.

A função percorre a matriz através de dois for, atrás do caractere "W", que denomina
a posição inicial de um fantasma. A variável qnt é utilizada para verificar se o fantasma encontrado é o fantasma de índice correto, e caso for, atribui as coordenadas x e y do caractere às posições iniciais do fantasma com aquele índice.

- void Print_Map

Recebe: Ponteiro para a matriz map.

Essa função printa a matriz obtida do arquivo no terminal.

- void Update_Score

Recebe: Ponteiro para a variável player_score, valor a acrescentar no score.

A função atualiza a variável player_score, usada para guardar a pontuação do jogador, somando o inteiro recebido à variável. A função também atualiza o display de pontuação no canto inferior esquerdo da tela.

- void Update_Time

Recebe: Ponteiro para a variável gameplay_time.

A função atualiza o display de tempo no canto inferior esquerdo da tela a cada segundo, usando a variável gameplay_time, que guarda o tempo de jogo.

- void Update_Lives

Recebe: Ponteiro para a variável lives.

A função atualiza o display de tempo no canto inferior esquerdo da tela quando o pacman morre, usando a variável lives, que guarda a quantidade de vidas do jogador.

- int Verify_Win

Recebe: Ponteiro para a matriz map.

Essa função usa dois for para percorrer a matriz atrás do caractere "o", que representa uma pastilha. Caso alguma pastilha seja encontrada, a função retorna 0, simbolizando que o jogo ainda não acabou. Se nenhuma pastilha for encontrada, retorna 1, indicando que o jogador venceu.

- void Restart_Game

Recebe: Ponteiros para as posições iniciais e atuais do pacman, Ponteiro para a última tecla apertada, Ponteiro para a variável lives.

O objetivo dessa função é reiniciar o jogo quando o pacman morre. As posições atuais do pacman são resetadas, recebem o valor das posições iniciais do mesmo. A última tecla apertada também é resetada, recebendo ' '. A função mostra um contador de 5 segundos antes de começar o jogo novamente.

- void Print_Ghost

Recebe: Ponteiro para a flag super.

Essa função printa o fantasma na tela. Se a flag super for 1, isto significa que o pacman está com o poder, então a função printa um "w" azul. Se a flag for 0, então o pacman não tem o poder, e a função printa um "W" vermelho.

- void Move_Pacman

Recebe: Ponteiros para as posições x e y atuais do pacman, Última tecla apertada pelo jogador.

A função move o pacman visualmente de acordo com a tecla direcional pressionada, e atualiza as posições x e y do mesmo.

- void Move_Ghost

Recebe: Ponteiros para as posições x e y atuais do ghost e do pacman, flag de superpoder, Último movimento do fantasma.

A função move os 5 fantasmas visualmente de acordo com a posição em que o pacman está e muda suas coordenadas X e Y. Para isso, é feito um cálculo do módulo da distância em X e Y de cada fantasma para o pacman. A partir disso, o fantasma escolhe a coordenada em que o pacman está mais distante para seguir. Na função, é calculada 70% de chance de o fantasma seguir o pacman e 30% de chance de que ele escolha um caminho randômico. Ainda, um fantasma é sempre impedido de “andar para trás” com o uso da variável last_move, esse comportamento só é interrompido caso o fantasma se encontre em um “beco sem saída” no mapa. 

- int module

Recebe: Inteiro.

A função retorna o módulo de um valor X recebido.

- void Pause_Game

Recebe: Ponteiro para a flag is_paused.

A flag is_paused sinaliza se o jogo está pausado ou não. Se ela for 1, a função printa "PAUSED" na parte inferior da tela. Caso seja 0, printa espaços para apagar o que foi escrito quando estava pausado.

- void End_Game

Recebe: Ponteiro para a variável player_score, Ponteiro para a variável lives.

Essa função printa o menu final ao terminar o jogo. Se a variável lives for 0, isso significa que o jogo acabou por falta de vidas, então printa "GAME OVER" e o score do jogador. Se não for 0, então o jogo acabou por falta de pastilhas no mapa, então printa "VICTORY" e o score do jogador.

- int main

Define-se todas as variáveis utilizadas.

Le o mapa, acha o pacman e os fantasmas, printa o mapa, começa o score, o timer e as vidas, e então começa a repetição do jogo.

É lido o caractere de movimentação, validado o caractere, para que o pacman nao pare caso a movimentação seja em direção a uma parede e então é feita a movimentação do pacman.

Então é feito o primeiro teste para verificar se o pacman tocou em um fantasma.

Após isso são movidos todos os fantasmas e é feito um segundo teste de colisão do pacman com os fantasmas. 

Após os testes de colisão, é verificado se o pacman pegou alguma pastilha e são alterados os valores de score e a flag de super poder. Além disso, verifica-se se acabaram as pastilhas para que o pacman ganhe o jogo.

Ao final é usado um timer em milisegundos para mover o pacman e os fantasmas. Para isso, são usadas flags can_move_pacman e can_move_ghost, as quais se tornam verdadeiras sempre que o timer atinge os valores de pacman_speed e ghosts_speed, respectivamente. Os fantasmas tem a mesma velocidade do pacman em jogo normal e 70% de sua velocidade quando o pacman está com super poder. Usa-se timer também para controlar o tempo de super poder, definido como 5 segundos.

## MANUAL DO JOGO:

Ao abrir a pasta do jogo, devem constar os arquivos: “pacman.exe”, “pacman.c”, “pacman.o” e “labirinto.txt”.

Há duas formas de abrir o jogo, executando o arquivo main.exe (executável), ou compilando o arquivo “main.c”.

Ao abrir o jogo, o usuário se depara com um labirinto de paredes definidas como “#”, pílulas definidas como “o” e super pílulas definidas como “*”. Além disso há fantasmas definidos como “W” ou “w” e o player pacman definido como “C”.

O objetivo do player é comer todas as pílulas sem ser morto pelos fantasmas que o seguem. Para isso, são utilizadas as teclas “W”, “X”, “A” e “D” para mover o pacman para cima, baixo, esquerda e direita, respectivamente. Para parar o pacman, utiliza-se a tecla “S” e para pausar e despausar o jogo, utiliza-se a tecla “P”.

Ao encostar em um fantasma, em uma situação normal, o Pacman perde uma vida. Sempre que o pacman é morto por um fantasma, as posições de todos os fantasmas e do player se reiniciam. O pacman conta com 3 vidas para tentar completar o labirinto. 

Ao comer uma superpílula, o Pacman ganha superpoderes por 5 segundos e pode comer fantasmas, que ficam mais lentos e menores.
O jogo tem um sistema de pontuação que segue a seguinte tabela:

Pílula: 10 pontos

Super pílula: 50 pontos

Fantasma: 200 pontos

Ao terminar as pílulas ou o pacman terminar suas vidas, é exibida uma tela de finalização mostrando a pontuação final do jogador e uma parabenização ou um game-over, de acordo com o resultado obtido.

