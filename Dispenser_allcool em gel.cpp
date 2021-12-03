//Dispenser de alcool em gel automatico com micro servo

// Inclusão de bibliotecas 
#include "Ultrasonic.h"
#include <Servo.h>
 
 
#define pinButton 3
#define pinEcho 4
#define pinTrigger 5
#define pinServo 6
#define pinLED 7
 
//Instanciando objetos
Servo servo;
Ultrasonic ultrasonic(pinTrigger, pinEcho);
 

boolean aux1 = 0;
volatile uint16_t aux2 = 0;
volatile byte cicles;
volatile byte i;
 
 
//Funcoes
uint16_t readSensorandCompare();
void alcoolTrigger(byte maxAgle, byte minAngle);
void interface();
 
void setup() {
  Serial.begin(9600);
  servo.attach(pinServo);
  servo.write(100);//Posição inicial do Servo de 100°
 
  //Entradas/Saídas digitais
  pinMode(pinLED, OUTPUT);
  pinMode(pinButton, INPUT_PULLUP);
 
  // Inicial interrupção externa no pino 3 e chama a função ISR0 //
  attachInterrupt(digitalPinToInterrupt(pinButton), ISR0, FALLING);
}
 
//Interrupt Service Rotine ISR
void ISR0() {
  aux2++;
  if ( aux2 > 2)aux2 = 0;
 
  if (aux2 == 0)cicles = 1;
  if (aux2 == 1)cicles = 2;
  if (aux2 == 2)cicles = 3;
 
  i = 0;
}
 
void loop(){
  readSensorandCompare();
  interface();
 
  delay(300); // Evita mais de um disparo por vez pois limita as leituras do sensor ultrassônico
}//endloop
 
// Função que obtem a distância do sensor ultrassônico e compara valores para chamar outras funções ==//
uint16_t readSensorandCompare(){
  uint16_t distanceCM = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
  Serial.print("aux2: ");
  Serial.print(aux2);
  Serial.print("  Cicles: ");
  Serial.print(cicles);
  Serial.print("  distanceCM: ");
  Serial.println(distanceCM);
 
  //Se mínimo está selecionado
  if (distanceCM < 10  && aux1 == 0 && aux2 == 0){
    alcoolTrigger(100, 80);
  }
  //Se médio está selecionado
  if (distanceCM < 10  && aux1 == 0 && aux2 == 1){
    alcoolTrigger(100, 70);
  }
  //Se máximo está selecionado
  if (distanceCM < 10  && aux1 == 0 && aux2 == 2){
    alcoolTrigger(100, 60);
  }
  //Permite o servo motor atuar de novo somente quando tirar a mão da frente do sensor
  if (distanceCM > 16 ){
    aux1 = 0;
  }
 
  return distanceCM;
}
 
//Função aciona o servo motor de acordo com o angulo fornecido, também aciona o LED ==//
void alcoolTrigger(byte maxAgle, byte minAngle){
  digitalWrite(pinLED, HIGH);
  servo.write(maxAgle);
  delay(300);
  servo.write(minAngle);
  delay(300);
  servo.write(maxAgle);
  digitalWrite(pinLED, LOW);
  aux1 = 1;
}
 
//Função que pisca o LED de acordo com a configuração feita pelo usuário: minimo, médio, máximo ====//
void interface(){
  if ( i < cicles){
    digitalWrite(pinLED, HIGH);
    delay(200);
    digitalWrite(pinLED, LOW);
    delay(100);
    i++;
  }
}
