#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>

#define N 16

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

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
  }

  read_ints(argv[1]);

  double complex z1 = 1.0 + 1.0 * I;
  double complex z2 = 1.0 - 2.0 * I;

  printf("Z1 = %.2f + %.2fi\tZ2 = %.2f %+.2fi\n", creal(z1), cimag(z1), creal(z2), cimag(z2));

  double complex output[N];
  output[0] = z1;
  printf("Output: %.2f + %.2fi\n", creal(output[0]), cimag(output[0]));

  printf("The Fourier transform is:\n\n");
  for (int i = 0; i < N; i++)
  {
      printf("x[%d] = %.2f \t X[%d] = %.2f + %.2fi \n",
              i, input[i], i, creal(output[0]), cimag(output[0]));
  }

  return 0;
}
