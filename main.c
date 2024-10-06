#include <stdio.h>
#include <string.h>
#include <math.h>

// Monetary values will be stored in long ints as 1/1,000ths of a cent 
// for the sake of resolution when calculating exponents,
// so 1 dollar as an integer is 100,000.
const long CENTS    = 1000;
const long DOLLARS  = 100000;

typedef enum
{
    MODE_C, MODE_A, MODE_FA, MODE_FC
} MODE;

typedef struct
{
    long    A;      // total amount of money
    long    P;      // principle amount in dollars
    long    c;      // first contribution amount
    double  r;      // return rate (1.00 = no change)
    double  i;      // inflation rate (1.00 = no change)
    int     t;      // amount of time in market in years 
    int     n;      // number of times a year to contribute to fund 
    MODE    mode;   // which mode the program will be calculating
} icif;

void Icif(icif *x);

int main(void)
{
    // A temporary variable will be made with test numbers until future implementations
    icif x = {.A = 8000000*DOLLARS, .P = 0, .r = 1.08, .i = 1.03, .t = 40, .n = 24, .mode = MODE_C};


    // Loading args into variables

    // If there are missing variables, ask them from console.
    // If A is given but not c, assume MODE_C. If c and not A, assume MODE_A
        // If both, ask which MODE if not given yet
        // If neither, ask for one or the other, then assume which MODE.

    Icif(&x);
    printf("$%.2lf\n", (float)x.c/DOLLARS);


    return 0;
}


// This function does the fast calculations for A or c depending on the mode, which will be displayed
void Icif(icif *x)
{
    // Preliminary calculation to make final equation more readable
    double ri = x->r - x->i;
    double rt = pow(x->r, (double)x->t);
    double it = pow(x->i, (double)x->t);
    double rn = pow(x->r, (double)x->n);
    double in = pow(x->i, (double)x->n);

    // The bulk (telescoping) part of the equation
    double coeff = (((rt - it)/ri) * ((rn - in)/ri));

    switch (x->mode)
    {
        case MODE_C:        x->c = (long)(x->A / coeff);    break;
        case MODE_A:        x->A = (long)(x->c * coeff);    break;
        case MODE_FAST:     x->A = (long)(x->c * coeff);    break;
        default: printf("error: unknown mode of calculation.\n");
    }

    // TODO: print the results into text file after the final format has been decided
}