// MPI Demo
//    mpicc mpiDemo.c
//    time mpirun -np 4                                  a.out
//    time mpirun -np 4 --mca orte_base_help_aggregate 0 a.out
//    time mpirun -np 4 -mca btl ^openib                 a.out
//    
//    time mpirun -np 6 -machinefile hosts.txt a.out
// 
// Manager-Worker model for parallel processing.
// 
// 2 4   0.6283180000000000
// 3 4   0.9424770000000000
// 1 4   0.3141590000000000
// 
// real    0m19.140s
// user    1m3.061s
// sys     0m13.251s

#include <stdlib.h>
#include <stdio.h>
// 
#include <mpi.h>
#include <time.h>
#include <unistd.h>

// 

// to run use the following: time mpirun a.out

#define row 180
#define col 240

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

int burnMyFire(char forest[row][col], double p_value)
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
                return (int)totalBurns;
        }
}



int main( int argc , char* argv[] )
{
   //
   // MPI variables
   //

   int        size    ;
   MPI_Status status  ;
   int        tag = 0 ;
   int	rank;
	int j;
	int k;
	double nbt;
	int prob;
   //
   // other variables
   //
    char forest[row][col];


    srand(time(NULL));
    printf("%f\n", (double)rand()/(double)RAND_MAX);
    
    clock_t begin = clock();
        


   MPI_Init(      &argc          , &argv ) ;
   MPI_Comm_size( MPI_COMM_WORLD , &size ) ; // same
   MPI_Comm_rank( MPI_COMM_WORLD , &rank ) ; // different
   double tmp = -1;
 

   if( rank == 0 )
   {
    for(double p_value = 0.0; p_value < 1.01; p_value+=0.01)
    {
      for( j = 1 ; j < size ; j++ )
      {
         MPI_Send( &p_value , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
      }
    }
    
    for( j = 1 ; j < size ; j++ )
    {
        MPI_Send( &tmp , 1 , MPI_DOUBLE , j , tag , MPI_COMM_WORLD ) ;
    }
    

      for( k = 1 ; k < size ; k++ )
      {
         MPI_Recv( &nbt , 1 , MPI_DOUBLE , MPI_ANY_SOURCE , tag , MPI_COMM_WORLD , &status ) ;
 
         j = status.MPI_SOURCE ;
  
   
      }
   }
   else
   {
      double p_value;
      while(1)
      {
        int sum = 0;
        MPI_Recv( &p_value , 1 , MPI_DOUBLE , 0 , tag , MPI_COMM_WORLD , &status ) ;
        if(p_value == -1)
            break;
        for(int x = 0; x < 100/ (size-1); x++)  //100 / divided by number of cores-1 because 1 is the manager
            sum+=burnMyFire(forest, p_value) ;
        MPI_Send( &sum , 1 , MPI_INTEGER , 0 , tag , MPI_COMM_WORLD ) ;
      }
 
  
   
   }
   MPI_Finalize() ;
    printf("\ndone");
   return 0;
}

//mpicc mpiDemo.c
//time mpirun -machinefile hostlist.txt a.out
