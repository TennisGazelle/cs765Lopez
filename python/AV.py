#!/usr/bin/python3.4

import json
import requests

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

av = AlphaVantage()
print (av.fetchStockInformation("AAPL", interval = AV_TIME_INTERVALS["ONE_MIN"]))