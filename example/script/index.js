'use strict'

require('colors')
const config = require('./config.json')

let io
const datas = {
  stringData: 'foo',
  intData: 5,
  floatData: 0.5,
  boolData: true,
  nested: {
    hello: 'world'
  }
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
  .on('pongy', (data) => {
    console.log('pongy'.blue, data)
  })
})

const nsp = io.of('/nsp')
nsp.on('connection', function (socket) {
  console.log('connection from namespace /nsp'.bold.green)

  let emitInterval = setInterval(() => {
    socket.emit('nsping')
  }, 2000)

  socket
  .on('disconnect', () => {
    console.log('disconnect from namespace /nsp'.bold.red)
    clearInterval(emitInterval)
  })
  .on('nspong', (data) => {
    console.log('nspong'.blue)
  })
})
