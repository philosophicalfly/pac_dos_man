#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<time.h>
#include<locale.h>


#define LINE            30
#define COLUMN          101
#define PILL            111
#define SUPER_PILL      42
#define WALL            35
#define GHOST           87
#define PACMAN          67
#define MAX_GHOSTS      5

//Struct do PacMan
typedef struct str_pacman
{
    int x,y;
    int start_x,start_y;
    int power;


} Pacman;

//Struct do fantasma
typedef struct str_ghost
{

    int x,y;
    int start_x,start_y;
    int alive;
    char last_move;

} Ghost;

//FUNÇÕES:

void debug(int x, char y)
{
    gotoxy(50,33);
    printf("DEBUG\t %d \t %c", x, y);
}

int Find_Ghost_Qtd(char map[][COLUMN])
{
    int i,j;
    int qnt = 0;
    for(i=0; i<LINE; i++)
        for(j=0; j<COLUMN; j++)
            if(map[i][j] == GHOST)
                qnt++;
    return qnt;
}

void gotoxy(int x, int y)
{
    //Move o cursor para um lugar na tela
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD)
    {
        x-1,y-1
    });
}

void SetConsoleSize(unsigned largura, unsigned altura)
{
    SMALL_RECT r;
    COORD c;
    HANDLE stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

    c.X = largura;
    c.Y = altura;
    SetConsoleScreenBufferSize(stdoutHandle, c); //Ajusta tamanho do buffer de armazenamento da tela

    r.Left = 0;
    r.Top = 0;
    r.Right = largura - 1;
    r.Bottom = altura - 1;
    SetConsoleWindowInfo(stdoutHandle, 1, &r); //Ajusta tamanho da tela
}

void Get_Map(char map[][COLUMN])
{
    //Pega a matriz do arquivo

    int i,j;
    FILE *arq;

    arq = fopen("labirinto.txt","r");

    for(i=0; i<LINE; i++)
    {
        for(j=0; j<COLUMN; j++)
            fscanf(arq, "%c", &map[i][j]);
    }

    fclose(arq);
}

void Find_Pacman(char map[][COLUMN], int *posX, int *posY)
{
    //Encontra a posição do pacman

    int i,j;
    for(i=0; i<LINE; i++)
        for(j=0; j<COLUMN; j++)
            if(map[i][j] == PACMAN)
            {
                *posX = j;
                *posY = i;
            }

}

void Find_Ghost(char map[][COLUMN],int *posX, int *posY,int current)
{
    //Encontra a posição do fantasma

    int i,j;
    int qnt = 0;
    for(i=0; i<LINE; i++)
        for(j=0; j<COLUMN; j++)
            if(map[i][j] == GHOST && current == qnt++)
            {
                *posX = j;
                *posY = i;
            }
}

void Print_Map(char map[][COLUMN])
{
    //Printa o labirinto na tela


    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


    int i,j;
    for(i=0; i<LINE; i++)
        for(j=0; j<COLUMN; j++)
        {
            if(map[i][j] == WALL)
            {
                SetConsoleTextAttribute(hConsole,  9);
                printf("#");
            }
            else if(map[i][j] == PILL)
            {
                SetConsoleTextAttribute(hConsole, 15);
                printf("o");
            }
            else if(map[i][j] == SUPER_PILL)
            {
                SetConsoleTextAttribute(hConsole, 14);
                printf("*");
            }
            else if(map[i][j] == PACMAN)
            {
                SetConsoleTextAttribute(hConsole, 14);
                printf("C");
            }
            else if(map[i][j] == GHOST)
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("W");
            }
            else
                printf("%c",map[i][j]);
        }
}

void Update_Score(long *player_score,int score)
{
    //Da update na pontuação

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    *player_score = *player_score + score;
    gotoxy(1,32);
    SetConsoleTextAttribute(hConsole, 2);
    printf("Score: %d", *player_score);
}

