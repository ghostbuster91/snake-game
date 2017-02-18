#include "s_console.cpp"


main()
{
      title("Snake by Ghost");
      
      FILE * records = fopen("c:\\cfg.rcf","r");
      if ( records != NULL )
      {
           fclose(records);
           system("DEL c:\\cfg.rcf");     
      }
      int wynik;
      
      resize(80, 40);

      do
      {
          
       wynik = menu();
       clrscr();
       if ( wynik >= 0 ) scores(wynik);
       if ( wynik == -1 ) break;      
       restart();
       
      }while( 1 );
       /*char buf[1000];
       DWORD dlg = 1000;
       DWORD err;
       InternetGetLastResponseInfo(&err, buf, &dlg);
       cout << buf;*/  
       // to powyzej to w razie czego do spr odpowiedzi z neta
            
      return 0;
}
