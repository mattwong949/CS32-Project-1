// Game.cpp

#include "Game.h"
#include "Arena.h"
#include "Player.h"
#include "globals.h"
#include "History.h"

#include <iostream>
#include <string>


Game::Game(int rows, int cols, int nRobots)
{
    if (nRobots < 0)
    {
        std::cout << "***** Cannot create Game with negative number of robots!" << std::endl;
        exit(1);
    }
    if (nRobots > MAXROBOTS)
    {
        std::cout << "***** Trying to create Game with " << nRobots
        << " robots; only " << MAXROBOTS << " are allowed!" << std::endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nRobots > 0)
    {
        std::cout << "***** Cannot create Game with nowhere to place the robots!" << std::endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with robots
    while (nRobots > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        // Don't put a robot where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_arena->addRobot(r, c);
        nRobots--;
    }
}

Game::~Game()
{
    delete m_arena;
}

void Game::play()
{
    Player* p = m_arena->player();
    if (p == nullptr)
    {
        m_arena->display();
        return;
    }
    do
    {
        m_arena->display();
        std::cout << std::endl;
        std::cout << "Move (u/d/l/r//h/q): ";
        std::string action;
        std::getline(std::cin,action);
        if (action.size() == 0)  // player stands
            p->stand();
        else
        {
            switch (action[0])
            {
                default:   // if bad move, nobody moves
                    std::cout << '\a' << std::endl;  // beep
                    continue;
                case 'q':
                    return;
                case 'h': // ask for history of robot deaths
                    (m_arena->history()).display();
                    std::cout << "Press enter to continue.";
                    std::cin.ignore(10000, '\n');
                    continue;
                case 'u':
                case 'd':
                case 'l':
                case 'r':
                    p->moveOrAttack(decodeDirection(action[0]));
                    break;
            }
        }
        m_arena->moveRobots();
    } while ( ! m_arena->player()->isDead()  &&  m_arena->robotCount() > 0);
    m_arena->display();
}

