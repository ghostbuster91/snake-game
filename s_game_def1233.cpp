#include <iostream>
#include "console.ddt"
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <wininet.h>
#include <vector>
#include <cmath>

#include "S_game_types.h"

#define StartX 39
#define StartY 15
#define Wersja "1.5.2.1"

using namespace ddt::console;
using namespace std;

/********************************************************************/
/********************************************************************/
/**              Zmienne Globalne 				                      **/
/********************************************************************/
/**/	     double speed = 10, speed0;		                        /**/
/**/	     SEGMENT Snake[2][800], food, bonus, map[3200];         /**/
/**/	     int length[] = { 5, 5 } , tmp_length;                  /**/
/**/	     const double ms1 = 100; 		                           /**/
/**/	     DIRECTION kierunek[2], f_kierunek[2];	               /**/
/**/	     GAME_STATE G_State;  				                        /**/
/**/		  bool transparent = true, hardcore = false;             /**/
/**/       bool (*wsk_map[4])();                                  /**/
/**/       int map_nr = 2;                                        /**/
/**/       vector<SEGMENT> tmapa;                                 /**/
/**/       string plik = "0";                                     /**/
/**/       int nr_of_players = 1;                                 /**/
/*				                                                        */
/********************************************************************/

  

  
  
int game()
{
  
  start();
  double end, tm_left, tstart = GetTime();
  unsigned char znak;
  int points = 0;
  speed0 = speed;
  tmp_length = length[0] + length[1];
   
  if ( wsk_map[map_nr] ) (*wsk_map[map_nr])();
  if ( map_nr == 3 )
  {
       for ( int m = 0; m < tmapa.size(); m++ )
       {
           map[m].x = tmapa.at(m).x;
           map[m].y = tmapa.at(m).y;
       }
  }
  put_food();
  draw_board();
  
  textcolor(8);
  gotoxy(3,40);
  cout << " Type \"p\" to pause the game";
  gotoxy(80,39);
  
  do
  {
        znak = 0; 
        
        while ( !kbhit() )
        {
              
                end = GetTime() + ms1/(speed * 100);
                                
                move();
                check_colision();
                draw_food();
                draw_snake();
                               
                if ( G_State == GS_OVER ) return points;

                points += map_event();   // obsluga zdarzen na mapie i zsumowanie z nich pkt    
                disp_beta(points, tstart);                
                gotoxy(80,39);
                waitms(ms1/speed, true);

        }
        
        if ( G_State == GS_OVER ) return points;

        if( !Obsluz_zdarzenie( znak = getch(), points ) ) return -1;
        
        tm_left = 50 * (end - GetTime());
        if ( tm_left > 0 ) waitms( tm_left, false); // doczekanie do czasu end

  }while (1);

}
/********************************************************************/
bool move()
{
     if ( G_State != GS_PLAY ) return false;
     int i, k;      

     for ( k = 0; k < nr_of_players; k++ )
     {
         for ( i = length[k] - 1; i > 0; i-- ) // zmiana wspolrzednych n-tego elementu na wspolrzedne n-1 elementu
         {
             Snake[k][i].x = Snake[k][i - 1].x;
             Snake[k][i].y = Snake[k][i - 1].y;
         }
         switch(kierunek[k])//zmiana wspolrzednych glowy
         {
            case DIR_UP:
            {
              Snake[k][0].y--;
              f_kierunek[k] = DIR_UP;
              break;
            }
            case DIR_DOWN:
            {
              Snake[k][0].y++;
              f_kierunek[k] = DIR_DOWN;
              break;
            }
            case DIR_LEFT:
            {
              Snake[k][0].x--;
              f_kierunek[k] = DIR_LEFT;
              break;
            }
            case DIR_RIGHT:
            {
              Snake[k][0].x++;
              f_kierunek[k] = DIR_RIGHT;
              break;
            }
         }
     }

     return true;
}

