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

stock_names = [
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
    # "LGF.A",
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
]

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
    for stock in stock_names:
        print ("compiling info for {}".format(stock))
        stock_values = av.fetchStockInformationTimeSeries(stock, function=AV_TIME_SERIES['DAILY'], interval=AV_TIME_INTERVALS['HOUR'])
        print ("writing info for {}".format(stock))
        with open ("../in/{}.log".format(stock), "w+") as f:
            for sv in stock_values:
                f.write("{}\n".format(sv))

#    print (stock_values)


