// GameOfLife.c : Implementation of the Conway's Game of Life
// https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
//
#include "stdafx.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// At this point input is defined as a set of constants. It can change to be given by the user.
#define n 50
#define m 50
#define sc 100 // c stands for simulation circles

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
	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	srand(time(NULL));
	int grid[n][m];

	// initialize grid with random values. This also can change in the future
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			grid[i][j] = RandInt(0, 1);
	}

	// run simulation
	for (;;)	// infinite simulation
	{
		//for (int k = 0; k < sc; k++)
		//{
		int grid_aux[n][m];	// auxiliary grid. It is needed because the state of the cells for the next generation should change SIMULATANEOUSLY for all the cells

		// print the grid
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 1)
					SetConsoleTextAttribute(hConsole, 2);	// 2: color code for green
				else
					SetConsoleTextAttribute(hConsole, 12);	// 12: color code for red
				printf("%d ", grid[i][j]);
			}
			printf("\n");
		}

		wait(2);

		// iterate through the grid
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				// iterate through each cell's neighbors
				unsigned int numOfAliveNeighbors = 0;
				for (int ii = (i - 1); ii <= (i + 1); ii++)
				{
					for (int jj = (j - 1); jj <= (j + 1); jj++)
					{
						// check bounds
						if (((ii >= 0) && (ii <= (n - 1))) && ((jj >= 0) && (jj <= (m - 1))))
							if (!((ii == i) && (jj == j)) && (grid[ii][jj] == 1)) numOfAliveNeighbors++;
					}
				}
				if (numOfAliveNeighbors == 3) grid_aux[i][j] = 1;
				else if (numOfAliveNeighbors == 2) grid_aux[i][j] = grid[i][j];
				else grid_aux[i][j] = 0;
			}
		}

		// update grid
		for (int i = 0; i < n; i++)
			for (int j = 0; j < m; j++)
				grid[i][j] = grid_aux[i][j];

		ClearScreen();
		//}
	}
	printf("\n");
    return 0;
}

