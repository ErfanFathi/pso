#include "PSO.h"

auto func( vector<double> x ) -> double
{
    double p1 = pow(x[0], 2) - 4; 

    return abs( p1 );
}

auto main() -> int
{
    PSO pso;

    pso.set_numberOfParticles(600);
    pso.set_numberOfDimension(1);
    pso.set_maximumOfIteration(2000);
    pso.set_minRand(-3.1);
    pso.set_maxRand(1.6);
    pso.set_errorCon(0.01);
    pso.set_w(0.98);
    pso.set_c1(0.8);
    pso.set_c2(1.2);

    auto result = pso.optimize(func);
    
    pso.printResult();

    
    return 0;
}