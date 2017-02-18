#include "S_game_def1233.cpp"

vector<SEGMENT> e_mapa;
SEGMENT wskaznik;
char gblock = '+';
int pointer_color = 7;

/********************************************************************/
bool editor()
{
     G_State = GS_EDIT; // stan gry edytor
     int k;
     for ( k = 0; k < 2; k++ )
     {
         for ( int i = 0; i < length[k] - 1; i++ ) // glowa wez ma poczatkowe wspolrzedne StartX i StartY
         {
             Snake[k][i].x = StartX + k * 12;
             Snake[k][i].y = StartY + i;
         }
     }
     clrscr();
     wskaznik.x = wskaznik.y = 10;
     bool koniec = false;
     
     draw_board();
     draw_snake();
     e_draw_help();
     
     do
     {
        draw_pointer();
        koniec = e_move();                
     }while(!koniec);
     
     G_State = GS_NOTSTARTED; // przywracanie stanu gry na nie rozpoczeta
     return true;
}
/********************************************************************/
bool e_move()
{
     char znak = getch();
     
     // BEGIN: zamalowywanie poprzedniego miejsca wskaznika -----
     bool dontcover = false;
     gotoxy(wskaznik.x, wskaznik.y);
     for ( int i = 0; i < e_mapa.size(); i++ )
     {    
          if ( e_mapa.at(i).x == wskaznik.x && e_mapa.at(i).y == wskaznik.y )
          {
               dontcover = true;
               textbackground(0);
               textcolor(8);
               cout << gblock;
               break;
          }
     }
               
      
     if ( !dontcover )
     {
        textcolor(0);
        cout << (char)219;
     }
     // END: zamalowywanie poprzedniego miejsca wskaznika -----
     
     switch(znak)
     {
                 case 72://strzalka w gore
                 {
                     if ( wskaznik.y > 2 )
                     {
                          if( wskaznik.y == (StartY + length[0] - 1) && wskaznik.x == StartX ||
                              wskaznik.y == (StartY + length[0] - 1) && wskaznik.x == StartX + (nr_of_players - 1) * 12 ) break;
                          wskaznik.y -= 1;
                     }
                     break;
                 }
                 case 80://strzalka w dol
                 {
                     if ( wskaznik.y < 38 )
                     {
                          if( wskaznik.y == (StartY - 1) && wskaznik.x == StartX ||
                              wskaznik.y == (StartY - 1) && wskaznik.x == StartX + (nr_of_players - 1) * 12 ) break;
                          wskaznik.y += 1;
                     }
                     break;
                 }
                 case 75://strzalka w lewo
                 {
                     if ( wskaznik.x > 2 )
                     {
                          if( wskaznik.x == (StartX + 1) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ||
                              wskaznik.x == (StartX + (nr_of_players - 1) * 13) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ) break;
                          wskaznik.x -= 1;
                     }
                     break;
                 }
                 case 77://strzalka w prawo
                 {
                     if ( wskaznik.x < 79 )
                     {
                          if( wskaznik.x == (StartX - 1) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ||
                              wskaznik.x == (StartX + (nr_of_players - 1) * 11) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ) break;
                          wskaznik.x += 1;
                     }
                     break;
                 }
                 case 27: // klawisz ESC
                 {
                      e_mapa.clear();
                      return true;
                 }
                 case 13: // klawisz ENTER
                 {
                      put_block();
                      break;
                 }
                 case 32: // klawisz SPACE
                 {
                      put_blocks();
                      break;
                 }
                 case 0: // klawisz DEL
                 {
                      case 83:
                      {    
                           delete_block();
                           break;
                      }
                      break;
                 }
                 case 9: // Tabulator
                 {
                      return !(e_menu());
                      break;
                 }                  
                 default : break;
     }
     return false;
}
/********************************************************************/
bool put_block()
{

     for ( int i = 0; i < e_mapa.size(); i++ )
     {
         if ( e_mapa.at(i).x == wskaznik.x && e_mapa.at(i).y == wskaznik.y ) return false;
              
     }
   
     e_mapa.push_back(wskaznik);
     
     gotoxy(wskaznik.x, wskaznik.y);
     textcolor(8);
     cout << gblock;
     return true;
}
/********************************************************************/
bool delete_block()
{
     for ( int i = 0; i < e_mapa.size(); i++ )
     {
         if ( e_mapa.at(i).x == wskaznik.x && e_mapa.at(i).y == wskaznik.y )
         {
              e_mapa.erase(e_mapa.begin() + i);
              return true;
         }
     }
     return false;
}
/*********************************************************************/
bool draw_pointer()
{
     
     gotoxy( wskaznik.x, wskaznik.y );
     for ( int i = 0; i < e_mapa.size(); i++ )
     {
         if ( e_mapa.at(i).x == wskaznik.x && e_mapa.at(i).y == wskaznik.y )
         {
             textbackground(pointer_color);
             textcolor(0); 
             cout << gblock;
             gotoxy(80, 40);
             return true;
         }
     }
     textcolor(pointer_color);
     cout << (char)219;
     gotoxy(80, 40);
     return true;
}
/*********************************************************************/
bool e_draw_menu(int pozycja)
{
     string menu[] = {"New map", "Load", "Save", "Options", "Quit" };
     textcolor(15);
     for ( int i = 0; i < 5; i++ )
     {
         gotoxy( 2 + i * 16 , 40);
         if ( i == pozycja ) textbackground(9);
         else textbackground(0); 
         cout << menu[i];
     }
     textbackground(0);
     gotoxy(80,40);    
     return true;
} 
/*********************************************************************/
bool e_menu()
{
     int pozycja = 0;
     bool koniec = false, koniec_2 = false;
     do
     {
          
          gotoxy(1, 40);
          textcolor(0);
          textbackground(0);
          for ( int i = 0; i < 79; i++ ) cout << (char)219; 
          if ( koniec_2 ) break;
          e_draw_menu( pozycja );
          
          char znak = getch();
          switch(znak)
          {
                 case 224://klawisze specjalne
                 znak=getch();
                 switch(znak)
                 {
                    case 75://strzaalka w lewo
                    {
                         if ( pozycja > 0 ) pozycja--;
                         break;
                    }
                    case 77://strzalka w prawo
                    {
                         if ( pozycja < 4 ) pozycja++;
                         break;
                    }
                 }
                 znak=0;
                 break;
                 case 13://ENTER
                 {
                      if( pozycja == 0 ) new_map();
                      else if ( pozycja == 1 ) load_map();
                      else if ( pozycja == 2 ) save_map();
                      //else if ( pozycja == 3 ) e_options();
                      else if ( pozycja == 4 ) 
                      {
                           e_mapa.clear();
                           return false;
                      }
                      break;
                 }
                 case 27: // ESC
                 {
                      e_mapa.clear();
                      return false;
                 }
                 case 9: // TAB
                 {
                      koniec_2 = true;
                      break;
                 }
                 default : break;
          }
     }while ( !koniec );
     e_draw_help();
     return true;
}
/********************************************************************/
bool e_draw_help()
{
     textbackground(0);
     textcolor(7);
     gotoxy(1,40);
     cout << "[TAB] - enter menu "  
          << "[DEL] - delete element "
          << "[ENTER / SPACE] - put element/s ";
          
     return true;
}         
/********************************************************************/
bool new_map()
{
     gotoxy(1, 40);
     textcolor(0);
     textbackground(0);
     for ( int i = 0; i < 79; i++ ) cout << (char)219;
     
     textcolor(15);
     gotoxy(1, 40);
     cout << " CZY NAPEWNO ? [T/N]";
     char znak;
     do
     {
          znak = getch();
          if( znak == 't' )
          {
              e_mapa.clear();
              clrscr();
              draw_board();
              e_draw_help();
          }
          else if( znak == 'n' )
          {
               gotoxy(1, 40);
               textcolor(0);
               textbackground(0);
               for ( int i = 0; i < 76; i++ ) cout << (char)219; 
          }
     }while ( znak != 'n' && znak != 't' );
     
     if ( e_mapa.empty() ) return true;
     else return false;
}
/********************************************************************/
bool put_blocks()
{
     char znak;
     bool koniec = false, empty = true;
     
     
     do
     {
        for ( int k = 0; k < e_mapa.size(); k++)
        {
            if ( e_mapa.at(k).x == wskaznik.x && e_mapa.at(k).y == wskaznik.y ) empty = false;
        }
        if ( empty ) e_mapa.push_back(wskaznik);
        empty = true;
        textcolor(0);
        textbackground(pointer_color);
        gotoxy(wskaznik.x, wskaznik.y);
        cout << gblock;
        
        znak = getch();
        textcolor(8);
        textbackground(0);
        gotoxy(wskaznik.x, wskaznik.y);
        cout << gblock;
        gotoxy(80,40);
        
        switch(znak)
        {
                    case 224:
                    znak = getch();
                    switch(znak)
                    {
                       case 72://strzalka w gore
                       {
                            if ( wskaznik.y > 2 )
                            {
                                 if( wskaznik.y == (StartY + length[0] - 1) && wskaznik.x == StartX ) break;
                                 wskaznik.y -= 1;
                            }
                            break;
                       }
                       case 80://strzalka w dol
                       {
                            if ( wskaznik.y < 23 )
                            {
                                 if( wskaznik.y == (StartY - 1) && wskaznik.x == StartX ) break;
                                 wskaznik.y += 1;
                            }
                            break;
                       }
                       case 75://strzalka w lewo
                       {
                            if ( wskaznik.x > 2 )
                            {
                                 if( wskaznik.x == (StartX + 1) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ) break;
                                 wskaznik.x -= 1;
                            }
                            break;
                       }
                       case 77://strzalka w prawo
                       {
                            if ( wskaznik.x < 79 )
                            {
                                 if( wskaznik.x == (StartX - 1) && wskaznik.y > (StartY - 1) && wskaznik.y < (StartY + length[0] - 1) ) break;
                                 wskaznik.x += 1;
                            }
                            break;
                       }
                    }
                    znak=0;
                    break;
                    case 32: // klawisz SPACE
                    {
                         koniec = true;
                         break;
                    }
                    case 27: // klawisz ESC
                    {
                      koniec = true;
                      break;
                    }
                    default : break;
        }
        
     }while( !koniec );
     
     return true;
}
                         
