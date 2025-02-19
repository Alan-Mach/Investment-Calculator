#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*
Monetary values will be stored in long ints as 1/1,000ths of a cent for 
the sake of resolution when calculating exponents, so 1 dollar as an 
integer is 100,000.
*/
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
static const int NUM_MODES = 4;

/*
This struct array is auxillary to the MODE enum. Since enums are only 
recognized when they are source code, using scanf() will not see an 
enum as a string. This will allow an enum string to be associated with
an enum value outside of the source code. 
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
    double  r;      // return rate (0.00 = no change)
    double  i;      // inflation rate (0.00 = no change)
    int     t;      // amount of time in market in years 
    int     n;      // number of times a year to contribute to fund 
} icif;


// A function that matches the struct MODE_ value to the enum mode
// Returns 0 if fails.
int matchMODE(char mode[])
{
    // Handling if an integer mode is input
    int x = strtol(mode, NULL, 10);
    if (x > 0 && x < NUM_MODES)
        return x;

    // Handling if a mode were input as a string
    for (int i = 0; i < NUM_MODES; i++)
    {
        if (!strcmp(mode, Mode[i].mode))
            return Mode[i].val;
    }

    return 0;
}

/*
This function loads all command line arguments into their respective struct members,
regardless of their order in the command line.

getArgs() does not care what mode it is when getting the rest of the values, since 
the mode may come after A or c in the command line. For example, if you entered a c 
value when the mode is MODE_c, getArgs() will still get that value. It will just be 
overwritten when the actual icif calculations are done.
*/
void getArgs(int argc, char *argv[], icif *x)
{
    if (argc == 1)
        return;

    for (int i = 1; argv[i] != NULL; i++)
	{
		if (*argv[i] == 'm')
            x->mode = matchMODE(strchr(argv[i],'=')+1);
        else if (*argv[i] == 'A')
        {
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->A));
            x->A = x->A*DOLLARS;
        }
        else if (*argv[i] == 'P')
        {
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->P));
            x->P = x->P*DOLLARS;
        }
        else if (*argv[i] == 'c')
        {
            sscanf(strchr(argv[i],'=')+1, "%ld", &(x->c));
            x->c = x->c*DOLLARS;
        }
        else if (*argv[i] == 'r')
        {
            sscanf(strchr(argv[i],'=')+1, "%lf", &(x->r));
            x->r = x->r/100;
        }
        else if (*argv[i] == 'i')
        {
            sscanf(strchr(argv[i],'=')+1, "%lf", &(x->i));
            x->i = x->i/100;
        }
        else if (*argv[i] == 't')
            sscanf(strchr(argv[i],'=')+1, "%d", &(x->t));
        else if (*argv[i] == 'n')
            sscanf(strchr(argv[i],'=')+1, "%d", &(x->n)); 
	}
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
    // Mode has to be confirmed first so that the program knows which 
    // variables it needs and which it doesn't need to ask for.
    while (!x->mode)
    {
        printf("\nPlease enter the mode of calculation.\n");
        printf("It can either be MODE_cT, MODE_AT, MODE_c, MODE_A.\n");
        char tempMode[8] = {};
        scanf("%s", tempMode);
        x->mode = matchMODE(tempMode);
    }
    if ((x->mode == MODE_cT) || (x->mode == MODE_c))
    {
        while (!x->A)
        {
            printf("\nPlease enter the target investment amount in dollars (without the $ sign, commas, or decimals).\n");
            scanf("%ld", &(x->A));
            x->A = x->A*DOLLARS;
        }
    }
    // P will be skipped since 0 is a valid value
    else if (x->mode == MODE_AT || x->mode == MODE_A)
    {
        while (!x->c)
        {
            printf("\nPlease enter the inital contribution amount in dollars (without the $ sign, commas, or decimals).\n");
            scanf("%ld", &(x->c));
            x->c = x->c*DOLLARS;
        }
    }
    /*
    (r - i) cannot =0 or else the formula will be undefined.
    Must ask for both vars at the same time to make sure their
    difference is not 0.

    Due to that, if only r or i was given as command line args
    and not the other, askVars() will not ask for the other as 
    it is assumed you intended for the other to be 0.
    */
    while (!(x->r - x->i))
    {
        printf("\nPlease enter the rate at which your investments will increase as a percentage (without the %% sign).\n");
        printf("0.0 means 0%% change, <0.0 means decreasing, and >0.0 means increasing.\n");
        scanf("%lf", &(x->r));
        x->r = (x->r)/100;

        printf("\nPlease enter the rate of inflation as a percentage (without the %% sign).\n");
        printf("0.0 means 0%% change, <0.0 means decreasing, and >0.0 means increasing.\n");
        scanf("%lf", &(x->i));
        x->i = (x->i)/100;

        if (!(x->r - x->i))
            printf("\nr - i cannot = 0. Please give different values.\n");
    }
    while (x->t <= 0)   // negative numbers not allowed here
    {
        printf("\nPlease enter the number of years you will be investing.\n");
        scanf("%d", &(x->t));
    }
    while (x->n <= 0)   // negative numbers not allowed here
    {
        printf("\nPlease enter the number of times a year you will contribute to the fund.\n");
        scanf("%d", &(x->n));
    }
}

