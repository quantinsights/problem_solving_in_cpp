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

// Annuities.

// An ordinary annuity pays out the same C dollars at the end of each year for n years.
// For a rate r, the future value of the annuity at the end of the year is :

//tex:
// $\begin{align}
// FV &= C(1+r)^{n-1}+\ldots+C(1+r)+C\\
//    &= \sum_{i=0}^{n-1}C(1+r)^i\\
//    &= C\frac{(1+r)^n - 1}{(1+r)}
// \end{align}$

double fv_annuity_discrete(double C, double r, double t) {
    return C * (pow((1 + r), t) - 1) / (1 + r);
}


// Risk-free Bonds.

// A bond is a financial contract between an issuer and the bondholders.
// On the issue date, investors lend the principal notional to a corporate/sovereign,
// in exchange for bonds. The maturity date of the bond specifies the date on which the loan
// will be repaid. A bond pays interest at a coupon rate on its par value until 
// the maturity date. 

// Treasury securities with maturities of 1 year or less are discount securities : the T-Bills.
// Treasury securities with original maturities between 2 and 10 years are called T-Notes.
// Those with maturities greater than 10 years are called T-Bonds.

// A bond has a par value. The par value 

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

    return 0;
}