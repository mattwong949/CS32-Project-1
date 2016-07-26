// Robot.cpp

#include "Robot.h"
#include "Arena.h"
#include "globals.h"

#include <iostream>


Robot::Robot(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        std::cout << "***** A robot must be in some Arena!" << std::endl;
        std::exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        std::cout << "***** Robot created with invalid coordinates (" << r << ","
        << c << ")!" << std::endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_health = INITIAL_ROBOT_HEALTH;
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

void Robot::move()
{
    // Attempt to move in a random direction; if we can't move, don't move
    int dir = randInt(0, 3);  // dir is now UP, DOWN, LEFT, or RIGHT
    m_arena->determineNewPosition(m_row, m_col, dir);
}

bool Robot::getAttacked(int dir)  // return true if dies
{
    m_health--;
    if (m_health == 0)
    {
        // robot dies so report death to History object
        m_arena->history().record(m_row, m_col);
        return true;
    }
    if ( ! m_arena->determineNewPosition(m_row, m_col, dir))
    {
        // robot dies so report death to History object
        m_arena->history().record(m_row, m_col);
        m_health = 0;
        return true;
    }
    return false;
}