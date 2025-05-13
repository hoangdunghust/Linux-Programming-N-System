// helpers.js
const os = require('os');
const net = require('net');

function getMyIP() {
    const interfaces = os.networkInterfaces();
    for (const iface of Object.values(interfaces)) {
        for (const conf of iface) {
            if (conf.family === 'IPv4' && !conf.internal) {
                return conf.address;
            }
        }
    }
    return 'Không tìm thấy IP';
}

function isValidIP(ip) {
    return net.isIP(ip) !== 0;
}

module.exports = { getMyIP, isValidIP };
