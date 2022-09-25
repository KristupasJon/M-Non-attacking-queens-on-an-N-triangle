#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "M Non-attacking queens on an N triangle.h"

void drawBoard(int n, int board[][n])
{
    for(int i = 0; i < n; ++i)
    {
        for(int h = 0; h < n - i; ++h)
        {
            printf(" ");
        }
        for(int j = 0; j <= i; ++j)
        {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

int inputQueenToBoard(int n, int board[][n], int x, int y, int queens, int queenX[], int queenY[])
{

    if(board[x][y] == 1 || y > x || x > n)
    {
        return 0;
    }

    if(board[x][y] == 0)
    {
        board[x][y] = 1;
        queenX[queens] = x;
        queenY[queens] = y;

    }

    //diagonal 1
    for(int i = x; i < n; ++i)
    {
        board[i][y] = 1;
    }

    //diagonal 2
    for(int i = x; i >= 0; --i)
    {
        if(y <= i)
        {
            board[i][y] = 1;
        }
    }
    //line 3
    for(int i = 0; i <= x; ++i)
    {
        board[x][i] = 1;
    }

    //diagonal 4
    int add = 0;
    for(int i = x; i <= n; ++i)
    {
        board[i][y + add] = 1;
        add++;
    }

    //diagonal 5
    add = 0;
    for(int i = x; i >= 0; --i)
    {
        if(y - add >= 0)
        {
            board[i][y - add] = 1;
        }
        add++;
    }

    return 1;
}

void bruteForceNonattackingQueensInTriangleBoard(int n, int total_queens, int posX[], int posY[], int *positions)
{
    //there cannot be more than (2 * n + 1) / 3 possible queens in an n sized triangle board
    if(total_queens > floor((2 * n + 1) / 3))
    {
        return;
    }

    int board[n + 1][n + 1], queenX[n], queenY[n], queens = 0;
    int total_spots = (n * (n + 1)) / 2;


    memset(board, 0, sizeof(board));
    memset(queenX, 0, sizeof(queenX));
    memset(queenY, 0, sizeof(queenY));

    int start_x = 0, start_y = 0;
    int total_positions = 0, counter = -1;
    int moved_pos = 0;

    while(1)
    {

        moved_pos = start_y;

        int quit_flag = 0, restore_flag = 0;

        for(int i = start_x; i < n; ++i)
        {
            for(int j = moved_pos; j <= i; ++j)
            {
                if(queens == total_queens)
                {
                    quit_flag = 1;
                    break;
                }

                if(inputQueenToBoard(n, board, i, j, queens, queenX, queenY) == 1)
                {
                    queens++;
                    if(i == j)
                    {
                        moved_pos = 0;
                    }
                    else
                    {
                        moved_pos = j;
                    }

                    break;
                }
            }

            if(quit_flag == 1)
            {
                break;
            }
        }

        if(queens == total_queens)
        {
            total_positions += queens;

            for(int i = 0; i < queens; ++i)
            {
                counter++;
                posX[counter] = queenX[i];
                posY[counter] = queenY[i];

            }
            *positions = total_positions;
            return;
        }
        else
        {
            queens = 0;
            memset(board, 0, sizeof(board));
            memset(queenX, 0, sizeof(queenX));
            memset(queenY, 0, sizeof(queenY));

            if(start_y + 1 <= start_x)
            {
                start_y += 1;
            }
            else
            {
                start_x += 1;
                start_y = 0;
            }
        }

        if(start_x == n)
        {
            break;
        }
    }

}

void fillSingleCollumnLeft(int n, int board[][n], double first_col1, int queen_count)
{
    int down = 0, pass_flag = 0;

    //clearing board
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            board[i][j] = 0;
        }
    }

    for(int i = n - first_col1; i < n; ++i)
    {
        if(pass_flag == 0)
        {
            board[i][down] = 1;
            down++;
            pass_flag = 1;
        }
        else
        {
            pass_flag = 0;
        }

    }
}

void fillSingleCollumnRight(int n, int board[][n], double first_col2, int queen_count)
{
    //clearing board
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            board[i][j] = 0;
        }
    }

    int pass_flag = 0, down = first_col2 - n;

    for(int i = first_col2 - n; i < n; ++i)
    {
        if(pass_flag == 0)
        {
            board[i][down] = 1;
            down++;
            pass_flag = 1;
        }
        else
        {
            pass_flag = 0;
        }

    }
}

