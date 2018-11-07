# TFG fachadas_dinamicas
##  app para una fachada cinetica
1. Modulo de server con [**SOCKET.IO**](https://socket.io).
1. Modelo cliente-Servidor con el framework [**EXPRESS**](http://expressjs.com/).
1. Datos del clima:   API  proveido por [DARKSKY](https://darksky.net)
## APP PASO A PASO

1. ejecutar en la terminal-> npm install pkg //para instalar el package [json](https://www.json.org/)
2. instalar la biblioteca serialport  y guardarlo-> npm install serialport --save //con lo cual tenemos el pkg lock.json
3. crear el folder server con el index.js para la lectura desde arduino requiriendo la libreria serialport
4. Para mostrar a una gran cantidad de clientes instalar express y tambien la libreria socket.io para tener un
una conexion en tiempo real npm install express socket.io
5. creamos el folder public hermano de server y creamos el archivo index.html
linkeamos con un script socket al archivo index.html y creamos main.js para el fronted
6. levantamos el servidor en el puerto 3000 con el comando node ./server/index.js
7. incluir libreria virtual wire.h para modulo de radio
8.Radio emisor forma parte del modulo PC-UNO:

  ###**MODULO RECEPTOR**
![EMISOR](http://www.tecnosurf.com/TFG/img/conexion_RF_serial.JPG)

### Observaciones
* debemos tener instalado node.js  (de hecho es un proyecto de node :) )
* si vamos en nuestra app en la ruta localhost:3000/socket.io/socket.io.js tenemos la libreria [socket](https://socket.io)
* Aplicaremos la biblioteca para servos varSpeedServo, que amplía la biblioteca estándar servo.h con la capacidad de configurar la velocidad y esperar a que se complete la posición de manera asincrona.
* aplicamos sockets por que a diferencia de la tecnologia ajax no depende de un evento del lado del cliente 
para mostrar los cambios.

