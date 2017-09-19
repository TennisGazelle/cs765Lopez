#!/usr/bin/python3.4

import json
import requests
import shutil

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
    
    for d in sorted(appleInfo["Time Series (Daily)"].items()):
        low = low + [d[1]["3. low"]]
        high = high + [d[1]["2. high"]]
        
        
    print (json.dumps(low, indent = 3))
    
def getAppleInfo():
    api_key = "5SEHLSGGK55MEPL1"
    parameters = {
        "function": AV_TIME_SERIES["DAILY"],
        "symbol":   "AAPL",
        "interval": AV_TIME_INTERVALS["ONE_MIN"],
        "apikey":   api_key
    }
    
    r = requests.get('https://www.alphavantage.co/query', params=parameters)
    #r = requests.get("https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=" + api_key)
    
    #print (json.dumps(r.json(), indent = 3))
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
