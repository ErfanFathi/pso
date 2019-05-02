#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
#include <random>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

class Environment
{
private:
    Point goal;
    
public:
    Environment();
    auto getGoal(){return goal;}
    void Update( vector <vector<double> > );
};

Environment::Environment()
{
    // Create A Random Goal
    mt19937 mersenne( static_cast<unsigned int>( time( nullptr ) ) );
    uniform_real_distribution<> rndx( 8, 632 );
    uniform_real_distribution<> rndy( 8, 472 );
    goal.x = rndx(mersenne);
    goal.y = rndy(mersenne);
}

void Environment::Update( vector <vector<double> > particles )
{
    Mat Env( 480, 640, CV_8UC3, Scalar(0, 0, 0) );
    circle( Env, goal, 8.0, Scalar( 0, 255, 0 ), -1, 8 );
    for( int i = 0; i < particles.size(); i++ )
    {
        circle( Env, Point2d( particles[i][0], particles[i][1] ), 8.0, Scalar( 255, 255, 255 ), -1, 8 );
    }
    imshow("Environment", Env);
    waitKey(300);
}


#endif