void Update_Time(int *gameplay_time)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    gotoxy(1,33);
    SetConsoleTextAttribute(hConsole, 2);
    printf("Time:  %d", *gameplay_time);
}

void Update_Lives(int *lives)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    gotoxy(1,34);
    SetConsoleTextAttribute(hConsole, 2);
    printf("Lives: %d", *lives);
}



int Verify_Win(char map[][COLUMN])
{
    int i, j;
    for(i=0; i<LINE; i++)
        for(j=0; j<COLUMN; j++)
            if(map[i][j] == PILL)
                return 0;
    return 1;
}

void Restart_Game(int *start_x, int *start_y, int *posX, int *posY,int *mov,int *lives)
{
    //Reinicia o jogo

    int i;
    gotoxy(*posX+1,*posY+1);
    printf(" ");
    *posX = *start_x;
    *posY = *start_y;
    *mov = ' ';
    gotoxy(*start_x+1,*start_y+1);
    printf("C");
    if(*lives != 0)
    {
        for(i=5; i>=0; i--)
        {
            Sleep(250);
            gotoxy(45,33);
            printf("ARE YOU READY?");
            Sleep(250);
            gotoxy(45,33);
            printf("      %d       ",i);
        }
        gotoxy(51,33);
        printf("GO!");
        Sleep(250);
        gotoxy(51,33);
        printf("   ");
    }
}

void Print_Ghost(int *super)
{
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if (*super)
    {
        SetConsoleTextAttribute(hConsole, 11);
        printf("w");
    }
    else
    {
        SetConsoleTextAttribute(hConsole, 12);
        printf("W");
    }
}

void Move_Pacman(int *posX, int *posY, char mov)
{
    //Move o Pacman baseado em onde o jogador quer ir

    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleTextAttribute(hConsole, 14);

    switch(mov)
    {
    case 'd':
        gotoxy(*posX+1,*posY+1);
        printf(" ");

        gotoxy(*posX+2,*posY+1);
        printf("C");
        *posX = *posX + 1;
        break;
    case 'w':
        gotoxy(*posX+1,*posY+1);
        printf(" ");

        gotoxy(*posX+1,*posY+0);
        printf("C");
        *posY = *posY - 1;
        break;
    case 'a':
        gotoxy(*posX+1,*posY+1);
        printf(" ");

        gotoxy(*posX+0,*posY+1);
        printf("C");
        *posX = *posX - 1;
        break;
    case 'x':
        gotoxy(*posX+1,*posY+1);
        printf(" ");

        gotoxy(*posX+1,*posY+2);
        printf("C");
        *posY = *posY + 1;
        break;
    }
}

int module(int x)
{
    if (x < 0)
        return -x;
    return x;
};

