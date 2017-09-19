const logger = require('./logger/logger');
const avClient = require('./clients/AlphaVantageClient');

const run = () => {
    logger.info('Starting');
    logger.info('getting apple information');
    let promises = [];
    promises.push(avClient.getInformationAbout({
        symbol: "AAPL"
    }));

    flag = true;
    
    Promise.all(promises)
        .then((infos) => {
            console.log(JSON.stringify(infos));
            flag = false;
        })
        .catch((err) => {
            logger.error(err);
            flag = false;
        });
        
    setTimeout(() => {
        logger.info("waited");
    }, 3000);

    while (flag);
    
}



run();