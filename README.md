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

The total amount of money of the investment fund is simply a sum of every contribution multiplied by the compound interest each one gained during the investment term. In other words: $c\cdot r^{t}$.
<br>
When summed, the equation would be: $\sum_{n=0}^{t}\left(c\cdot r^{\left(t-n\right)}\right)$.
<br>
$(t-n)$ is decreasing because the later a contribution is made, the less time it has to accumulate compound interest.

The contributions must be made with additional compound interest, this time in the form of inflation, which would look like $c\cdot i^{t}$.
<br>
When summed, the equation would be: $\sum_{n=0}^{t}\left(c\cdot i^{\left(n\right)}\right)$.
<br>
This time, $t$ increases because the later contributions are made, the more inflation it must compensate.

Putting the two summations together, you get: $\sum_{n=0}^{t}\left(c\cdot r^{\left(t-n\right)}i^{\left(n\right)}\right)$.
When the summation is expanded adn the coefficient is factored, you get:
$$
c\left(r^{n}i^{0}+r^{\left(n-1\right)}i^{1}+r^{\left(n-2\right)}i^{2}+...+r^{2}i^{\left(n-2\right)}+r^{1}i^{\left(n-1\right)}+r^{0}i^{n}\right)
$$
This pattern of increasing and decreasing polynomials already exists. It's called a <ins>Telescoping Series</ins>:

The fun thing about this series is that if you multiply the entire series by $(x-y)$, it collapses into a very brief expression:
$$
\left(x^{n}-y^{n}\right)=\left(x-y\right)\left(x^{n}y^{0}+x^{\left(n-1\right)}y^{1}+x^{\left(n-2\right)}y^{2}+...+x^{2}y^{\left(n-2\right)}+x^{1}y^{\left(n-1\right)}+x^{0}y^{n}\right)
$$

Working the other way, the series can be represented as: $\left(\frac{x^{n}-y^{n}}{x-y}\right)$

If you plug back in our variables and contribution, you get:
$$
A=c\left(\frac{r^{t}-i^{t}}{r-i}\right)
$$

And if you move things around, you can make an equaiton which extrapolates $c$ when given $A$:
$$\Large
c=\frac{A}{\left(\frac{r^{t}-i^{t}}{r-i}\right)}
$$

However, using this formula only gives the contribution amount for an entire year. What if you wanted to contribute multiple times a year? Simple. You can just treat $c$ as $A$ and rerun the previous equation. The only difference is that you won't be using $t$ (the number of years), you would be using $n$ (the number of contributions per year).
$$\Large
c_{n}=\frac{c_{t}}{\left(\frac{r^{n}-i^{n}}{r-i}\right)}
$$

When we substitute the latter equation into the former, we get:
$$\Large
c=\frac{A}{\left(\frac{r^{t}-i^{t}}{r-i}\right)\left(\frac{r^{n}-i^{n}}{r-i}\right)}
$$

This formula finds the amount of the very first contribution given a final target for an investment fund, and switching things around would get the equaiton at the top.