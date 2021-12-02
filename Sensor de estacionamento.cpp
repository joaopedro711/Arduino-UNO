//Sensor de estacionamento com modulo HC-SR04 e Buzzer passivo


#define echo 4
#define trig 7
#define pierro 2

float tempo, distancia;

void setup(){
    Serial.begin(9600);
    pinMode(pierro, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(trig, OUTPUT);
}

void loop(){
    digitalWrite(trig, HIGH);
    delay(1000);
    digitalWrite(trig, LOW);

    //calculos
    tempo = pulseIn(echo, HIGH);    //pulseIn calcula a duração do pulso
    distancia = tempo * 0.01715;

    //condicionais a respeito da distancia
    if(distancia >= 150){
        digitalWrite(pierro,1);
        delay(2000);
        digitalWrite(pierro,0);
        delay(2000);
    }
    else if(distancia <= 149 && distancia > 120){
        digitalWrite(pierro,1);
        delay(1000);
        digitalWrite(pierro,0);
        delay(1000);
    }
    else if(distancia <= 119 && distancia > 100){
        digitalWrite(pierro,1);
        delay(500);
        digitalWrite(pierro,0);
        delay(500);
    }
    else if(distancia <= 99 && distancia > 60){
        digitalWrite(pierro,1);
        delay(250);
        digitalWrite(pierro,0);
        delay(250);
    }
    else if(distancia <= 59 && distancia > 40){
        digitalWrite(pierro,1);
        delay(125);
        digitalWrite(pierro,0);
        delay(125);
    }
    else{
        digitalWrite(pierro,1);
        delay(5);
        digitalWrite(pierro,0);
        delay(5);
    }

    //Mostra na tela a distancia que o sensor estar medindo
    Serial.println(distancia);
}