//Alterar!
void Move_Ghost(char map[][COLUMN], int *ghostX, int *ghostY, int *pacX, int *pacY, int *super, char* last_move)
{
    int flag_same_direction = 1, flag_stopped = 1;      //flags pra nao mudar de direção ou ficar parado
    int difX = *ghostX - *pacX;                         //distancia do eixo X de um fantasma para o pacman
    int difY = *ghostY - *pacY;                         //distancia do eixo Y de um fantasma para o pacman
    if(*super == 1)
    {
        *last_move = 'p';
        difX *= -1;                         //distancia do eixo X de um fantasma para o pacman
        difY *= -1;                         //distancia do eixo Y de um fantasma para o pacman
    }
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    srand(time(NULL));
    if (rand()%10 < 7)                                  //70% de chance de o fantasma seguir o pacman
    {
        if(module(difX) > module(difY))                 //se o modulo da distancia do eixo X é maior que a do Y,
            //ele tenta seguir em X
        {
            if(difX > 0)                                //se a distancia do fantasma em X é maior que 0
            {
                //tenta ir pra esquerda
                if(map[*ghostY][*ghostX - 1] != WALL && *last_move != 'd')
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX,*ghostY + 1);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostX = *ghostX - 1;
                    *last_move = 'a';
                    flag_stopped = 0;                   //flag verifica que o fantasma se moveu

                }

            }
            else                                        //se a distancia do fantasma em X é menor que 0
            {
                //tenta ir pra direita
                if(map[*ghostY][*ghostX + 1] != WALL && *last_move != 'a')
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 2,*ghostY + 1);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostX = *ghostX + 1;
                    *last_move = 'd';
                    flag_stopped = 0;                   //flag verifica que o fantasma se moveu

                }

            }
        }
        else                                            //se o modulo da distancia do eixo Y é maior que a do X,
            //ele tenta seguir em Y
        {
            if(difY > 0)                                //se a distancia do fantasma em Y é maior que 0
                //tenta ir pra cima
            {
                if(map[*ghostY - 1][*ghostX] != WALL && *last_move != 'x')
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 1,*ghostY);
                    Print_Ghost(super);
                    *ghostY = *ghostY - 1;
                    *last_move = 'w';
                    flag_stopped = 0;                   //flag verifica que o fantasma se moveu

                }

            }
            else                                        //se a distancia do fantasma em Y é menor que 0
                //tenta ir pra baixo
            {
                if(map[*ghostY + 1][*ghostX] != WALL && *last_move != 'w')
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 1,*ghostY + 2);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostY = *ghostY + 1;
                    *last_move = 'x';
                    flag_stopped = 0;                   //flag verifica que o fantasma se moveu

                }

            }
        }
    }
    //caso o fantasma nao tenha se movido, a flag_stopped vai estar zerada,
    //isso significa que o fantasma nao consegue seguir o pacman pq existe uma parede impedindo
    //nesse caso, o fantasma adquire um caráter randomico, e vai pra qualquer lado possivel até que
    //ele consiga se mover.
    //PARTE RANDOMICA:
    if (flag_stopped == 1)
    {
        do
        {
            switch(rand()%4)
            {
            case 0: //Tentativa de ir para CIMA
                //se para cima nao é parede e o ultimo movimento nao é para baixo
                if(map[*ghostY - 1][*ghostX] != WALL && ((*last_move != 'x')||
                        (
                            (map[*ghostY + 1][*ghostX] == WALL) && //Se o fantasma está sem saída, conforme testado aqui
                            (map[*ghostY][*ghostX + 1] == WALL) && //o programa ignora que ele nao pode "andar para tras"
                            (map[*ghostY][*ghostX - 1] == WALL)    //dessa forma o fantasma escapa do caminho sem saida
                        )                                          //a mesma coisa é feita para os outros 3 lados
                                                        ))
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 1,*ghostY);
                    Print_Ghost(super);
                    *ghostY = *ghostY - 1;
                    *last_move = 'w';
                    flag_same_direction = 0;                        //verifica que o fantasma se moveu randomicamente
                    break;
                }
                else

                case 1: //Tentativa de ir para DIREITA
                if(map[*ghostY][*ghostX + 1] != WALL && ((*last_move != 'a')||
                        (
                            (map[*ghostY][*ghostX - 1] == WALL)&&
                            (map[*ghostY - 1][*ghostX] == WALL)&&
                            (map[*ghostY + 1][*ghostX] == WALL)
                        )))
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 2,*ghostY + 1);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostX = *ghostX + 1;
                    *last_move = 'd';
                    flag_same_direction = 0;                        //verifica que o fantasma se moveu randomicamente
                    break;
                }
                else

                case 2: //Tentativa de ir para BAIXO
                if(map[*ghostY + 1][*ghostX] != WALL && ((*last_move != 'w')||(
                            (map[*ghostY - 1][*ghostX] == WALL) &&
                            (map[*ghostY][*ghostX + 1] == WALL) &&
                            (map[*ghostY][*ghostX - 1] == WALL)
                        )
                                                        ))
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX + 1,*ghostY + 2);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostY = *ghostY + 1;
                    *last_move = 'x';
                    flag_same_direction = 0;                        //verifica que o fantasma se moveu randomicamente
                    break;
                }
                else

                case 3: //Tentativa de ir para ESQUERDA
                if(map[*ghostY][*ghostX - 1] != WALL && ((*last_move != 'd')||(
                            (map[*ghostY][*ghostX + 1] == WALL)&&
                            (map[*ghostY - 1][*ghostX] == WALL)&&
                            (map[*ghostY + 1][*ghostX] == WALL)
                        )))
                {
                    gotoxy(*ghostX + 1,*ghostY + 1);
                    if(map[*ghostY][*ghostX] == GHOST)
                        printf(" ");
                    else
                    {
                        if(map[*ghostY][*ghostX] == SUPER_PILL)
                            SetConsoleTextAttribute(hConsole, 14);
                        else
                            SetConsoleTextAttribute(hConsole, 15);
                        if(map[*ghostY][*ghostX] != 'C')
                            printf("%c",map[*ghostY][*ghostX]);
                        else
                            printf("%c", ' ');
                    }
                    gotoxy(*ghostX,*ghostY + 1);
                    SetConsoleTextAttribute(hConsole, 12);
                    Print_Ghost(super);
                    *ghostX = *ghostX - 1;
                    *last_move = 'a';
                    flag_same_direction = 0;                        //verifica que o fantasma se moveu randomicamente
                    break;
                }
            }
        }
        while (flag_same_direction == 1);
    }
}

