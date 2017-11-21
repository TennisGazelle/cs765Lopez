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
    Stock appleStock("AAPL"), spotStock("SPOT"), dellStock("DELL");

    market.push_back(appleStock);
    market.push_back(spotStock);
    market.push_back(dellStock);

    market.print();
    cout << endl << endl;

//    Portfolio pA(&market[0], 3);
    vector <Portfolio> normalPortfolios(10);
    for (auto &portfolio : normalPortfolios) {
        for (unsigned int i = 0; i < appleStock.data.size(); i++) {
            if (shootWithProbability(.5)) {
//                cout << "action at timestep [" << i << "]" << endl;
                portfolio.doAction(market, i);
//                portfolio.print();
            }
            if (i == appleStock.data.size()-1){
                portfolio.finalizeActions(market, i);
            }
        }
        portfolio.print();
    }

    return 0;
}