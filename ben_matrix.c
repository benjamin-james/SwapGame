#include "ben_matrix.h"
#include "stdlib.h"
#include "stdio.h"

bool Matrix_swapRows(Matrix *m, int r1, int r2)
{
	if(r1 < m->rows && r1 >= 0 && r2 < m->rows && r2 >= 0 )
	{
	int i;
	int a = 0,b = 0;
	for(i = 0; i < m->columns; i++)
	{
		
		a = m->matrix[r1][i];
		b = m->matrix[r2][i];
		m->matrix[r2][i] = a;
		m->matrix[r1][i] = b;
	}
	return 1;
	}
	return 0;
}
bool Matrix_swapColumns(Matrix *m, int c1, int c2)
{
	if(c1 < m->columns && c1 >= 0 && c2 < m->columns && c2 >= 0 )
	{
	int i;
	int a = 0,b = 0;
	for(i = 0; i < m->rows; i++)
	{
		a = m->matrix[i][c1];
		b = m->matrix[i][c2];
		m->matrix[i][c2] = a;
		m->matrix[i][c1] = b;
	}
	return 1;
	}
	return 0;
}
Matrix *Matrix_scalarMultiply(int x, Matrix *m)
{
	int i,j;
	Matrix *result = Matrix_create(m->rows,m->columns);
	for(i = 0; i < m->rows; i++)
	{
		for(j = 0; j < m->columns; j++)
		{
			Matrix_place(x * Matrix_get(m,i,j),result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_removeRowColumn(Matrix *m, int r, int c)
{
	Matrix *result = Matrix_create(m->rows-1,m->columns-1);
	int i,j;
	for(i = 0; i < m->rows - (r >= m->rows); i++)
	{
		for(j = 0; j < m->columns - (c >= m->columns); j++)
		{
			Matrix_place(Matrix_get(m,i,j),result,i-(i>r),j-(j>c));
		}
	}
	return result;
}

Matrix *Matrix_getSubMatrix(Matrix *m,int r, int c, int rows, int columns)
{
	if(c + columns > m->columns || r + rows > m->rows) return NULL;
	Matrix *sub = Matrix_create(rows,columns);
	int i,j;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			Matrix_place(Matrix_get(m,r + i,c + j),sub,i,j);
		}
	}
	return sub;
}
Matrix *Matrix_copy(Matrix *m)
{
	Matrix *ret = Matrix_create(m->rows,m->columns);
	for(int i = 0; i < m->rows; i++)
	{
		for(int j = 0; j < m->columns; j++)
		{
			Matrix_place(Matrix_get(m,i,j),ret,i,j);
		}
	}
	return ret;
}
Matrix *Matrix_moveSubMatrix(Matrix *mat, int r1, int c1, int w, int h, int r2, int c2)
{
	Matrix *ref = Matrix_create(w,h);
	Matrix *ret = Matrix_copy(mat);
	int dr = r2-r1;
	int dc = c2-c1;
	int temp = 0;
	int i,j,f=0;
	//build reference matrix
	for(i = 0; i < mat->rows; i++)
	{
		for(j = 0; j < mat->columns; j++)
		{
			temp = 0;
			if(r1 <= i && i < r1+w && c1 <= j && j < c1+h)	//is in selected matrix
			{
				//what it is pointing to
				temp |= (((i+mat->rows+r2)%mat->rows) & 0xFF) << 8;
				temp |= ((j+mat->columns+c2)%mat->columns) & 0xFF;
			}
			if(r2 <= i && i < r2+w && c2 <= j && j < c2+h)
			{
				//where it came from
				temp |= (((i+mat->rows-r2+r1+r1)%mat->rows) & 0xFF) << 24;
				temp |= (((j+mat->columns-c2+c1+c1)%mat->columns) & 0xFF) << 16;
			}
			Matrix_place(temp,ref,i,j);
		}
	}
	for(i = 0; i < ref->rows; i++)
	{
		for(j = 0; j < ref->columns; j++)
		{
			f=0;
			temp = 0;
			f = Matrix_get(ref,i,j);
			if(f & 0xFFFF0000)	//this position is going to be replaced
			{
				int m = f & 0xFF000000;
				int n = f & 0xFF0000;
				while(f & 0xFFFF0000)//while this position is going to be replaced
				{
					f = Matrix_get(ref,m,n);	//see what it points to
					m = f & 0xFF000000;
					n = f & 0xFF0000;
				}//m and n are where they are on the big matrix
				
				//m and n are now in the same position as (i,j) on big matrix after swap
				Matrix_place(Matrix_get(mat,m,n),ret,i,j);//swap
			}
			else if(f)//pointing to something
			{
				//set position in final matrix
				Matrix_place(Matrix_get(mat,f & 0xFF00,f & 0xFF),ret,i,j);
			}
		}
	}
	for(i = 0; i < ref->rows; i++)
	{
		free(ref->matrix[i]);
	}
	free(ref->matrix);
	free(ref);
	return ret;
}
Matrix *Matrix_rule(int rows, int columns,int(*func)(int,int))
{
	Matrix *m = Matrix_create(rows,columns);
	int i,j;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			Matrix_place(func(i,j),m,i,j);
		}
	}
	return m;
}
Matrix *Matrix_input()
{
	int i,j,rows = -1,columns = -1;
	int in;
	do {
		printf("How many rows in the matrix?\n\t");
		scanf("%d",&rows);
	} while(rows <= 0);
	do {
		printf("How many columns in the matrix?\n\t");
		scanf("%d",&columns);
	} while(columns <= 0);
	Matrix *matrix = Matrix_create(rows,columns);
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			printf("Enter a value for row %d and column %d: ",i+1,j+1);
			scanf("%f",&in);
			Matrix_place(in,matrix,i,j);
		}
	}
	return matrix;
}
void Matrix_print(Matrix *m)
{
	int i,j;
	printf("\n");
	for(i = 0; i < m->rows; i++)
	{
		//printf("| \t");
		for(j = 0; j < m->columns; j++)
		{
			printf("%d\t",Matrix_get(m,i,j));
		}
		printf("\n");//"|\n"
	}
}
int Matrix_get(Matrix *m, int row, int column)
{
	return m->matrix[row][column];
}
int *Matrix_getColumn(Matrix *m,int column)
{
	if(column >= m->columns) return NULL;
	int *array = malloc(sizeof(int) * m->rows);
	int i;
	for(i = 0; i < m->rows; i++)
	{
		array[i] = Matrix_get(m,i,column);
	}
	return array;
}
int *Matrix_getRow(Matrix *m,int row)
{
	if(row >= m->rows) return NULL;
	int *array = malloc(sizeof(int) * m->columns);
	int i;
	for(i = 0; i < m->columns; i++)
	{
		array[i] = Matrix_get(m,row,i);
	}
	return array;
}
bool Matrix_replaceColumn(Matrix *m,int *array,int column)
{
	if(!array) return 0;
	if(column >= m->columns || sizeof(array)/sizeof(int) < m->rows) return 0;
	int i;
	for(i = 0; i < m->rows; i++)
	{
		Matrix_place(array[i],m,i,column);
	}
	return 1;
}
bool Matrix_replaceRow(Matrix *m,int *array,int row)
{
	if(!array) return 0;
	if(row >= m->rows || sizeof(array)/sizeof(int) < m->columns) return 0;
	int i;
	for(i = 0; i < m->columns; i++)
	{
		Matrix_place(array[i],m,row,i);
	}
	return 1;
}
Matrix *Matrix_rotateClockwise(Matrix *m)
{
	if(m->rows != m->columns) return NULL;
	int size = m->rows;
	Matrix *result = Matrix_create(size,size);
	int i,j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			
			Matrix_place(Matrix_get(m,size-1-j,i),result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_rotateCounterClockwise(Matrix *m)
{
	if(m->rows != m->columns) return NULL;
	int size = m->rows;
	Matrix *result = Matrix_create(size,size);
	int i,j;
	for(i = 0; i < size; i++)
	{
		for(j = 0; j < size; j++)
		{
			Matrix_place(Matrix_get(m,j,size-1-i),result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_create(int rows,int columns)
{
	Matrix *m = malloc(sizeof(Matrix));
	m->matrix = (int **)malloc(sizeof(int *) * rows);
	int i;
	for(i = 0; i < rows; i++)
	{
		m->matrix[i] = (int *)malloc(sizeof(int) * columns);
	}
	m->rows = rows;
	m->columns = columns;
	return m;
}
Matrix *Matrix_add(Matrix *m1,Matrix *m2)
{
	if(m1->rows != m2->rows || m1->columns != m2->columns) return NULL;
	Matrix *result = Matrix_create(m1->rows,m1->columns);
	int i,j;
	for(i = 0; i < m1->rows; i++)
	{
		for(j = 0; j < m1->columns; j++)
		{
			Matrix_place(m1->matrix[i][j]+m2->matrix[i][j],result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_subtract(Matrix *m1,Matrix *m2)
{
	if(m1->rows != m2->rows || m1->columns != m2->columns) return NULL;
	Matrix *result = Matrix_create(m1->rows,m1->columns);
	int i,j;
	for(i = 0; i < m1->rows; i++)
	{
		for(j = 0; j < m1->columns; j++)
		{
			Matrix_place(m1->matrix[i][j]-m2->matrix[i][j],result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_multiply(Matrix *m1,Matrix *m2)
{
	if(m1->columns != m2->rows) return NULL;
	Matrix *result = Matrix_create(m1->rows,m2->columns);
	int i,j,k;
	int sum;
	for(i = 0; i < m1->rows; i++)
	{
		for(j = 0; j < m2->columns; j++)
		{
			sum = 0.0;
			for(k = 0; k < m1->columns; k++)
			{
				sum += Matrix_get(m1,i,k) * Matrix_get(m2,k,j);
			}
			Matrix_place(sum,result,i,j);
		}
	}
	return result;
}
Matrix *Matrix_fill(int rows, int columns, int **array)
{
	Matrix *m = Matrix_create(rows,columns);
	int i,j;
	for(i = 0; i < rows; i++)
	{
		for(j = 0; j < columns; j++)
		{
			Matrix_place(array[i][j],m,i,j);
		}
	}
}
bool Matrix_place(int i, Matrix *m,int r,int c)
{
	if(r < m->rows && c < m->columns)
	{
		m->matrix[r][c] = i;
		return 1;
	}
	else
	{
		return 0;
	}
}
