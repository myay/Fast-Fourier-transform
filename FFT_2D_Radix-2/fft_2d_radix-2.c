#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include <stdbool.h>
#include <sys/time.h>

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

void complex_swap_rows( uint8_t x, uint8_t i, uint8_t j )
{
  double complex z_temp = input[x][i];
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
        complex_swap_rows(x, i, j);
      }
    }
  }
}

void complex_swap_collumns( uint8_t y, uint8_t i, uint8_t j )
{
  double complex z_temp = input[i][y];
  input[i][y] = input[j][y];
  input[j][y] = z_temp;
}

void bit_reverse_collumns(void)
{
  //swap in place, for every collumn
  uint8_t y, i, j;
  for ( y = 0; y < Y; y++ )
  {
    for ( i = 0; i < X; i++ )
    {
      j = BitReverseTable[i];
      if (i < j)
      {
        complex_swap_collumns(y, i, j);
      }
    }
  }
}

void fft_rows(int log_x, bool inverse)
{
  double complex twiddle_base, twiddle_factor;
  double complex top, bottom;
  int m;
  int stage;
  int x;

  for ( x = 0; x < X; x++ )
  {
    for ( stage = 1; stage <= log_x; stage++ ) // log2(N) times
    {
      m = pow( 2, stage );
      double cos_arg = (2*M_PI)/m ;
      double sin_arg = (-1)*cos_arg;
      if(inverse)
      {
        sin_arg *= (-1);
      }
      twiddle_base = cos( cos_arg ) + sin( sin_arg ) * I;

      for ( int k = 0; k < Y; k += m )
      {
        twiddle_factor = 1;

        for ( int j = 0; j < (m/2); j++ )
        {
          top = input[x][ k + j ];
          bottom = twiddle_factor * input[x][ k + j + m/2 ];

          input[x][ k + j ] = (top + bottom);
          input[x][ k + j + m/2 ] = (top - bottom);

          twiddle_factor *= twiddle_base;
        }
      }
    }
  }
}

void fft_collumns(int log_y, bool inverse)
{
  double complex twiddle_base, twiddle_factor;
  double complex top, bottom;
  int m;
  int stage;
  int y;

  for ( y = 0; y < Y; y++ )
  {
    for ( stage = 1; stage <= log_y; stage++ ) // log2(N) times
    {
      m = pow( 2, stage );
      double cos_arg = (2*M_PI)/m ;
      double sin_arg = (-1)*cos_arg;
      if(inverse)
      {
        sin_arg *= (-1);
      }
      twiddle_base = cos( cos_arg ) + sin( sin_arg ) * I;
      for ( int k = 0; k < X; k += m )
      {
        twiddle_factor = 1;

        for ( int j = 0; j < (m/2); j++ )
        {
          top = input[ k + j ][y];
          bottom = twiddle_factor * input[ k + j + m/2 ][y];

          input[ k + j ][y] = (top + bottom);
          input[ k + j + m/2 ][y] = (top - bottom);

          twiddle_factor *= twiddle_base;

          if(inverse && (stage == log_y))
          {
            input[k + j][y] /= (X*Y);
            input[k + j + m/2][y] /= (X*Y);
          }
        }
      }
    }
  }
}

void fft_2d(bool inverse)
{
  bit_reverse_rows();

  int divide;
  int log_dim;

  divide = X;
  log_dim = 0;
  while ( (divide/=2) != 0 )
  {
    log_dim++;
  }
  printf("Log2(X) = %d\n", log_dim);

  fft_rows(log_dim, inverse);

  bit_reverse_collumns();

  divide = Y;
  log_dim = 0;
  while ( (divide/=2) != 0 )
  {
    log_dim++;
  }
  printf("Log2(Y) = %d\n", log_dim);

  fft_collumns(log_dim, inverse);

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

  /* forward transform */
  fft_2d(0);
  printf("\nInput transformed:\n");
  print_array(input);

  /* inverse transform */
  fft_2d(1);
  printf("\nInverse:\n");
  print_array(input);

  return 0;
}
