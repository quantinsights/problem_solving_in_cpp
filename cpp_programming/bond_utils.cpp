// ==========================================================================================
//  C++ for financial engineering series.
//
//                          2. Basic Financial Mathematics
// ------------------------------------------------------------------------------------------

#include<iostream>
#include<cmath>
#include<vector>
#include<tuple>
#include<boost/date_time/gregorian/greg_date.hpp>
#include<boost/date_time/gregorian/greg_duration.hpp>

using boost::gregorian::date;
using boost::gregorian::date_duration;

// 1. The Time value of money.

//
// The value of any financial contract is present value of its expected cashflows.
// Interest is cost of borrowing money. Let r be the annual interest rate. If the interest
// is compounded once per year, the future value of P dollars after n years is 
// FV = P(1+r)^n

// To look at it from another perspective, X dollars n years from now, are worth
// X(1+r)^(-n) today, its present value. The process of obtaining the present value
// is called discounting.

// If interest is compounded m times a year, then the rate per period is r/m. The total
// number of periods are mn. The future value is

// FV = P(1+r/m)^(mn).

double fv_discrete(double P, double r, double m, double n)
{
    return P * pow((1 + r / m), m * n);
}

// Example. With an annual interest rate of 10% compounded twice per annum, each dollar
// will grow to be [1 + (0.1)/2]^2 = $1.1025 1 year from now. The rate is therefore 
// equivalent to an interest rate of 10.25% compounded once per annum.

// Example. An insurance company has to pay $20 million dollars 4 years from now to 
// pensioners. Suppose that it can invest money at an annual rate 7% compounded 
// semi-annually. The company should therefore invest 20,000,000/(1+(0.07/2))^8 
// = $15,188,231 today.

double pv_discrete(double X, double r, double m, double n)
{
    return X * pow((1 + r / m), -m * n);
}

// From Calculus, we know that,

// lim_(x->0) (1+1/x)^x = e.

// So, 

//      lim_(m->infinity) (1+r/m)^mn
//    = lim_(r/m->0) (1+r/m)^ { m/r x rn}
//    = lim_(r/m->0) [(1+r/m)^(m/r)]^rn
//    = e^rn

// Thus, as m->infinity, we obtain continuous compounding.

// FV = e^rn.

double fv_continuous(double P, double r, double t) {
    return P * exp(r * t);
}

double pv_continuous(double P, double r, double t) {
    return P * exp(-r * t);
}

// 2. Annuities.

// An ordinary annuity pays out the same C dollars at the end of each year for n years.
// For a rate r, the future value of the annuity at the end of the year is :

//tex:
// $\begin{align}
// FV &= C(1+r)^{n-1}+\ldots+C(1+r)+C\\
//    &= \sum_{i=0}^{n-1}C(1+r)^i\\
//    &= C\frac{(1+r)^n - 1}{r}
// \end{align}$

// The present value of the annuity today is :

//tex:
// $\begin{align}
// PV &= \frac{C}{1+r}+\frac{C}{(1+r)^2}+\ldots+\frac{C}{(1+r)^n}\\
//    &= \frac{C}{(1+r)}\frac{(1+r)^{-n}-1}{(1+r)^{-1}-1}\\
//    &= C\frac{1-(1+r)^{-n}}{r}
// \end{align}$

double fv_annuity_discrete(double C, double r, double t) {
    return (C/r) * (pow((1 + r), t) - 1);
}

double pv_annuity_discrete(double C, double r, double t)
{
    return (C / (1 + r)) * (1 - pow((1 + r), -t)) / r;
}
// Example.

// The PV of an annuity of $100 per annum for 5 years at an annual interest rate of 6.25%
// is :

// 100/0.0625 [1-(1+0.0625)^(-5)] = $418.3869

// 3. Amortization.

// Amortization is the method of repaying a loan through regular payments of interest and
// principal. The size of the loan is - the original balance is reduced - is reduced
// by the principal part of the payment. As the principal gets paid down over the term of
// the loan, the interest part of the payment diminishes.

