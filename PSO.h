#ifndef PSO_H
#define PSO_H

#include <iostream>
#include <random>
#include <algorithm>
#include <functional>
#include <utility>

using namespace std;

class PSO
{

private:

    int                          numberOfParticles  ;
    int                          numberOfDimensions ;
    int                          maximumOfIteration ; // Termination Condition By Iteration

    double                       minRand            ; // Minimum Of Initial Variables
    double                       maxRand            ; // Maximum Of Initial Variables
    double                       errorCon           ; // Termination Condition By Error

    double                       W                  ; // Inertial Coefficient
    double                       C1                 ; // Acceleration Coefficient
    double                       C2                 ; // Acceleration Coefficient

    pair<vector<double>, double> result             ;

public:

    PSO( int    NOP = 500  , int    NOD = 1   , int    MOI = 1000,
         double MIR = -2.0 , double MAR = 2.0 , double ERC = 0.01,
         double w   = 0.9  , double c1  = 0.6 , double c2  = 1.4 )
         : numberOfParticles  (NOP),
         numberOfDimensions   (NOD),
         maximumOfIteration   (MOI),
         minRand              (MIR),
         maxRand              (MAR),
         errorCon             (ERC),
         W                    (w  ),
         C1                   (c1 ),
         C2                   (c2 )
         {}

    auto set_numberOfParticles ( int    NOP ) { this->numberOfParticles  = NOP ; };

    auto set_numberOfDimension ( int    NOD ) { this->numberOfDimensions = NOD ; };

    auto set_maximumOfIteration( int    MOI ) { this->maximumOfIteration = MOI ; };

    auto set_minRand           ( double MIR ) { this->minRand            = MIR ; };

    auto set_maxRand           ( double MAR ) { this->maxRand            = MAR ; };

    auto set_errorCon          ( double ERC ) { this->errorCon           = ERC ; };

    auto set_w                 ( double w   ) { this->W                  = w   ; };

    auto set_c1                ( double c1  ) { this->C1                 = c1  ; };

    auto set_c2                ( double c2  ) { this->C2                 = c2  ; };

    auto optimize( function<double (vector<double> )> fitFunc )
    {
        mt19937 mersenne( static_cast<unsigned int>( time( nullptr ) ) );
        uniform_real_distribution<> rnd1( minRand, maxRand );
        uniform_real_distribution<> rnd2( 0, 1 );

        vector<double> localBest( numberOfDimensions );
        generate( localBest.begin(), localBest.end(), [&]{ return rnd1( mersenne );} );

        vector<double> globalBest( numberOfDimensions );
        globalBest = localBest;

        vector <vector<double> > particles;
        particles.resize( numberOfParticles, vector<double>( numberOfDimensions, 0 ) );

        vector<double> velocity;
        velocity.resize( numberOfDimensions, 0 );

        for ( auto &row : particles )
        {
            vector<double> temp( numberOfDimensions );
            temp.clear();

            for ( auto &col : row )
            {
                col = rnd1( mersenne );
                temp.push_back( col );
            }

            localBest.clear();
            localBest = temp;

            if ( fitFunc( localBest ) < fitFunc( globalBest ) )
            {
                globalBest.clear();
                globalBest = localBest;
            }
        }

        int iterator = 0;
        while ( fitFunc( globalBest ) > errorCon and iterator < maximumOfIteration )
        {
            ++iterator;
            for ( int i = 0; i < numberOfParticles; ++i )
            {
                for ( int j = 0; j < numberOfDimensions; ++j )
                {
                    double r1 = rnd2( mersenne );
                    double r2 = rnd2( mersenne );

                    velocity[j] = W * velocity[j] 
                                    + ( C1 * r1 * ( localBest[j]  - particles[i][j] ) )
                                    + ( C2 * r2 * ( globalBest[j] - particles[i][j] ) );
                    
                    particles[i][j] = particles[i][j] + velocity[j];
                }

                if ( fitFunc( particles[i] ) < fitFunc( localBest ) )
                {
                    localBest.clear();
                    localBest = particles[i];
                }
            }

            if ( fitFunc( localBest ) < fitFunc( globalBest ) )
            {
                globalBest.clear();
                globalBest = localBest;
            }

        }

        this->result = make_pair( globalBest, fitFunc(globalBest) );
        return make_pair( globalBest, fitFunc(globalBest) );

    }

    auto printResult() -> void
    {
        for (int i = 0; i < result.first.size(); i++)
            cout << "Parameter " << i+1 << " : " << result.first[i] << endl;

        cout << "error : " << result.second << endl;
    }

};

#endif