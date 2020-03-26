#include <stdio.h>
#include <math.h> //include -lm flag to rung

int main(void)
{
	int array[] = {3, 1 ,4, 1, 5, 9, 2, 6};
	int matrix[4][8];
	for(int x = 0; x < 8; x++)
	{
		matrix[0][x] = array[x];
		printf("%d ", array[x]);
	}
	printf("\n");
	for(int x = 1; x < 4; x++)
	{
		for(int y = 0; y < 8/pow(2, x); y ++)
		{
			matrix[x][y] = matrix[x-1][y*2] + matrix[x-1][(y*2)+1];
			printf("%d ", matrix[x][y]);
		}
		printf("\n");
	}
	return 0;
}

