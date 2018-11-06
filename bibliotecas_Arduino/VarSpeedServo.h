/ *
  VarSpeedServo.h - Biblioteca de Servo controlada por interrupciones para Arduino usando temporizadores de 16 bits - Versión 2
  Derechos de autor (c) 2009 Michael Margolis. Todos los derechos reservados.
  Esta biblioteca es software libre; puedes redistribuirlo y / o
  modificarlo bajo los términos del público general menor de GNU
  Licencia publicada por la Free Software Foundation; ya sea
  versión 2.1 de la Licencia, o (a su elección) cualquier versión posterior.
  Esta biblioteca se distribuye con la esperanza de que sea útil,
  pero SIN NINGUNA GARANTÍA; sin siquiera la garantía implícita de
  COMERCIABILIDAD o APTITUD PARA UN PROPÓSITO PARTICULAR. Ver el GNU
  Lesser General Public License para más detalles.
  Debería haber recibido una copia del Público General Menor de GNU
  Licencia junto con esta biblioteca; Si no, escribe al Software Libre
  Foundation, Inc., 51 Franklin St, quinto piso, Boston, MA 02110-1301 EE. UU.
* /


/ *
  Función de slowmove y código de soporte agregado 2010 por Korman. Las limitaciones anteriores se aplican
  a todo el código agregado, excepto el mantenedor oficial de la biblioteca Servo. Si él,
  y solo él considera que la mejora es una buena idea para agregar a la biblioteca oficial de Servo,
  puede agregarlo sin el requisito de nombrar al autor de las partes original para
  Esta versión de la biblioteca.
* /

/ *
  Actualizado 2013 por Philip van Allen (pva), 
  - actualizado para Arduino 1.0 +
  - slowmove consolidado en el comando de escritura (mientras se mantiene slowmove () para compatibilidad
     con la versión de Korman)
  - se agregó el parámetro de espera para permitir que el comando de escritura se bloquee hasta que se complete el movimiento
  - Se agregó la capacidad de reproducción de secuencia para mover asíncronamente el servo a través de una serie de posiciones, se debe llamar en un bucle
  
  Un servo se activa al crear una instancia de la clase Servo que pasa el pin deseado al método attach ().
  Los servos se pulsan en segundo plano usando el valor escrito más recientemente usando el método write ()
  Tenga en cuenta que la escritura analógica de PWM en los pines asociados con el temporizador se deshabilita cuando se conecta el primer servo.
  Los temporizadores se utilizan según sea necesario en grupos de 12 servos: 24 servos usan dos temporizadores, 48 ​​servos usarán cuatro.
  La secuencia utilizada para silenciar los temporizadores se define en timers.h
  Los métodos son:
   VarSpeedServo - Clase para la manipulación de servomotores conectados a pines Arduino.
   adjuntar (pin): conecta un servomotor a un pin de E / S.
   adjuntar (pin, mín., máx.): se conecta a los valores mínimo y máximo de un pin en microsegundos
   el valor predeterminado mínimo es 544, máximo es 2400  
 
   write (valor) - Establece el ángulo del servo en grados. (el ángulo no válido que es válido como pulso en microsegundos se trata como microsegundos)
   escritura (valor, velocidad): la velocidad varía la velocidad del movimiento a la nueva posición 0 = velocidad completa, 1-255 más lento a más rápido
   write (valor, velocidad, espera) - espera es un valor lógico que, si es verdadero, hace que la función de llamada se bloquee hasta que se complete el movimiento
   writeMicroseconds () - Establece el ancho del pulso del servo en microsegundos 
   read () - Obtiene el último ancho de pulso del servo escrito como un ángulo entre 0 y 180. 
   readMicroseconds (): obtiene el último ancho de pulso del servo escrito en microsegundos. (fue read_us () en el primer lanzamiento)
   agregado () - Devuelve verdadero si hay un servo adjunto. 
   detach (): evita que los servos conectados pulsen su pin de E / S. 
   movimiento lento (valor, velocidad): igual que escritura (valor, velocidad), retenido por compatibilidad con la versión de Korman
   detener () - detiene el servo en la posición actual
   sequencePlay (secuencia, secuencia de posiciones); // Reproducir una secuencia de bucle comenzando en la posición 0
   sequencePlay (secuencia, secuencia de posiciones, bucle, startPosition); // reproducir la secuencia con el número de posiciones, bucle si es verdadero, comenzar en la posición
   sequenceStop (); // detener la secuencia en la posición actual
 * /

# ifndef VarSpeedServo_h
# define  VarSpeedServo_h

# include  < inttypes.h >

/ * 
 * Se define para los temporizadores de 16 bits utilizados con la biblioteca Servo. 
 *
 * Si se define _useTimerX, TimerX es un temporizador de 16 bits en el tablero actual
 * timer16_Sequence_t enumera la secuencia a la que deben asignarse los temporizadores
 * _Nbr_16timers indica cuántos temporizadores de 16 bits están disponibles.
 *
 * /

