# TFG fachadas_dinamicas
##  app para una fachada cinetica
* Modulo de server con socket.io
* Modelo cliente-Servidor con Express

## APP PASO A PASO

1. ejecutar en la terminal-> npm install pkg //para instalar el package json
2. instalar la biblioteca serialport  y guardarlo-> npm install serialport --save //con lo cual tenemos el pkg lock.json
3. crear el folder server con el index.js para la lectura desde arduino requiriendo la libreria serialport
4. Para mostrar a una gran cantidad de clientes instalar express y tambien la libreria socket.io para tener un
una conexion en tiempo real npm install express socket.io
5. creamos el folder public hermano de server y creamos el archivo index.html
linkeamos con un script socket al archivo index.html y creamos main.js para el fronted
6. levantamos el servidor en el puerto 3000 con el comando node ./server/index.js
7. incluir libreria virtual wire.h para modulo de radio

### Observaciones
* debemos tener instalado node.js  (de hecho es un proyecto de node :) )
* si vamos en nuestra app en la ruta localhost:3000/socket.io/socket.io.js tenemos la libreria socket
* Aplicaremos la biblioteca para servos varSpeedServo, que amplía la biblioteca estándar servo.h con la capacidad de configurar la velocidad y esperar a que se complete la posición de manera asincrona.
* aplicamos sockets por que a diferencia de la tecnologia ajax no depende de un evento del lado del cliente 
para mostrar los cambios.
*datos del clima con API  proveido por (DARKSKY)[https://api.darksky.net]
