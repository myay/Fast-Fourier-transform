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
#define X 4 // number of rows
#define Y 4 // and collumns

#ifndef M_PI
#define M_PI 3.1416
#endif

typedef unsigned char uint8_t;

/* Lookup table to reverse incides from http://graphics.stanford.edu/~seander/bithacks.html#BitReverseObvious */

/*
static const unsigned char BitReverseTable[256] =
{
  #   define R2(n)     n,     n + 2*64,     n + 1*64,     n + 3*64
  #   define R4(n) R2(n), R2(n + 2*16), R2(n + 1*16), R2(n + 3*16)
  #   define R6(n) R4(n), R4(n + 2*4 ), R4(n + 1*4 ), R4(n + 3*4 )
    R6(0), R6(2), R6(1), R6(3)
};
*/
static const unsigned char BitReverseTable[4] = { 0x0, 0x2, 0x1, 0x3 };

double complex input[X][Y];
double complex z_temp; // for swapping complex numbers

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

void complex_swap( uint8_t x, uint8_t i, uint8_t j )
{
  z_temp = input[x][i];
  input[x][i] = input[x][j];
  input[x][j] = z_temp;
}

void bit_reverse_rows(void)
{
  //swap in place, for every row
  uint8_t x, i, j;
  for ( x = 0; x < X; x++ )
  {
    for ( i = 0; i < Y; i++ )
    {
      j = BitReverseTable[i];
      if (i < j)
      {
        complex_swap(x, i, j);
      }
    }
  }
}

void fft_2d()
{

}

int main (int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Specify a file with input numbers. Try: ./dft /path/to/file\n");
    return -1;
  }

  read_input(argv[1]);

  printf("\nInput:\n");
  print_array(input);

  bit_reverse_rows();

  printf("\nInput bit-reversed:\n");
  print_array(input);

  fft_2d();
  printf("\nInput transformed:\n");
  print_array(input);

  return 0;
}
