'use strict'

const config = require('./config.json')
const colors = require('colors')
let io
const datas = [{
  stringData: "foo",
  intData: 5,
  floatData: 0.5,
  boolData: true
}]

io = require('socket.io')(config.server.port)
io.on('connection', function (socket) {
  console.log('connection'.bold.green)

  let emitInterval = setInterval(() => {

    socket.emit('server-event', datas)
  }, 2000)

  socket.on('disconnect', () => {
    console.log('disconnect'.bold.red)
    clearInterval(emitInterval)
  })
})

