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

typedef unsigned char uint8_t;

double complex input[N];
double complex output[N];

//bool first_bf = 1;
/*
static unsigned char lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf};
*/

static uint8_t lookup[3][8] = { {0x0, 0x4, 0x2, 0x6, 0x1, 0x5, 0x3, 0x7}, {0x0, 0x2, 0x4, 0x6, 0x1, 0x3, 0x5, 0x7}, {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7} };

static uint8_t lookup2[2][4] = { {0x0, 0x2, 0x1, 0x3}, {0x0, 0x1, 0x2, 0x3} };

void read_array (const char* file_name)
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
      output[i] = real + img * I;
  }
  fclose(numbers);
}

void print_arrays (void)
{
  printf("\n");
	for(int n = 0; n < N; n++ )
  {
    printf( "x[%d] = %.3f + %.3fi\t\t", n, creal(input[n]), cimag(input[n]) );
    printf( "X[%d] = %.3f + %.3fi\n", n, creal(output[n]), cimag(output[n]) );
  }
}

void fft(void)
{

}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_array(argv[1]);

  fft();

  print_arrays();

  return 0;
}
