#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <string>

//---typy zmiennych---//
struct SEGMENT
{
       int x;
       int y;
};
enum DIRECTION { DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT };
enum GAME_STATE { GS_NOTSTARTED, GS_PLAY, GS_OVER, GS_EDIT };
enum ELEMENT { MENU, OPTIONS };

//---prototypy funkcji---//

//** GRA
     int menu();
     int game();
     int caught();
     int caught_b( int );
     int map_event();
     bool scores( int );
     bool tscore( int );

     bool start();
     bool Obsluz_zdarzenie( char, int );
     bool move();
     bool check_colision();
     bool put_food();
     bool put_bonus();
     bool options();
     bool restart();
     bool rload_map( int, int );
     void support();
     
     //bool console();
//** koniec GRA

//** edytor
     bool editor();                       // glowna funkcja
     bool e_move();                       // komunikacja z userem
     bool e_menu();                       // menu edytora
     bool new_map();                      // nowa mapa
     bool save_map();                     // zapis mapy
     bool load_map();                     // wczytanie mapy
     bool put_block();                    // dodanie elementu
     bool put_blocks();                   // dodawanie wielu elementow
     bool delete_block();                 // usuwanie elementu
     bool e_draw_help();                  // rysowanie info o klawiszach
     bool e_draw_menu( int );             // rysowanie menu
     bool draw_pointer();                 // rysowanie wskaznika
     std::string pobierz_nazwe( int, int);// pobranie nazwy
//** koniec edytor

//** grafika GRA
     bool draw_snake();
     bool draw_board();
     bool draw_food();
     bool draw_element( int, ELEMENT );
     bool draw_bar ( int, int );
//** koniec grafika GRA

//** dodatki GRA
     void pause( int );
     void waitms( double, bool );
     inline void disp_beta( int, double );
     double GetTime();
//**koniec dodatki gra


bool map1();
bool map2();
inline void clear();
inline void zmaluj( std::string , int );
inline void logo_effect();


//console
bool login();
bool log(bool);
bool console();
std::string get_command(bool);
bool f_speed(bool);
bool f_transparent(bool);
bool f_length(bool);
bool f_hardcore(bool);
bool logout(bool &);
bool help();
bool f_food(bool);
bool f_bonus(bool);
bool f_direction(bool);
bool f_snake_pos(bool);

#endif // GAME_H_INCLUDED