// This function does the fast calculations for A or c depending on the mode, which will be displayed to the console
void Icif(icif *x)
{
    // Preliminary calculation to make final equation more readable
    double rn =         1 + (x->r/x->n);
    double in =         1 + (x->i/x->n);
    double rn_nt =      pow(rn, (double)(x->n * x->t + 1));
    double last_term =  pow(in, (double)(x->n * x->t));
    double in_nt =      last_term * in;

    // The bulk part of the calculation
    double coeff = (((rn_nt - in_nt)/(rn - in)) - last_term);

    // Doing the last part of the equation depending on which value is needed
    switch (x->mode)
    {
        case 1: x->c = (long)(x->A / coeff);    break;
        case 2: x->A = (long)(x->c * coeff);    break;
        case 3: x->c = (long)(x->A / coeff);    break;
        case 4: x->A = (long)(x->c * coeff);    break;
        default: printf("error: unknown mode of calculation.\n");
    }

    // TODO: handle the calculations when there is a P value.
}

/*
This function loops to find the contribution amount for every term and tabulates it to a .csv file.

It is assumed that Icif() has already been executed before this function.
*/
void IcifTabulate(icif *x)
{
    FILE *fp = fopen("icif.csv", "w");
    if (fp == NULL)
    {
        printf("\nCould not make icif.csv file. Not tabulating :(\n");
        return;
    }

    // Table headers
    fprintf(fp, "Year-Period,Contribution Amount,Total Contributions,Total Value\n");

    double rn = 1+(x->r/x->n);
    double in = 1+(x->i/x->n);

    // totalCont's value represents the total contributions at the beginning of a period, whereas 
    // totalValue's value represents the value at the end of a period when interest has been gained.
    long contribution = x->c;
    long totalCont = x->c;
    long totalValue = x->c * rn;

    fprintf(fp, "1-1,%.2lf,%.2lf,%.2lf\n", (double)contribution/DOLLARS, (double)totalCont/DOLLARS, (double)totalValue/DOLLARS);  // First row

    for (int i = 1; i < (x->n*x->t); i++)
    {
        contribution = (long)(contribution * in);
        totalCont += contribution;
        totalValue = (long)((totalValue + contribution) * rn);

        fprintf(fp, "%d-%d,%.2lf,%.2lf,%.2lf\n", (i/x->n)+1, (i%x->n)+1, (double)contribution/DOLLARS, (double)totalCont/DOLLARS, (double)totalValue/DOLLARS);
    }

    fclose(fp);
}

int main(int argc, char *argv[])
{
    icif x = {.mode = 0, .A = 0*DOLLARS, .P = 0, .r = 0, .i = 0, .t = 0, .n = 0};

    getArgs(argc, argv, &x);
    askVars(&x);

    Icif(&x);
    if ((x.mode == MODE_cT) || (x.mode == MODE_AT))
        IcifTabulate(&x);

    printf("\n");
    printf("Mode: %d\n", x.mode);
    printf("A: $%.2lf\n", (double)x.A/DOLLARS);
    printf("P: $%.2lf\n", (double)x.P/DOLLARS);
    printf("c: $%.2lf\n", (double)x.c/DOLLARS);
    printf("r: %.2lf%%\n", x.r*100);
    printf("i: %.2lf%%\n", x.i*100);
    printf("t: %d\n", x.t);
    printf("n: %d\n", x.n);

    return 0;
}