/********************************************************************/
bool save_map()
{
     const string extention = ".smap";
     string file_name;
     ofstream file;
     
     file_name = pobierz_nazwe(1,40);
     if ( file_name.size() == 0 ) return false;
     
     file.open( (file_name + extention).c_str() );
     if ( file.good() )
     {
          for ( int j = 0; j < e_mapa.size(); j++ )
          {
              file << e_mapa.at(j).x << endl;
              file << e_mapa.at(j).y << endl;
          }
          file.close();
          
          gotoxy(1, 40);
          textcolor(0);
          textbackground(0);
          for ( int k = 0; k < 79; k++ ) cout << (char)219;
          textcolor(10);
          gotoxy(1, 40);
          cout << "Zapisano " << file_name + extention;
     }
     else 
     {
          cout << " HUJ ";
     }
     getch();
     return true;
}
/********************************************************************/
bool load_map()
{
     ifstream file;     
     const string extention = ".smap";
     string file_name;
     SEGMENT tmp;

     file_name = pobierz_nazwe(1,40);
     if ( file_name.size() == 0 ) return false;
     file.open( (file_name + extention).c_str() );
     if ( file.good() )
     {
          clrscr();
          e_mapa.clear();
          while( !file.eof() )
          {      
                 tmp.x = 0;
                 tmp.y = 0;
                 file >> tmp.x;
                 file >> tmp.y;
                 if ( tmp.x && tmp.y ) e_mapa.push_back(tmp);
          }
          draw_board();
          for ( int k = 0; k < e_mapa.size(); k++ )
          {
              gotoxy(e_mapa.at(k).x, e_mapa.at(k).y);
              cout << gblock;
          }
          return true;
     }
     else
     {
         cout << "error";
         return false;
     }
}
/********************************************************************/
