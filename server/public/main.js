//por este lado tenemos el fronted o cliente

const socket= io()
socket.on("lectura_serial",function(data){
    let serial = document.querySelector("#lectura")
    serial.innerHTML= data.toString()
})
