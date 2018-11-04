 
#include <Servo.h> 
// Incluímos la librería servo.h
# define tiempo_1 10;

Servo servoMotor;
// Declaramos la variable para controlar el servo


//funcion de configuraciones e inicializacion
void setup() {
  /*Iniciamos el monitor serie en 9600 baudios La tasa de baudios (en inglés baud rate)
 ―también conocida como baudaje― es el número de unidades de señal por segundo.*/
  Serial.begin(9600);

  // Iniciamos el servo en el pin 9
  servoMotor.attach(9);
}

void loop() {
  
  // Desplazamos a la posición 0º
  servoMotor.write(0);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 90º
  servoMotor.write(90);
  // Esperamos 1 segundo
  delay(1000);
  
  // Desplazamos a la posición 180º
  servoMotor.write(180);
  // Esperamos 1 segundo
  delay(1000);
 
 // Vamos a tener dos bucles uno para mover en sentido positivo y otro en sentido negativo
  // Para el sentido positivo
  for (int i = 0; i <= 180; i++)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
    // Hacemos una pausa de "tiempo_1 milisegundos"
    delay(tiempo_1);
  }
 
  // Para el sentido negativo
  for (int i = 179; i > 0; i--)
  {
    // Desplazamos al ángulo correspondiente
    servoMotor.write(i);
   // Hacemos una pausa de "tiempo_1 milisegundos"
    delay(tiempo_1);
  }
}
