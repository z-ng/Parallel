#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define row 300
#define col 400

void displayMatrix(char forest[row][col])
{
	printf("%c\n", '\n');
	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; c++)
		{
			printf("%c", forest[r][c]);
                        //printf("%c", ' ');
		}
		printf("%c\n", ' ');
	}
}

int isItBurning(char forest[row][col])
{
        for (int x = 0; x < row; x++)
        {
                for (int y = 0; y < col; y++)
                {
                    if(forest[x][y] == '*')
                    {
                        return -1;
                    }
                }
        }
        return 1;
}


int main()
{
	char forest[row][col];
	srand(time(NULL));
	printf("%f\n", (double)rand()/(double)RAND_MAX);
        
        clock_t begin = clock();
        
        for(double p_value = 0; p_value < 1.01; p_value+=0.01)
        {
            int numberOfBurns = 0;
            int totalBurns = 0;
            for(int iteration = 0; iteration < 100; iteration++)
            {
                for (int r = 0; r < row; ++r)
                {
                        for (int c = 0; c < col; ++c)
                        {
                                if ((double)rand() / (double)RAND_MAX < p_value)
                                        forest[r][c] = 'T';
                                else
                                        forest[r][c] = ' ';
                        }
                }
                
                for (int r = 0; r < row; r++)
                {
                        if (forest[r][0] == 'T')
                                forest[r][0] = '*';
                }

                numberOfBurns = 0;
                while(isItBurning(forest) < 0)
                {
                    numberOfBurns+=1;
                    for (int x = 0; x < row; x++) // the . = forset fire slowing down
                    {
                        for(int y = 0; y < col; y++)
                        {
                            if(forest[x][y] == '*')
                            {
                                forest[x][y] = '.';
                            }
                        }
                    }
                    
                    for (int x = 0; x < row; x++) // the * = new forest fire starting
                    {
                            for (int y = 0; y < col; y++)
                            {
                                if(forest[x][y] == 'T')
                                {
                                    if (x - 1 >= 0 && forest[x - 1][y] == '.')
                                            forest[x][y] = '*';
                                    if (x + 1 < row && forest[x + 1][y] == '.')
                                            forest[x][y] = '*';
                                    if (y - 1 >= 0 && forest[x][y - 1] == '.')
                                            forest[x][y] = '*';
                                    if (y + 1 < col && forest[x][y + 1] == '.')
                                            forest[x][y] = '*';
                                }
                            }
                    }
                    
                    for (int x = 0; x < row; x++) // the . = forset fire slowing down
                    {
                        for(int y = 0; y < col; y++)
                        {
                            if(forest[x][y] == '.')
                            {
                                forest[x][y] = ' ';
                            }
                        }
                    }
                }
                totalBurns+=numberOfBurns;
            }
            //printf("%f\t", p_value);
            printf("%f\n", (double)totalBurns/col/101);
            //printf("%f\n", (double)totalBurns);
            numberOfBurns = 0;
            
        }
            clock_t end = clock();
            double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
            printf("\n%f", time_spent);
}
