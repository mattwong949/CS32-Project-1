// History.h

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int grid[MAXROWS][MAXCOLS]; // 2D array that contains corresponding int values to # of dead robots
    int m_rows; // # rows in the game
    int m_cols; // # cols in the game
};


#endif /* History_h */
