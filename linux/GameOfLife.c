// GameOfLife.c : Implementation of the Conway's Game of Life
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// At this point input is defined as a set of constants. It can change to be given by the user.
#define N 50
#define M 50
#define sc 100 // c stands for simulation circles
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

unsigned int RandInt(unsigned int min, unsigned int max)
{
	double scaled = (double)rand() / RAND_MAX;
	return (max - min + 1) * scaled + min;
}

void ClearScreen()
{
	system("@cls||clear");
}

void wait(int seconds)
{   // Pretty crossplatform, both ALL POSIX compliant systems AND Windows
#ifdef _WIN32
	Sleep(1000 * seconds);
#else
	sleep(seconds);
#endif
}


int main()
{
	// Dynamically allocated memory
	// If statically allocated memory is ok, then use grid[n][m]
	int *grid[N];
	for (int i = 0; i < M; ++i)
	{
		grid[i] = (int *)malloc(M * sizeof(int));
	}
	//int grid[n][m];

	srand(time(NULL));

	// initialize grid with random values. This also can change in the future
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; ++j)
		{
			grid[i][j] = RandInt(0, 1);
		}
	}

	int generation = 0;
	// run simulation
	for (;;)	// infinite simulation
	{
		//for (int k = 0; k < sc; k++)
		//{
		
		int *grid_aux[N];
		for (int i = 0; i < M; ++i)
		{
			grid_aux[i] = (int *)malloc(M * sizeof(int));
		}
		//int grid_aux[n][m];	// auxiliary grid. It is needed because the state of the cells for the next generation should change SIMULATANEOUSLY for all the cells

		// print the grid
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				if (grid[i][j] == 1)
				{
					printf(ANSI_COLOR_GREEN "*" ANSI_COLOR_RESET " ");
				}
				else
				{
					printf(ANSI_COLOR_RED "*" ANSI_COLOR_RESET " ");
				}
			}
			printf("\n");
		}
		printf("\n");
		printf("Generation: %d", generation);
		printf("\n");

		wait(1);

		// iterate through the grid
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				// iterate through each cell's neighbors
				unsigned int numOfAliveNeighbors = 0;
				for (int ii = (i - 1); ii <= (i + 1); ++ii)
				{
					for (int jj = (j - 1); jj <= (j + 1); ++jj)
					{
						// check bounds
						if (((ii >= 0) && (ii <= (N - 1))) && ((jj >= 0) && (jj <= (M - 1))))
						{
							if (!((ii == i) && (jj == j)) && (grid[ii][jj] == 1)) 
							{
								numOfAliveNeighbors++;
							}
						}
					}
				}
				if (numOfAliveNeighbors == 3)
				{
					grid_aux[i][j] = 1;
				}
				else if (numOfAliveNeighbors == 2)
				{
					grid_aux[i][j] = grid[i][j];
				}
				else
				{
					grid_aux[i][j] = 0;
				}
			}
		}

		// update grid
		for (int i = 0; i < N; ++i)
		{
			for (int j = 0; j < M; ++j)
			{
				grid[i][j] = grid_aux[i][j];
			}
		}

		// free memory
		for (int i = 0; i < N; ++i)
		{
			free(grid_aux[i]);
		}

		ClearScreen();
		generation++;
		//}
	}
	printf("\n");
    return 0;
}

