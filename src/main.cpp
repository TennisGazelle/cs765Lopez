#include <iostream>

#include "Logger.h"

using namespace std;

int main(int argc, char *argv[]) {
    Logger logger("../out/somefile.log");
    logger.log("hello world");
    return 0;
}