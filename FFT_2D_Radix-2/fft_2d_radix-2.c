#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <float.h>

/* Choose X*Y  complex input values (type double) in input.txt.
 * For example with X = 4 and Y = 4, the input in form of (real,imaginary) can be specified as
 * (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1).
 */
#define X 2 // number of rows
#define Y 2 // and collumns

#ifndef M_PI
#define M_PI 3.1416
#endif

typedef unsigned char uint8_t;

double complex input[X][Y];
double complex output[X][Y];


static uint8_t lookup[8] = {0x0, 0x4, 0x2, 0x6, 0x1, 0x5, 0x3, 0x7};

//static uint8_t lookup2[2][4] = { {0x0, 0x2, 0x1, 0x3}, {0x0, 0x1, 0x2, 0x3} };

void read_input (const char* file_name)
{
  FILE *numbers;
  numbers = fopen(file_name, "r");

  if (numbers == NULL)
  {
    printf("Error reading file, try ./dft_2d /path/to/file\n");
    exit (0);
  }

  double real = 0.0, img = 0.0;

  for (int x = 0; x < X; x++)
  {
    for (int y = 0; y < Y; y++)
    {
      fscanf(numbers, "(%lf,%lf) ", &real, &img);
      input[x][y] = real + img * I;
    }
  }
  fclose(numbers);
}


void bit_reverse_row(int row)
{

}

void bit_reverse_collumn(int collumn)
{

}


void print_array (double complex toprint[][Y])
{
  for (int x = 0; x < X; x++)
  {
    for (int y = 0; y < Y; y++)
    {
      printf( " %.2f+%.2fi\t", creal( toprint[x][y] ), cimag( toprint[x][y] ) );
    }
    printf("\n");
  }
  printf("\n");
}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);

  print_array(input);

  return 0;
}
