#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "../include/algorithm.h"

using namespace std;

/******************************************************
 * In your algorithm, you can just use the the funcitons
 * listed by TA to get the board information.(functions
 * 1. ~ 4. are listed in next block)
 *
 * The STL library functions is not allowed to use.
******************************************************/

/*************************************************************************
 * 1. int board.get_orbs_num(int row_index, int col_index)
 * 2. int board.get_capacity(int row_index, int col_index)
 * 3. char board.get_cell_color(int row_index, int col_index)
 * 4. void board.print_current_board(int row_index, int col_index, int round)
 *
 * 1. The function that return the number of orbs in cell(row, col)
 * 2. The function that return the orb capacity of the cell(row, col)
 * 3. The function that return the color fo the cell(row, col)
 * 4. The function that print out the current board statement
*************************************************************************/

Board TempBoard;

typedef struct Coordinate
{
    int x, y;
    void setPosition(int i, int j)
    {
        x = i;
        y = j;
    }
}Grid;

Grid *SearchAdjacent(int i, int j)
{
    Grid *Adjacents = new Grid[8];
    for(int k = 0; k < 8; k++)
    {
        Adjacents[k].setPosition(-1,-1);
    }

    int num = 0;
    if(i==0)
    {
        Adjacents[num].setPosition(i+1, j); num++;
    }
    else if(i==ROW-1)
    {
        Adjacents[num].setPosition(i-1, j); num++;
    }
    else
    {
        Adjacents[num].setPosition(i-1, j); num++;
        Adjacents[num].setPosition(i+1, j); num++;
    }

    if(j==0)
    {
        Adjacents[num].setPosition(i, j+1); num++;
    }
    else if(j==COL-1)
    {
        Adjacents[num].setPosition(i, j-1); num++;
    }
    else
    {
        Adjacents[num].setPosition(i, j-1); num++;
        Adjacents[num].setPosition(i, j+1); num++;
    }

    if(i==0 && j==0)
    {
        Adjacents[num].setPosition(i+1, j+1); num++;
    }
    else if(i==ROW-1 && j==0)
    {
        Adjacents[num].setPosition(i-1, j+1); num++;
    }
    else if(i==0 && j== COL-1)
    {
        Adjacents[num].setPosition(i+1, j-1); num++;
    }
    else
    {
        Adjacents[num].setPosition(i-1, j-1); num++;
        Adjacents[num].setPosition(i-1, j+1); num++;
        Adjacents[num].setPosition(i+1, j-1); num++;
        Adjacents[num].setPosition(i+1, j+1); num++;
    }
    return Adjacents;
}

int Score(Board TempBoard, Player player)
{
    int score = 0;
    int myOrb = 0;
    int enemyOrb = 0;
    bool vulnerable = false;
    char playerColor = player.get_color();
    char enemyColor;
    if(playerColor == 'r')
    {
        enemyColor = 'b';
    }
    else
    {
        enemyColor = 'r';
    }
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(TempBoard.get_cell_color(i,j) == playerColor)
            {
                myOrb += TempBoard.get_orbs_num(i, j);
                Grid *Adjacents = SearchAdjacent(i, j);
                for(int k=0; k<8; k++)
                {
                    if(Adjacents[k].x == -1 && Adjacents[k].y == -1)
                    {
                        break;
                    }
                    else
                    {
                        if(TempBoard.get_cell_color(Adjacents[k].x, Adjacents[k].y) == enemyColor && TempBoard.get_orbs_num(Adjacents[k].x, Adjacents[k].y) == TempBoard.get_capacity(Adjacents[k].x, Adjacents[k].y)-1)
                        {
                            if(TempBoard.get_orbs_num(i,j) < TempBoard.get_capacity(i,j)-1)
                            {
                                score -= (9 - TempBoard.get_capacity(Adjacents[k].x, Adjacents[k].y));
                                vulnerable = true;
                            }
                        }
                    }
                }
                if(!vulnerable)
                {
                    if(TempBoard.get_capacity(i,j) == 3)
                    {
                        score += 5;
                    }
                    else if(TempBoard.get_capacity(i, j) == 5)
                    {
                        score += 4;
                    }

                    if(TempBoard.get_orbs_num(i,j) == TempBoard.get_capacity(i, j)-1)
                    {
                        score += 4;
                    }

                }
            }
            else
            {
                enemyOrb += TempBoard.get_orbs_num(i, j);
            }
        }
    }
    score += myOrb;
    return score;
}

void algorithm_A(Board board, Player player, int index[]){
    //////your algorithm design///////////

    TempBoard = board;
}
