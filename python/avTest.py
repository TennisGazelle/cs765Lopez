#!/usr/bin/python3.4

import json
import requests
import shutil
import numpy as np
import matplotlib.pyplot as plt
from graph_tool.all import *

AV_TIME_SERIES = {
    "INTRADAY":   "TIME_SERIES_INTRADAY",
    "DAILY":      "TIME_SERIES_DAILY",
    "DAILY_ADJ":  "TIME_SERIES_DAILY_ADJUSTED",
    "WEEKLY":     "TIME_SERIES_WEEKLY",
    "MONTHLY":    "TIME_SERIES_MONTHLY"
}

AV_TIME_INTERVALS = {
    "ONE_MIN":        "1min",
    "FIVE_MIN":       "5min",
    "FIFTEEN_MIN":    "15min",
    "HALF_HOUR":      "30min",
    "HOUR":           "60min"
}

def stock_main():
    appleInfo = getStockInfo("AAPL")
    low = []
    high = []
    open = []
    close = []
    
    highest = 0
    lowest = 10000
    for d in sorted(appleInfo["Time Series (5min)"].items()):
        open = open + [float(d[1]["1. open"])]
        high = high + [float(d[1]["2. high"])]
        low = low + [float(d[1]["3. low"])]
        close = close + [float(d[1]["4. close"])]
        highest = max([highest, open[-1], high[-1], low[-1], close[-1]])
        lowest = min([lowest, open[-1], high[-1], low[-1], close[-1]])

    print ("range is ({},{})".format(lowest, highest))

    ug = Graph(directed = False)
    vertex_name = ug.new_vertex_property("string")
    vertex_value = ug.new_vertex_property("float")
    ug.vertex_properties["name"] = vertex_name
    ug.vertex_properties["value"] = vertex_value
    
    v1 = ug.add_vertex()
    vertex_name[v1] = "APPL"
    vertex_value[v1] = high[-1]

    v2 = ug.add_vertex()
    vertex_name[v2] = "NEW STOCK"
    vertex_value[v2] = "100"

    edge = ug.add_edge(v1, v2)

    graph_draw(ug, vertex_text = ug.vertex_properties["name"], vertex_font_size = 18, output_size = (600, 600), output = "graph.png")

    extra = 0.05 * (highest - lowest)
    plt.fill_between(range(0, len(low)), low, high, facecolor='black')
    plt.plot(range(0, len(open)), open, linewidth=0.5)
    plt.plot(range(0, len(close)), close, linewidth=0.5)
    plt.axis([0, len(low), lowest - extra, highest + extra])
    #plt.show()
    
def getStockInfo(symbol):
    api_key = "5SEHLSGGK55MEPL1"
    parameters = {
        "symbol":   symbol,
        "function": AV_TIME_SERIES["INTRADAY"],
        "interval": AV_TIME_INTERVALS["ONE_MIN"],
        "apikey":   api_key
    }
    
    r = requests.get('https://www.alphavantage.co/query', params=parameters)
    #r = requests.get("https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=" + api_key)
    
    #print (json.dumps(r.json(), indent = 3))
    #print ("url:", r.url)
    return r.json()['Meta Data']


def main():
    #stock_main()
    stock_names = [
        "M",
        "LMT",
        "GRUB",
        "TVIAQ",
        "T",
        "BUD",
        "MMM",
        "SHOO"
    ]
        #"CCV",
    #stock = stock_names[-1]
    for stock in stock_names:
        print(json.dumps(getStockInfo(stock), indent = 3))

if __name__ == '__main__':
    main()
