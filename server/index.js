

const express = require("express")
const app = express()
const socketIO= require("socket.io")
const http = require("http")
const servidor =http.createServer(app)
const io = socketIO.listen(servidor)
servidor.listen(3000, function(){
    console.log("servidor escuchando en puerto", 3000)
})

app.use(express.static(__dirname + "/public")) //aqui indicamos que public sera enviada a todos los clientes


/*
---- A PARTIR DE AQUI TENEMOS!!----
--- COMUNICACION SERIAL
--- TRAEMOS LA LECTURA SERIAL DE ARDUINO A NODE JS
---
*/
const serialport= require("serialport");
const parser= serialport.parsers.Readline// readline para tener cada lectura en una nueva linea 
const puerto = new serialport("COM3",{
    baudRate:9600,
})//inicializamos desde donde estiramos la lectura

const lectura = puerto.pipe(new parser({ delimeter:"\r\n"})) //pipe: tubo en En
    lectura.on("open",function()
    {
        console.log("conectado!")
    })

lectura.on("data",function(data){
    console.log(data);
    io.emit("lectura_serial", data)
})
puerto.on("error",function(err){
    console.log(err)
})
