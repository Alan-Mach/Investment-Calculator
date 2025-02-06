# Investment-Calculator
Most investment calculators on the internet let you choose a single amount you are going to contribute repeatedly for the entire term. However, $1,000 invested today will be worth more than $1,000 invested 10 years from now. What if you wanted to scale your investments over time to account for that inflation? What would your investment portfolio be worth?

This is where the <ins>Inflating Contributions Investment Formula (ICIF)</ins> comes in. It calculates what your portfolio would be worth when the amount you are contributing into a fund slowly increases. This could be used to account for inflation, or it could be used to represent how a salary progression allows you to invest more as time progresses.

This formula is:\
$$A=c\left(\frac{\left(\left(1+\frac{r}{n}\right)^{\left(nt+1\right)}-\left(1+\frac{i}{n}\right)^{\left(nt+1\right)}\right)}{\left(1+\frac{r}{n}\right)-\left(1+\frac{i}{n}\right)}-\left(1+\frac{i}{n}\right)^{nt}\right)$$
where:
- A = The total amount of money at the end of the investment term
- c = The amount of the very first contribution in dollars
- r = The rate of interest on investments (0 = no increase)
- i = The rate of inflation (0 = no increase)
- t = The duration of the investment term in years
- n = The number of times a contribution will be made per year

## Running the Program
Compiling: 
- Run the command `make` in the command line.
    - You only need to run this command once. If you are using the program again, there is no need to `make` again

If you want to run without args:
- enter `./main.e`

If you want to run with args:
- use the format `./main.e mode=1 A=1000 c=1000 r=1 i=1 t=1 n=1`, replacing the example values with your own
    - Do not put spaces where there aren't any in the format. The only spaces are to separate variables apart.
    - Do not put commas, $, or % signs with any values
    - For now, the mode value is represented as a number and not the name (as seen below)
    - The variables can be in different orders, but `./main.e` must be first.

Running:
- If you entered any args, the program will read those first..
- Then, it will ask for any missing variables it needs. It will continuously ask until a valid value is given. Simply enter your desired value into the console and press enter (be sure to follow the directions printed on the screen).
    - First it will ask for the mode, since that determines which value you want to calculate and whether you want to tabulate the results (refer to "Modes" below).
    - If you make a mistake, you cannot undo the value you put in unless the value you entered was not valid. You can just rerun the program again if necessary.
- Then it will ask for the rest of the necessary values from the formula above and calculate the value according to your selected mode.
- If you choose to tabulate your investment values, then you will also find an output file named icif.csv that contains all the data. 
    - You can then import that file into most spreadsheet software. You may have to format the units to dollars. 

Cleaning:
- `make clean`

## The Program
Features:
- command line args or though user input
- can calculate a final investment value given a starting contribution amount
- can extrapolate an initial investment value given a final investment goal

Modes: 
1. `MODE_cT`: Uses $A$ to find $c$, and the intermediate $c$ values for every period will be calculated and tabulated in a .csv file for excel.
    - Whatever value is stored in $c$ before the calculation will be overwritten.
    - If you do import to excel, set the delimiter to be commas. 
2. `MODE_AT`: Uses $c$ to find $A$, and the intermediate $c$ values for every period will be calculated and tabulated in a .csv file for excel.
    - Whatever value is stored in $A$ before the calculation will be overwritten.
    - If you do import to excel, set the delimiter to be commas. 
3. `MODE_c`: Uses $A$ to find $c$, the intermediate values will not be calculated.
    - Whatever value is stored in $c$ before the calculation will be overwritten.
4. `MODE_A`: Uses $c$ to find $A$, the intermediate values will not be calculated.
    - Whatever value is stored in $A$ before the calculation will be overwritten.

For the tabulated modes (`MODE_cT` and `MODE_AT`), the .csv file will record the following numbers for each period:
- The period.
- The amount needed to contribute for that period.
- The running total of all contributions made up until that point.
- The running total of the entire investment fund including compound interest.

Limitations:
- This program does not allow the changing of the interest or inflation rates over time; there is only one return rate for the entire investment term.
- Expense Ratios are not accounted for in the formula. However, if you are investing into mutual funds or ETFs, they should already be factored into the expected return rates.
- This program does not extrapolate what r or i may be when provides the rest of the variables. You must provide these values yourself
- Due to the computer's rounding errors, the values in the last rows of the .csv file may be slightly different from the value printed to the console.

Future Features:
- Will allow the function variables to also be read through an input file instead of in the command line or scanf().
- Will also track an upper bound and lower bound interest rate, as well as an upper and lower bound inflation rate.
- Will factor changes in the interest rate over time (to simulate protfolio rebalancing).
- A github.io website to make the program more accessible.
- Monte Carlo simulations to find the risk of ruin.


## Deriving the Formula

The total amount of money of the investment fund is simply a sum of every contribution multiplied by the compound interest each one gained during the investment term. In other words: $c\cdot r^{t}$.

When summed, the equation would be:\
$$\sum_{k=0}^{t}\left(c\cdot r^{\left(t-k\right)}\right)$$

$(t-k)$ is decreasing because the later a contribution is made, the less time it has to accumulate compound interest.

The contributions must be made with additional compound interest, this time in the form of inflation, which would look like $c\cdot i^{t}$.

