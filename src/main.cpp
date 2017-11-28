#include <iostream>
#include <Timer.h>
#include <Portfolio.h>
#include <digraph/digraph.hpp>
#include <cmath>

#include "Logger.h"

using namespace std;

const string STOCK_NAMES[] = {
        "A",
        "AAL",
        "AAP",
        "AAPL",
        "ABBV",
        "ABC",
        "ABT",
        "ACN",
        "ADBE",
        "ADI",
        "ADM",
        "ADP",
        "ADS",
        "ADSK",
        "AEE",
        "AEP",
        "AES",
        "AET",
        "AFL",
        "AGN",
        "AIG",
        "AIV",
        "AIZ",
        "AJG",
        "AKAM",
        "ALB",
        "ALK",
        "ALL",
        "ALLE",
        "ALXN",
        "AMAT",
        "AME",
        "AMG",
        "AMGN",
        "AMP",
        "AMT",
        "AMZN",
        "AN",
        "ANTM",
        "AON",
        "APA",
        "APC",
        "APD",
        "APH",
        "ARNC",
        "ATVI",
        "AVB",
        "AVGO",
        "AVY",
        "AWK",
        "AXP",
        "AYI",
        "AZO",
        "BA",
        "BAC",
        "BAX",
        "BBBY",
        "BBT",
        "BBY",
        "BCR",
        "BDX",
        "BEN",
        "BF.B",
        "BIIB",
        "BK",
        "BLK",
        "BLL",
        "BMY",
        "BRK.B",
        "BSX",
        "BWA",
        "BXP",
        "C",
        "CA",
        "CHRW",
        "CHTR",
        "CI",
        "CINF",
        "CL",
        "CLX",
        "CMA",
        "CMCSA",
        "CME",
        "CMG",
        "CMI",
        "CMS",
        "CNC",
        "CNP",
        "COF",
        "COG",
        "COH",
        "COL",
        "COO",
        "COP",
        "COST",
        "COTY",
        "CPB",
        "CRM",
        "CSCO",
        "CSRA",
        "CSX",
        "CTAS",
        "CTL",
        "CTSH",
        "CTXS",
        "CVS",
        "CVX",
        "CXO",
        "D",
        "DAL",
        "DE",
        "DFS",
        "DG",
        "DGX",
        "DHI",
        "DHR",
        "DIS",
        "DISCA",
        "DISCK",
        "DLPH",
        "DLR",
        "DLTR",
        "DNB",
        "DOV",
        "DPS",
        "DRI",
        "DTE",
        "DUK",
        "DVA",
        "DVN",
        "EA",
        "EBAY",
        "ECL",
        "ED",
        "EFX",
        "EIX",
        "EL",
        "EMN",
        "EMR",
        "EOG",
        "EQIX",
        "EQR",
        "EQT",
        "ES",
        "ESRX",
        "ESS",
        "ETFC",
        "ETN",
        "ETR",
        "EVHC",
        "GIS",
        "GLW",
        "GM",
        "GOOG",
        "GOOGL",
        "GPC",
        "GPN",
        "GPS",
        "GRMN",
        "GS",
        "GT",
        "GWW",
        "HAL",
        "HAS",
        "HBAN",
        "HBI",
        "HCA",
        "HCN",
        "HCP",
        "HD",
        "HES",
        "HIG",
        "HOG",
        "HOLX",
        "HON",
        "HP",
        "HPE",
        "HPQ",
        "HRB",
        "HRL",
        "HRS",
        "HSIC",
        "HST",
        "HSY",
        "HUM",
        "IBM",
        "ICE",
        "IDXX",
        "IFF",
        "ILMN",
        "INCY",
        "INTC",
        "INTU",
//        "IP",
//        "IPG",
//        "IR",
//        "IRM",
//        "ISRG",
//        "ITW",
//        "IVZ",
//        "JBHT",
//        "JCI",
//        "JEC",
//        "JNJ",
//        "JNPR",
//        "JPM",
//        "JWN",
//        "K",
//        "KEY",
//        "KHC",
//        "KIM",
//        "KLAC",
//        "KMB",
//        "KMI",
//        "KMX",
//        "KO",
//        "KORS",
//        "KR",
//        "KSS",
//        "KSU",
//        "L",
//        "LB",
//        "LEG",
//        "LEN",
//        "LH",
//        "LKQ",
//        "MDLZ",
//        "MDT",
//        "MET",
//        "MHK",
//        "MKC",
//        "MLM",
//        "MMC",
//        "MMM",
//        "MNK",
//        "MNST",
//        "MO",
//        "MON",
//        "MOS",
//        "MPC",
//        "MRK",
//        "MRO",
//        "MS",
//        "MSFT",
//        "MSI",
//        "MTB",
//        "MTD",
//        "MU",
//        "MUR",
//        "MYL",
//        "NAVI",
//        "NBL",
//        "NDAQ",
//        "NEE",
//        "NEM",
//        "NFLX",
//        "NFX",
//        "NI",
//        "NKE",
//        "NLSN",
//        "NOC",
//        "NOV",
//        "NRG",
//        "NSC",
//        "NTAP",
//        "NTRS",
//        "NUE",
//        "NVDA",
//        "NWL",
//        "NWS",
//        "NWSA",
//        "O",
//        "OKE",
//        "OMC",
//        "ORCL",
//        "ORLY",
//        "OXY",
//        "PAYX",
//        "PBCT",
//        "PCAR",
//        "PCG",
//        "PCLN",
//        "PDCO",
//        "PEG",
//        "PEP",
//        "PFE",
//        "PFG",
//        "PG",
//        "PGR",
//        "PH",
//        "PHM",
//        "PKI",
//        "PLD",
//        "PM",
//        "PNC",
//        "PNR",
//        "PNW",
//        "PPG",
//        "PPL",
//        "PRGO",
//        "PRU",
//        "PSA",
//        "RTN",
//        "SBUX",
//        "SCG",
//        "SCHW",
//        "SEE",
//        "SHW",
//        "SIG",
//        "SJM",
//        "SLB",
//        "SLG",
//        "SNA",
//        "SNI",
//        "SO",
//        "SPG",
//        "SPGI",
//        "SRCL",
//        "SRE",
//        "STI",
//        "STT",
//        "STX",
//        "STZ",
//        "SWK",
//        "SWKS",
//        "SWN",
//        "SYF",
//        "SYK",
//        "SYMC",
//        "SYY",
//        "T",
//        "TAP",
//        "TDC",
//        "TDG",
//        "TEL",
//        "TGNA",
//        "TGT",
//        "TIF",
//        "TJX",
//        "TMK",
//        "TMO",
//        "TRIP",
//        "TROW",
//        "TRV",
//        "TSCO",
//        "TSN",
//        "TSS",
//        "TWX",
//        "TXN",
//        "TXT",
//        "UA",
//        "UAA",
//        "UAL",
//        "UDR",
//        "UHS",
//        "ULTA",
//        "UNH",
//        "UNM",
//        "UNP",
//        "UPS",
//        "URBN",
//        "URI",
//        "USB",
//        "UTX",
//        "V",
//        "VAR",
//        "VFC",
//        "VIAB",
//        "VLO",
//        "VMC",
//        "VNO",
//        "VRSK",
//        "VRSN",
//        "VRTX",
//        "VTR",
//        "VZ",
//        "WAT",
//        "WBA",
//        "WDC",
//        "WEC",
//        "WFC",
//        "WHR",
//        "WLTW",
//        "WM",
//        "WMB",
//        "WMT",
//        "WRK",
//        "WU",
//        "WY",
//        "WYN",
//        "WYNN",
//        "XEC",
//        "XEL",
//        "XL",
//        "XLNX",
//        "XOM",
//        "XRAY",
//        "XRX",
//        "XYL",
//        "YUM",
//        "ZBH",
//        "ZION",
//        "ZTS"

};

