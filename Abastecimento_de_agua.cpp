//Sistema de abastecimento de reservatorio de agua

int ledverde = 11;
int ledvermelho = 12;
int motor = 13;
int sensorbaixo = 6;
int sensoralto = 7;


int a, b;

void setup(){
    pinMode(ledverde, OUTPUT);
    pinMode(ledvermelho, OUTPUT);
    pinMode(motor, OUTPUT);
    pinMode(sensoralto, INPUT);
    pinMode(sensorbaixo, INPUT);
    digitalWrite(sensorbaixo, HIGH);
    digitalWrite(sensoralto, HIGH);
}

void loop(){
    a = digitalRead(sensorbaixo);   //0 == se esta enchendo, 1 == vazia
    b = digitalRead(sensoralto);    //0 == nivel apice da caixa

    //se a caixa estiver vazia
    if((a == LOW || a == HIGH) && b == LOW)
        ligamotor();

    //se a caixa estiver cheia    
    else if(a == HIGH && b == HIGH)
        desligamotor();

    //caso os sensores deem diferentes    
    else if(a == LOW && b == HIGH)
        erro();

}

void ligamotor(){
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledvermelho, LOW);
    digitalWrite(motor, HIGH);
}
void desligamotor(){
    digitalWrite(ledverde, LOW);
    digitalWrite(ledvermelho, HIGH);
    digitalWrite(motor, LOW);
}
void erro(){
    digitalWrite(ledverde, HIGH);
    digitalWrite(ledvermelho, HIGH);
    digitalWrite(motor, LOW);
}