#include "determinant.h"


#define BUFFFER 10
int main(int argc, char const *argv[]) {
	FILE * fp;
	if(argc == 2)
	{
		if((fp=fopen(*(argv+1),"r"))==NULL)
		{
			printf("\nError in opening the file!\n");
			return(-1);
		}
		else
		{
			int matrix_size;	
			printf("Hello, I am determinant programm, which use La'Place recursive formula.");
		



		}
	}
	else
	{
	int matrix_size;
	

	printf("Hello, I am determinant programm, which use La'Place recursive formula."); 
	printf("Please insert number of rows and columns (only rectangular matrix ;( )between 1 - 7 \n");
	
	if(scanf("%d",&matrix_size) && is_number_valid(matrix_size)) {

		double** matrix = allocate_matrix(matrix_size);

		fill_array(matrix,matrix_size);
		show_array(matrix,matrix_size);

		if(matrix_size<2)
		{
			printf("It is not necessary to calculate determinant\n");
		}
		else
		{
			double det =calculate_determinant(matrix,matrix_size);
			printf("Determinant is equal = %lf",det);
		}


	}
	else 
		printf("Bad value. It should be integer between 1 -7 \n");
	
	return 0;	
}
}