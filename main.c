#include <stdio.h>
#include <string.h>
#include <math.h>

// Monetary values will be stored in long ints as 1/1,000ths of a cent 
// for the sake of resolution when calculating exponents,
// so 1 dollar as an integer is 100,000.
static const long CENTS    = 1000;
static const long DOLLARS  = 100000;

/*  
Modes:
1. A to c, tabulated
2. c to A, tabulated
3. A to c, not tabulated
4. c to A, not tabulated
*/
typedef enum
{
    MODE_cT = 1, MODE_AT, MODE_c, MODE_A
} MODE;

/*
This struct array is auxillary to the MODE enum. Since enums are only 
recognized when they are source code, using scanf() will not see an 
enum as a string. This allows an enum string to be associated with
and enum value outside of source code. 
*/
typedef struct MODE_
{
    int val;
    char mode[8];
} MODE_;
static const MODE_ Mode[] =
{
    {MODE_cT, "MODE_cT"},
    {MODE_AT, "MODE_AT"},
    {MODE_c, "MODE_c"},
    {MODE_A, "MODE_A"}
};

// ICIF stands for Inflating Contributions Investment Formula.
typedef struct
{
    int     mode;   // which mode the program will be calculating
    long    A;      // total amount of money
    long    P;      // principle amount in dollars
    long    c;      // first contribution amount
    double  r;      // return rate (1.00 = no change)
    double  i;      // inflation rate (1.00 = no change)
    int     t;      // amount of time in market in years 
    int     n;      // number of times a year to contribute to fund 
} icif;


// This function loads all command line arguments into their respective struct members,
// regardless of their order in the command line. 
void getArgs(int argc, char *argv[], icif *x)
{
    if (argc == 1)
        return;

    for (int i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == 'm')
            sscanf(strchr(argv[i],'=')+1, "%d", &(x->mode));    // store arg value into struct variable
        else if (*argv[i] == 'A' && (x->mode == MODE_cT || x->mode == MODE_c))
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->A));
        else if (*argv[i] == 'P')
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->P));
        else if (*argv[i] == 'c' && (x->mode == MODE_AT || x->mode == MODE_A))
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->c));
        else if (*argv[i] == 'r')
            sscanf(strchr(argv[i],'=')+1, "%lf", &(x->r));
        else if (*argv[i] == 'i')
            sscanf(strchr(argv[i],'=')+1, "%lf", &(x->i));
        else if (*argv[i] == 't')
            sscanf(strchr(argv[i],'=')+1, "%d", &(x->t));
        else if (*argv[i] == 'n')
            sscanf(strchr(argv[i],'=')+1, "%d", &(x->n)); 
	}
}

// A function that matches the struct MODE_ value to the enum mode
int matchMODE(char mode[])
{
    int enumSize = sizeof(Mode) / sizeof(MODE_);
    for (int i = 0; i < enumSize; i++)
    {
        if (!strcmp(mode, Mode[i].mode));
            return Mode[i].val;
    }

    return 0;
}

/*
A function that asks for icif function variables from the console for any 
variables that has a value of 0 (except P).

0 is assumed to indicate that the user still hasn't made a choice on 
which value to give.

This function should be used after getArgs() to get the rest of the 
necessary values not given as args.
*/
void askVars(icif *x)
{
    while (!x->mode)
    {
        printf("Please enter the mode of calculation.\n");
        printf("It can either be MODE_cT, MODE_AT, MODE_c, MODE_A.\n");
        char tempMode[8] = {};
        scanf("%s", tempMode);
        x->mode = matchMODE(tempMode);
    }
    if (x->mode == MODE_cT || x->mode == MODE_c)
    {
        while (!x->A)
        {
            printf("Please enter the target investment amount in dollars (without the $ sign or commas).\n");
            int tempA = 0;
            scanf("%d", &tempA);
            x->A = (long)tempA*DOLLARS;
        }
    }
    // P will be skipped since 0 is a valid value
    if (x->mode == MODE_AT || x->mode == MODE_A)
    {
        while (!x->c)
        {
            printf("Please enter the inital contribution amount in dollars (without the $ sign or commas).\n");
            int tempc = 0;
            scanf("%d", &tempc);
            x->c = (long)tempc*DOLLARS;
        }
    }
    while (!x->r)
    {
        printf("Please enter the rate at which your investments will increase as a percentage (without the %% sign).\n");
        printf("0.0 means 0%% change, <0.0 means decreasing, and >0.0 means increasing.\n");
        double tempr = 0.0;
        scanf("%lf", &tempr);
        x->r = 1 + (tempr/100);
    }
    while (!x->i)
    {
        printf("Please enter the rate of inflation as a percentage (without the %% sign).\n");
        printf("0.0 means 0%% change, <0.0 means decreasing, and >0.0 means increasing.\n");
        double tempi = 0.0;
        scanf("%lf", &tempi);
        x->i = 1 + (tempi/100);
    }
    while (!x->t)
    {
        printf("Please enter the number of years you will be investing.\n");
        scanf("%d", &(x->t));
    }
    while (!x->n)
    {
        printf("Please enter the number of times a year you will contribute to the fund.\n");
        scanf("%d", &(x->n));
    }
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

    // Doing the last part of the equation depending on which value is needed
    switch (x->mode)
    {
        case 1: x->c = (long)(x->A / coeff);    break;
        case 2: x->A = (long)(x->c * coeff);    break;
        case 3: x->c = (long)(x->A / coeff);    break;
        case 4: x->A = (long)(x->c * coeff);    break;
        default: printf("error: unknown mode of calculation.\n");
    }

    // TODO: print the results into text file after the final format has been decided
}

/*
This function does a single incremental step to inflate the given contribution amount
*/
void ICstep(icif *x)
{

}

int main(int argc, char *argv[])
{

    // A temporary variable will be made with test numbers until future implementations
    //icif x = {.A = 8000000*DOLLARS, .P = 0, .r = 1.08, .i = 1.03, .t = 40, .n = 24, .mode = 1};
    icif x = {.mode = 0, .A = 0*DOLLARS, .P = 0, .r = 0, .i = 0, .t = 0, .n = 0};

    getArgs(argc, argv, &x);
    askVars(&x);


    // Loading args into variables

    // If there are missing variables, ask them from console.
    // If A is given but not c, assume MODE_C. If c and not A, assume MODE_A
        // If both, ask which MODE if not given yet
        // If neither, ask for one or the other, then assume which MODE.

    Icif(&x);
    printf("$%.2lf\n", (double)x.c/DOLLARS);


    return 0;
}