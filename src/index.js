const logger = require('./logger/logger');
const avClient = require('./clients/AlphaVantageClient');

const run = () => {
    logger.info('Starting');
    logger.info('getting apple information');
    let promises = [];
    promises.push(avClient.getInformationAbout({
        symbol: "AAPL"
    }));
    
    Promise.all(promises)
        .then((infos) => {
            console.log(JSON.stringify(infos[0]));
        })
        .catch((err) => {
            logger.error(err);
        });
        
    setTimeout(() => {
        logger.info("waited");
    }, 3000);
    
}

run();