// Home mortgages are typically amortized.

// Example. Suppose a home buyer takes a 15-year $250,000 mortgage at an 8% rate of interest
// Solving the ordinary annuity equation for C, with PV = 250,000, n=15x12=180, r=0.08/12=0.00666
// we get C = 

double amort_cashflow(double PV, double n, double r)
{
    // We simply invert the PV function of an ordinary annuity and make C the dependent variable
    // and PV the independent variable.
    // PV = C/r [1 - (1+r)^-n]
    // C = (PV r) / [1 - (1+r)^-n]

    return (PV * r) / (1 - pow((1 + r), -n));
}

// This helper function prints an amortization chart.

void amort_chart(double PV, double n, double r)
{
    double C = amort_cashflow(PV, n, r);

    // Pretty-printing the amortization table.
    // Header row.
    std::cout << "Month\t" << "Payment\t\t" << "Interest\t" << "Prin Pmt\t" << "Outst.\n";
    std::cout << "-----\t" << "-------\t\t" << "--------\t" << "--------\t" << "------\n";

    double p = PV;
    double int_pmt = 0.0;
    double princ_pmt = 0.0;
    // Body of the table.
    for (int i = 1; i <= n; ++i)
    {
        int_pmt = (r * p);
        princ_pmt = C - int_pmt;
        p -= princ_pmt;
        std::cout << i << "\t" << C << "\t\t" << int_pmt << "\t\t" << princ_pmt << "\t\t" << p << "\n";
    }
}

// 4. Discount curves and discount factors.

// Investors are risk-averse. They perceive higher credit risk when lending/depositing money for longer time-periods.
// Markets demand a risk-premium for longer maturities by way of higher interest rates. For instance, the rate for 
// an ON(overnight) deposit may be 4%, the rate for 1M(month) deposit may be 6%, and for 1Y deposit may be 12%.
// Markets have different rates for each maturity.

// Instrument   Quote Ask(%)    Underlying      Start Date      Maturity Date
// ---------------------------------------------------------------------------
// Depo ON      0.040           Euribor1D       01-JAN-2020     02-JAN-2020
// Depo TN      0.040           Euribor1D       02-JAN-2020     03-JAN-2020
// Depo SN      0.040           Euribor1D       01-JAN-2020     03-JAN-2020
// Depo 1W      0.070           Euribor1W       01-JAN-2020     08-JAN-2020
// Depo 1M      0.110           Euribor1M       01-JAN-2020     01-FEB-2020
// Depo 3M      0.180           Euribor3M       01-JAN-2020     01-APR-2020
// Depo 6M      0.320           Euribor6M       01-JAN-2020     01-JUL-2020
// Depo 12M     0.540           Euribor12M      01-JAN-2020     01-JAN-2021

//tex:
// This set of maturities and corresponding rates $\{(t,r(0,t))\}$ is called a rate-curve.

// Rates can be expressed as spot-to-maturity or forwards. Since, the future value
// of an investment at the end of T=2 years, must be equal to the investing cash for t=1 year,
// and rolling over this deposit; re-investing the proceeds for another 1 year, 
// mathematically, we must have-

//tex:
//$(1+r(0,s))(1+f(s,t))=(1+r(0,t))$

// f(s,t) is called the forward.


// 5. Risk-free Bonds.

// A bond is a financial contract between an issuer and the bondholders.
// On the issue date, investors lend the principal notional to a corporate/sovereign,
// in exchange for bonds. The maturity date of the bond specifies the date on which the loan
// will be repaid. A bond pays interest at a coupon rate on its par value until 
// the maturity date. 

// Treasury securities with maturities of 1 year or less are discount securities : the T-Bills.
// Treasury securities with original maturities between 2 and 10 years are called T-Notes.
// Those with maturities greater than 10 years are called T-Bonds.

