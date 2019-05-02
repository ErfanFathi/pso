#include "PSO.h"

auto func( vector<double> x, Point goal ) -> double
{
    double p1 = pow(x[0] - goal.x, 2);
    double p2 = pow(x[1] - goal.y, 2);
    double error = sqrt(p2+p1);
    return  error;
}

auto main() -> int
{
    PSO pso;

    pso.set_numberOfParticles(10);
    pso.set_numberOfDimension(2);
    pso.set_maximumOfIteration(200);
    pso.set_minRand(0);
    pso.set_maxRand(480);
    pso.set_errorCon(1);
    pso.set_w(0.5);
    pso.set_c1(0.2);
    pso.set_c2(1.8);

    auto result = pso.optimize(func);
    
    pso.printResult();

    return 0;
}