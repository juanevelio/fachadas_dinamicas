//para flashear arduino hay que instalar el paquete Firmata 
//luego podemos resetear la memoria de arduino uno
// para esto ejecutamos firmata no --debug
const board = require("firmata");
board.requestPort(function(error, port)
{
    if(error)
    {
        console.log(error)
    }
    else return;
}
