#include <stdio.h>
#include <math.h>

// money will be calculated in cents as an int

int readVariables(fd);

int main(void)
{
    int A = 0;          // total amount
    double P = 0.0;     // principle amount in dollars
    double c = 0.0;     // first contribution amount
    double r = 0.0;     // nominal return rate as a percent
    double i = 0.0;     // inflation rate as a percent
    int t = 0;          // ammount of time in market in years 
    int n = 0;          // number of times a year to contribute to fund 


    // Retreiving information from user
    printf("How many years will you be investing in the market? Please Enter an integer: ");
    scanf("%d", &period);
    printf("How many times will you invest in a year? Please Enter an integer: ");
    scanf("%d", &interval);
    printf("How much money have you already invested? Please Enter a value: ");
    scanf("%lf", &principle);
    printf("How much money do you plan to invest at each interval? Please Enter a value: ");
    scanf("%lf", &contribution);
    printf("What is the average inflation rate? Please Enter a value: ");
    scanf("%lf", &inflation);
    printf("What is your average annual return rate? Please Enter a value: ");
    scanf("%lf", &interest);

    // Interest on first interval of principle
    total = principle*pow(interest, (double)1.0/interval);

    for (int i = 1; i < period*interval; i++)
    {
        total = (contribution*pow(inflation, (double)i/interval)) + (total*pow(interest, (double)1.0/interval)); 
    }

    printf("$%lf\n", total);

    return 0;
}

int readVariables(fd)
{

    return;
}