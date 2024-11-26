# Investment-Calculator
This program is centered around the <ins>Inflating Contributions Investment Formula (ICIF)</ins>. It is similar to traditional investment formulas, which track interest on regular contributions. However, this formula also accounts for the contribution amounts increasing over time to meet inflation.

This formula is:
$$\large 
A=c\left(\frac{\left(\sqrt[n]{r}^{\left(nt+1\right)}-\sqrt[n]{i}^{\left(nt+1\right)}\right)}{\sqrt[n]{r}-\sqrt[n]{i}}-\sqrt[n]{i}^{nt}\right)
$$
where:
- A = The total amount of money at the end of the investment term
- c = The amount of the very first contribution in dollars
- r = The rate of interest on investments (1.00 = no increase)
- i = The rate of inflation (1.00 = no increase)
- t = The duration of the investment term in years
- n = The number of times a contribution will be made per year

If you also want to include a principle investment, P, you can add to the end of the previous formula:   $P⋅r^{(n+\frac{1}{t})}$ (assuming your principle was invested one period before the contributions begin).

## Running the Program
Compiling: 
- run the command `make` in the command line

If you want to run without args:
- enter `./main`

If you want to run with args:
- use the format `./main `

Cleaning:
- `make clean`

## The Program
Features:
- command line args or though user input
- can calculate a final investment value givne a starting contribution
- can extrapolate an initial investment value given a final investment goal

Modes: 
1. Uses $A$ to find $c$, and the intermediate $c$ values for every period will be calculated
    - Whatever value is stored in $c$ before the calculation will be overwritten.
2. Uses $c$ to find $A$, and the intermediate $c$ values for every period will be calculated
    - Whatever value is stored in $A$ before the calculation will be overwritten.
3. Uses $A$ to find $c$, the intermediate values will not be calculated.
    - Whatever value is stored in $c$ before the calculation will be overwritten.
4. Uses $c$ to find $A$, the intermediate values will not be calculated.
    - Whatever value is stored in $A$ before the calculation will be overwritten.

At the top of the text file, the following will be printed:
- The arguments of the investment equation.
- The final value of the investment fund ($A$).
- The first contribution amount ($c$).

The text file will then print a table with the following for every period:
- The period.
- The amount needed to contribute for that period.
- The running total of all contributions made up until that point.
- The running total of the entire investment fund including compound interest.

Limitations:
- This program does not allow the changing of the interest or inflation rates over time.
- Expense Ratios are not accounted for in the formula.

Future Features:
- will also track an upper bound and lower bound interest rate, as well as an upper and lower bound inflation rate.
- factors changes in the interest rate over time (to simulate protfolio rebalancing).
- will export to XML format and will receive arguments through text file.
- Monte Carlo simulations to find the risk of ruin.


## Deriving the Formula

The total amount of money of the investment fund is simply a sum of every contribution multiplied by the compound interest each one gained during the investment term. In other words: $c\cdot r^{t}$.

When summed, the equation would be: 
$$
\sum_{k=0}^{t}\left(c\cdot r^{\left(t-k\right)}\right)
$$
$(t-k)$ is decreasing because the later a contribution is made, the less time it has to accumulate compound interest.

The contributions must be made with additional compound interest, this time in the form of inflation, which would look like $c\cdot i^{t}$.

When summed, this equation would be: 
$$
\sum_{k=0}^{t}\left(c\cdot i^{\left(k\right)}\right)
$$
This time, $t$ increases because the later contributions are made, the more inflation it must compensate.

Putting the two summations together, you get: 
$$
\sum_{k=0}^{t}\left(c\cdot r^{\left(t-k\right)}i^{\left(k\right)}\right)
$$
When the summation is expanded and the coefficient is factored, you get:
$$
c\left(r^{n}i^{0}+r^{\left(n-1\right)}i^{1}+r^{\left(n-2\right)}i^{2}+...+r^{2}i^{\left(n-2\right)}+r^{1}i^{\left(n-1\right)}+r^{0}i^{n}\right)
$$

