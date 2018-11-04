 
#include <Servo.h> 
// Incluímos la librería servo.h


Servo servoMotor;
// Declaramos la variable para controlar el servo


//funcion de configuraciones e inicializacion
void setup() {
  // Iniciamos el monitor serie en 9600 baudios
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
}
