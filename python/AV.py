#!/usr/bin/python3.4

import json
import requests
from Graph import *

stocks = []
# this should look like this per stock
#{
    # name: "AAPL",
    # percentDiff: 4,
    # currentValue: 4,
#}

stock_names = sorted([
    "MMM",
    "ABT",
    "ABBV",
    "ACN",
    "ATVI",
    "AYI",
    "ADBE",
    "AAP",
    "AES",
    "AET",
    "AMG",
    "AFL",
    "A",
    "APD",
    "AKAM",
    "ALK",
    "ALB",
    "ALXN",
    "ALLE",
    "AGN",
    "ADS",
    "LNT",
    "ALL",
    "GOOGL",
    "GOOG",
    "MO",
    "AMZN",
    "AEE",
    "AAL",
    "AEP",
    "AXP",
    "AIG",
    "AMT",
    "AWK",
    "AMP",
    "ABC",
    "AME",
    "AMGN",
    "APH",
    "APC",
    "ADI",
    "ANTM",
    "AON",
    "APA",
    "AIV",
    "AAPL",
    "AMAT",
    "ADM",
    "ARNC",
    "AJG",
    "AIZ",
    "T",
    "ADSK",
    "ADP",
    "AN",
    "AZO",
    "AVB",
    "AVY",
    # "BHI",
    "BLL",
    "BAC",
    "BCR",
    "BAX",
    "BBT",
    "BDX",
    "BBBY",
    "BRK.B",
    "BBY",
    "BIIB",
    "BLK",
    "HRB",
    "BA",
    "BWA",
    "BXP",
    "BSX",
    "BMY",
    "AVGO",
    "BF.B",
    "CHRW",
    "CA",
    "COG",
    "CPB",
    "COF",
    "CAH",
    "KMX",
    "CCL",
    "CAT",
    "CBOE",
    "CBG",
    "CBS",
    "CELG",
    "CNC",
    "CNP",
    "CTL",
    "CERN",
    "CF",
    "SCHW",
    "CHTR",
    "CHK",
    "CVX",
    "CMG",
    "CB",
    "CHD",
    "CI",
    "XEC",
    "CINF",
    "CTAS",
    "CSCO",
    "C",
    "CFG",
    "CTXS",
    "CME",
    "CMS",
    "COH",
    "KO",
    "CTSH",
    "CL",
    "CMCSA",
    "CMA",
    "CAG",
    "CXO",
    "COP",
    "ED",
    "STZ",
    "GLW",
    "COST",
    "COTY",
    "CCI",
    "CSRA",
    "CSX",
    "CMI",
    "CVS",
    "DHI",
    "DHR",
    "DRI",
    "DVA",
    "DE",
    "DLPH",
    "DAL",
    "XRAY",
    "DVN",
    "DLR",
    "DFS",
    "DISCA",
    "DISCK",
    "DG",
    "DLTR",
    "D",
    "DOV",
    "DOW",
    "DPS",
    "DTE",
    # "DD",
    "DUK",
    "DNB",
    "ETFC",
    "EMN",
    "ETN",
    "EBAY",
    "ECL",
    "EIX",
    "EW",
    "EA",
    "EMR",
    "ETR",
    "EVHC",
    "EOG",
    "EQT",
    "EFX",
    "EQIX",
    "EQR",
    "ESS",
    "EL",
    "ES",
    "EXC",
    "EXPE",
    "EXPD",
    "ESRX",
    "EXR",
    "XOM",
    "FFIV",
    "FB",
    "FAST",
    "FRT",
    "FDX",
    "FIS",
    "FITB",
    "FSLR",
    "FE",
    "FISV",
    "FLIR",
    "FLS",
    "FLR",
    "FMC",
    "FTI",
    "FL",
    "F",
    "FTV",
    "FBHS",
    "BEN",
    "FCX",
    "FTR",
    "GPS",
    "GRMN",
    "GD",
    "GE",
    "GGP",
    "GIS",
    "GM",
    "GPC",
    "GILD",
    "GPN",
    "GS",
    "GT",
    "GWW",
    "HAL",
    "HBI",
    "HOG",
    "HAR",
    "HRS",
    "HIG",
    "HAS",
    "HCA",
    "HCP",
    "HP",
    "HSIC",
    "HES",
    "HPE",
    "HOLX",
    "HD",
    "HON",
    "HRL",
    "HST",
    "HPQ",
    "HUM",
    "HBAN",
    "IDXX",
    "ITW",
    "ILMN",
    "INCY",
    "IR",
    "INTC",
    "ICE",
    "IBM",
    "IP",
    "IPG",
    "IFF",
    "INTU",
    "ISRG",
    "IVZ",
    "IRM",
    "JBHT",
    "JEC",
    "SJM",
    "JNJ",
    "JCI",
    "JPM",
    "JNPR",
    "KSU",
    "K",
    "KEY",
    "KMB",
    "KIM",
    "KMI",
    "KLAC",
    "KSS",
    "KHC",
    "KR",
    "LB",
    "LLL",
    "LH",
    "LRCX",
    "LEG",
    "LEN",
    "LUK",
    "LVLT",
    "LLY",
    "LNC",
    "LLTC",
    "LKQ",
    "LMT",
    "L",
    "LOW",
    "LYB",
    "MTB",
    "MAC",
    "M",
    "MNK",
    "MRO",
    "MPC",
    "MAR",
    "MMC",
    "MLM",
    "MAS",
    "MA",
    "MAT",
    "MKC",
    "MCD",
    "MCK",
    "MJN",
    "MDT",
    "MRK",
    "MET",
    "MTD",
    "KORS",
    "MCHP",
    "MU",
    "MSFT",
    "MAA",
    "MHK",
    "TAP",
    "MDLZ",
    "MON",
    "MNST",
    "MCO",
    "MS",
    "MSI",
    "MUR",
    "MYL",
    "NDAQ",
    "NOV",
    "NAVI",
    "NTAP",
    "NFLX",
    "NWL",
    "NFX",
    "NEM",
    "NWSA",
    "NWS",
    "NEE",
    "NLSN",
    "NKE",
    "NI",
    "NBL",
    "JWN",
    "NSC",
    "NTRS",
    "NOC",
    "NRG",
    "NUE",
    "NVDA",
    "ORLY",
    "OXY",
    "OMC",
    "OKE",
    "ORCL",
    "PCAR",
    "PH",
    "PDCO",
    "PAYX",
    "PYPL",
    "PNR",
    "PBCT",
    "PEP",
    "PKI",
    "PRGO",
    "PFE",
    "PCG",
    "PM",
    "PSX",
    "PNW",
    "PXD",
    "PNC",
    "RL",
    "PPG",
    "PPL",
    "PX",
    "PCLN",
    "PFG",
    "PG",
    "PGR",
    "PLD",
    "PRU",
    "PEG",
    "PSA",
    "PHM",
    "PVH",
    "QRVO",
    "QCOM",
    "PWR",
    "DGX",
    "RRC",
    "RTN",
    "O",
    "RHT",
    "REG",
    "REGN",
    "RF",
    "RSG",
    "RAI",
    "RHI",
    "ROK",
    "COL",
    "ROP",
    "ROST",
    "RCL",
    "R",
    "SPGI",
    "CRM",
    "SCG",
    "SLB",
    "SNI",
    "STX",
    "SEE",
    "SRE",
    "SHW",
    "SIG",
    "SPG",
    "SWKS",
    "SLG",
    "SNA",
    "SO",
    "LUV",
    "SWN",
    "SWK",
    "SPLS",
    "SBUX",
    "STT",
    "SRCL",
    "SYK",
    "STI",
    "SYMC",
    "SYF",
    "SYY",
    "TROW",
    "TGT",
    "TEL",
    "TGNA",
    "TDC",
    "TSO",
    "TXN",
    "TXT",
    "BK",
    "CLX",
    "COO",
    "HSY",
    "MOS",
    "TRV",
    "DIS",
    "TMO",
    "TIF",
    "TWX",
    "TJX",
    "TMK",
    "TSS",
    "TSCO",
    "TDG",
    "RIG",
    "TRIP",
    "FOXA",
    "FOX",
    "TSN",
    "USB",
    "UDR",
    "ULTA",
    "UA",
    "UAA",
    "UNP",
    "UAL",
    "UNH",
    "UPS",
    "URI",
    "UTX",
    "UHS",
    "UNM",
    "URBN",
    "VFC",
    "VLO",
    "VAR",
    "VTR",
    "VRSN",
    "VRSK",
    "VZ",
    "VRTX",
    "VIAB",
    "V",
    "VNO",
    "VMC",
    "WMT",
    "WBA",
    "WM",
    "WAT",
    "WEC",
    "WFC",
    "HCN",
    "WDC",
    "WU",
    "WRK",
    "WY",
    "WHR",
    "WFM",
    "WMB",
    "WLTW",
    "WYN",
    "WYNN",
    "XEL",
    "XRX",
    "XLNX",
    "XL",
    "XYL",
    "YHOO",
    "YUM",
    "ZBH",
    "ZION",
    "ZTS"
])

