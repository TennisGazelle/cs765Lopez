#include <iostream>
#include <Timer.h>
#include <Portfolio.h>
#include <digraph/digraph.hpp>

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
//        "TVIAQ",
        "T",
        "BUD",
        "MMM",
        "SHOO"
};

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

double getSumOfCorrelationsBetweenPortfoliosAtIndex(int i, int j, vector<Stock>& market, vector<Portfolio>& portfolios) {
    int sum = 0;
    for (auto p : portfolios) {
        sum += p.getCorrelationBetween(&market[i], &market[j]);
    }
    return sum;
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
    for (const auto &sn : STOCK_NAMES) {
        Stock stock(sn);
        market.push_back(stock);
    }

    market.print();
    cout << endl << endl;

    // declare the indexes at which to
    vector<bool> actionIndexes(market[0].data.size());
    for (unsigned int i = 0; i < actionIndexes.size(); i++){
        actionIndexes[i] = shootWithProbability(.05);
        cout << (actionIndexes[i]);
    }
    cout << endl;

    vector<Portfolio> portfolios;
    unsigned int offset = 1;
    // put in a focus for each one
    for (unsigned int i = 0; i < market.size(); i++) {
        portfolios.emplace_back(Portfolio(&market[i], offset));

        // for each data point
        for (unsigned int data_index = 0; data_index < market[0].data.size(); data_index++) {
            if (actionIndexes[data_index]) {
                portfolios[i].doAction(market, data_index);
                if (i == actionIndexes.size()-1) {
                    portfolios[i].finalizeActions(market, data_index);
                }
            }
        }

        cout << "Created Portfolio [" << i << "," + market[i].symbol + "] - Total Return with offset " << offset << ": " << portfolios[i].getMoney() << endl;
    }


    ofstream fout("../out/correlation.csv");
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << "," << market[i].symbol;
        fout << "," << market[i].symbol;
    }
    cout << endl;
    fout << endl;
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << market[i].symbol;
        fout << market[i].symbol;
        for (unsigned int j = 0; j < market.size(); j++) {
            cout << ",";
            fout << ",";
            double c = getSumOfCorrelationsBetweenPortfoliosAtIndex(i, j, market, portfolios);
            cout << c;
            fout << c;
        }
        cout << endl;
        fout << endl;
    }
    fout.close();

//    for (const auto& node : graph.nodes()) {
//        for (const auto& edge : graph.connections(node)) {
//            cout << node << " - " << edge.first << " with correlation: " << float(edge.second)/10000.0f << endl;
//        }
//    }

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