bool shootWithProbability(double prob) {
    double shot = double(rand())/double(RAND_MAX);
    return (shot <= prob);
}

double getSumOfCorrelationsBetweenPortfoliosAtIndex(int i, int j, vector<Stock>& market, vector<Portfolio>& portfolios) {
    double sum = 0.0;
    for (auto& p : portfolios) {
        sum += p.getCorrelationBetween(&market[i], &market[j]);
        if (isnan(sum)) {
            cout << endl;
            cout << i << "," << j << ": " << p.getFocus()->symbol << " ";
            p.print();
        }
    }
    return sum/double(portfolios.size());
}

vector< vector<double> > getCorrelationMatrix(Market &m, vector<Portfolio>& pfs) {
    vector< vector<double> > correlation;
    correlation.resize(m.size());
    for (auto& row : correlation) {
        row.resize(m.size());
    }

    for (unsigned int i = 0; i < m.size(); i++) {
        for (unsigned int j = 0; j < m.size(); j++) {
            correlation[i][j] = getSumOfCorrelationsBetweenPortfoliosAtIndex(i, j, m, pfs);
        }
    }

    return correlation;
}

void outputCorrelationMatrixToFile(const string& filename, const vector< vector<double> >& matrix, Market& market) {
    ofstream fout("../out/correlation.csv");
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << "," << market[i].symbol;
        fout << "," << market[i].symbol;
    }
    cout << endl;
    fout << endl;
    unsigned int count_edges = 0;
    for (unsigned int i = 0; i < market.size(); i++) {
        cout << market[i].symbol;
        fout << market[i].symbol;
        for (unsigned int j = 0; j < market.size(); j++) {
            cout << ",";
            fout << ",";
            double c = matrix[i][j];
            if (i != j && (c > 0.52 || c < -0.52)) {
                count_edges++;
                cout << c;
                fout << c;
            }
        }
        cout << endl;
        fout << endl;
    }
    fout.close();
    cout << count_edges/2 << " total edges." << endl;
}

