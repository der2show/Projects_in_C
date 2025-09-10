#ifndef SHIP_H
#define SHIP_H

//#define _SEARCHING_     // wydruk kontrolny procesu "płynięcia statku", sprawdzania pozycji, itd.
#define PARAMETER_ERROR -1

// typ wyliczeniowy
typedef enum { UP, RIGHT, DOWN, LEFT } Directions;

int move( int** pTab, int nRow, int nCol, int nDepth, int move, int x, int y, int* px, int* py, int** pRoot );
int root( int** pTab, int nRow, int nCol, int nDepth, int x, int y, int** pRoot, int x_dest, int y_dest );
void clearRoot( int** pRoot, int nRow, int nCol );
int setTab( char* sFile, int** pTab, int nRow, int nCol );

#endif //SHIP_H

