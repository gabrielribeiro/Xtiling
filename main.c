#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "conio.h"

//Jogadores
struct Jogador
{
    char Nome[50];
    int Pontos;
}Jogador;

//Métodos
int    Menu();
int    NumeroJogadores();
void   EscolherJogadores(struct Jogador *jogadores[], int numJogadores);
void   IniciarJogo(struct Jogador *jogadores[], int numJogadores, int numlancamentos);
void   DesenharCenario();
void   DesenharHomem();
int    DesenharAlvo();
int    ControleAngulo();
int    ControleBarra();
int    LancarPedra(float velocidade, float anguloRad);
int    CalcularPontuacao(int alvo, int pos);
void   MostrarResultados(struct Jogador *jogadores[], int numJogadores);
float  AnguloParaRad(int angulo);
void   Creditos();

//Main
int main(int argc, char *argv[])
{
    int numJogadores;
    int opcao = 0;
    
    opcao = Menu();
    clrscr();
  
    switch(opcao)
    {
        case 1:
            numJogadores = NumeroJogadores();
            struct Jogador jogadores[numJogadores];
            
            EscolherJogadores(&jogadores, numJogadores);
            
            IniciarJogo(&jogadores, numJogadores, 5);
            
            MostrarResultados(&jogadores, numJogadores);
            
            break;
        case 2:
            Creditos();
            break;
    }
        
    return 0;
}

//Implementação dos Métodos
int Menu()
{         
     gotoxy(13, 5);   printf("##.....##.########.####.##.......####.##....##..######..");
     gotoxy(13, 6);   printf(".##...##.....##.....##..##........##..###...##.##....##.");
     gotoxy(13, 7);   printf("..##.##......##.....##..##........##..####..##.##.......");
     gotoxy(13, 8);   printf("...###.......##.....##..##........##..##.##.##.##...####");
     gotoxy(13, 9);   printf("..##.##......##.....##..##........##..##..####.##....##.");
     gotoxy(13, 10);  printf(".##...##.....##.....##..##........##..##...###.##....##.");
     gotoxy(13, 11);  printf("##.....##....##....####.########.####.##....##..######..");

     gotoxy(16, 17);  printf(">");     
     gotoxy(18, 17);  printf("Jogar");
     gotoxy(38, 17);  printf("Creditos");
     gotoxy(58, 17);  printf("Sair");
     
     _setcursortype(0);
     
     int opcao = 1;
     
     while(1)
     {
         if (kbhit())
         {
             int cmd = getch();

             switch(cmd)
             {
                  case 75: //esq
                       if (opcao > 1)
                          opcao--;
                       break;
                  case 77: //dir
                       if (opcao < 3)
                          opcao++;
                       break;
                  case 13: //Enter
                       return opcao; //Sair da função
                       break;
             }
            
             gotoxy(16, 17);
             printf(" ");
             gotoxy(36, 17);
             printf(" ");
             gotoxy(56, 17);
             printf(" ");
            
             switch(opcao)
             {
                  case 1:
                       gotoxy(16, 17);
                       break;
                  case 2:
                       gotoxy(36, 17);
                       break;
                  case 3:
                       gotoxy(56, 17);
                       break;
             }
             
             printf(">");
         }
     }
}

int NumeroJogadores()
{
    int numJog;
    
    gotoxy(36, 2);
    printf("JOGADORES");

    gotoxy(10, 6);
    printf("Quantas pessoas vao jogar?  ");    
    scanf("%i", &numJog);
    
    return numJog;
}

void EscolherJogadores(struct Jogador *jogadores[], int numJogadores)
{
    char nome[50];
    int i;
    
    for(i = 0; i < numJogadores; i++)
    {        
        fflush(stdin);

        gotoxy(10, 7+i);
        printf("Digite o nome do jogador numero %i:  ", i+1);
        gets(nome);
        
        jogadores[i] = (struct Jogador *) malloc(sizeof(struct Jogador));

        strcpy(jogadores[i]->Nome, nome);
        
        jogadores[i]->Pontos = 0;
    }
}

void IniciarJogo(struct Jogador *jogadores[], int numJogadores, int numlancamentos)
{   
    int l, j, alvo, angulo;
    int cores[4] = {LIGHTBLUE, LIGHTRED, LIGHTGREEN, YELLOW};
        
    clrscr();
    
    for (l = 1; l <= numlancamentos; l++)
    {
        for (j = 0; j < numJogadores; j++)
        {
            DesenharHomem();
            DesenharCenario();
            alvo = DesenharAlvo();

            if (j > 3)
               textcolor(cores[(j%3) -1]);
            else
                textcolor(cores[j]);

            gotoxy(1,1);
            printf("%ix %s %ipts", l, jogadores[j]->Nome, jogadores[j]->Pontos);

            textcolor(WHITE);
                    
            //gotoxy(1,3);
            //printf("angulo: ");
            //scanf("%f", &angulo);
            
            gotoxy(2, 5);
            printf("%c ", 219);
            gotoxy(52, 5);
            printf("%c ", 219);
            gotoxy(1, 3);
            printf("Controle o angulo pelas setas e aperte espaco 2 vezes");
            
            angulo = ControleAngulo();
                        
            int velocidade = ControleBarra();
            
            float anguloRad = AnguloParaRad(angulo);
            
            textcolor(WHITE);
        
            //Contar pontuação com base no retorno de LancarPedra
            int pos = LancarPedra(velocidade, anguloRad);
            
            int pontuacao = CalcularPontuacao(alvo, pos);

            jogadores[j]->Pontos += pontuacao;
            
            gotoxy(75,2);
            printf("+%i", pontuacao);
            sleep(1200);
            
            clrscr();
        }
    }
}