// Decir qué temporizadores de 16 bits se pueden usar y en qué orden
# si está definido (__ AVR_ATmega1280__) || definido (__ AVR_ATmega2560__)
# define  _useTimer5
# define  _useTimer1 
# define  _useTimer3
# define  _useTimer4 
typedef  enum {_timer5, _timer1, _timer3, _timer4, _Nbr_16timers} timer16_Sequence_t;

# elif definido (__ AVR_ATmega32U4__)  
# define  _useTimer3
# define  _useTimer1 
typedef  enum {_timer3, _timer1, _Nbr_16timers} timer16_Sequence_t;

# elif definido (__ AVR_AT90USB646__) || definido (__ AVR_AT90USB1286__)
# define  _useTimer3
# define  _useTimer1
typedef  enum {_timer3, _timer1, _Nbr_16timers} timer16_Sequence_t;

# elif definido (__ AVR_ATmega128__) || definido (__ AVR_ATmega1281 __) || definido (__ AVR_ATmega2561__)
# define  _useTimer3
# define  _useTimer1
typedef  enum {_timer3, _timer1, _Nbr_16timers} timer16_Sequence_t;

# else   // todo lo demás
# define  _useTimer1
typedef  enum {_timer1, _Nbr_16timers} timer16_Sequence_t;                  
# endif

# define  VarSpeedServo_VERSION            2       // versión de software de esta biblioteca

# define  MIN_PULSE_WIDTH        544      // el impulso más corto enviado a un servo  
# define  MAX_PULSE_WIDTH       2400      // el pulso más largo enviado a un servo
# define  DEFAULT_PULSE_WIDTH   1500      // ancho de pulso predeterminado cuando se conecta el servo
# define  REFRESH_INTERVAL     20000      // tiempo mínimo para actualizar los servos en microsegundos

# define  SERVOS_PER_TIMER        12      // el número máximo de servos controlados por un temporizador
# define  MAX_SERVOS    (_Nbr_16timers * SERVOS_PER_TIMER)

# define  INVALID_SERVO          255      // indicador que indica un índice de servo no válido

# define  CURRENT_SEQUENCE_STOP    255     // usado para indicar que la secuencia actual no se usa y la secuencia debería detenerse


typedef  struct   {
  uint8_t nbr: 6 ;             // un número de pin de 0 a 63
  uint8_t isActive: 1 ;             // verdadero si este canal está habilitado, pin no pulsado si es falso
} ServoPin_t;  

typedef  struct {
  ServoPin_t Pin;
   ticks int sin firmar ;
	 valor int sin firmar ;			// Extensión para espera externa (Gill)
	unsigned  int target;			// Extensión para slowmove
	uint8_t speed;					// Extensión para slowmove
} servo_t ;

typedef  struct {
  posición uint8_t ;
  uint8_t speed;
} servoSequencePoint;

clase  VarSpeedServo
{
público:
  VarSpeedServo ();
  uint8_t  attach ( int pin);           // adjuntar el pin dado al siguiente canal libre, establece pinMode, devuelve el número de canal o 0 si falla
  uint8_t  attach ( int pin, int min, int max); // como arriba, pero también establece los valores mínimo y máximo para las escrituras.
   desvinculación del vacío ();
   escritura nula ( valor int );             // si el valor es <200 se trata como un ángulo, de lo contrario, como ancho de pulso en microsegundos
   escritura vacía ( valor int , uint8_t velocidad); // Mover a la posición dada a velocidad reducida.
          // velocidad = 0 es idéntico a escritura, velocidad = 1 más lenta y velocidad = 255 más rápida.
          // En el RC-Servos probado, las diferencias de velocidad por encima de 127 no se pueden notar,
          // por los límites mecánicos del servo.
   escritura nula ( valor int , uint8_t speed, bool wait); // el parámetro de espera hace que la llamada se bloquee hasta que se complete el movimiento
  void  writeMicroseconds ( valor int ); // Ancho de pulso de escritura en microsegundos
  void  slowmove ( valor int , uint8_t speed);
   parada vacía (); // detén el servo donde está
  
  int  leer ();                        // devuelve el ancho del pulso actual como un ángulo entre 0 y 180 grados
  int  readMicroseconds ();            // devuelve el ancho de pulso actual en microsegundos para este servo (fue read_us () en la primera versión)
  bool  adjunta ();                   // devuelve true si este servo está adjunto, de lo contrario false

  uint8_t  sequencePlay (servoSequencePoint sequenceIn [], uint8_t numPositions, bool loop, uint8_t startPos);
  uint8_t  sequencePlay (servoSequencePoint sequenceIn [], uint8_t numPositions); // Reproducir una secuencia de bucle comenzando en la posición 0
  void  sequenceStop (); // detener el movimiento
   espera vacía (); // espera a que termine el movimiento  
  bool  isMoving (); // devuelve true si el servo sigue moviéndose
privado:
   uint8_t servoIndex;               // indexar en los datos del canal para este servo
   int8_t min;                       // mínimo es este valor multiplicado por 4 agregado a MIN_PULSE_WIDTH    
   int8_t max;                       // máximo es este valor multiplicado por 4 agregado a MAX_PULSE_WIDTH
   servoSequencePoint * curSequence; // para secuencias
   uint8_t curSeqPosition; // para secuencias

};

# endif
