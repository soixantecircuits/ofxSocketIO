'use strict'

require('colors')
const config = require('./config.json')

let io
const datas = {
  stringData: 'foo',
  intData: 5,
  floatData: 0.5,
  boolData: true
}

io = require('socket.io')(config.server.port)
io.on('connection', function (socket) {
  console.log('connection'.bold.green)

  console.log('query:', socket.handshake.query)

  let emitInterval = setInterval(() => {
    socket.emit('server-event', datas)
    socket.emit('pingy')
  }, 2000)

  socket
  .on('disconnect', () => {
    console.log('disconnect'.bold.red)
    clearInterval(emitInterval)
  })
  .on('pong', (data) => {
    console.log('pongy'.blue, data)
  })
})