When summed, this equation would be:\
$$\sum_{k=0}^{t}\left(c\cdot i^{\left(k\right)}\right)$$ \
This time, $t$ increases because the later contributions are made, the more inflation it must compensate.

Putting the two summations together, you get: \
$$\sum_{k=0}^{t}\left(c\cdot r^{\left(t-k\right)}i^{\left(k\right)}\right)$$

When the summation is expanded and the coefficient is factored, you get:\
$$c\left(r^{n}i^{0}+r^{\left(n-1\right)}i^{1}+r^{\left(n-2\right)}i^{2}+...+r^{2}i^{\left(n-2\right)}+r^{1}i^{\left(n-1\right)}+r^{0}i^{n}\right)$$

There is a very similar bivariate polynomial that looks like this:\
$$(x^{\left(n-1\right)}y^{0}+x^{\left(n-2\right)}y^{1}+x^{\left(n-3\right)}y^{2}+...+x^{2}y^{\left(n-3\right)}+x^{1}y^{\left(n-2\right)}+x^{0}y^{\left(n-1\right)})$$

The cool thing about that polynomial is that if you multiply the entire series by $(x-y)$, it collapses into a very brief expression:\
$$\left(x^{n}-y^{n}\right)=\left(x-y\right)\left(x^{\left(n-1\right)}y^{0}+x^{\left(n-2\right)}y^{1}+x^{\left(n-3\right)}y^{2}+...+x^{2}y^{\left(n-3\right)}+x^{1}y^{\left(n-2\right)}+x^{0}y^{\left(n-1\right)}\right)$$

Working the other way, the polynomial can be represented as: \
$$\left(\frac{x^{n}-y^{n}}{x-y}\right)$$

This isn't exactly what we need, though. The polynomial in the equation is reduced one power since $x$ starts at $(n-1)$. To account for this, the equation we need should have $(n+1)$: \
$$\left(\frac{x^{\left(n+1\right)}-y^{\left(n+1\right)}}{x-y}\right)$$

However, this new equation will have the term $(x^{0}y^{\left(n-1\right)})$. Since this term experiences no compound interest and only inflation, it should be removed.

The current equation will look like: \
$$\left(\frac{x^{\left(n+1\right)}-y^{\left(n+1\right)}}{x-y}-y^{n}\right)$$

If you plug back in our variables and contribution, you get:\
$$A=c\left(\frac{r^{\left(t+1\right)}-i^{\left(t+1\right)}}{r-i}-y^{t}\right)$$

And if we flip the equation, we can extrapolate a contribution amount given a final investment target:\
$$c=\frac{A}{\left(\frac{r^{\left(t+1\right)}-i^{\left(t+1\right)}}{r-i}-y^{t}\right)}$$

However, using this formula only gives the contribution amount for an entire year. What if you wanted to find out how much to contribute multiple times a year? Simple. Like the common coumpound interest formula, $A=P\left(1+\frac{r}{n}\right)^{nt}$, you need to turn $t$ into $nt$, which gives you the total number of subannual terms. Additionally, you need to account for the $r$ and $i$ growth rates, so they will reduce to $\left(1+\frac{r}{n}\right)$ and $\left(1+\frac{i}{n}\right)$ respectively.

When factoring those in, we get:\
$$A=c\left(\frac{\left(\left(1+\frac{r}{n}\right)^{\left(nt+1\right)}-\left(1+\frac{i}{n}\right)^{\left(nt+1\right)}\right)}{\left(1+\frac{r}{n}\right)-\left(1+\frac{i}{n}\right)}-\left(1+\frac{i}{n}\right)^{nt}\right)$$ \
This formula quickly calculates a final A value when given a starting contribution. Flipping it will get:\
$$c=A\left(\frac{\left(\left(1+\frac{r}{n}\right)^{\left(nt+1\right)}-\left(1+\frac{i}{n}\right)^{\left(nt+1\right)}\right)}{\left(1+\frac{r}{n}\right)-\left(1+\frac{i}{n}\right)}-\left(1+\frac{i}{n}\right)^{nt}\right)$$ \
This formula finds the amount of the very first contribution given a final target for an investment fund.

Converting this formula back into a summation will give:\
$$c\sum_{k=0}^{nt-1}\left(1+\frac{i}{n}\right)^{\left(k\right)}\left(1+\frac{r}{n}\right)^{\left(nt-k\right)}$$
This formula will be useful when tabulating the accumulated investment fund over time, since you will need the sum after each term. 

However, when getting the contribution amount, the compound interest on investments will not be needed, only the inflation. Therefore, another equation is needed without it. \
$$\sum_{k=0}^{nt-1}c\left(1+\frac{i}{n}\right)^{\left(k\right)}$$ \
This formula will help find the accumulated principle value of money you have contributed to the fund so far.

We will also need an equation that will give the individual contribution values and not an accumulated sum, so the formula will be made into a sequence.
$$c_{n}=ci^{\left(n-1\right)}$$ \
This formula will be used to calculate how much you need to contribute into your investment fund for every term.

Collectively, these five equations will allow the program to tabulate for each term:
1. The amount of money you will need to contribute.
2. The total amount of money you have contributed so far.
3. The current size of your fund including investment returns