#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

// At this point input is defined as a set of constants. 
// TODO: Change it to be given by the user.
#define N 40
#define M 40

// (ANSI) colors
#define ANSI_COLOR_BOLD_BLACK "\e[1;30m"
#define ANSI_COLOR_BOLD_WHITE "\e[1;37m"
#define ANSI_COLOR_RESET "\e[0m"

unsigned int randomInteger(unsigned int minOfRange, unsigned int maxOfRange)
{
  double scaled = (double)rand() / RAND_MAX;
  return (maxOfRange - minOfRange + 1) * scaled + minOfRange;
}

void clearScreen()
{
  system("@cls||clear");
}

void wait(int seconds)
{   
// Pretty cross-platform, both for POSIX-compliant systems and Windows
#ifdef _WIN32
  Sleep(1000 * seconds);
#else
  sleep(seconds);
#endif
}

int main()
{
  int *grid[N];
  for (int i = 0; i < M; ++i)
  {
    grid[i] = (int *)malloc(M * sizeof(int));
  }

  srand(time(NULL));
  
  // initialize grid with random values. This may change in the future
  for (int i = 0; i < N; i++)
  {
    for (int j = 0; j < M; j++)
    {
      grid[i][j] = randomInteger(0, 1);
    }
  }

  int generation = 0;

  // run simulation
  for (;;)    // infinite simulation
  {
    // auxiliary grid. It is needed because the state of the cells for the next generation should change SIMULATANEOUSLY for all the cells
    int *grid_aux[N];
    for (int i = 0; i < M; ++i)
    {
      grid_aux[i] = (int *)malloc(M * sizeof(int));
    }

    // print the grid
    for (int i = 0; i < N; ++i)
    {
      for (int j = 0; j < M; ++j)
      {
        if (grid[i][j] == 1)
        {
          printf(ANSI_COLOR_BOLD_WHITE "*" ANSI_COLOR_RESET " ");
        }
        else
        {
          printf(ANSI_COLOR_BOLD_BLACK "*" ANSI_COLOR_RESET " ");
        }
      }
      printf("\n");
    }
    printf("\n");
    printf("Generation: %d", generation);
    printf("\n");

    wait(1);  // sleep for 1 second

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
            // TODO: Apply logic for the cells in the boundaries of the grid
            if (((ii >= 0) && (ii <= (N - 1))) && ((jj >= 0) && (jj <= (M - 1))))
            {
              if ((ii != i) || (jj != j))
              {
                if ((grid[ii][jj] == 1)) 
                {
                  numOfAliveNeighbors++;
                }
              }
            }
          }
        }

        if (grid[i][j] == 1)  // live cell
        {
          if ((numOfAliveNeighbors == 2) || (numOfAliveNeighbors == 3))
          {
            grid_aux[i][j] = 1; // cell lives on to the next generation
          }
          else if (numOfAliveNeighbors < 2)
          {
            grid_aux[i][j] = 0; // cell dies, as if by underpopulation
          }
          else  // numOfAliveNeighbors > 3
          {
            grid_aux[i][j] = 0; // cell dies, as if by overpopulation
          }
        }
        else  // dead cell
        {
          if (numOfAliveNeighbors == 3)
          {
            grid_aux[i][j] = 1; // cell revives, as if by reproduction
          }
          else
          {
            grid_aux[i][j] = 0; // cell stays dead
          }
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

    clearScreen();
    generation++;
  }
  printf("\n");
  return 0;
}