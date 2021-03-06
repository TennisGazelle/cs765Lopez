#ifndef __LOGGER_CPP_
#define __LOGGER_CPP_

#include "Logger.h"

Logger::Logger() : outputFileName(""), outputLocation(CONSOLE) {

}

Logger::Logger(const string& _outputFileName) : outputFileName(_outputFileName), outputLocation(FILE) {

}

Logger::~Logger() {
    if (outputLocation == FILE) {
        outputToFile();
    }
}

void Logger::log(const string& logMessage) {
    if (outputLocation == CONSOLE) {
        cout << logMessage << endl;
    } else {
        logs.push_back(logMessage);
    }
}

void Logger::outputToFile() {
    ofstream fout(outputFileName.c_str());
    for (const string &s : this->logs) {
        fout << s << endl;
    }
    fout.close();
}

#endif