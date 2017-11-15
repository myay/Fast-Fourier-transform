#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

/* Choose X*Y  complex input values (type double) in input.txt.
 * For example with X = 4 and Y = 4, the input in form of (real,imaginary) can be specified as
 * (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1) (1,0) (1,0) (1,0) (1,0) (1,-1).
 */
#define X 2 // number of rows
#define Y 2 // and collumns

#ifndef M_PI
#define M_PI 3.1416
#endif

double complex input[X][Y];
double complex output[X][Y];

void read_input (const char* file_name)
{
  FILE *numbers;
  numbers = fopen(file_name, "r");

  if (numbers == NULL){
      printf("Error reading file, try ./dft_2d /path/to/file\n");
      exit (0);
  }

  double real = 0.0;
  double img = 0.0;

  for (int i = 0; i < X; i++)
  {
    for (int j = 0; j < Y; j++)
    {
        fscanf(numbers, "(%lf,%lf) ", &real, &img);
        input[i][j] = real + img * I;
    }
  }

  fclose(numbers);
}

void print_array (double complex toprint[][Y])
{
  for (int i = 0; i < X; i++)
  {
    for (int j = 0; j < Y; j++)
    {
        printf( " %.3f+%.3fi\t\t", creal( toprint[i][j] ), cimag( toprint[i][j] ) );
    }
    printf("\n");
  }
  printf("\n");
}


void dft (double complex in[][Y], double complex out[][Y], bool inverse)
{




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
  print_array(input);
  print_array(output);

  //dft(input, output, 0);
  /*
  dft(output, input, 1);
  */
  return 0;
}