There is a very similar bivariate polynomial that looks like this:
$$
(x^{\left(n-1\right)}y^{0}+x^{\left(n-2\right)}y^{1}+x^{\left(n-3\right)}y^{2}+...+x^{2}y^{\left(n-3\right)}+x^{1}y^{\left(n-2\right)}+x^{0}y^{\left(n-1\right)})
$$

The cool thing about that polynomial is that if you multiply the entire series by $(x-y)$, it collapses into a very brief expression:
$$
\left(x^{n}-y^{n}\right)=\left(x-y\right)\left(x^{\left(n-1\right)}y^{0}+x^{\left(n-2\right)}y^{1}+x^{\left(n-3\right)}y^{2}+...+x^{2}y^{\left(n-3\right)}+x^{1}y^{\left(n-2\right)}+x^{0}y^{\left(n-1\right)}\right)
$$

Working the other way, the polynomial can be represented as: 
$$\left(\frac{x^{n}-y^{n}}{x-y}\right)$$

This isn't exactly what we need, though. The polynomial in the equation is reduced one power since $x$ starts at $(n-1)$. To account for this, the equation we need should have $(n+1)$: 
$$\left(\frac{x^{\left(n+1\right)}-y^{\left(n+1\right)}}{x-y}\right)$$

However, this new equation will have the term $(x^{0}y^{\left(n-1\right)})$. Since this term experiences no compound interest and only inflation, it should be removed.

The current equation will look like: 
$$\left(\frac{x^{\left(n+1\right)}-y^{\left(n+1\right)}}{x-y}-y^{n}\right)$$

If you plug back in our variables and contribution, you get:
$$A=c\left(\frac{r^{\left(t+1\right)}-i^{\left(t+1\right)}}{r-i}-y^{t}\right)$$

And if we flip the equation, we can extrapolate a contribution amount given a final investment target:
$$\Large
c=\frac{A}{\left(\frac{r^{\left(t+1\right)}-i^{\left(t+1\right)}}{r-i}-y^{t}\right)}
$$

However, using this formula only gives the contribution amount for an entire year. What if you wanted to find out how much to contribute multiple times a year? Simple. Like other finance formulas, you need to turn $t$ into $nt$, which gives you the total number of subannual terms. Additionally, you need to account for the $r$ and $i$ growth rates, so they will reduce to $\sqrt[n]{r}$ and $\sqrt[n]{i}$ respectively.

When factoring those in, we get:
$$
A=c\left(\frac{\left(\sqrt[n]{r}^{\left(nt+1\right)}-\sqrt[n]{i}^{\left(nt+1\right)}\right)}{\sqrt[n]{r}-\sqrt[n]{i}}-\sqrt[n]{i}^{nt}\right)
$$
This formula quickly calculates a final A value when given a starting contribution. Flipping it will get:
$$
c=A\div\left(\frac{\left(\sqrt[n]{r}^{\left(nt+1\right)}-\sqrt[n]{i}^{\left(nt+1\right)}\right)}{\sqrt[n]{r}-\sqrt[n]{i}}-\sqrt[n]{i}^{nt}\right)
$$
This formula finds the amount of the very first contribution given a final target for an investment fund.

Converting this formula back into a summation will give:
$$
c\sum_{k=0}^{nt-1}\left(\sqrt[n]{i}^{k}\right)\left(\sqrt[n]{r}^{\left(nt-k\right)}\right)
$$
This formula will be useful when tabulating the accumulated investment fund over time, since you will need the sum after each term. 

However, when getting the contribution amount, the compound interest on investments will not be needed, only the inflation. Therefore, another equation is needed without it. 
$$
c\sum_{k=0}^{nt-1}\left(\sqrt[n]{i}^{k}\right)
$$
This formula will help find the accumulated principle value of money you have contributed to the fund so far

We will also need an equation that will give the individual contribution values and not an accumulated sum, so the formula will be made into a sequence.
$$
c_{n}=ci^{\left(n-1\right)}
$$
This formula will be used to calculate how much you need to contribute into your investment fund for every term.

Collectively, these five equations will allow the program to tabulate for each term:
1. The amount of money you will need to contribute.
2. The total amount of money you have contributed so far.
3. The current size of your fund including investment returns