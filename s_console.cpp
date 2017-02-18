#include "s_editor.cpp"

vector<string> commands;

bool console()
{
     
     bool ok;
     static bool access = false;
     string command;
     commands.push_back("log"); // funkcja log zwracajaca wartosci wszystkich zmiennych lokalnych
     commands.push_back("login"); // funkcja logujaca do systemu
     commands.push_back("logout"); // funkcja wylogowywujaca
     commands.push_back("speed");
     commands.push_back("length");
     commands.push_back("transparent");
     commands.push_back("hardcore");
     commands.push_back("help");
     commands.push_back("food");
     commands.push_back("bonus");
     commands.push_back("kierunek");
     commands.push_back("snake");
     commands.push_back("exit");
     commands.push_back("quit");
     
     textcolor(0);
     clrscr();
     textcolor(10);
     cout << " WELCOME to snake console version 2.0 (8.03.10) " << endl;
     cout << " the console is for you and is waiting for orders" << endl;
     cout << " type \"help\" if you dont know what to do" << endl;
     do
     {
       textcolor(10);
       if (access) cout << "&>";
       else cout << "->";
       command = get_command(false);
       if ( command.size() == 0 ) break;
       else 
       {
            if ( command == "log" ) log(access);
            if ( command == "speed" ) f_speed(access);
            if ( command == "logout" ) logout(access);
            if ( command == "length" ) f_length(access);
            if ( command == "transparent" ) f_transparent(access);
            if ( command == "hardcore" ) f_hardcore(access);
            if ( command == "help" ) help();
            if ( command == "food" ) f_food(access);
            if ( command == "bonus" ) f_bonus(access);
            if ( command == "kierunek" ) f_direction(access);
            if ( command == "snake" ) f_snake_pos(access);
            if ( command == "exit" || command == "quit" ) break;
            if ( command == "login" )
            {
                 access = login();
                 if ( access )
                 {
                      textcolor(10);
                      cout << "access gained";
                 }
                 else 
                 {
                      textcolor(12);
                      cout << "access denied";
                 }
                 cout << endl;
            }
            ok = false;
            for ( int k = 0; k < commands.size(); k++ ) if ( commands.at(k) == command ) ok = true;
            if(!ok)
            {
                 textcolor(10);
                 cout << endl << "The command " << command << " was not found" << endl;
            }
       }

                                    
     }while(1);
     
     
     clrscr();
     draw_board();
     draw_food();
     draw_snake();
     textcolor(8);
     gotoxy(3,25);
     cout << " Type \"p\" to pause the game";    
     
     return true;
}
/*********************************************************************/
string get_command(bool cover)
{
       string napis;
       char tmp1;
       int x = wherex(), y = wherey();
       do
       {
        gotoxy(x, y);
        textcolor(0);
        textbackground(0);
        for ( int i = 0; i < 50; i++ ) cout << (char)219;
        napis.clear();
        gotoxy(x, y);       
        
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
                if ( !cover ) cout << tmp1;
                else cout << "*";
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
/*********************************************************************/
bool log( bool access )
{
     textcolor(7);
     textbackground(0);
     f_speed(false);
     f_transparent(false);
     f_hardcore(false);
     f_food(false);
     f_bonus(false);
     f_direction(false);
     f_snake_pos(false);
     cout << endl << " access " << access<< endl;
     return true;
}
/*********************************************************************/
bool login()
{
     string r_name = "ghost", name;
     string r_password = "qwe", password;
     cout << endl << "Enter name: ";
     name = get_command(false);
     cout << endl << "Enter password: ";
     password = get_command(true);
     cout << endl;
     if ( name == r_name && password == r_password ) return true;
     return false;
}
/*********************************************************************/
bool f_speed( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " The speed is ";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Enter new speed: ";
         cin >> speed;
         cout << " The speed is now ";
     }
     cout << speed << endl;
     return true;
}   
/*********************************************************************/
bool f_length( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " The length is ";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Enter new length: ";
         cin >> length[0];
         cout << " The length is now ";
     }
     cout << length[0] << endl;
     return true;
}
/*********************************************************************/   
bool f_transparent( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " Ghost mode is ";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Set the ghost mode: ";
         cin >> transparent;
         cout << " The Ghost mode is now ";
     }
     if ( transparent ) cout << "ON";
     else cout << "OFF";
     cout << endl;
     return true;
}   
/*********************************************************************/
bool f_hardcore( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " Hardcore mode is ";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Set the hardcore mode: ";
         cin >> hardcore;
         cout << " The hardcore mode is now ";
         
     }
     
     if ( hardcore ) cout << "ON";
     else cout << "OFF";
     cout << endl;
     return true;
}   
/*********************************************************************/
bool logout( bool & access)
{
     if ( access == false ) return false;
     textcolor(10);
     cout << endl << " You have loged out" << endl;
     access = false;
     return true;
}   
/*********************************************************************/
bool help()
{
     textcolor(14);
     cout << endl << " List of commands:" << endl;
     cout << " login to log in" << endl;
     cout << " transparent to set the ghost mode" << endl;
     cout << " hardcore to set the hardcore mode" << endl;
     cout << " speed to set the speed" << endl;
     cout << " length to set the length" << endl;
     cout << " logout to log off" << endl;
     cout << " food to set food position" << endl;
     cout << " bonus to set bonus position" << endl;
     cout << " snake to set snake head position" << endl;
     cout << " kierunek to set snake's direction" << endl;
     cout << " exit or quit to quit console" << endl;
     return true;
}
/*********************************************************************/
bool f_food( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " The food is"; 
     }
     else if (access)
     {
         textcolor(14);
         cout << " Enter new position of food: " << endl << " x = ";
         cin >> food.x;
         cout << " y = ";
         cin >> food.y;
         cout << " The position of food is now";
     }
     cout << " at x = " << food.x << " and y = " << food.y << endl;
     return true;
}
/*********************************************************************/
bool f_bonus( bool access)
{
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " The bonus is";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Enter new position of bonus: " << endl << " x = ";
         cin >> bonus.x;
         cout << " y = ";
         cin >> bonus.y;
         cout << " The position of bonus is now";
     }
     cout << " at x = " << bonus.x << " and y = " << bonus.y << endl;
     return true;
}
/*********************************************************************/
bool f_direction( bool access)
{
     bool koniec = false;
     cout << endl;
     if ( !access )
     {
          textcolor(10);
          cout << " The direction is ";
     }
     else if (access)
     {
         textcolor(14);
         cout << " Enter new direction (use arrows): " << endl;
         char znak = getch();
         do
         {
           switch(znak)
           {
                     case 224://klawisze specjalne
                     znak=getch();
                     switch(znak)
                     {
                          case 72: // strzalka w gore
                          {
                               kierunek[0] = DIR_UP;
                               koniec = true;
                               break;
                          }
                          case 80: // strzalka w dol
                          {
                               kierunek[0] = DIR_DOWN;
                               koniec = true;
                               break;
                          }
                          case 75: // strzalka w lewo
                          {
                               kierunek[0] = DIR_LEFT;
                               koniec = true;
                               break;
                          }
                          case 77: // strzalka w prawo
                          {
                               kierunek[0] = DIR_RIGHT;
                               koniec = true;
                               break;
                          }
                          default : break;
                     }  
                     
                     default : break;
           }
         }while(!koniec);
         cout << " The direction is now: ";
     }
     switch(kierunek[0])
     {
                     case DIR_DOWN:
                     {
                          cout << "DIR_DOWN";
                          break;
                     }
                     case DIR_UP:
                     {
                          cout << "DIR_UP";
                          break;
                     }
                     case DIR_LEFT:
                     {
                          cout << "DIR_LEFT";
                          break;
                     }
                     case DIR_RIGHT:
                     {
                          cout << "DIR_RIGHT";
                          break;
                     }
                     default : break;
     }
     cout << endl;
     return true;
}
/*********************************************************************/
bool f_snake_pos(bool access)
{
     cout << endl;
     if( !access )
     {
         textcolor(10);
         cout << " The Snake position is";
     }
     else
     {
         textcolor(14);
         cout << " Enter new position of Snake: " << endl << " x = ";
         cin >> Snake[0][0].x;
         cout << " y = ";
         cin >> Snake[0][0].y;
         cout << " The position of Snake is now";
     }
     cout << " at x = " << Snake[0][0].x << " and y = " << Snake[0][0].y << endl;
     return true;
}
/*********************************************************************/
