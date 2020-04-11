#include<iostream>
#include<cmath>
#include<vector>
#include<tuple>
#include<boost/date_time/gregorian/greg_date.hpp>
#include<boost/date_time/gregorian/greg_duration.hpp>

using boost::gregorian::date;
using boost::gregorian::date_duration;

// Iteration statements.

// A loop can be expressed as a for-, while- or do-while statement:

// while(condition) statement

// do statement while(expression);

// for(initialization;termination;expression) statement;

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