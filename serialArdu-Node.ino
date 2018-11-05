

int contador;
void setup() {
  // put your setup code here, to run once:
pinMode(13,OUTPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
for(int i = 0; i<=200; i+=30)
{
  digitalWrite(13, HIGH);
delay(i);
digitalWrite(13, LOW);
delay(i);
Serial.println(i);
  
  }
  for(int i = 200; i>=0; i-=30)
{
  digitalWrite(13, HIGH);
delay(i);
digitalWrite(13, LOW);
delay(i);
Serial.println(i);
  
  }
}