void fillCollumn(int n, int board[][n], double first_col1, double first_col2, int queen_count)
{
    int down = 0, pass_flag = 0;

    //clearing board
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            board[i][j] = 0;
        }
    }

    for(int i = n - first_col1; i < n; ++i)
    {
        if(pass_flag == 0)
        {
            board[i][down] = 1;
            down++;
            pass_flag = 1;
        }
        else
        {
            pass_flag = 0;
        }

    }

    pass_flag = 0, down = first_col2 - n;

    for(int i = first_col2 - n; i < n; ++i)
    {
        if(pass_flag == 0)
        {
            board[i][down] = 1;
            down++;
            pass_flag = 1;
        }
        else
        {
            pass_flag = 0;
        }
    }
}

void findQueenPositions(int n, int board[][n], int posX[], int posY[], int *counter, int *start, int queen_count)
{
    int count = *counter + 1;
    int start_count = *counter + 1;
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            if(board[i][j] == 1)
            {
                posX[count] = i;
                posY[count] = j;
                count++;
                *start += 1;
            }
        }
    }

    if(*start < queen_count)
    {
        return;
    }

    count--;

    //clearing board
    for(int i = 0; i < n; ++i)
    {
        for(int j = 0; j <= i; ++j)
        {
            board[i][j] = 0;
        }
    }

    int check_flag = 1;
    int queens = 0, queenX[n + 1], queenY[n + 1];

    for(int i = start_count; i <= count; ++i)
    {
        check_flag = inputQueenToBoard(n, board, posX[i], posY[i], queens, queenX, queenY);
        queens++;

        if(check_flag == 0)
        {
            *start = 0;
            return;
        }
    }

    if(queen_count <= *start)
    {
        *counter = count;
    }

}

void smartNonattackingQueensInTriangleBoard(int n, int queen_count, int posX[], int posY[], int *positions)
{
    //there cannot be more than (2 * n + 1) / 3 possible queens in an n sized triangle board

    if(queen_count > (int)floor((2 * n + 1) / 3))
    {
        return;
    }

    int board[n][n + 1], counter = 0, start = 0;

    double first_col1 = floor((2 * (double)n + 1) / 3);
    double first_col2 = ceil((4 * (double)n + 2) / 3);
    double second_col1 = ceil((2 * (double)n + 1) / 3);
    double second_col2 = floor((4 * (double)n + 2) / 3);

    fillCollumn(n, board, first_col1, first_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start >= queen_count)
    {
        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillCollumn(n, board, second_col1, second_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillCollumn(n, board, first_col1, second_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillCollumn(n, board, second_col1, first_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillSingleCollumnRight(n, board, first_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillSingleCollumnRight(n, board, second_col2, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillSingleCollumnLeft(n, board, first_col1, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }

        return;
    }
    start = 0;

    fillSingleCollumnLeft(n, board, second_col1, queen_count);
    findQueenPositions(n, board, posX, posY, &counter, &start, queen_count);
    if(counter > 0 && start == queen_count)
    {

        if(start > queen_count)
        {
            *positions = queen_count;
        }
        else
        {
            *positions += start;
        }
        return;
    }
    start = 0;

}

void printAnswersNonAttackingQueensUniversal(int start_index, int queen_count, int positions,  int posX[], int posY[])
{
    if(start_index == 1)
    {
        queen_count++;
    }

    for(int i = start_index; i < queen_count; ++i)
    {
        printf("(%d, %d) ", posX[i], posY[i]);
    }
    printf("\n");
}
