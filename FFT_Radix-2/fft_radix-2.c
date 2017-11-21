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

/*
static unsigned char lookup[16] = {
0x0, 0x8, 0x4, 0xc, 0x2, 0xa, 0x6, 0xe,
0x1, 0x9, 0x5, 0xd, 0x3, 0xb, 0x7, 0xf};
*/

static uint8_t lookup[3][8] = { {0x0, 0x4, 0x2, 0x6, 0x1, 0x5, 0x3, 0x7}, {0x0, 0x2, 0x4, 0x6, 0x1, 0x3, 0x5, 0x7}, {0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7} };

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
  }

  fclose(numbers);
}

void print_arrays (void)
{
	for(int n = 0; n < N; n++ )
  {
    printf( "x[%d] = %.3f + %.3fi\t\t", n, creal(input[n]), cimag(input[n]) );
    printf( "X[%d] = %.3f + %.3fi\n", n, creal(output[n]), cimag(output[n]) );
  }
}

uint8_t stage_reversal(uint8_t index, int stage)
{

  return 0;
}

void twiddle_factor(int r)
{

}

void butterfly(int n1, int n2, int stage)
{
  printf("Stage: %d, x[%d] and x[%d]\n", stage, n1, n2 );
}

void fft(void)
{
  // access two array entries in bit reverse order and compute butterfly

  // first do butterfly(n,n+N/2)
  int divide = N;
  int max_stage = 0;
  while ( (divide/=2) != 0 )
  {
    max_stage++;
    printf("%d and %d\n", divide, max_stage);
  }

  int fft_stage = 0;

  for (; fft_stage < max_stage; fft_stage++ ) // do log2(N) times
  {
    for (int n = 0; n < N; n+=2) //
    {
      butterfly( lookup[fft_stage][n], lookup[fft_stage][n+1], fft_stage );
    }

  }
    //last stage : butterfly(n, n + N/N)



  //
}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_array(argv[1]);
  print_arrays();

  fft();

  return 0;
}
