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

void algorithm_A(Board board, Player player, int index[]){
    //////your algorithm design///////////

    TempBoard = board;
}