void DesenharHomem()
{    
    textcolor(WHITE);
    //cabeça
    gotoxy(6,20);
    printf("O");
    //braço dir
    gotoxy(5,21);
    printf("/");
    //braço esq
    gotoxy(7,20);
    printf("_");
    //estilingue
    gotoxy(8,20);
    printf("Y");
    //barriga
    gotoxy(6,21);
    printf("%c",179);
    gotoxy(6,22);
    printf("%c",179);
    //pernas    
    gotoxy(5,23);
    printf("/");
    gotoxy(7,23);
    printf("\\");
    
}

void DesenharCenario()
{
    int i;
    for(i=2;i<80;i++)
    {
        textcolor(LIGHTGREEN);
        gotoxy(i,24);
        printf("%c",176);
        gotoxy(i,25);
        printf("%c",176);
    }
}

int DesenharAlvo()
{    
    int x = rand() % 40 + 30;
    int y = 21;

    textcolor(LIGHTRED);
    
    //Externo
    gotoxy(x-2,y-2);
    printf("%c",201);

    gotoxy(x-1,y-2);
    printf("%c",205);
    gotoxy(x,y-2);
    printf("%c",205);
    gotoxy(x+1,y-2);
    printf("%c",205);
    
    gotoxy(x+2,y-2);
    printf("%c",187);
    
    gotoxy(x+2,y-1);
    printf("%c",186);
    gotoxy(x+2,y);
    printf("%c",186);
    gotoxy(x+2,y+1);
    printf("%c",186);
    
    gotoxy(x+2,y+2);
    printf("%c",188);

    gotoxy(x-1,y+2);
    printf("%c",205);
    gotoxy(x,y+2);
    printf("%c",205);
    gotoxy(x+1,y+2);
    printf("%c",205);

    gotoxy(x-2,y+2);
    printf("%c",200);
    
    gotoxy(x-2,y-1);
    printf("%c",186);
    gotoxy(x-2,y);
    printf("%c",186);
    gotoxy(x-2,y+1);
    printf("%c",186);
    
    //Interno
    gotoxy(x-1,y-1);
    printf("%c",201);

    gotoxy(x,y-1);
    printf("%c",205);
    
    gotoxy(x+1,y-1);
    printf("%c",187);
    
    gotoxy(x+1,y);
    printf("%c",186);
    
    gotoxy(x+1,y+1);
    printf("%c",188);

    gotoxy(x,y+1);
    printf("%c",205);    

    gotoxy(x-1,y+1);
    printf("%c",200);
    
    gotoxy(x-1,y);
    printf("%c",186);   
    
    //Ponto
    gotoxy(x,y);
    printf("%c",254);

    return round(x);
}

int ControleAngulo()
{
      
    int cmd;
    int angulo = 45;
    int posX = 12;
    int posY = 16;
    
    gotoxy(posX, posY);
    printf("%c", 248);
    
    gotoxy(10, 22);
    printf("%2.i%c", angulo, 248);
    
    while(1)
    {
        sleep(20);
        
        if(kbhit())
        {
            //Limpa última posição da pedra
            gotoxy(posX, posY);
   			    printf(" ");

            cmd = getch();
            switch(cmd)
            {
                case 72: //Cima
                     if (angulo < 90)
                          angulo++;
                     break;
                case 80: //Baixo
                     if (angulo > 1)
                          angulo--;
                     break;
                case 32:
                     return angulo;
                     break;
            }
            
            if (angulo <= 18) //Pos 1
            {
               posX = 15;
               posY = 20;
            }
            else if (angulo <= (18*2)) //Pos 2
            {
               posX = 14;
               posY = 18;
            }
            else if (angulo <= (18*3)) //Pos 3
            {
               posX = 12;
               posY = 16;
            }
            else if (angulo <= (18*4)) //Pos 4
            {
               posX = 10;
               posY = 14;
            }
            else if (angulo <= (18*5)) //Pos 5
            {
               posX = 8;
               posY = 13;
            }
            
            gotoxy(posX, posY);
            printf("%c", 248);
            
            gotoxy(10, 22);
            printf("%2.i%c", angulo, 248);
        }
    }
    
    return angulo;
}

