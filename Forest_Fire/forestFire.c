#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define row 30
#define col 40

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

	for (int r = 0; r < row; ++r)
	{
		for (int c = 0; c < col; ++c)
		{
			if ((double)rand() / (double)RAND_MAX > 0.3)
				forest[r][c] = 'T';
			else
				forest[r][c] = ' ';
		}
	}
	displayMatrix(forest);
	for (int r = 0; r < row; r++)
	{
		if (forest[r][0] == 'T')
			forest[r][0] = '*';
	}

	displayMatrix(forest);
        while(isItBurning(forest) < 0)
        {
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
                
		displayMatrix(forest);
                sleep(1);
        }
	displayMatrix(forest);
}
