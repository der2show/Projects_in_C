//------------------------------------------------------------------
//        Statek - algorytm z nawrotami ( BACKTRACKING )
//------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "ship.h"

#define N 10
#define M 10
#define SHIP_DEPTH 5    // głębokość zanurzenia okrętu

int** CreateTab2D( int nCol, int nRow );
void freeTab2D( int*** pTab );
void PrintMatrix( int** pTab, int nRow, int nCol );

int main( int argc, char* argv[] )
{
        /*
        // testowanie cze same funkcje działają
        //int** tab20 = CreateTab2D( N, M );      // komunikat
        int** tab20 = NULL;
        if( !CreateTab2D(N,M ) )
        {
                printf( "Failed to create tab2D\n" );
                return 1;
        }
        tab20[1][1] = 2;
        tab20[7][3] = 2;
        tab20[8][6] = 2;
        tab20[3][3] = 2;
        PrintMatrix( tab20, N, M);
        freeTab2D( &tab20 );
        */

        if( argc != 2 )
        {
                printf("Usage: %s <file_name>\n ", argv[0] );
                return 1;
        }

        //Wykreowac dynamicznie dwie tablice dwuwymiarowe (ogolnie moga byc rozne wymiary szerok i wysok)
        // kreowanie  druga metoda tworzenia dynamicznego tablic 2D
        int** depthTab =  CreateTab2D( N, M );
        int** rootTab = CreateTab2D( N, M );

        if( !depthTab || !rootTab )
        {
                printf("Failed to create depthTab and rootTab\n");
                freeTab2D( &depthTab );
                freeTab2D( &rootTab );
                return 2;
        }

        // wyzerowac obie tablice (zaleznie czy bylo malloc czy calloc(preferowany))
        // wczytac dane (sprawdzic argc)  glebokosci

        if( !setTab( argv[1], depthTab, N, M ) )
        {
                printf("Failed to load depth data!\n");
                freeTab2D( &depthTab );
                freeTab2D( &rootTab );
                return 3;
        }
        printf("\n[----------------------------------------------------------]\n\n\t\t\t\t\tMap of depths:\n\n");
        PrintMatrix( depthTab, N, M );

        // dorobić aby było 10 x 10
        // Jezeli nie znaleziono drogi od (0,0) do (N-1,M-1)- funkcja rekur root - wypisac
        // "** Nie ma mozliwosci doplynac do portu!!\n\n";
        // jesli ok to wypisac trase

        if( root( depthTab, N, M, SHIP_DEPTH, 0, 0, rootTab, N-1, M-1 ) )
        {
                printf("\n[----------------------------------------------------------]\n\n\t\t\t\t\tRoute to port:\n\n");
                PrintMatrix( rootTab, N, M );
        }
        else printf("\n[----------------------------------------------------------]\n\n\t\t\t\tShip didn't reach the port!\n");
        printf("\n[----------------------------------------------------------]\n\n");

        //zwolnic pamiec!! - nie z funkcji, z której mieliśmy nie korzystać
        freeTab2D( &depthTab );
        freeTab2D( &rootTab );
        return 0;
}

int** CreateTab2D( int nCol, int nRow )
{
        // inaczej niż w przypadku macierzy, zwracany adres tablicy, 2 parametry
        // zacznemy tak samo bo jest tablica tablic, potem 1 callociem alokujemy pTab[0] oraz wszystkie wiersze/kolumny
        // pętla for działa od 1, aby podwiązać do adresów początków

        if( nCol <= 0 || nRow <= 0 )
        {
                printf("Invalid tab size!\n");
                return NULL;
        }

        int** p = (int**)calloc(  nRow , sizeof( int* ) );
        if( !p )
        {
                printf("Failed to allocate memory for p! in CreateTab2d()\n");
                return NULL;
        }

        p[0] = (int*)calloc( nRow * nCol , sizeof( int ) );
        if( !p[0] )
        {
                printf("Failed to allocate memory for *p! in CreateTab2d()\n");
                return NULL;
        }

        int* temp = p[0];
        for( int i = 1; i < nRow; i++ )
        {
                temp += nCol;
                p[i] = temp;
        }

        return p;
}

void freeTab2D( int*** pTab )
{
        if( !pTab )
        {
                printf("Missing pTab in freeTab2D()\n");
                return;
        }

        free( **pTab );           // zwolnic 0-owy elem tablicy
        free( *pTab );            // zwolnic tablice tablic
        *pTab = NULL;             // wynulowac wskaznik
}

void PrintMatrix( int** pTab, int nRow, int nCol )
{
        // drukuje macierz

        if( !pTab || nRow < 1 )
        {
                printf("Missing pTab or invalid dim in PrintMatrix()\n");
                return;
        }

        for( int i = 0; i < nRow; i++ )
        {
                int* v = *pTab++;
                for( int j = 0; j < nCol; j++ )
                {
                        //printf("%d ", pTab[i][j] );
                        printf("%d ", *v++ );
                }
                printf("\n");
        }
        printf("\n");
}