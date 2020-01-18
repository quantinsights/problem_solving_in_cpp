#include <iostream>
#include <cmath>
#include <fstream>

int main()
{
    const double g = 32.0; 

    //The user provides the initial conditions theta(0) and theta'(0)
    double theta_0, omega_0, l, t_f;
    std::cout << "Enter theta_0, omega_0, l, t_f : ";
    std::cin >> theta_0 >> omega_0 >> l >> t_f;

    // The general solution to the homogenous equation d2theta/dt2 + (g/l)theta = 0 is:
    // theta(t) = c_1 cos(sqrt(g/l)t) + c_2 sin (sqrt(g/l)t)
    // where c_1 = theta_0 and c_2 = sqrt(l/g) omega_0

    double theta, t, c_1, c_2, omega;
    c_1 = theta_0;
    c_2 = sqrt(l / g) * omega_0;

    std::ofstream simple_pendulum_data;
    simple_pendulum_data.open("simple_pendulum.dat",std::ios::out);
    simple_pendulum_data.precision(17);

    for (t = 0.0; t <= t_f; t += 0.01)
    {
        theta = c_1 * cos(sqrt(g / l) * t) + c_2 * sin(sqrt(g / l) * t);
        omega = -sqrt(g / l) * c_1 * sin(sqrt(g / l) * t) + sqrt(g / l) * c_2 * cos(sqrt(g / l) * t);
        simple_pendulum_data << t << " " << theta << " " << omega << std::endl;
    }

    simple_pendulum_data.close();

    return 0;
}