#include <iostream>
#include <Timer.h>
#include <Portfolio.h>

#include "Logger.h"

using namespace std;

const string STOCK_NAMES[] = {
        "AAPL",
        "BAC",
        "NFLX",
        "TSLA",
        "RGSE",
        "BAM",
        "KTOS",
        "DIS",
        "FIT",
        "NKE",
        "SSC",
        "BABA",
        "LGF.A",
        "PLNT",
        "COST",
        "INTC",
        "CLSN",
        "TWTR",
        "MSFT",
        "SBUX",
        "F",
        "GPRO",
        "GE",
        "ANG",
        "AABA",
        "CMG",
        "INTU",
        "SIRI",
        "LUV",
        "DAL",
        "AAL",
        "GOOG",
        "GOOGL",
        "WIX",
        "CMCSA",
        "MCD",
        "M",
        "LMT",
        "GRUB",
        "TVIAQ",
        "T",
        "BUD",
        "MMM",
        "SHOO"
};

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

int main(int argc, char *argv[]) {
//    srand((unsigned int)time(nullptr));
    srand(1);
    Timer timer;
    timer.start();
    Logger logger;
    logger.log("hello world");
    timer.stop();
    cout << "writing to file took " << timer.getElapsedTime() << " seconds." << endl;

    Market market;
    for (auto sn : STOCK_NAMES) {
        Stock stock(sn);
        market.push_back(stock);
    }

    market.print();
    cout << endl << endl;

    Portfolio pA;
    for (unsigned int i = 0; i < market[0].data.size(); i++) {
        cout << "i: " << i << endl;
        if (shootWithProbability(.5)) {
            pA.doAction(market, i);
            pA.print();

            if (i == market[0].data.size()-1) {
                pA.finalizeActions(market, i);
            }
        }
    }

    // get the relation between apple and spot
    cout << "Correlation between spot and dell: " << pA.getCorrelationBetween(&market[1], &market[2]);


//    vector <Portfolio> normalPortfolios(10);
//    for (auto &portfolio : normalPortfolios) {
//        for (unsigned int i = 0; i < appleStock.data.size(); i++) {
//            if (shootWithProbability(.5)) {
////                cout << "action at timestep [" << i << "]" << endl;
//                portfolio.doAction(market, i);
////                portfolio.print();
//            }
//            if (i == appleStock.data.size()-1){
//                portfolio.finalizeActions(market, i);
//            }
//        }
//        portfolio.print();
//    }

    return 0;
}