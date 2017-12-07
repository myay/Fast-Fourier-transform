#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

/* Choose X*Y  complex input values (type double) in input.txt.
 * For example with X = 4 and Y = 4, the input in form of (real,imaginary) can be specified as
 * (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1).
 */
#define X 4 // number of rows
#define Y 4 // and collumns

#ifndef M_PI
#define M_PI 3.1416
#endif

double complex input[X][Y];
double complex output[X][Y];

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

void print_array (double complex toprint[][Y])
{
  printf("\n");

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

void dft_2d (double complex in[][Y], double complex out[][Y], bool inverse)
{
  int u, v, x, y;
  double cos_arg, sin_arg;
  double complex inner_sum;
  double complex outer_exp;

  for (u = 0; u < X ; u++)
  {
    for (v = 0; v < Y ; v++)
    {
      for (x = 0; x < X; x++)
      {
        for (y = 0; y < Y; y++)
        {
          sin_arg = ((-1)*(2*M_PI*v*y) / Y);
	        cos_arg = sin_arg;

          if(inverse)
          {
            sin_arg *= (-1);
          }

          inner_sum += (in[x][y]) * (cos( cos_arg ) + sin( sin_arg ) * I);
        }

        sin_arg = ((-1)*(2*M_PI*u*x) / X);
	      cos_arg = sin_arg;

        if (inverse)
        {
          sin_arg *= (-1);
        }

        outer_exp = (cos( cos_arg ) + sin( sin_arg ) * I);
        out[u][v] += (inner_sum * outer_exp);
        inner_sum = 0;
      }

      if (inverse)
      {
        out[u][v] /= ((X)*(Y));
      }
    }
  }
}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);

  dft_2d(input, output, 0);
  print_array(input);
  print_array(output);

  printf("Inverse:\n");
  dft_2d(output, input, 1);
  print_array(output);
  print_array(input);

  return 0;
}
