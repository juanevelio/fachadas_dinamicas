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
    console.log(data)
})
puerto.on("error",function(err){
    console.log(err)
})