// A bond has a par value. The par value of the bond is what causes the net present value of all
// cash-flows to be zero.

struct discountCurve {
    // We assume that the discountCurve is a piece-wise constant function
    // of time t.
    std::vector<double> r_t;
    std::vector<date> dates;
} ;

double yearFrac(date d1, date d2) { return ((d2 - d1).days() / 365.0); }

void search(discountCurve d, date keyDate, date& prevDate, date& currDate, double& df_1, double& df_2)
{
    // We use continuously compounded rates.
    df_2 = 1.0;
    for (int i = 1; i < d.dates.size(); ++i)
    {
        prevDate = d.dates[i - 1];
        currDate = d.dates[i];

        df_1 = df_2;
        df_2 *= exp(-d.r_t[i] * yearFrac(prevDate, currDate));

        if (keyDate >= prevDate && keyDate < currDate)
            break;
    }
}

// Linear interpolation of discount factors
double lin_interp(date x, date x1, double y1, date x2, double y2) {
    double y = (yearFrac(x, x1) * y2 + yearFrac(x2, x) * y1) / (yearFrac(x1, x2));
    return y;
}

// Returns the discount factor.
double df(discountCurve d, date from, date to)
{
    double df_from, df_to, df_1, df_2;
    date prevDate, currDate;

    search(d, from, prevDate, currDate, df_1, df_2);
    df_from = lin_interp(from, prevDate, df_1, currDate, df_2);

    search(d, to, prevDate, currDate, df_1, df_2);
    df_to = lin_interp(to, prevDate, df_1, currDate, df_2);

    // d02 = d01 * d12.
    // d12 = d02 / d01.
    return (df_to / df_from);
}

double df_to_zero(double df, date from, date to) {
    // df(t1,t2) = exp(-r * yearfrac(t2-t1))
    // so to find the zero rate, we just find the inverse function r in terms of df.
    // r = -1/yearfrac(t2-t1)*ln(df(t1,t2)

    return (-1 / yearFrac(from, to) * log(df));
}

void init_curve(discountCurve& d, std::vector<std::tuple<date, double>> x)
{
    for (int i = 0; i < x.size(); ++i)
    {
        d.dates.push_back(std::get<0>(x[i]));
        d.r_t.push_back(std::get<1>(x[i]));
    }
}

double cash_flow_pv(std::vector<date>& t,
    std::vector<double>& cashlow_amts,
    discountCurve disc_curve, date today)
{
    double PV = 0.0;
    for (int i = 0; i < t.size(); ++i)
    {
        PV += cashlow_amts[i] * df(disc_curve, today, t[i]);
    }
    return PV;
}


int main() {

    const date today(2020,1,1);

    // Construct a simple discount curve
    discountCurve discount_curve;
    
    init_curve(discount_curve, std::vector<std::tuple<date, double>> { 
        std::make_tuple(today, 0.0),
        std::make_tuple(date(2020,6,30),0.05),
        std::make_tuple(date(2021,1,1),0.06),
        std::make_tuple(date(2021,6,30),0.05),
        std::make_tuple(date(2022,1,1),0.04),
        std::make_tuple(date(2022,6,30), 0.03),
        std::make_tuple(date(2023,1,1),0.06),
        std::make_tuple(date(2023,6,30),0.05),
        std::make_tuple(date(2024,1,1),0.05)
    });
    
    // Find a few discount factors
    double discFactor = df(discount_curve, date(2020, 1, 1), date(2020, 6, 30));
    std::cout << "Discount factor = " << discFactor << std::endl;
    std::cout << "Forward = " << df_to_zero(discFactor, date(2020, 1, 1), date(2020, 6, 30)) << std::endl;

    // Find the amortized cash-flow for a housing mortgage
    double C = amort_cashflow(250000.00, 180.0, 0.006667);
    std::cout << "Cashflow = " << C << std::endl;

    // Pretty-print an amortization table
    amort_chart(250000.00, 180.0, 0.006667);

    return 0;
}