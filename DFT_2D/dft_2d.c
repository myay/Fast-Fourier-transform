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
  for (int x = 0; x < X; x++)
  {
    for (int y = 0; y < Y; y++)
    {
      printf( " %.3f+%.3fi\t\t", creal( toprint[x][y] ), cimag( toprint[x][y] ) );
    }
    printf("\n");
  }
  printf("\n");
}

void dft_2d (double complex in[][Y], double complex out[][Y], bool inverse)
{
  int u = 0, v = 0, x = 0, y = 0;
  double cos_arg, sin_arg;
  double complex outer_exp;

  for (; u < X ; u++)
  {
    for (; v < Y ; v++)
    {
      for (; x < X; x++)
      {
        for (; y < Y; y++)
          {
              cos_arg = ((2*M_PI*v*y) / Y);
              sin_arg = ((-1)*(2*M_PI*v*y) / Y);
              out[u][v] += (in[x][y]) * (cos( cos_arg ) + sin( sin_arg )*I);
          }
          cos_arg = ((2*M_PI*u*x) / X);
          sin_arg = ((-1)*(2*M_PI*u*x) / X);
          outer_exp = (cos( cos_arg ) + sin( sin_arg ) * I);
          out[u][v] *= outer_exp;
      }
    }
  }
  /*
  double complex *in_ptr = in;
  double complex *out_ptr = out;

  double sin_arg = 0.0;
  double cos_arg = 0.0;
  for (int k = 0; k < N; k++)
  {
    for (int n = 0; n < N; n++)
    {
      sin_arg = ((-1)*(2*M_PI*k*n) / N);
      cos_arg = ((2*M_PI*k*n) / N);

      if (inverse)
      {
        sin_arg *= (-1);
      }

      *out_ptr += (*in_ptr) * (cos( cos_arg ) + sin( sin_arg )*I);
      in_ptr++;
    }

    if (inverse)
    {
      (*out_ptr) /= (N+1);
    }

    in_ptr = in;
    out_ptr++;
  }
  */
}


int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);


  //dft(input, output, 0);

  dft_2d(input, output, 1);
  print_array(input);
  print_array(output);

  return 0;
}
