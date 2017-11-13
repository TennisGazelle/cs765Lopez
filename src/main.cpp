#include <iostream>
#include <Timer.h>
#include <Portfolio.h>

#include "Logger.h"

using namespace std;

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

int main(int argc, char *argv[]) {
    srand((unsigned int)time(nullptr));
    Timer timer;
    timer.start();
    Logger logger;
    logger.log("hello world");
    timer.stop();
    cout << "writing to file took " << timer.getElapsedTime() << " seconds." << endl;

    Market market;
    Stock appleStock, spotStock;

    appleStock.symbol = "AAPL";
    appleStock.getValuesFromFile();

    spotStock.symbol = "SPOT";
    spotStock.getValuesFromFile();

    market.push_back(appleStock);
    market.push_back(spotStock);

    market.print();
    cout << endl << endl;


    Portfolio pA(&market[0], 3);
    Portfolio normal;
    for (unsigned int i = 0; i < appleStock.data.size(); i++) {
        if (shootWithProbability(.1)) {
            cout << "action at timestep [" << i << "]" << endl;
            normal.doAction(market, i);
            pA.doAction(market, i);
            pA.print();
        }
        if (i == appleStock.data.size()-1){
            pA.finalizeActions(market, i);
        }
    }

    return 0;
}