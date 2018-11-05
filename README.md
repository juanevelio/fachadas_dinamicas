# TFG fachadas_dinamicas
##  app para una fachada dinamica
* Modulo de server con socket.io
* Modelo cliente-Servidor con Express

APP PASO A PASO
  1. ejecutar en la terminal-> npm install pkg //para instalar el package json
  2. instalar la biblioteca serialport  y guardarlo-> npm install serialport --save //con lo cual tenemos el pkg lock.json
  3. crear el folder server con el index.js para la lectura desde arduino requiriendo la libreria serialport
  4. Para mostrar a una gran cantidad de clientes instalar express y tambien la libreria socket.io para tener un
  una conexion en tiempo real npm install express socket.io
  5. creamos el folder public hermano de server y creamos el archivo index.html
  Obs: debemos tener instalado node.js  (de hecho es un proyecto de node :) )
