# Investment-Calculator
This program is centered around the <ins>Inflating Contributions Investment Formula (ICIF)</ins>. It is similar to traditional investment formulas, which track interest on regular contributions. However, this formula also accounts for the contribution amounts increasing over time to meet inflation.

This formula is:
$$\large 
A=c\left(\frac{r^{t}-i^{t}}{r-i}\right)\left(\frac{r^{n}-i^{n}}{r-i}\right)
$$
where:
- A = The total amount of money at the end of the investment term
- c = The amount of the very first contribution in dollars
- r = The rate of interest on investments (1.00 = no increase)
- i = The rate of inflation (1.00 = no increase)
- t = The duration of the investment term in years
- n = The number of times a contribution will be made per year

If you also want to include a principle investment, P, you can add to the end of the previous formula:   $P\cdot r^{\left(n+1\right)}$

Program Features:
- takes in and outputs all information through a .txt file
- can calculate a final investment value givne a starting contribution
- can extrapolate an initial investment value given a final investment goal

Limitations:
- This program does not allow the changing of the interest or inflation rates over time.
- Expense Ratios are not accounted for in the formula.

Future Features:
- converts the nominal value of investments into its real value
- will also track an upper bound and lower bound interest rate, as well as an upper and lower bound inflation rate.
- factors changes in the interest rate over time (to simulate protfolio rebalancing).



## Deriving the Formula