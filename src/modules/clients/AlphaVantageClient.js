import {
    AV_TIME_INTERVALS,
    AV_TIME_SERIES
} from '../constants/AVConstants';
const logger = require('./../logger/logger');

class AlphaVantageClient {
    constructor() {
        this.baseUrl = 'https://www.alphavantage.co/query';
        this.apiKey = '5SEHLSGGK55MEPL1';
    }
    
    fetch(url, { method = "GET", body = null } = {}) {
        //logger.info('asking url:' + url);
        return new Promise((resolve, reject) => {
            logger.info("FETCHING....");
            fetch(url, {
                method,
                headers: {
                    'Accept': 'application/json'
                },
                body: JSON.stringify(body)
            })
            .then((res) => {
                logger.info(res);
                resolve(res)
            })
            .catch((err) => {
                logger.error('Error in fetching: URL:' + url + ' ' + err);
                reject(err);
            });
        });
    }
    
    getQueryParamString(params) {
        let result = "?"
        Object.keys(params).forEach((key) => {
            result += key + "=" + params[key] + "&"
        })
        return result.slice(0, -1);
    }
    
    getInformationAbout({ symbol, func = AV_TIME_SERIES.DAILY, interval = AV_TIME_INTERVALS.ONE_MIN }) {
        const params = {
            symbol,
            "function": func,
            interval,
            apikey: this.apiKey
        };
        const url = this.baseUrl + this.getQueryParamString(params);
        
        return new Promise((resolve, reject) => {
            this.fetch(url)
            .then((info) => {
                return info
            })
            .catch((err) => {
                return err;
            });
        });
    }
}

const avClient = new AlphaVantageClient();
module.exports = avClient;