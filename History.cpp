// History.cpp

#include "History.h"

#include <iostream>

History::History(int nRows, int nCols)
{
    // record number of rows and columns for game
    m_rows = nRows;
    m_cols = nCols;
    
    // fill in the game part of the 2D array with 0s
    for (int r = 0; r < nRows; r++)
        for (int c = 0; c < nCols; c++)
            grid[r][c] = 0;
}

// History object is notified of a robot death in - bool Robot::getAttacked(int dir)
bool History::record(int r, int c)
{
    // r or c is not within the bounds of the game
    if (r < 1 || r > m_rows || c < 1 || c > m_cols)
        return false;
    
    // increment the appropriate int in the 2D array
    // robot coordinates of r = 1 and c = 1 correspond to grid[0][0]
    grid[r - 1][c - 1]++;
    
    return true;
}

void History::display() const
{
    clearScreen();
    
    // loop through the rows and columns of the 2D array
    for (int i = 0; i < m_rows; i++)
    {
        for (int j = 0; j < m_cols; j++)
        {
            int numDied = grid[i][j]; // retrieve # dead robots on a grid space
            
            if (numDied == 0) // no robots dead
                std::cout << '.';
            else
            {
                if (numDied >= 26) // 26 or more robots have died on a space
                    std::cout << 'Z';
                else // print the appropriate alphabet character
                    std::cout << static_cast<char>('A' - 1 + numDied);
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}
