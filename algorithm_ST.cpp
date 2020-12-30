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
    else if(i==ROW-1 && COL-1)
    {
        Adjacents[num].setPosition(i-1, j-1); num++;
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

Board move(Board TempBoard, Grid position, Player player)
{
    char playerColor = player.get_color();
    TempBoard.place_orb(position.x, position.y, &player);

    return TempBoard;
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

int **bestn(Board TempBoard, Player player)
{
    int **conf = new int* [ROW];
    for(int i = 0; i < ROW; i++)
    {
        conf[i] = new int[COL];
    }
    for (int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            conf[i][j] = -10000;
        }
    }

    char playerColor = player.get_color();

    for(int i = 0; i < ROW; i++)
    {
        for(int j = 0; j < COL; j++)
        {
            if(TempBoard.get_cell_color(i, j) == playerColor || TempBoard.get_cell_color(i, j) == 'w')
            {
                Grid position;
                position.setPosition(i, j);
                conf[i][j] = Score(move(TempBoard, position, player), player);
            }
        }
    }
    return conf;
}

std::pair<Grid, int> minimax(Board TempBoard, int depth, int breadth, Player player)
{
    int **best_move = bestn(TempBoard, player);
    Grid best_position[breadth];
    int best_value[breadth];
    Grid best_nextPosition;
    int best_nextValue;
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

    for(int i=0; i<breadth; i++)
    {
        best_value[i] = -10000;
    }

    for (int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            if(TempBoard.get_cell_color(i,j) == enemyColor) continue;
            for (int k=0; k< breadth; k++)
            {
                if(best_move[i][j] > best_value[k])
                {
                    for(int l=breadth-1; l >= k+1; l--)
                    {
                        best_value[l] = best_value[l-1];
                        best_position[l].setPosition(best_position[l-1].x, best_position[l-1].y);
                    }
                    best_value[k] = best_move[i][j];
                    best_position[k].setPosition(i, j);
                    break;
                }
            }
        }
    }

    for(int i=0; i<ROW; i++)
    {
        delete[]best_move[i];
    }
    delete[]best_move;

    best_nextPosition = best_position[0];
    best_nextValue = Score(move(TempBoard, best_nextPosition, player), player);

    if(depth==1)
    {
        return std::make_pair(best_nextPosition, best_nextValue);
    }

    for (int i=0; i<breadth; i++)
    {
        Board newBoard(move(TempBoard, best_position[i], player));
        pair <Grid, int> best_move = minimax(newBoard, depth-1, breadth, player);
        int value = best_move.second;
        if(value > best_nextValue)
        {
            best_nextValue = value;
            best_nextPosition = best_position[i];
        }
    }
    return std::make_pair(best_nextPosition, best_nextValue);
}

void algorithm_A(Board board, Player player, int index[]){
    //////your algorithm design///////////
    TempBoard = board;
    pair <Grid, int> result = minimax(TempBoard, 2, 12, player);
    index[0] = result.first.x;
    index[1] = result.first.y;
}
