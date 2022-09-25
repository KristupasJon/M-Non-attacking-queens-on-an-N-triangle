#ifndef M_NON-ATTACKING_QUEENS_ON_AN_N_TRIANGLE_H_INCLUDED
#define M_NON-ATTACKING_QUEENS_ON_AN_N_TRIANGLE_H_INCLUDED

void drawBoard(int n, int board[][n]);
int inputQueenToBoard(int n, int board[][n], int x, int y, int queens, int queenX[], int queenY[]);
void bruteForceNonattackingQueensInTriangleBoard(int n, int total_queens, int posX[], int posY[], int *positions);
void fillSingleCollumnLeft(int n, int board[][n], double first_col1, int queen_count);
void fillSingleCollumnRight(int n, int board[][n], double first_col2, int queen_count);
void fillCollumn(int n, int board[][n], double first_col1, double first_col2, int queen_count);
void findQueenPositions(int n, int board[][n], int posX[], int posY[], int *counter, int *start, int queen_count);
void smartNonattackingQueensInTriangleBoard(int n, int queen_count, int posX[], int posY[], int *positions);
void printAnswersNonAttackingQueensUniversal(int start_index, int queen_count, int positions,  int posX[], int posY[]);

#endif // M_NON-ATTACKING_QUEENS_ON_AN_N_TRIANGLE_H_INCLUDED
