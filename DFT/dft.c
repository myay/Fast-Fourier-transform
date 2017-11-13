#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>

/* Choose N complex input values (type double) in input.txt.
 * For example with N = 8, the input in form of (real,imaginary) can be specified as
 * (0,0) (0.707,0) (1,0) (0.707,0) (0,0) (-0.707,0) (-1,0) (-0.707,0)
 * which is a discrete time sinus function between 0 and 2pi.
 */
#define N 8

#ifndef M_PI
#define M_PI 3.1416
#endif

double complex input[N];
double complex output[N];

void read_input (const char* file_name)
{
  FILE *numbers;
  numbers = fopen(file_name, "r");

  if (numbers == NULL){
      printf("Error reading file, try ./dft /path/to/file\n");
      exit (0);
  }

  double real = 0.0;
  double img = 0.0;

  for (int i = 0; i < N; i++)
  {
      fscanf(numbers, "(%lf,%lf) ", &real, &img);
      input[i] = real + img * I;
  }

  fclose(numbers);
}

void dft (double complex *in, double complex *out, bool inverse)
{
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
}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);

  //double complex z1 = 1.0 + 1.0 * I;

  dft(input, output, 0);

  printf("Input on the left, output DFT on the right:\n\n");
  for (int i = 0; i < N; i++)
  {
    printf( "x[%d] = %.3f + %.3fi\t\t", i, creal(input[i]), cimag(input[i]) );
    printf( "X[%d] = %.3f + %.3fi\n", i, creal(output[i]), cimag(output[i]) );
  }

  dft(output, input, 1);

  printf("\nInverse DFT:\n\n");

  for (int i = 0; i < N; i++)
  {
      printf( "X[%d] = %.3f + %.3fi\t\t", i, creal(output[i]), cimag(output[i]) );
      printf( "x[%d] = %.3f + %.3fi\n", i, creal(input[i]), cimag(input[i]) );
  }

  return 0;
}
