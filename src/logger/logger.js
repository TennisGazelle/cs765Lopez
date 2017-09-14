const colors = require('colors');

class Logger {
  constructor () {
    this.levels = {
      INFO: 'INFO',
      WARN: 'WARN',
      ERROR: 'ERROR',
      LOG: 'LOG'
    };
  }
  createMessage (level, message) {
    const d = new Date();
    const timestamp = (d.getMonth() + 1) + '/' + (d.getDate()) + '/' + d.getFullYear() + ' ' + d.getHours() + ':' + (d.getMinutes() + 1) + ':' + d.getSeconds() + ':' + d.getMilliseconds();
    return '[' + timestamp + ' ' + level + '] ' + message;
  }
  info (message) {
    console.log(colors.cyan(this.createMessage(this.levels.INFO, message)));
  }
  warn (message) {
    console.log(colors.yellow(this.createMessage(this.levels.WARN, message)));
  }
  error (message) {
    console.log(colors.red(this.createMessage(this.levels.ERROR, message)));
  }
  log (message) {
    console.log(this.createMessage(this.levels.LOG, message));
  }
}

const logger = new Logger();

module.exports = logger;
