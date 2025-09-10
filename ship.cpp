#include "ship.h"

#include <cstring>
#include <stdio.h>
#include <stdlib.h>

int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot )
{
    /*  pTab - tablica okreslajaca glebokosc w kazdym kwadracie
        nRow, nCol - rozmiar pTab,
        nDepth - glebokosc zanurzenia statku
        move - kierunek ruchu (wart typu wylicz)
        x, y - indeksy w tablicy skad wykonujemy kolejny ruch np. zaczynamy od 0,0
        px, py - nowe wspolrzedne  (parametry WY)
        pRoot - tablica pamietajaca ruchy o rozm nRow, nCol
    */

    /*  x  y - wsporzedne skad robimy nowy ruch
        wykonac kolejny ruch w kierunku move obliczajac nowe wspolrzedne *px *py
        (switch)
        sprawdzic czy nowe indeksy *px i *py sa w zakresie indeksow tablicy
        a nastepnie sprawdzic warunek czy nie jest za plytko ">nDepth " oraz
        czy nie bylo sie juz w lokalizacji (*px,*py) - wg tabl pRoot (wart 0 w nowej lokalicacji)
        jesli wszystkie warunki poprawne to zwracamy 1
        else 0
    */

    if( !pTab || !pRoot || !px || !py ) return PARAMETER_ERROR;

    *px = x;
    *py = y;

    switch( move )
    {
        case UP:    (*py)--; break;
        case RIGHT: (*px)++; break;
        case DOWN:  (*py)++; break;
        case LEFT:  (*px)--; break;
    }

    if( *px < 0 || *px >= nRow || *py < 0 || *py >= nCol )
    {
        #ifdef _SEARCHING_
        printf("Move out of borders: (%d,%d) !\n", *px, *py );
        #endif
        return 0;
    }

    if( pTab[*px][*py] <= nDepth )
    {
        #ifdef _SEARCHING_
        printf("Too shallow in (%d,%d): depth %d <= %d !\n", *px, *py, pTab[*px][*py], nDepth );
        #endif
        return 0;
    }

    if( pRoot[*px][*py] != 0 )
    {
        #ifdef _SEARCHING_
        printf("(%d,%d) was visited before!\n", *px, *py );
        #endif
        return 0;
    }

    return 1;
}

//----------------------------------------------------------------------------------
int root( int** pTab, int nRow, int nCol, int nDepth,  int x, int y, int** pRoot,
           int x_dest, int y_dest )
{
    //  --- rekurencyja
    /*  pTab tabl glebokosci   o romiarze nRow  i nCol
        dDepth - glebokosc zanurzenia statku (!)
        x, y - wspolrzedne skad robimy kolejny ruch
        pRoot tablica kolejnych ruchow (w pole wstawia sie numer kolejnego ruchu)
        x_dest, y_dest - wsporzedne portu
    */

    /*  tutaj musimy wymyśleć, nie ma szkicu, nie wolno korzystać zmiennych globalnych, nic nie modyfikować parametrów
        jak zmienna lokalna zachowuje wartość po wyjściu z funkcji - static_int, zmienna statyczna ( tylko o zasięgu tego pliku )
        Dodatkowe, jeśli mamy zmienną globalną int x = 1, to możemy jej użyć w innym pliku jako zmienna globalna -> extend_int x
        tabl pRoot pamieta droge   -   numer ruchu pole przez ktore odwiedzono (plynie statek)
                                    0 pole nie odwiedzone
        wstawic do tablicy pRoot kolejny numer ruchu
    */

    /*  zdefiniowac nowe wspolrzedne (zmienne lokalne xnew, ynew)
        sprwadzic wszystkie mozliwosci ruchu, pętla for
        jesli ruch jest mozliwy w zadanym kierunku
        jesli wykonanie kolejnego kroku sie powiodlo - rekurencyjnie root()
    */

    if( !pTab || !pRoot ) return PARAMETER_ERROR;

    static int step = 1;
    pRoot[x][y] = step++;

    if( x == x_dest && y == y_dest )
    {
        printf("\n[----------------------------------------------------------]\n\n\t\t\t\t\tPort was found in (%d,%d)\n", x, y );
        return 1;
    }

    #ifdef _SEARCHING_
    printf("Checking position (%d,%d), step %d\n", x, y, pRoot[x][y] );
    #endif

    int x_new = 0;
    int y_new = 0;

    for( int i = UP; i <= LEFT; i++ )
    {
        if( move( pTab, nRow, nCol, nDepth, i, x, y, &x_new, &y_new, pRoot ) )
        {
            #ifdef _SEARCHING_
            printf("Moving %d from (%d,%d) to (%d,%d)\n", i, x, y, x_new, y_new);
            #endif

            if( root( pTab, nRow, nCol, nDepth, x_new, y_new, pRoot, x_dest, y_dest ) )
                return 1;
        }
    }

    pRoot[x][y] = 0;
    step--;
    #ifdef _SEARCHING_
    printf("Backtracking from (%d,%d)\n", x, y );
    #endif

    return 0;

}

void clearRoot( int** pRoot, int nRow, int nCol )
{
    // zeruje tablice, wywołuje funkcję bibliotecznę, napisać ale nie będziemy korzystać

    if( !pRoot )
    {
        printf("Missing pRoot in clearRoot()!\n");
        return;
    }

    memset( *pRoot, 0, nRow * nCol * sizeof( int ) );
}

int setTab( char* sFile, int** pTab, int nRow, int nCol )
{
    /*  wczytuje dane z pliku
        sFile -  nazwa pliku wejsciowego - parametr main()
        pTab  - tablica glebokosci morza
        param: nRow, nCol wymiary tablicy glebokosci morza
        w razie niepowodzenia otwarcia pliku do odczytu zwraca 0
        else 1
    */

    if( !sFile || !pTab ) return PARAMETER_ERROR;

    FILE* fin = fopen( sFile, "r" );
    if( !fin )
    {
        //printf("Error opening file %s\n", sFile );
        return 0;
    }

    for( int i = 0; i < nRow; i++ )
    {
        int* v = *pTab++;
        for( int j = 0; j < nCol; j++ )
            fscanf( fin, "%d", v++ );
    }

    fclose( fin );
    return 1;
}