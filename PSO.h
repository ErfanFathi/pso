#ifndef PSO_H
#define PSO_H

#include "Environment.h"
#include <algorithm>
#include <functional>
#include <utility>

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
         double MIR = 0    , double MAR = 640 , double ERC = 0.01,
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

    auto optimize( function<double (vector<double>, Point )> fitFunc )
    {
        // Set A Instance From Environment And Get Goal Position
        Environment ENV;
        auto goal = ENV.getGoal();

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

            if ( fitFunc( localBest, goal ) < fitFunc( globalBest, goal ) )
            {
                globalBest.clear();
                globalBest = localBest;
            }
        }

        int iterator = 0;
        while ( fitFunc( globalBest, goal ) > errorCon and iterator < maximumOfIteration )
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

                if ( fitFunc( particles[i], goal ) < fitFunc( localBest, goal ) )
                {
                    localBest.clear();
                    localBest = particles[i];
                }
            }

            if ( fitFunc( localBest, goal ) < fitFunc( globalBest, goal ) )
            {
                globalBest.clear();
                globalBest = localBest;
            }
            
            // Update Monitor
            ENV.Update( particles );
        }

        // Print Goal Position
        cout<<"Goal Point Is : "<<goal.x<<" , "<<goal.y<<endl;

        this->result = make_pair( globalBest, fitFunc(globalBest, goal) );
        return make_pair( globalBest, fitFunc(globalBest, goal) );

    }

    auto printResult() -> void
    {
        cout << "PSO Predicted Point : " << result.first[0] << " , " << result.first[1] << endl;
        cout << "Error : " << result.second << endl;
    }

};

#endif