void varyThreshold(const vector< vector<double> >& matrix) {
    vector<double> values;
    values.reserve(matrix.size()*matrix.size());
    for (const auto& row : matrix) {
        for (const auto& col : row) {
            values.push_back(abs(col));
        }
    }
    sort(values.begin(), values.end());

    int count = 0;
    for (float t = 0.0; t < 1.0; t += 0.01f) {
        while (values[count] < t) {
            count ++;
        }
        cout << "num of values lower than " << t << " : " << count << "[" << double(count)/double(values.size()) << "%]" << endl;
    }
}

int main(int argc, char *argv[]) {
//    srand((unsigned int)time(nullptr));
    srand(1);

    Market market;
    for (const auto &sn : STOCK_NAMES) {
        Stock stock(sn);
        market.push_back(stock);
    }

    market.print();
    cout << endl << endl;

    // declare the indexes at which to
    unsigned int offset = 3;
    vector<bool> actionIndexes(market[0].data.size());
    for (unsigned int i = 0; i < actionIndexes.size(); i++){
        actionIndexes[i] = shootWithProbability(.24);
        if (i + offset >= actionIndexes.size())
            actionIndexes[i] = false;
        cout << i << ": " << (actionIndexes[i]) << endl;
    }
    cout << endl;

    vector<Portfolio> portfolios;
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
                if (isnan(portfolios[i].getMoney())) {
                    cout << "Portfolio [" << i << "," << market[i].symbol << "] became nan with action at timestep: " << data_index << endl;
                }
            }
        }

        cout << "Created Portfolio [" << i << "," + market[i].symbol + "] - Total Return with offset " << offset << ": " << portfolios[i].getMoney() << endl;
    }

    vector< vector<double> > correlationMatrix = getCorrelationMatrix(market, portfolios);

    outputCorrelationMatrixToFile("../out/correlation.csv", correlationMatrix, market);

    varyThreshold(correlationMatrix);

    return 0;
}