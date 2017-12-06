/*
 * teexGraph --- by Frank Takes --- https://github.com/franktakes/teexgraph
 * 
 * The Timer class measures wall clock execution time, respecting paralellism.
 * Create the object Timer T and run T.click() to see time since the last click.
 */

#include "teexgraph/BadTimer.h"
// #include "omp.h"
#include <iostream>
using namespace std;

// constructor
BadTimer::BadTimer() {
    current = -1;
}

// show and restart timer
void BadTimer::click() {
    if(current != -1)
        cerr << "Time passed: " << now() - current << " sec." << endl;
    restart();
}

// get now time
double BadTimer::now() {
    #ifdef _OPENMP
    // return omp_get_wtime();
    #endif
    return(double) clock() / (double) CLOCKS_PER_SEC;
}

// restart timer
void BadTimer::restart() {
    current = now();
}

