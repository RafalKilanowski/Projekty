#ifndef DETERMINANT_H
#define DETERMINANT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#define NUM_OF_ALLOCS 10000
int cnt = 0;

static int is_error =1;

void *my_alloc (unsigned int size)
{
	if (cnt < NUM_OF_ALLOCS)
	{
		cnt++;
		return malloc(size);
	}
	return NULL;
}

bool is_number_valid(int temp_number)
{
	if(temp_number >=1 && temp_number <=7)
		return true;
	else
		return false;
}

double** allocate_matrix(int matrix_size)
{
		int i =0;
		double** matrix = my_alloc(sizeof(double*)*(matrix_size));
		for(;i<matrix_size;i++)
		{
			matrix[i] = my_alloc(sizeof(double)*(matrix_size));
		}
		return matrix;
}

int fill_array(double **matrix, int matrix_size)
{
	int iterator1, iterator2;
	int scanf_result;

	for(iterator1=0;iterator1<matrix_size;iterator1++)
	{
		for(iterator2=0;iterator2<matrix_size;iterator2++)
		{

			while((!(scanf_result=scanf("%lf",&matrix[iterator1][iterator2])) || scanf_result ==EOF))
			{
				if(scanf_result ==EOF)
					return 0;
				while(getchar()!='\n')
					continue;
				printf("You have inserted inaproperiate value, try one more time\n");
			}
		}

	}
return 1;
}


void show_array(double **matrix, int matrix_size1)
{
	int iterator1,iterator2;

	for(iterator1=0;iterator1<matrix_size1;iterator1++)
	{
		for(iterator2=0;iterator2<matrix_size1;iterator2++)
		{
		printf("%lf ",matrix[iterator1][iterator2]);
		}
		printf("\n");
	}

}
void fre (double ** matrix,int matrix_size)
{	
	int i;
	for(i=0;i<matrix_size;i++)
	{
		free(matrix[i]);
	}
	free(matrix);
}

double calculate_determinant(double **matrix,int matrix_size)
{
	double determinant=0;
	int i,j,k;
	int mall_check=1;
	if(matrix_size == 2)
	{
		determinant=matrix[0][0]*matrix[1][1]-matrix[0][1]*matrix[1][0];
		return determinant;
	}
	else
	{
		
		
		double** temp_matrix = NULL;
		if((temp_matrix=my_alloc(sizeof(double*)*(matrix_size-1))) == NULL)
		{
			is_error=0;
			return 0;
		}

		for(i=0;i<matrix_size-1;i++)
		{
			
			if((temp_matrix[i]= my_alloc(sizeof(double)*(matrix_size-1))) != NULL)
			memset(*(&temp_matrix[i]),0,sizeof(double)*(matrix_size-1));
			else
			{
				is_error=0;
				mall_check=0;
				fre(temp_matrix,i);
				return 0;
			}
				
		}
		if(mall_check == 1)
		{
		for(i=0;i<matrix_size;i++) {

			for(j=1;j<matrix_size;j++) {

				int temp_minor_num =0;

				for(k=0;k<matrix_size;k++) {
					if(k!=i)
					{
						temp_matrix[j-1][temp_minor_num]=matrix[j][k];
						temp_minor_num++;
					}
				}
			}
			determinant=determinant+matrix[0][i]*pow((-1),(2+i))*calculate_determinant(temp_matrix,matrix_size-1);
		}
		
		fre(temp_matrix,matrix_size-1);
		return determinant;
		}
		else
		{
			for(i=0;i<mall_check;i++)
			{	
				free(temp_matrix[i]);
			}
			free(temp_matrix);
			return 0;
		}
		
	}
}

void print_result(double det)
{
	if(is_error == 1)
	printf("Determinant is equal = %lf\n",det);
	else
	printf("Error when allocating memory!\n");
}


#endif