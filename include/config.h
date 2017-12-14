//
// Created by daniellopez on 11/28/17.
//

#ifndef STOCKCOMPLEXNETWORKS_CONFIG_H
#define STOCKCOMPLEXNETWORKS_CONFIG_H

#include <string>
#include <vector>
using namespace std;

const unsigned int MAX_OFFSET = 50;

#define PEARSON_W_SQUARE_V_SQUARE_ROOT  50
#define PEARSON_W_LOG_V_EXP             51
#define PEARSON_W_CUBE_V_CUBE_ROOT      52

// list from here
// https://github.com/datasets/s-and-p-500-companies/blob/master/data/constituents-financials.csv
const string FILE_HEADER = "../out/", FILE_CSV_EXTENSION = ".csv", FILE_TSV_EXTENSION = ".tsv";
const vector<string> STOCK_NAMES = {
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
//        "C",
//        "CA",
//        "CAG",
//        "CAH",
//        "CAT",
//        "CB",
//        "CBG",
//        "CBOE",
//        "CBS",
//        "CCI",
//        "CCL",
//        "CELG",
//        "CERN",
//        "CF",
//        "CFG",
//        "CHD",
//        "CHK",
//        "CHRW",
//        "CHTR",
//        "CI",
//        "CINF",
//        "CL",
//        "CLX",
//        "CMA",
//        "CMCSA",
//        "CME",
//        "CMG",
//        "CMI",
//        "CMS",
//        "CNC",
//        "CNP",
//        "COF",
//        "COG",
//        "COH",
//        "COL",
//        "COO",
//        "COP",
//        "COST",
//        "COTY",
//        "CPB",
//        "CRM",
//        "CSCO",
//        "CSRA",
//        "CSX",
//        "CTAS",
//        "CTL",
//        "CTSH",
//        "CTXS",
//        "CVS",
//        "CVX",
//        "CXO",
//        "D",
//        "DAL",
//        "DE",
//        "DFS",
//        "DG",
//        "DGX",
//        "DHI",
//        "DHR",
//        "DIS",
//        "DISCA",
//        "DISCK",
//        "DLR",
//        "DLTR",
//        "DNB",
//        "DOV",
//        "DPS",
//        "DRI",
//        "DTE",
//        "DUK",
//        "DVA",
//        "DVN",
//        "EA",
//        "EBAY",
//        "ECL",
//        "ED",
//        "EFX",
//        "EIX",
//        "EL",
//        "EMN",
//        "EMR",
//        "EOG",
//        "EQIX",
//        "EQR",
//        "EQT",
//        "ES",
//        "ESRX",
//        "ESS",
//        "ETFC",
//        "ETN",
//        "ETR",
//        "EVHC",
//        "EW",
//        "EXC",
//        "EXPD",
//        "EXPE",
//        "EXR",
//        "F",
//        "FAST",
//        "FB",
//        "FBHS",
//        "FCX",
//        "FDX",
//        "FE",
//        "FFIV",
//        "FIS",
//        "FISV",
//        "FITB",
//        "FL",
//        "FLIR",
//        "FLR",
//        "FLS",
//        "FMC",
//        "FOX",
//        "FOXA",
//        "FRT",
//        "FSLR",
//        "FTI",
//        "FTR",
//        "FTV",
//        "GD",
//        "GE",
//        "GGP",
//        "GILD",
//        "GIS",
//        "GLW",
//        "GM",
//        "GOOG",
//        "GOOGL",
//        "GPC",
//        "GPN",
//        "GPS",
//        "GRMN",
//        "GS",
//        "GT",
//        "GWW",
//        "HAL",
//        "HAS",
//        "HBAN",
//        "HBI",
//        "HCA",
//        "HCN",
//        "HCP",
//        "HD",
//        "HES",
//        "HIG",
//        "HOG",
//        "HOLX",
//        "HON",
//        "HP",
//        "HPE",
//        "HPQ",
//        "HRB",
//        "HRL",
//        "HRS",
//        "HSIC",
//        "HST",
//        "HSY",
//        "HUM",
//        "IBM",
//        "ICE",
//        "IDXX",
//        "IFF",
//        "ILMN",
//        "INCY",
//        "INTC",
//        "INTU",
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
//        "LLL",
//        "LLY",
//        "LMT",
//        "LNC",
//        "LNT",
//        "LOW",
//        "LRCX",
//        "LUK",
//        "LUV",
//        "LYB",
//        "M",
//        "MA",
//        "MAA",
//        "MAC",
//        "MAR",
//        "MAS",
//        "MAT",
//        "MCD",
//        "MCHP",
//        "MCK",
//        "MCO",
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
//        "PSX",
//        "PVH",
//        "PWR",
//        "PX",
//        "PXD",
//        "PYPL",
//        "QCOM",
//        "QRVO",
//        "R",
//        "RCL",
//        "REG",
//        "REGN",
//        "RF",
//        "RHI",
//        "RHT",
//        "RIG",
//        "RL",
//        "ROK",
//        "ROP",
//        "ROST",
//        "RRC",
//        "RSG",
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
//        "XYL",
//        "YUM",
//        "ZBH",
//        "ZION",
//        "ZTS"
};

#endif //STOCKCOMPLEXNETWORKS_CONFIG_H