/********************************************************************/
bool Obsluz_zdarzenie( char sign, int score )
{
       if ( !sign ) return false;
       switch(sign)
       {
                   case 72://strzalka w gore
                   {
                       if ( kierunek[0] != DIR_DOWN && f_kierunek[0] != DIR_DOWN ) kierunek[0] = DIR_UP;
                       break;
                   }
                   case 80://strzalka w dol
                   {
                       if ( kierunek[0] != DIR_UP && f_kierunek[0] != DIR_UP ) kierunek[0] = DIR_DOWN;
                       break;
                   }
                   case 75://strzalka w lewo
                   {
                       if ( kierunek[0] != DIR_RIGHT && f_kierunek[0] != DIR_RIGHT ) kierunek[0] = DIR_LEFT;
                       break;
                   }
                   case 77://strzalka w prawo
                   {
                       if ( kierunek[0] != DIR_LEFT && f_kierunek[0] != DIR_LEFT ) kierunek[0] = DIR_RIGHT;
                       break;
                   }
                   if ( nr_of_players > 1 )
                   {
                      case 119://W
                      {
                           if ( kierunek[1] != DIR_DOWN && f_kierunek[1] != DIR_DOWN ) kierunek[1] = DIR_UP;
                           break;
                      }
                      case 115://S
                      {
                           if ( kierunek[1] != DIR_UP && f_kierunek[1] != DIR_UP ) kierunek[1] = DIR_DOWN;
                           break;
                      }
                      case 97://A
                      {
                           if ( kierunek[1] != DIR_RIGHT && f_kierunek[1] != DIR_RIGHT ) kierunek[1] = DIR_LEFT;
                           break;
                      }
                      case 100://D
                      {
                           if ( kierunek[1] != DIR_LEFT && f_kierunek[1] != DIR_LEFT ) kierunek[1] = DIR_RIGHT;
                           break;
                      }
                      case 87://W
                      {
                           if ( kierunek[1] != DIR_DOWN && f_kierunek[1] != DIR_DOWN ) kierunek[1] = DIR_UP;
                           break;
                      }
                      case 83://S
                      {
                           if ( kierunek[1] != DIR_UP && f_kierunek[1] != DIR_UP ) kierunek[1] = DIR_DOWN;
                           break;
                      }
                      case 65://A
                      {
                           if ( kierunek[1] != DIR_RIGHT && f_kierunek[1] != DIR_RIGHT ) kierunek[1] = DIR_LEFT;
                           break;
                      }
                      case 68://D
                      {
                           if ( kierunek[1] != DIR_LEFT && f_kierunek[1] != DIR_LEFT ) kierunek[1] = DIR_RIGHT;
                           break;
                      }
                   }
                   case 112://klawisz p
                   {
                      pause( score );
                      clrscr();
                      textcolor(7);
                      draw_board();
                      textcolor(8);
                      gotoxy(3,40);
                      cout << " Type \"p\" to pause the game";
                      gotoxy(80,39);
                      break;
                   }
                   case 27: // klawisz ESC
                   {
                        return false;
                   }
                   default : break;
       }
       return true;
}
/********************************************************************/
void pause( int points )
{
  char znak;
  // rysowanie napisu pause
  textcolor(14);
  gotoxy(25,5);
  cout << "+++++    ++   ++  ++   ++++ ++++++"; 
  gotoxy(25,6);
  cout << "++  ++  ++++  ++  ++ ++     ++";
  gotoxy(25,7);
  cout << "++  ++ ++  ++ ++  ++ ++     ++";
  gotoxy(25,8);
  cout << "++++   ++  ++ ++  ++   ++   +++++";
  gotoxy(25,9);
  cout << "++     ++++++ ++  ++     ++ ++";
  gotoxy(25,10);
  cout << "++     ++  ++ ++++++     ++ ++";
  gotoxy(25,11);
  cout << "++     ++  ++  ++++  +++++  ++++++";
  gotoxy(25,13);
  // koniec rysowania
  cout << "Twoj wynik " << points;
  
  do
  {   
    znak=getch();
    if( znak == 96 )
    {
        console();
        // rysowanie napisu pause
        textcolor(14);
        gotoxy(25,5);
        cout << "+++++    ++   ++  ++   ++++ ++++++"; 
        gotoxy(25,6);
        cout << "++  ++  ++++  ++  ++ ++     ++";
        gotoxy(25,7);
        cout << "++  ++ ++  ++ ++  ++ ++     ++";
        gotoxy(25,8);
        cout << "++++   ++  ++ ++  ++   ++   +++++";
        gotoxy(25,9);
        cout << "++     ++++++ ++  ++     ++ ++";
        gotoxy(25,10);
        cout << "++     ++  ++ ++++++     ++ ++";
        gotoxy(25,11);
        cout << "++     ++  ++  ++++  +++++  ++++++";
        gotoxy(25,13);
        // koniec rysowania
        cout << "Twoj wynik " << points;
    }
  }while( znak != 112 );
}
/********************************************************************/
void waitms( double count, bool kb ) // czekanie milisekund
{
  double end = GetTime() + count / 100;
  if( kb ) while( GetTime() < end ) { }
  else while( GetTime() < end && !kbhit() ) { }
}
/********************************************************************/
bool start()
{
  if ( G_State != GS_NOTSTARTED ) return false;

  int i, k;
  for ( k = 0; k < nr_of_players; k++ )
  {
    kierunek[k] = DIR_LEFT;
    f_kierunek[k] = DIR_LEFT;
    for ( i = 0; i < length[k] - 1; i++ ) // glowa wez ma poczatkowe wspolrzedne StartX i StartY
    {
       Snake[k][i].x = StartX + k * 12;
       Snake[k][i].y = StartY + i;
    }
  }
  bonus.x = 0;
  bonus.y = 0;
  for ( int b = 0; b < 3200; b++ )
  {
      map[b].x = 0;
      map[b].y = 0;
  }
  wsk_map[0] = map1;
  wsk_map[1] = map2;
  wsk_map[2] = NULL;
  wsk_map[3] = NULL;

  
  G_State = GS_PLAY;
  return true;
}
/********************************************************************/
bool draw_snake()
{
     if ( G_State != GS_PLAY && G_State != GS_EDIT ) return false;
     
     int k, i;
     for ( k = 0; k < nr_of_players; k++ )
     {
         gotoxy(Snake[k][length[k] - 1].x, Snake[k][length[k] - 1].y);
         textcolor(0);
         textbackground(0);
         cout << (char)219;
         textcolor(7);
     
     
         for ( i = 0; i < length[k] - 1; i++ )
         {
             gotoxy( Snake[k][i].x , Snake[k][i].y );
             if( i == 0) textcolor(14 + k);
             else textcolor(10 - k);
             cout << (char)254;  // mozna tez 219
         }
     }
         
     gotoxy(80,39);           
     return true;
}
/********************************************************************/
bool check_colision() // sprawdzanie czy glowa nie weszla na ktorys z segmentwo lub na sciane
{
     if ( G_State != GS_PLAY ) return false;
     
     int j = 0, k, i;

     for ( k = 0; k < nr_of_players; k++ )
     {     
           for ( int i = 1; i < length[k] - 1; i++ )
           {
               if ( Snake[k][0].x == Snake[k][i].x && Snake[k][0].y == Snake[k][i].y ||
                    Snake[0][0].x == Snake[1][0].x && Snake[1][0].y == Snake[0][0].y ||
                    k == 1 && Snake[0][0].x == Snake[1][i].x && Snake[0][0].y == Snake[1][i].y || 
                    k == 0 && Snake[0][i].x == Snake[1][0].x && Snake[0][i].y == Snake[1][0].y )
               {
                  G_State = GS_OVER;
                  return true;
               }
           }
          
           
           
           if ( Snake[k][0].x == 1 || Snake[k][0].x == 80 || Snake[k][0].y == 1 || Snake[k][0].y == 39 ) 
           {
              if (transparent)
              {
                 if ( Snake[k][0].x == 1 ) Snake[k][0].x = 79;
                 if ( Snake[k][0].x == 80 ) Snake[k][0].x = 2;
                 if ( Snake[k][0].y == 1 ) Snake[k][0].y = 38;
                 if ( Snake[k][0].y == 39 ) Snake[k][0].y = 2;
              }
              else G_State = GS_OVER;
           }
     
           while ( map[j].x != 0 && map[j].y != 0 )
           {
                 if ( Snake[k][0].x == map[j].x && Snake[k][0].y == map[j].y )
                 {
                    G_State = GS_OVER;
                    return true;
                 }
                 ++j;
           }
     }
     return true;
}
/********************************************************************/
bool draw_board()
{
     if ( G_State != GS_PLAY  && G_State != GS_EDIT) return false;
     
     int h = 0;
     textbackground(0);
     textcolor(7);
     clrscr();
     gotoxy(1,1);
     cout << (char)201; // lewy gorny rog
     for ( int i = 2; i < 80; i++ ) // gorna pozioma linia
     {
          gotoxy(i, 1);
          cout << (char)205;
     }
     cout << (char)187; //prawy gorny rog

     for ( int j = 2; j < 39; j++ )// lewa pionowa linia
     {
         gotoxy(1, j);
         cout << (char)186;
     }
     for ( int j = 2; j < 39; j++ )//prawa pionowa linia
     {
         gotoxy(80, j);
         cout << (char)186;
     }
     gotoxy(80,39);
     cout << (char)188; // prawy dolny rog
     gotoxy( 1, 39 );
     cout << (char)200; // lewy dolny rog
     for( int k = 2; k < 80; k++ ) cout << (char)205; // dolna pozioma linia
     
     textcolor(8);
     if ( G_State == GS_PLAY )
     {
        while( map[h].x != 0 && map[h].y != 0 )
        {
            gotoxy( map[h].x, map[h].y );
            cout << "+";
            ++h;
        }
     }

     

     gotoxy(80,39);
     return true;
}
/********************************************************************/
double GetTime()
{
       long long f, t;
       QueryPerformanceFrequency((PLARGE_INTEGER) &f);
       QueryPerformanceCounter((PLARGE_INTEGER) &t);
       return (double)t / (double)f;
}
/********************************************************************/
inline void disp_beta( int score, double time )
{
     textcolor(10);
     if( hardcore )
     {
         gotoxy(10, 1);
         cout << "SPEED: " << speed;
     }
     gotoxy(25,1);
     cout << "SCORE: " << score;
     gotoxy(60,1);
     cout << "TIME: " << ceil(GetTime() - time) << " sec";
}
/*********************************************************************/
bool put_food()
{
     if ( G_State != GS_PLAY ) return false;
     bool xy_good;
     int i, h = 0, k = 0;
     srand(time(NULL));
     do 
     {
        xy_good = true;
        food.x = rand() % 78 + 2;
        food.y = rand() % 37 + 2;
        for ( k = 0; k < nr_of_players; k++ )
        {
            for ( i = 0; i < length[k] - 1; i++ )
            {
                if ( food.x == Snake[k][i].x && food.y == Snake[k][i].y ) xy_good = false;
            }
        }
        if ( food.x == bonus.x && food.y == bonus.y ) 
        {
           xy_good = false;
           break;
        }
        
        while( map[h].x != 0 && map[h].y != 0 )
        {
            if ( food.x == map[h].x && food.y == map[h].y ) 
            {
                 xy_good = false;
                 ++h;
                 break;
            }
            ++h;
        }
                
     } while(!xy_good);
     return true;
}
/*********************************************************************/
int caught()
{
    int k;
    for ( k = 0; k < nr_of_players; k++ )
    {
        if ( Snake[k][0].x == food.x && Snake[k][0].y == food.y )
        {
           int tmp = (int)speed;
           length[k]++;
           if ( hardcore ) speed++;
           return tmp;
        }
    }
    return 0;     
}
/*********************************************************************/
bool draw_food()
{
     if ( G_State != GS_PLAY ) return false;
     
     textcolor(12);
     gotoxy( food.x, food.y );
     cout << (char)248;
     
     if ( bonus.x != 0 && bonus.y != 0 )
     {
          gotoxy( bonus.x, bonus.y );
          textcolor(14);
          cout << (char)79;
     }
     return true;
}
/*********************************************************************/
int menu()
{
     int lista = 0;
     bool koniec = false;
     int wynik;
     char znak;
     
     do
     {
       clrscr();   
       draw_element(lista, MENU);
       znak = getch();
       switch(znak)
       {
         case 224://klawisze specjalne
         znak=getch();
         switch(znak)
         {
             case 72://strzaalka w gore
             {
               if ( lista > 0 ) lista--;
               break;
             }
             case 80://strzalka w dol
             {
               if ( lista < 4 ) lista++;
               break;
             }
         }
         znak=0;
         break;
         case 13://ENTER
         {
             if( lista == 0 )
             {
                 wynik = game();
                 if( wynik >= 0 ) koniec = true;
                 if( wynik == -1 ) restart();
                 break;
             }
             else if ( lista == 1 ) editor();
             else if ( lista == 4 ) abort();
             else if ( lista == 2 ) options();
             else if ( lista == 3 ) support();
             break;
         }
         case 27: // ESC
         {
              koniec = true;
              wynik = -1;
         }
       }
     } while( !koniec );
     
     return wynik;
}    
/*********************************************************************/
bool draw_element( int pozycja, ELEMENT a )
{
     if ( G_State != GS_NOTSTARTED ) return false;
     
     clrscr();
     gotoxy(70,40);
     textcolor(8);
     textbackground(0);
     cout << "v" << (Wersja);
          
     // rysowanie logo
     gotoxy(25,3);
     cout << "   ++++ +    +   ++   ++  ++ ++++++";
     gotoxy(25,4);
     cout << " ++     ++   +  ++++  ++ ++  ++    ";
     gotoxy(25,5);
     cout << " ++     + +  + ++  ++ ++ +   ++    "; 
     gotoxy(25,6);
     cout << "   ++   +  + + ++  ++ ++++   +++++ "; 
     gotoxy(25,7);
     cout << "     ++ +  + + ++++++ ++ ++  ++    ";
     gotoxy(25,8);
     cout << "     ++ +   ++ ++  ++ ++  ++ ++    ";
     gotoxy(25,9);
     cout << " +++++  +    + ++  ++ ++  ++ ++++++";
     // koniec rysowania
     
     int i, zamaluj_tmp;
     if ( a == MENU )
     {
        string lista[] = { "New Game", "Editor", "Options", "Support", "Exit" };
        textcolor(15);
        for ( i = 0; i < 5; i++ )
        {
            gotoxy(38,12 + 2 * i);
            if ( i == pozycja )
            {
                 cout << lista[i];
                 zamaluj_tmp = i;
            }     
            else 
            {    textbackground(0);
                 cout << lista[i];
            }
        }
        zmaluj(lista[pozycja], zamaluj_tmp);
        logo_effect();
        gotoxy(80,40);
        textbackground(0);
        return true;
     }
     if ( a == OPTIONS )
     {
          string lista[] = { "Speed", "length", "ghost_mode", "map", "hardcore", "players", "exit" };
          double cfg[6];
          textbackground(0);
          textcolor(15);  
      
          cfg[0] = speed;
          cfg[1] = length[0] - 1;
          cfg[2] = (double)transparent;
          cfg[3] = map_nr;
          cfg[4] = (double)hardcore;
          cfg[5] = nr_of_players;
        
        for ( i = 0; i < 7; i++ )
        {
            gotoxy(38,12 + 2 * i);
            if ( i == pozycja )
            {
               cout << lista[i];
               zamaluj_tmp = i; 
            }
            else 
            {
                 textbackground(0);
                 cout << lista[i];
            }
            gotoxy(51, 12 + 2 * i);
            if ( i != 6 )
            {
                 if ( i == 3 && map_nr == 3)
                 {
                      if ( plik == "0" ) cout << "wczytaj";
                      else 
                      {
                           textcolor(10);
                           cout << plik;
                           textcolor(7);
                      }
                 }
                 else
                 {
                     if ( i == 2 || i == 4 ) 
                     {
                        if( !cfg[i] ) cout << "OFF";
                        else cout << "ON";
                     }
                     else cout << cfg[i];
                 }
            }
        }
        zmaluj(lista[pozycja], zamaluj_tmp);
        logo_effect();
        gotoxy(80,40);
        textbackground(0);
        return true;
     }
}
/*********************************************************************/
bool options()
{
     if( G_State != GS_NOTSTARTED ) return false;
    
     int pozycja = 0;
     char znak;
     bool koniec;
     const int max_speed = 12;
     const int max_length = 8;
     const int max_map = 3;
     const int min_speed = 2;
     const int min_length = 5;
     const int min_map = 0;
     const int min_players = 1;
     const int max_players = 2;
                
     do
     {
       draw_element( pozycja, OPTIONS );
       znak = getch();
       switch(znak)
       {
         case 224://klawisze specjalne
         znak=getch();
         switch(znak)
         {
             case 72://strzaalka w gore
             {
               if ( pozycja > 0 ) pozycja--;
               else if ( pozycja == 0 ) pozycja = 6;
               break;
             }
             case 80://strzalka w dol
             {
               if ( pozycja < 6 ) pozycja++;
               else if ( pozycja == 6 ) pozycja = 0;
               break;
             }
             case 77: // strzalka w prawo
             {
               if( pozycja == 0 && speed < max_speed ) speed++;
               if( pozycja == 1 && length[0] < max_length ) length[0]++;
               if( pozycja == 2 && transparent == false ) transparent = true;
               if( pozycja == 3 && map_nr < max_map ) map_nr++;
               if( pozycja == 4 && hardcore == false ) hardcore = true;
               if( pozycja == 5 && nr_of_players < 2 ) nr_of_players++;
               break;
             }
             case 75: // strzalka w lewo
             {
               if( pozycja == 0 && speed > min_speed ) speed--;
               if( pozycja == 1 && length[0] > min_length ) length[0]--;
               if( pozycja == 2 && transparent == true ) transparent = false;
               if( pozycja == 3 && map_nr > min_map ) map_nr--;
               if( pozycja == 4 && hardcore == true ) hardcore = false;
               if( pozycja == 5 && nr_of_players > 1 ) nr_of_players--;
               break;
             }
         }
         znak=0;
         break;
         case 13://ENTER
         {
             if( pozycja == 3 && map_nr == 3)
             {
                 rload_map(38,18);
             } 
             else if( pozycja == 6 )
             {
               koniec = true;
             }
             break;
         }
         case 43: // +
         {
              if( pozycja == 0 && speed < max_speed ) speed++;
              if( pozycja == 1 && length[0] < max_length ) length[0]++;
              if( pozycja == 2 && transparent == false ) transparent = true;
              if( pozycja == 3 && map_nr < max_map ) map_nr++;
              if( pozycja == 4 && hardcore == false ) hardcore = true;
              if( pozycja == 5 && nr_of_players < 2 ) nr_of_players++;
              break;
         }
         case 45: // -
         {
              if( pozycja == 0 && speed > min_speed ) speed--;
              if( pozycja == 1 && length[0] > min_length ) length[0]--;
              if( pozycja == 2 && transparent == true ) transparent = false;
              if( pozycja == 3 && map_nr > min_map ) map_nr--;
              if( pozycja == 4 && hardcore == true ) hardcore = false;
              if( pozycja == 5 && nr_of_players > 1 ) nr_of_players--;
              break;
         }
         case 27: // klawisz ESC
         {
             koniec = true;
             break;
         }
         
                  
       }
     } while( !koniec );
     
}
/*********************************************************************/
bool restart()
{       
    if( G_State != GS_PLAY  && G_State != GS_OVER) return false;
	speed = speed0;				                     
    length[0] = 5;
    length[1] = 5;                  
	G_State = GS_NOTSTARTED;  				                  
	return true;
}                            
/*********************************************************************/
bool put_bonus()
{
     if ( G_State != GS_PLAY ) return false;
     bool xy_good;
     int i, j = 0, h = 0;
     int k = 0;
     do
     {
       xy_good = true;
       srand( (int)(GetTime() * 10) );
       bonus.x = rand() % 78 + 2;
       bonus.y = rand() % 37 + 2;
       
       for ( k = 0; k < nr_of_players; k++)
       {
           for ( i = 0; i < length[k] - 1; i++ )
           {
               if ( bonus.x == Snake[k][i].x && bonus.y == Snake[k][i].y )
               {
                  xy_good = false; 
                  break;
               }
           }
       }
       
       if ( bonus.x == food.x && bonus.y == food.y ) xy_good = false;
       while( map[h].x != 0 && map[h].y != 0 )
       {
         if ( food.x == map[h].x && food.y == map[h].y ) 
         {
              xy_good = false;
              ++h;
              break;
         }
         ++h;
       }
       
     } while( !xy_good ); 
     
     return true;
}
/*********************************************************************/
int caught_b( int time_left)
{
    for ( int k = 0; k < nr_of_players; k++ )
    {
        if ( Snake[k][0].x == bonus.x && Snake[k][0].y == bonus.y )
        {                   
          bonus.x = 0;
          bonus.y = 0;
          
          textcolor(0);
          for ( int i = length[k] - 1; i > length[k] - 5; i-- )
          {
              gotoxy(Snake[k][i].x, Snake[k][i].y);
              textbackground(0);
              cout << (char)219;
          }
          length[k] -= (int)floor(0.3 * length[k]);
          textcolor(7);
          return ( 10 * length[k] + time_left * (int)(speed/5) );
        }
    }        
    return 0;
}            
/*********************************************************************/
bool draw_bar( int left_time, int const_time )
{
     if( G_State != GS_PLAY ) return false;
     int i, j;
     double procent = ( (double)left_time / (double)const_time );
     if( bonus.x != 0 && bonus.y != 0 )
     {
         textcolor(10);
         gotoxy(50,40);
         cout << " [";
         for ( i = 0; i < (int)ceil( 25 * procent ); i++ ) cout << "=";
         for ( j = 0; j < 25 - i; j++ ) cout << " ";
         cout << "]";
     }
     return true;
}  
/*********************************************************************/
int map_event()
{
     //if( restart ) tmp_length = length;
     int score = 0, tmp;
     static int b_time_left = 0, ex_time = 0, tmp2;
     const int b_time = (int)(3 * speed) + 65; // dlugosc zycia bonusa
     
     // zbieranie i wstawianie zwyklego food
     tmp = caught();
     if ( tmp )
     {
          put_food();
          score = tmp;
     }
     
     // wstawianie bonusa
     if( length[0] + length[1] * (nr_of_players - 1) - tmp_length > 5  && b_time_left < 1 )
     { // jesli dlugosc podzielna przez 6 i wieksza o 4 od podstawowej
       // i rozna od dlugosci ostatniej przy ktorej dodano dodatek
       if ( put_bonus() )
       {
           b_time_left = b_time;
           tmp_length = length[0] + length[1] * (nr_of_players - 1);
       } 
     }
     // zbieranie bonusa
     tmp = caught_b( b_time_left );
     
     // jesli zdobyto zapisz zdobyta wartosc bonusa
     if ( tmp > 0 )
     {
          b_time_left = 0;
          ex_time = 20;
          tmp2 = tmp;
          tmp_length -= (int)floor(0.3 * tmp_length);
     }
     
     //jesli nie zebrany a istnieje to skroc jego czas
     if( b_time_left > 0 && tmp == 0 ) 
     {   
         draw_bar( b_time_left, b_time );
         if ( --b_time_left == 0 )
         {
             gotoxy( bonus.x, bonus.y );    
             textcolor(0);
             cout << (char)219;
             textcolor(7);
             
             bonus.x = 0;
             bonus.y = 0;
             clear();
         }
          // pasek pozostalosci czasu bonusa
     }
     else 
     {
          score += tmp;
          clear();
     }
     
     // wyswietlanie zdobytej wartosci bonusa
     if ( ex_time > 0 )
     { 
          gotoxy(65,40);
          textcolor(10);
          cout << "+" << tmp2;
          ex_time --;
          if ( ex_time == 0 ) clear();
          
     }
     
     return score; // zwracanie ilosci punktow naliczonej w tej sesji
}
/*********************************************************************/
bool map1()
{
     for( int i = 0; i < 18; i++ )
     {
          map[i].x = 41;
          map[i].y = 4 + i;
     }
     for( int j = 18; j < 67; j++ )
     {
          map[j].x = -3 + j;
          map[j].y = 13;
     }
     return true;
}
/*********************************************************************/
bool map2()
{
     for( int i = 0; i < 22; i++ )
     {
          map[i].x = 41;
          map[i].y = 2 + i;
     }
     for( int j = 22; j < 100; j++ )
     {
          map[j].x = j - 20;
          map[j].y = 13;
     }
     return true;
}
/*********************************************************************/
bool scores ( int wynik )
{
           clrscr();
           textcolor(10);
           cout << " PLEASE WAIT ";
           bool good = false;
           int recordy[15], pozycja = 0 ,j = 0, tmp = 0, rozmiar;
           string name, r_name[15];
           for ( int i = 0; i < 15; i++ ) 
           {
               recordy[i] = 0;
               r_name[i] = "noname";
           }
           
           // network
           HINTERNET hint,ftp;

           hint = InternetOpen("tester",INTERNET_OPEN_TYPE_DIRECT,NULL,NULL,0);
           ftp = InternetConnect(hint, "webpark.pl" ,
           INTERNET_DEFAULT_FTP_PORT,"ghostsnake1","kasper123",INTERNET_SERVICE_FTP,INTERNET_FLAG_PASSIVE,101); 
           // nawiazywanie polaczenia
           
           clrscr();
           gotoxy(31,1);
           textcolor(15);
           cout << "Twoj wynik to " << wynik << endl;
           
           textcolor(7);
           gotoxy(1,21);
           cout << " Connecting server: ";
           gotoxy(30,21);
           cout << "[";
           textcolor(10);
           
           if ( GetLastError() == 0 )
           { 
               textcolor(10);
               cout << "OK";
               good = true;
           }
           else 
           {
               textcolor(4);
               cout << "FAIL";
               good = false;
           }
           textcolor(7);
           cout << "]";
           
           if ( good ) // jesli nawiazano polaczenie to pobierz plik z servera
           {
              FtpGetFile(ftp,"/.www/cfg.rcf","c:\\cfg.rcf",true, FILE_ATTRIBUTE_NORMAL, INTERNET_FLAG_TRANSFER_BINARY,0);
           
              textcolor(7);
              gotoxy(1,22);
              cout << " Downloading scores: ";
              gotoxy(30,22);
              cout << "[";
              if ( GetLastError() == 0 ) 
              { 
                   textcolor(10);
                   cout << "OK";
                   good = true;
              }
              else 
              {
                  textcolor(4);
                  cout << "FAIL";
                  good = false;
              }
              textcolor(7);
              cout << "]";
              
              if( good )
              {
                  fstream plik, plik2;
                  plik.open("c:\\cfg.rcf",ios::in);    
                  if ( plik.good() )
                  {
                     for ( int u = 0; u < 15; u++ )
                     {   
                         plik >> recordy[u];
                         plik >> r_name[u];
                         if ( recordy[u] >= wynik ) 
                         {
                            ++pozycja;
                         }
                     }
                     plik.close();
                 
                     if ( pozycja < 15 )
                     {
                        do
                        {
                          name = pobierz_nazwe(2,2);
                          rozmiar = name.size();
                          if ( rozmiar == 0 ) 
                          {
                             pozycja = 15;
                             break;
                          }
                          if ( rozmiar > 10)
                          {
                             gotoxy(19,2);
                             textcolor(0);
                             for ( int z = 0; z < rozmiar; z++ ) cout << (char)219;
                             textcolor(7);  
                             gotoxy(19,2);                              
                          }
                        }while( rozmiar > 10 || rozmiar < 1 );
                    
                        textcolor(0);
                        gotoxy(1,2);                    
                        for( int b = 1; b < 40; b++ ) cout << (char)219; // czyszczenie lini
                        textcolor(7);
                        if ( rozmiar > 0 || pozycja < 15)
                        {
                           for ( int k = 14; k > pozycja ; k-- ) 
                           {
                               recordy[k] = recordy[k - 1];
                               r_name[k] = r_name[k - 1];
                           }
                           recordy[pozycja] =  wynik;
                           r_name[pozycja] = name;
                        }
                     }
                  }
                  else cout << endl << " brak dostepu do pliku ";
              
                  plik2.open("c:\\cfg.rcf", ios::out ); // zapis zmian do pliku
                  if( plik2.good() )
                  {
                      gotoxy(12,4);
                      textcolor(7);
                      cout << "Best scores:";
                      for ( int n = 0; n < 15; n++ ) // wyswietlanie wynikow
                      {
                          plik2 << recordy[n] << endl << r_name[n] << endl;
                          gotoxy(15, 5 + n );
                          if ( n == pozycja ) textbackground(4);
                          else textbackground(0);
                          cout << n + 1 << ". " << recordy[n] << "  " << r_name[n] << endl;
                      }
                      plik2.close();
                  }
                  else cout << " brak dostepu do pliku ";
              
                  textbackground(0);
                  tmp = 0;
          
                  if ( pozycja < 15 && rozmiar != 0 ) // jesli zmieniono plik z wynikami to wyslij nowa wersje na serwer
                  {
                    tmp = 1;
                    // network
                    FtpPutFile(ftp,"c:\\cfg.rcf","/.www/cfg.rcf",FTP_TRANSFER_TYPE_BINARY,0);
                   
                    textcolor(7);
                    gotoxy(1,23);
                    cout << " Updating scores: ";
                    gotoxy(30,23);
                    cout << "[";
                    if ( GetLastError() == 0 )
                    { 
                        textcolor(10);
                        cout << "OK";
                    }
                    else 
                    {
                        textcolor(4);
                        cout << "FAIL";
                    }
                    textcolor(7);
                    cout << "]";
                   
                    InternetCloseHandle(ftp);
                    InternetCloseHandle(hint);
                    //end network 
                   
                  }
                  if ( good ) // co rownoznaczne z tym ze plik istnieje
                  {
                     textcolor(7);
                     gotoxy(1,23 + tmp);
                     cout << " Deleting tmp files: ";
                     gotoxy(30,23 + tmp);
                     cout << "[";
                     if ( system("DEL c:\\cfg.rcf") == 0 ) // usuwanie pliku z wynikami
                     {
                        textcolor(10);
                        cout << "OK";
                     }
                     else 
                     {
                        textcolor(4);
                        cout << "FAIL";
                     }
                     textcolor(7);
                     cout << "]";     
                  }
              }
           }
           else tscore(wynik);
           textcolor(7);
           gotoxy(55,21);
           cout << "Press Enter";
           gotoxy(55,22);
           cout << "to continue";
           gotoxy(80,40);
           
           while ( getch() != 13 ); 
              
          return true;
}
/*********************************************************************/
inline void clear()
{
       gotoxy(50,40);
       textcolor(0);
       textbackground(0);
       for ( int k = 0; k < 30; k++ ) cout << (char)219;
}
/*********************************************************************/
inline void zmaluj( string napis, int pozycja )
{
       int tmp = 0, size = napis.size();
       gotoxy(38, 12 + 2 * pozycja );
       while ( !kbhit() && tmp < size )
       {
             textbackground(9);
             textcolor(7);
             cout << napis[0 + (tmp++)];
             waitms( 7, false );
       }
}
/*********************************************************************/
inline void logo_effect()
{
     static int pozycja = 0;
     static bool running = false;
     string wiersz[7];
     textcolor(8);
     textbackground(0);
     
     wiersz[0] = "   ++++ +    +   ++   ++  ++ ++++++";
     wiersz[1] = " ++     ++   +  ++++  ++ ++  ++    ";
     wiersz[2] = " ++     + +  + ++  ++ ++ +   ++    "; 
     wiersz[3] = "   ++   +  + + ++  ++ ++++   +++++ "; 
     wiersz[4] = "     ++ +  + + ++++++ ++ ++  ++    ";
     wiersz[5] = "     ++ +   ++ ++  ++ ++  ++ ++    ";
     wiersz[6] = " +++++  +    + ++  ++ ++  ++ ++++++";
     
     double start = GetTime();
     gotoxy(80,40);
     while ( !kbhit() )
     {     
           if ( GetTime() - start > 3 || running == true )
           {
                running = true;
                while ( !kbhit() )
                {
                      
                      if ( pozycja == 0 )
                      {
                           textcolor(14);
                           gotoxy(25, 3 + pozycja);
                           cout << wiersz[pozycja];
                      }
                      if ( pozycja > 0 && pozycja < 7 )
                      {
                          textcolor(8);
                          gotoxy(25, 2 + pozycja);
                          cout << wiersz[pozycja - 1];
                          textcolor(14);
                          gotoxy(25, 3 + pozycja);
                          cout << wiersz[pozycja];
                      }
                      if ( pozycja > 6 )
                      {
                           textcolor(8);
                           gotoxy(25, 2 + pozycja);
                           cout << wiersz[pozycja - 1];
                           pozycja = 0;
                           running = false;
                           gotoxy(80,40);
                           break;
                      }
                      pozycja++;    
                      waitms( 12, false );
                }
                start = GetTime(); 
           }
     }
}   
/*********************************************************************/
bool rload_map( int x, int y )
{
     ifstream file;     
     const string extention = ".smap";
     string file_name;
     SEGMENT tmp;
     int n = 0;
     
     file_name = pobierz_nazwe(x,y);
     if ( file_name.size() == 0 ) return false;
     file.open( (file_name + extention).c_str() );
     if ( file.good() )
     {
          clrscr();
          tmapa.clear();
          while( !file.eof() )
          {      
                 tmp.x = 0;
                 tmp.y = 0;
                 file >> tmp.x;
                 file >> tmp.y;
                 if ( tmp.x && tmp.y )
                 {
                      tmapa.push_back(tmp);
                 }
          }
          plik = file_name;
          return true;
     }
     else
     {
         cout << "error";
         return false;
     }    
}
/*********************************************************************/
string pobierz_nazwe(int x, int y)
{
       string napis;
       char tmp1;
       do
       {
        gotoxy(x, y);
        textcolor(0);
        textbackground(0);
        for ( int i = 0; i < 79; i++ ) cout << (char)219;
        napis.clear();
        gotoxy(x, y);
        textcolor(8);       
        cout << "Podaj nazwe [max 15]: ";
        
        // BEGIN: super skomplikowane pobieranie napisu w celu nie przejscia do nastepna linie
        do
        {
           textcolor(15);  
           tmp1 = getch();
           switch(tmp1)
           {
                       case 224://klawisze specjalne
                       tmp1=getch();
                       switch(tmp1)
                       {
                          default : 
                          {
                               tmp1 = 0;
                               break;
                          }
                       }
           }
           if( (int)tmp1 == 8 && napis.size() > 0)
           {
                napis.erase(napis.begin() + napis.size() - 1);
                if( napis.size() == 0 ) napis.clear();
                textcolor(0);
                cout << (char)8 << (char)219 << (char)8;
           }
           else if( ( (int)tmp1 > 47 && (int)tmp1 < 58) || // zakres dla liter i liczb
                    ( (int)tmp1 > 64 && (int)tmp1 < 91) ||
                    ( (int)tmp1 > 96 && (int)tmp1 < 123)  )   //(int)tmp != 13 && (int)tmp != 8)
           {
                cout << tmp1;
                napis.push_back(tmp1);
           }
           else if ( (int)tmp1 == 27 ) // klawisz ESC
           {
                napis.clear();
                napis.resize(0);
                return napis;
           }
        }while( (int)tmp1 != 13 && napis.size() < 16 );
        // END: super skomplikowane pobieranie napisu
           
       }while( napis.size() < 2 || napis.size() > 15 );
       
       return napis;
}
/********************************************************************/
bool tscore( int wynik ) // wyniki lokalne
{    
     fstream wplik, rplik;
     string r_name[15], name;
     int recordy[15], pozycja = 0, rozmiar;
     
     for( int i = 0; i < 15; i++ ) 
     {
        recordy[i] = 0;
        r_name[i] = "noname";
     }  
     
     rplik.open("c:\\bests.rcf", ios::out|ios::in );
     if( rplik.good() )
     {
         for ( int i = 0; i < 15; i++ )
         {
             rplik >> recordy[i];
             cout << recordy[i];
             rplik >> r_name[i];
             if ( recordy[i] >= wynik )
             {
                  ++pozycja;
             }
         }
         rplik.close();
         if ( pozycja < 15 )
         {
                        do
                        {
                          name = pobierz_nazwe(2,2);
                          rozmiar = name.size();
                          if ( rozmiar == 0 ) 
                          {
                             pozycja = 15;
                             break;
                          }
                          if ( rozmiar > 10)
                          {
                             gotoxy(19,2);
                             textcolor(0);
                             for ( int z = 0; z < rozmiar; z++ ) cout << (char)219;
                             textcolor(7);  
                             gotoxy(19,2);                              
                          }
                        }while( rozmiar > 10 || rozmiar < 1 );
                    
                        textcolor(0);
                        gotoxy(1,2);                    
                        for( int b = 1; b < 40; b++ ) cout << (char)219; // czyszczenie lini
                        textcolor(7);
                        if ( rozmiar > 0 || pozycja < 15)
                        {
                           for ( int k = 14; k > pozycja ; k-- ) 
                           {
                               recordy[k] = recordy[k - 1];
                               r_name[k] = r_name[k - 1];
                           }
                           recordy[pozycja] =  wynik;
                           r_name[pozycja] = name;
                        }
         }
         
         wplik.open("c:\\bests.rcf", ios::out ); // zapis zmian do pliku
         if( wplik.good() )
         {
              gotoxy(8,4);
              textcolor(7);
              cout << "Local best scores:";
              for ( int n = 0; n < 15; n++ ) // wyswietlanie wynikow
              {
                  wplik << recordy[n] << endl << r_name[n] << endl;
                  gotoxy(15, 5 + n );
                  if ( n == pozycja ) textbackground(4);
                  else textbackground(0);
                  cout << n + 1 << ". " << recordy[n] << "  " << r_name[n] << endl;
               }
               wplik.close();
         }
         else cout << " brak dostepu do pliku ";
     }
     else cout << "Brak dostepu do pliku";
                     
         
     
     return true;
}
/********************************************************************/
void support()
{
     textcolor(0);
     clrscr();
     textcolor(10);
     cout << " PLEASE WAIT ";
     textcolor(0);
     if ( system("ping www.wp.pl") != 0 )
     {
        clrscr();
        textcolor(7);
        gotoxy(10,10);
        cout << "Przepraszamy ale nastapil blad przy probie polaczenia z internetem.";
        gotoxy(10,11);
        cout << "W razie jakichkolwiek uwag pisz na gg: 3558775. Pozdrawiam Ghost\n";
        gotoxy(10,12);
        system("PAUSE");
     }
     else system("start www.ghostsnake1.webpark.pl");
     clrscr();
}
