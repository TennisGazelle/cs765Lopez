#include <iostream>
#include <Timer.h>
#include <Portfolio.h>

#include "Logger.h"

using namespace std;

int main(int argc, char *argv[]) {
    Timer timer;
    timer.start();
    Logger logger("../out/somefile.log");
    logger.log("hello world");
    timer.stop();
    cout << "writing to file took " << timer.getElapsedTime() << " seconds." << endl;

    Portfolio p1, p2;

    Market market;
    Stock s1, s2;

    s1.symbol = "A";
    s1.data.push_back(1.0);
    s1.data.push_back(2.0);
    s1.data.push_back(3.0);
    s1.data.push_back(4.0);
    s1.data.push_back(0.5);

    s2.symbol = "B";
    s2.data.push_back(1.0);
    s2.data.push_back(3.0);
    s2.data.push_back(5.0);
    s2.data.push_back(7.0);
    s2.data.push_back(0.2);

    market.push_back(s1);
    market.push_back(s2);

    market.print();
    cout << endl << endl;

//    p1.buyAll(market, 3);
//    p1.print();
//    p1.sellAll(market, 4);
//
//    p1.print();

    Portfolio pA(&market[0], 3);
    pA.buyAll(market, 1);
    pA.print();
    pA.sellAll(market, 5);
    pA.print();


    return 0;
}