void Pause_Game(int *is_paused)
{
    if(*is_paused)
    {
        gotoxy(50,33);
        printf("      ");
        *is_paused = *is_paused - 1;
    }
    else
    {
        gotoxy(50,33);
        printf("PAUSED");
        *is_paused = *is_paused + 1;
    }
}

void End_Game(int *player_score, int *lives)
{
    char end;
    system("cls");
    gotoxy(45,15);
    if(*lives == 0)
    {
        printf("GAME OVER");
        gotoxy(45,16);
        printf("SCORE: %d", *player_score);
    }
    else
    {
        printf("VICTORY!!!");
        gotoxy(45,16);
        printf("SCORE: %d", *player_score);
    }
    gotoxy(45,18);
    printf("Press 'E' to exit");
    gotoxy(45,30);
    while (tolower(end) != 'e')
        end = getch();
}

//CÓDIGO:

//"changelog":

//  bug de colisao com fantasmas corrigido
//  coloquei timer pra fantasmas e pacman ao inves de sleep
//  fiz uma flag pro pause na letra p, travando todas as movimentações
//  modifiquei a função que printa o tempo de jogo por conta ta mudança do sleep pra timer
//  criei a flag is_powerful que vai se ativar quando o pacman come uma superpastilha,
//      ela controla as velocidades dos fantasmas
//  dei superpower ao pacman, diminui o tamanho dos fantasmas automaticamente, come fantasmas
//  adicionei o final de jogo mostrando score
//  NA VERDADE ISSO NUNCA FOI FEITO, MAS FUNCIONA SEM: (fazer o fantasma só mudar de direção ao encontrar bifurcação)
//  TERMINADO::: 70% de chance de o pacman ser seguido, e os fantasmas reiniciam o jogo na posição inicial

// De todos os itens da definição do trabalho, ainda faltam:

//  (menor importancia) fazer o pacman receber o comando
//      de mudança de direçao antes de ele achar bifurcação
//  (menor importancia) adicionar setas de direção no jogo

