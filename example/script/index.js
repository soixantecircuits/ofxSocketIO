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

const simplyTheBest = [
  `I call you when I need you, my heart's on fire`,
  `You come to me, come to me wild and wired`,
  `Oh, you come to me`,
  `give me everything I need.`,
  `Give me a lifetime of promises and a world of dreams`,
  `Speak the language of love like you know what it means`,
  `And it can't be wrong, take my heart`,
  `And make it strong, baby`
]

io = require('socket.io')(config.server.port)
io.on('connection', function (socket) {
  console.log('connection'.bold.green)

  console.log('query:', socket.handshake.query)

  let emitInterval = setInterval(() => {
    socket.emit('server-event', datas)
    socket.emit('pingy')
  }, 2000)

  socket.emit('array-event', simplyTheBest)

  socket
  .on('disconnect', () => {
    console.log('disconnect'.bold.red)
    clearInterval(emitInterval)
  })
  .on('pongy', (data) => {
    console.log('pongy'.blue, data)
  })
  .on('tina', (lines) => {
    JSON.parse(lines).forEach(line => {
      console.log('tina'.green, line)
    })
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
