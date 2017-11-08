#include <iostream>
#include <Timer.h>

#include "Logger.h"

using namespace std;

int main(int argc, char *argv[]) {
    Timer timer;
    timer.start();
    Logger logger("../out/somefile.log");
    logger.log("hello world");
    timer.stop();
    cout << "writing to file took " << timer.getElapsedTime() << " seconds." << endl;
    return 0;
}