int main()
{
    //Variáveis:
    char map[LINE][COLUMN];
    int i,j;
    int win =               0;
    int lives =             3;
    int qtGhosts =          Find_Ghost_Qtd(map);

    //variaveis de movimentação
    int mov, last_mov;
    int pacman_speed =      800;
    int ghosts_speed;
    int is_paused =        0;
    int is_powerful =       0;

    //variaveis que mostram dados ao usuario
    int gameplay_time =     0;
    long player_score =     0;

    //variaveis do timer de movimentação
    int msec, timer_pacman, last_timer_pacman, can_move_pacman, timer_ghost, last_timer_ghost, can_move_ghost;
    float last_game_timer, game_timer;

    int flag_start_power =0, max_time_power=0;

    Pacman player;
    Ghost ghosts[MAX_GHOSTS];
    HANDLE  hConsole;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    clock_t start = clock(), time_dif;
    clock_t start_power = clock();

    //Tamanho da tela:
    SetConsoleSize(101,36);

    //Obtendo a matriz:
    Get_Map(map);

    //Encontrando o pac-man:
    Find_Pacman(map,&player.start_x, &player.start_y);
    player.x = player.start_x;
    player.y = player.start_y;

    //Procurando fantasmas:
    qtGhosts = Find_Ghost_Qtd(map);
    for(i=0; i<qtGhosts; i++)
    {
        Find_Ghost(map,&ghosts[i].start_x,&ghosts[i].start_y,i);
        ghosts[i].x = ghosts[i].start_x;
        ghosts[i].y = ghosts[i].start_y;
    }

    //Mostrando o labirinto:
    Print_Map(map);

    //Mostrando a pontuação:
    Update_Score(&player_score, 0);

    //Mostrando o tempo:
    Update_Time(&gameplay_time);

    //Mostrando as vidas:
    Update_Lives(&lives);

    //Início do jogo:
    while(!win && lives > 0)
    {

        //define velocidade dos ghosts quando o pacman esta com power ou nao
        if(is_powerful)ghosts_speed=pacman_speed*0.7;
        else ghosts_speed = pacman_speed;

        Update_Time(&gameplay_time);
        //Esperando input do jogador:
        if(kbhit())
        {
            while(kbhit())
            {
                last_mov = mov;
                mov = getch();
            }
            mov = tolower(mov);

            //"Validando" a entrada do jogador para não parar o pacman
            //caso o jogador selecione a direção paralela ao movimento
            //na qual há uma parede
            switch(mov)
            {
            case 'd':
                if(map[player.y][player.x + 1] == WALL)
                    mov = last_mov;
                break;
            case 'w':
                if(map[player.y - 1][player.x ] == WALL)
                    mov = last_mov;
                break;
            case 'a':
                if(map[player.y][player.x - 1] == WALL)
                    mov = last_mov;
                break;
            case 'x':
                if(map[player.y + 1][player.x ] == WALL)
                    mov = last_mov;
                break;
            case 's':
                break;
            case 'p':
                Pause_Game(&is_paused);
                mov = last_mov;
                break;
            default:
                mov = last_mov;
                break;
            }
        }

        //Movendo o pacman:
        if(can_move_pacman && !is_paused)           //se o timer permite movimentação
        {
            can_move_pacman = 0;                    //retira permissão
            switch(mov)
            {
            case 'd':
                if(map[player.y][player.x + 1] != WALL)
                    Move_Pacman(&player.x,&player.y,mov);
                break;
            case 'w':
                if(map[player.y - 1][player.x] != WALL)
                    Move_Pacman(&player.x,&player.y,mov);
                break;
            case 'a':
                if(map[player.y][player.x - 1] != WALL)
                    Move_Pacman(&player.x,&player.y,mov);
                break;
            case 'x':
                if(map[player.y + 1][player.x] != WALL)
                    Move_Pacman(&player.x,&player.y,mov);
                break;
            case 's':
                mov = ' ';
                last_mov = ' ';
            }
        }


        for(i=0; i<qtGhosts; i++)                   //Testando se o pacman tocou em algum fantasma
        {
            if(player.x == ghosts[i].x && player.y == ghosts[i].y)
            {
                if(!is_powerful)
                {
                    for(j=0; j<qtGhosts; j++)                   //Testando se o pacman tocou em algum fantasma
                    {
                        gotoxy((ghosts[j].x+1),(ghosts[j].y+1));
                        printf("%c", ' ');
                        ghosts[j].x = ghosts[j].start_x;
                        ghosts[j].y = ghosts[j].start_y;
                    }
                    lives--;
                    Update_Lives(&lives);

                    if(lives > 0)
                    Restart_Game(&player.start_x,&player.start_y,&player.x,&player.y,&mov,&lives);
                }
                else
                {
                    ghosts[i].x = ghosts[i].start_x;
                    ghosts[i].y = ghosts[i].start_y;
                    map[player.y][player.x] = 32;
                    Update_Score(&player_score, 200);
                }
            }
        }

        //Movendo fantasmas:
        if(can_move_ghost && !is_paused)            //se o timer permite movimentação
        {
            can_move_ghost = 0;                     //retira permissão
            for(i=0; i<qtGhosts; i++)
            {
                Move_Ghost(map,&ghosts[i].x,&ghosts[i].y, &player.x, &player.y, &is_powerful, &ghosts[i].last_move);
            }
        }


        for(i=0; i<qtGhosts; i++)                   //Testando se o pacman tocou em algum fantasma
        {
            if(player.x == ghosts[i].x && player.y == ghosts[i].y)
            {
                if(!is_powerful)
                {

                    for(j=0; j<qtGhosts; j++)                   //Testando se o pacman tocou em algum fantasma
                    {
                        gotoxy((ghosts[j].x+1),(ghosts[j].y+1));
                        printf("%c", ' ');
                        ghosts[j].x = ghosts[j].start_x;
                        ghosts[j].y = ghosts[j].start_y;
                    }
                    lives--;
                    Update_Lives(&lives);
                    if(lives > 0)
                    Restart_Game(&player.start_x,&player.start_y,&player.x,&player.y,&mov,&lives);
                }
                else
                {
                    ghosts[i].x = ghosts[i].start_x;
                    ghosts[i].y = ghosts[i].start_y;
                    map[player.y][player.x] = 32;
                    Update_Score(&player_score, 200);
                }
            }
        }

        if(map[player.y][player.x] == PILL)         //Testando se o pacman pegou alguma pastilha
        {
            map[player.y][player.x] = 32;
            Update_Score(&player_score, 10);
        }
        if(map[player.y][player.x] == SUPER_PILL)   //Testando se o pacman pegou alguma superpastilha
        {
            map[player.y][player.x] = 32;
            Update_Score(&player_score, 50);
            flag_start_power = 1;                   //se pegou, ganha poder
        }

        win = Verify_Win(map);                      //Verificando se ainda há alguma pastilha no mapa:


        time_dif = clock() - start;                 //diferença de tempo do começo do programa ate o estado atual
        msec = time_dif * 1000 / CLOCKS_PER_SEC;    //contador de milesimos

        can_move_pacman = 0;                        //flag de permissao do pacman
        timer_pacman = msec%(1000-pacman_speed);    //timer do pacman zerando a cada x msec
        if(last_timer_pacman > timer_pacman)        //se o timer zerar
            can_move_pacman = 1;                    //da permissao de movimentação
        last_timer_pacman = timer_pacman;           //salva ultimo timer

        can_move_ghost = 0;                         //flag de permissao do ghost
        timer_ghost = msec%(1000-ghosts_speed);     //timer do ghost zerando a cada x msec
        if(last_timer_ghost> timer_ghost)           //se o timer zerar
            can_move_ghost = 1;                     //da permissao de movimentação
        last_timer_ghost = timer_ghost;             //salva ultimo timer

        game_timer = msec%1000;                     //segundos do tempo de jogo
        if(last_game_timer > game_timer)            //se zerar,
            gameplay_time++;                        //incrementa um
        last_game_timer = msec%1000;                //salva ultimo timer

        //define o tempo maximo do poder
        if (flag_start_power==1)
        {
            max_time_power = msec + 5000;           //tempo atual mais 5 segundos
            is_powerful = 1;                        //da poder
            flag_start_power = 0;                   //zera a flag
        }

        if (msec > max_time_power)                  //se o tempo de jogo passar o maximo do poder,
            is_powerful = 0;                        // perde poder


    }

    //finalização do jogo
    End_Game(&player_score, &lives);
}