int ControleBarra()
{
	int cmd;
  int loop = 1;
	
  int posBar = 1;
  int soma = 1;
	
  int maxBar = 48;
  int minBar = 1;
    
	int posX = 1;
	int posY = 5;
        
	while(loop)
	{
	   sleep(50);
	   gotoxy(posX+posBar+1, posY);
	   
	   //Desenha Intensidade pelas cores
	   if (posBar <= maxBar-13)
	   {
          textcolor(LIGHTGREEN);
	   }
	   else if (posBar >= maxBar-3)
	   {
          textcolor(LIGHTRED);
	   }
	   else
	   {
          textcolor(YELLOW);
	   }
	   
	  printf("%c ", 219);
	   
	   //Encerra
	   if (kbhit())
	   {
		  if ((int)getch() == 32)
		  {
			   loop = 0;
			   printf("%i m/s", posBar);
			   break;
			   //velocidade = posbar
			   //começa o lançamento
		  }
	   }
	   
	   //Somar barra a cada iteração no while
	   //caso a soma == 1 soma
	   if (soma == 1)
	   {
		  posBar++;
		  soma = (posBar == maxBar) ? 0 : 1;
	   }
	   else if (soma == 0)
	   {
		  posBar--;
		  soma = (posBar == minBar) ? 1 : 0;
	   }

	}
    
    return posBar;
}

float AnguloParaRad(int angulo)
{
    //angulo em rad para grau
    //  180  -  Pi
    //  ang  -  x
    return angulo * M_PI / 180;
}

int LancarPedra(float velocidade, float anguloRad)
{
    float posX = 0;
    float posY = 0;
    float tempoDecorrido = 0;
       
    while (1)
    {
        sleep(20);
        tempoDecorrido += 20;
     
        //Milissegundos para Segundos
        float t = tempoDecorrido/1000;
    
        //Limpa última posição da pedra
    		if (posX != 0 && posY != 0)
    		{
    			gotoxy(round(posX + 8), round(20 - posY));
    			printf(" ");
    		}
        
        //Calcula posição X e Y da pedra
        posX = velocidade * cos(anguloRad) * t;
        //posY = tan(anguloRad) * posX - ( 10 / (2 * (velocidade * velocidade)) * (cos(anguloRad) * cos(anguloRad)) ) * (posX * posX);
        posY = (velocidade * sin(anguloRad) * t) - 0.5 * 9.8 * (t*t);
        
        //Imprime na tela a posição X e Y
        //gotoxy(1,5);
        //printf("%0.0f, %0.0f", posX, posY);
        
        //Desenha a bolinha em sua posição X e Y
        //Se passar do limite Y máximo, continua
        //Se passar do limite X máximo, acaba
        //Se passar do limite Y mínimo, acaba
        if (posY > -3 && posY < 20 && posX < 72)
        {
             gotoxy(round(posX + 8), round(20 - posY));
             printf("@");
        }
        else if (posY <= -3 || posX >= 72)
        {
             //retorna posX
             return round(posX + 8);
        }
    }
}

int CalcularPontuacao(int alvo, int pos)
{    
     if (pos > 80)
        return 0;

     int pontuacao;
     pontuacao = round(pos*100/alvo);

     if (pontuacao <= 0 || pontuacao > 200)
          return 0;
     else if (pontuacao > 100)
          return 200 - pontuacao;
     else
         return pontuacao;
}

void MostrarResultados(struct Jogador *jogadores[], int numJogadores)
{
    clrscr();
    int i;
    int v = 0;
    
    gotoxy(36, 2);
    printf("PONTUACAO");
     
    for(i = 0; i < numJogadores; i++)
    {
          if (jogadores[i]->Pontos >= jogadores[v]->Pontos)
          {
             v = i;
          }
    }
    
    gotoxy(17, 10);
    printf("%s GANHOU com %i PONTOS!", jogadores[v]->Nome, jogadores[v]->Pontos);

    gotoxy(20, 22);  printf("Pressione qualquer tecla para sair");
    getch();    
}

void Creditos()
{         
     gotoxy(13, 5);   printf("##.....##.########.####.##.......####.##....##..######..");
     gotoxy(13, 6);   printf(".##...##.....##.....##..##........##..###...##.##....##.");
     gotoxy(13, 7);   printf("..##.##......##.....##..##........##..####..##.##.......");
     gotoxy(13, 8);   printf("...###.......##.....##..##........##..##.##.##.##...####");
     gotoxy(13, 9);   printf("..##.##......##.....##..##........##..##..####.##....##.");
     gotoxy(13, 10);  printf(".##...##.....##.....##..##........##..##...###.##....##.");
     gotoxy(13, 11);  printf("##.....##....##....####.########.####.##....##..######..");

     gotoxy(20, 15);  printf("11100575  |  G A B R I E L   R I B E I R O");
     gotoxy(20, 18);  printf("11164126  |  L U C A S   A R G A T E");

     gotoxy(20, 22);  printf("Pressione qualquer tecla para sair");
     getch();
}
