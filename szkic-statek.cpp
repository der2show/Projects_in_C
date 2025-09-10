/*==================
BACKTRACKING  algorytm z nawrotami
-------------
og�lny algorytm wyszukiwania wszystkich (lub kilku) rozwi�za� niekt�rych problem�w 
obliczeniowych, kt�ry stopniowo generuje kandydat�w na rozwi�zanie jednak, 
gdy stwierdzi, �e znaleziony kandydat x nie mo�e by� poprawnym rozwi�zaniem, 
nawraca (ang. "backtracks") do punktu, gdzie mo�e podj�� inn� decyzje 
zwi�zan� z jego budow�
==============================*/

modul:   ship.cpp  ship.h

//zdefini stale N i M - wymiary  (na 10)  tam gdzie main()
#define SHIP_DEPTH 5    // glebokosc zanurzenia okretu   tam gdzie main()

// zdefiniowac typ wyliczeniowy: kierunki ruchu : UP RIGHT DOWN LEFT  (wartosci kolejne od 0)
// Korzystać ze stałych

// bez pragmy!, tylko na kompliacji warunkowej

int move( int** pTab, int nRow, int nCol, int nDepth, 
     	    int move, int x, int y, int* px, int* py, int** pRoot );

/* pTab - tablica okreslajaca glebokosc w kazdym kwadracie
   nRow, nCol - rozmiar pTab, 
   nDepth - glebokosc zanurzenia statku 
   move - kierunek ruchu (wart typu wylicz)
   x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
   px, py - nowe wspolrzedne  (parametry WY)
   pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
*/
int root( int** pTab, int nRow, int nCol, int nDepth,  
		  int x, int y, int** pRoot, int x_dest, int y_dest  );   //--- rekurencyja
/* pTab tabl glebokosci   o romiarze nRow  i nCol
    dDepth - glebokosc zanurzenia statku (!)
    x, y - wspolrzedne skad robimy kolejny ruch
    pRoot tablica kolejnych ruchow (w pole wstawia sie numer kolejnego ruchu)
    x_dest, y_dest - wsporzedne portu
*/

void clearRoot( int** pRoot, int nRow, int nCol );
// zeruje tablice, wywołuje funkcję bibliotecznę, napisać ale raczej nie będziemy korzystać

int setTab( char* sFile, int** pTab, int nRow, int nCol ); 
// wczytuje dane z pliku
  // sFile -  nazwa pliku wejsciowego - parametr main()
  // pTab  - tablica glebokosci morza
      // param: nRow, nCol wymiary tablicy glebokosci morza
  // w razie niepowodzenia otwarcia pliku do odczytu zwraca 0 
  // else 1

//===================================================================================
//=======================================
// implamentacja

//-------------------------------------------------------------
int move( int** pTab, int nRow, int nCol, int nDepth, 
     	  int move, int x, int y, int* px, int* py, int** pRoot )
{ // x  y - wsporzedne skad robimy nowy ruch
  // wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
       //(switch)
  // sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
	// a nastepnie sprawdzic warunek czy nie jest za plytko ">nDepth " oraz
  // czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot (wart 0 w nowej lokalicacji)

  //  jesli wszystkie warunki poprawne to zwracamy 1
  //    else 0
}   

//----------------------------------------------------------------------------------
int root( int** pTab, int nRow, int nCol, int nDepth,  int x, int y, int** pRoot,
           int x_dest, int y_dest )
{
  // tutaj musimy wymyśleć, nie ma szkicu, nie wolno korzystać zmiennych globalnych, nic nie modyfikować parametrów
  // jak zmienna lokalna zachowuje wartość po wyjściu z funkcji - static_int, zmienna statyczna ( tylko o zasięgu tego pliku )
  // Dodatkowe, jeśli mamy zmienną globalną int x = 1, to możemy jej użyć w innym pliku jako zmienna globalna -> extend_int x
  // tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek) 
  //                                0 pole nie odwiedzone
  // wstawic do tablicy pRoot kolejny numer ruchu

  if( statek_dotarl do portu ) 
    return 1;
    
  
 // zdefiniowac nowe wspolrzedne (zmienne lokalne xnew, ynew) 
      // sprwadzic wszystkie mozliwosci ruchu, pętla for
	     //jesli ruch jest mozliwy w zadanym kierunku 
            //jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
               return 1;
	
	// jesli wracamy to ustawiamy w pRoot ze ruch byl zly
    return 0;
  
}   



//=============================================================
//  pLIK CPP
//-------------------------------------------------------------
int main()
{
  //!!argc
  //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary szerok i wysok)
    // kreowanie  druga metoda tworzenia dynamicznego tablic 2D
  
  // wyzerowac obie tablice (zaleznie czy bylo malloc czy calloc(preferowany))
  // wczytac dane (sprawdzic argc)  glebokosci 
  10 12 9 10 8 6 4 4 7 8
  10 12 9 10 8 4 5 6 6 5
   6 9  9  5 4 6 4 4 7 8
  ....
      // dorobić aby było 10 x 10
  // Jezeli nie znaleziono drogi od (0,0) do (N-1,M-1)- funkcja rekur root - wypisac
  // "** Nie ma mozliwosci doplynac do portu!!\n\n";

  // jesli ok to wypisac trase
  //zwolnic pamiec!! - w funkcji
  return 0;
}
//==========================================================


int** CreateTab2D( int nCol, int nRow )
{
  // inaczej niż w przypadku macierzy, zwracany adres tablicy, 2 parametry
  // zacznemy tak samo bo jest tablica tablic, potem 1 callociem alokujemy pTab[0] oraz wszystkie wiersze/kolumny
  // pętla działa od 1, podwiązać do adresów początków
  int** p = (int**)calloc(1, sizeof(int*) * nRow);
  if( !p ) return NULL;


  return p;
}

void freeTab2D( int*** pTab )
{
 // zwolnic 0-owy elem tablicy 
 // zwolnic tablice tablic
 // wynulowac wskaznik
}