AV_TIME_SERIES = {
    "INTRADAY":   "TIME_SERIES_INTRADAY",
    "DAILY":      "TIME_SERIES_DAILY",
    "DAILY_ADJ":  "TIME_SERIES_DAILY_ADJUSTED",
    "WEEKLY":     "TIME_SERIES_WEEKLY",
    "MONTHLY":    "TIME_SERIES_MONTHLY",
}
AV_TECHNICAL_INDICATORS = {
    "SimpleAverage":            "SMA",
    "ExponentialAverage":       "EMA",
    "WeightedAverage":          "WMA",
    "DoubleExpAverage":         "DEMA",
    "TripleExpAverage":         "TEMA",
    "TriangularAverage":        "TRIMA",
    "KaufmanAdaptiveAverage":   "KAMA",
    "MESAAdaptiveAverage":      "MAMA",  #optional: fastlimit, slowlimit, floats
    "TripleExp":                "T3"
}
AV_TIME_INTERVALS = {
    "ONE_MIN":        "1min",
    "FIVE_MIN":       "5min",
    "FIFTEEN_MIN":    "15min",
    "HALF_HOUR":      "30min",
    "HOUR":           "60min"
}
AV_SERIES_TYPES = {
    "open": "open",
    "close": "close",
    "high": "high",
    "low": "low"
}
class AlphaVantage:
    secret_key = "5SEHLSGGK55MEPL1"
    url = "https://www.alphavantage.co/query"

    def fetchStockInformation(self, symbol, function = AV_TIME_SERIES["INTRADAY"], interval = AV_TIME_INTERVALS["ONE_MIN"]):
        parameters = {
            "symbol":       symbol,
            "function":     function,
            "interval":     interval,
            "apikey":       self.secret_key
        }

        return requests.get(self.url, params=parameters).json()

    def fetchStockInformationTimeSeries(self, symbol, function = AV_TIME_SERIES["INTRADAY"], interval = AV_TIME_INTERVALS["ONE_MIN"]):
        info = self.fetchStockInformation(symbol, function, interval)
        low = []
        for k in info.keys():
            if "Time Series" in k:
                info = info[k]
                break
        for timeslot in sorted(info.items()):
            low += [float(timeslot[1]["3. low"])]

        return low
    
    def fetchStockTechnicalIndicator(self, symbol, function, interval = AV_TIME_INTERVALS["ONE_MIN"], time_period = 60, series_type = AV_SERIES_TYPES["open"]):
        parameters = {
            "function":     function,
            "symbol":       symbol,
            "interval":     interval,
            "time_period":  time_period,
            "series_type":  series_type,
            "apikey":       self.secret_key
        }

        return requests.get(self.url, params=parameters).json()

    def fetchStockTechIndTimeSeries(self, symbol, function, interval = AV_TIME_INTERVALS["ONE_MIN"], time_period = 60, series_type = AV_SERIES_TYPES["open"]):
        info = self.fetchStockTechnicalIndicator(symbol, function, interval, time_period, series_type)
        low = []
        for k in info.keys():
            if "Technical Analysis" in k:
                info = info[k]
                break

        for timeslot in sorted(info.items()):
            low += [float(timeslot[1][function])]

        return low


    def fetchSectorPerformances(self):
        parameters = {
            "function": "SECTOR",
            "apikey":   self.secret_key
        }

        return requests.get(self.url, params=parameters).json()

    def fetchStockCurrentPrice(self, symbol):
        r = self.fetchStockInformation(symbol)
        timeToLookUp = r["Meta Data"]["3. Last Refreshed"]
        return float(r["Time Series (1min)"][timeToLookUp]["4. close"])

    def fetchStockPercentDifference(self, symbol):
        r = self.fetchStockInformation(symbol)
        timeToLookUp = r["Meta Data"]["3. Last Refreshed"]
        close = float(r["Time Series (1min)"][timeToLookUp]["4. close"])
        open = float(r["Time Series (1min)"][timeToLookUp]["1. open"])
        return [open, close, close/open]

