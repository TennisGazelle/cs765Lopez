#!/usr/bin/python3.4

import json
import requests
import shutil
import numpy as np
import matplotlib.pyplot as plt

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
    appleInfo = getAppleInfo()
    low = []
    high = []
    openP = []
    close = []
    
    highest = 0
    lowest = 10000
    for d in sorted(appleInfo["Time Series (5min)"].items()):
        openP = openP + [float(d[1]["1. open"])]
        high = high + [float(d[1]["2. high"])]
        low = low + [float(d[1]["3. low"])]
        close = close + [float(d[1]["4. close"])]
        highest = max([highest, openP[-1], high[-1], low[-1], close[-1]])
        lowest = min([lowest, openP[-1], high[-1], low[-1], close[-1]])

    print ("range is ({},{})".format(lowest, highest))        
        
    #print (json.dumps(low, indent = 3))
    extra = 0.05 * (highest - lowest)
    plt.fill_between(range(0, len(low)), low, high, facecolor='black')
    plt.plot(range(0, len(openP)), openP, linewidth=2.0)
    plt.plot(range(0, len(close)), close, linewidth=2.0)
    plt.axis([0, len(low), lowest - extra, highest + extra])
    plt.show()
    
def getAppleInfo():
    api_key = "5SEHLSGGK55MEPL1"
    parameters = {
        "function": AV_TIME_SERIES["INTRADAY"],
        "symbol":   "AAPL",
        "interval": AV_TIME_INTERVALS["FIVE_MIN"],
        "apikey":   api_key
    }
    
    r = requests.get('https://www.alphavantage.co/query', params=parameters)
    #r = requests.get("https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=" + api_key)
    
    print (json.dumps(r.json(), indent = 3))
    print ("url:", r.url)
    return r.json()

def movie_main():
    movie_title = raw_input("What movie do you want to know more about?: ")

    movie_request = {
        't' : movie_title,
        'plot' : 'full',
        'tomatoes' : True,
        'r' : 'json'
    }

    r = requests.get('http://omdbapi.com/', params=movie_request, verify=False)
    print ("The URL was:", r.url)
    print (json.dumps( r.json(), indent = 3 ))

    print ("this is the url ", r.json()['Poster'])

    local_pic = movie_title + ' picture.jpg'

    pic = requests.get( r.json()["Poster"], stream=True )
    with open( local_pic, 'wb' ) as outfile:
        shutil.copyfileobj( pic.raw, outfile )

    #Image.open( local_pic ).show()


    #r = requests.get('https://api.github.com/user', auth=('user','pass'))
    #print r.headers
    #print r.encoding
    #print r.text

def main():
     stock_main()

if __name__ == '__main__':
    main()
