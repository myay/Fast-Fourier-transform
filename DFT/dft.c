#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define N 8

#ifndef M_PI
#define M_PI 3.1416
#endif

double input[N];
double complex output[N];

void read_ints (const char* file_name)
{
  FILE *numbers;
  numbers = fopen(file_name, "r");
  int i;

  if (numbers == NULL){
      printf("Error reading file, try ./dft /path/to/file\n");
      exit (0);
  }

  for (i = 0; i < N; i++){
      fscanf(numbers, "%lf,", &input[i]);
  }

  fclose(numbers);
}

void dft (double *in, double complex *out)
{
  double *in_ptr = in;
  double complex *out_ptr = out;

  for (int k = 0; k < N; k++)
  {
    for (int n = 0; n < N; n++)
    {
      *out_ptr += (*in_ptr) * (cos((2*M_PI*k*n) / N) + sin((-1)*(2*M_PI*k*n) / N)*I);
      in_ptr++;
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

  read_ints(argv[1]);

  //double complex z1 = 1.0 + 1.0 * I;

  dft(input, output);

  printf("Input on the left, output DFT on the right:\n\n");
  for (int i = 0; i < N; i++)
  {
      printf("x[%d] = %.3f \t X[%d] = %.3f + %.3fi \n",
              i, input[i], i, creal(output[i]), cimag(output[i]));
  }

  return 0;
}