if __name__ == '__main__':
    av = AlphaVantage()

    # gra = Graph()
    # for stock in stock_names:
    #     stock_values = av.fetchStockPercentDifference(stock)
    #     stock_price = stock_values[1]
    #     stock_percent = stock_values[2]
    #     print ("stock {} has % diff of {}".format(stock, stock_percent))
    #
    #     newStock = {
    #         "name": stock,
    #         "percentDiff": stock_percent,
    #         "currentValue": stock_price
    #     }
    #     stocks += [newStock]
    #
    # edgeDiffThreshold = 1000
    # for s in stocks:
    #     gra.newVertex(s.name, s.currentValue)
    # gra.draw()


    # for left in range(0, len(stocks)):
    #     for right in range (left, len(stocks)):
    #         distance = abs(stocks[left] - stocks[right])

    # stock = stock_names[0]
    corrected = []
    for stock in stock_names:
        # print ("compiling info for {}".format(stock))
        # stock_values = av.fetchStockInformationTimeSeries(stock, function=AV_TIME_SERIES['DAILY'], interval=AV_TIME_INTERVALS['FIFTEEN_MIN'])
        try:
            stock_values = av.fetchStockTechIndTimeSeries(stock, function=AV_TECHNICAL_INDICATORS['SimpleAverage'], interval=AV_TIME_INTERVALS['FIFTEEN_MIN'], time_period=60, series_type=AV_SERIES_TYPES['open'])
            # print (stock_values)
            print ("writing info for {}, {} total lines".format(stock, len(stock_values)))
            with open ("../in/{}.log".format(stock), "w+") as f:
                for sv in stock_values:
                    f.write("{}\n".format(sv))
            corrected += [stock]
        except TypeError as te:
            print ("Error for stock {}".format(stock))
            pass

    print (json.dumps(corrected, indent = 3))
#    print (stock_values)


