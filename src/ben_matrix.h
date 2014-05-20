#ifndef BEN_MATRIX_H
#define BEN_MATRIX_H
#include "stdbool.h"
typedef struct
{
	int rows;
	int columns;
	int **matrix;
} Matrix;
Matrix *Matrix_moveSubMatrix(Matrix *mat, int r, int c, int w, int h, int x, int y);
Matrix *Matrix_scalarMultiply(int x, Matrix *m);
Matrix *Matrix_removeRowColumn(Matrix *m, int r, int c);
Matrix *Matrix_getSubMatrix(Matrix *m,int x, int y, int rows, int columns);
Matrix *Matrix_rule(int rows, int columns,int(*func)(int,int));
Matrix *Matrix_input();
Matrix *Matrix_copy(Matrix *m);
void Matrix_print(Matrix *m);
int Matrix_get(Matrix *m, int row, int column);
int *Matrix_getColumn(Matrix *m,int column);
int *Matrix_getRow(Matrix *m,int row);
bool Matrix_replaceColumn(Matrix *m,int *array,int column);
bool Matrix_replaceRow(Matrix *m,int *array,int row);
bool Matrix_swapRows(Matrix *m, int r1, int r2);
bool Matrix_swapColumns(Matrix *m, int c1, int c2);
Matrix *Matrix_rotateCounterClockwise(Matrix *m);
Matrix *Matrix_rotateClockwise(Matrix *m);
Matrix *Matrix_create(int rows,int columns);
Matrix *Matrix_add(Matrix *m1,Matrix *m2);
Matrix *Matrix_subtract(Matrix *m1,Matrix *m2);
Matrix *Matrix_multiply(Matrix *m1,Matrix *m2);
Matrix *Matrix_fill(int rows, int columns, int **array);
bool Matrix_place(int i, Matrix *m,int r,int c);
#endif
