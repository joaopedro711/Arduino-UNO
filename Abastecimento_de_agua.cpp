#include <LiquidCrystal.h> // Inclusão da biblioteca do LCD
LiquidCrystal lcd (2, 3, 4, 5, 6, 7); // define os pinos de envio de dados do LCD

#define Bomba1_LED 12
#define Bomba2_LED 11
#define Bomba3_LED 10
#define Alarme_Max 8
#define Alarme_Min 9
#define POT A2

void setup() {

  lcd.begin(16, 2); // declara que o LCD contém 16 linhas e 2 colunas
  lcd.setCursor(0, 0); // declara que o cursor do LCD estará na linha 0 e coluna 0
  lcd.print("Volume em Litros"); // Imprime na tela do LCD a informação "Volume em Litros"

  pinMode(Bomba1_LED, OUTPUT); // declara que a variável Bomba1_LED é uma saída
  pinMode(Bomba2_LED, OUTPUT); // declara que a variável Bomba2_LED é uma saída
  pinMode(Bomba3_LED, OUTPUT); // declara que a variável Bomba3_LED é uma saída
  pinMode(Alarme_Max, OUTPUT); // declara que a variável Alarme_Max é uma saída
  pinMode(Alarme_Min, OUTPUT); // declara que a variável Alarme_Min é uma saída
  pinMode(POT, INPUT); // declara que a variável POT é uma entrada
}

void loop() {

  int nivel = analogRead (POT); // Declara a variável nivel como sendo a do potenciômetro

  if (nivel >= 1) { // Se o nível do reservatório for >= 1 imprime no LCD a variável nível (valor do potenciômetro)
    lcd.setCursor(7, 16);
    lcd.print(nivel);
    lcd.print("               "); //imprime espaço em branco para limpar a coluna 2
  }

  if ((nivel <= 200) && (nivel >= 1)) { // Se o nível do reservatório for <= a 200 "E" >= a 1, todas as bombas ligam
    digitalWrite (Bomba1_LED, HIGH);
    digitalWrite (Bomba2_LED, HIGH);
    digitalWrite (Bomba3_LED, HIGH);
  }
  else if (nivel >= 201) { // Se não o nível do reservatório for >= a 201, a Bomba 1 e 3 desligam
    digitalWrite (Bomba1_LED, LOW);
    digitalWrite (Bomba3_LED, LOW);
  }

  if ((nivel <= 150) && (nivel >= 1)) { // Se o nível do reservatório for <= a 150 "E" >= 1 o alarme mínimo aciona
    tone (Alarme_Min, 440); // toca alarme em 440 Hz
  }

  else if (nivel >= 200) { // Se não o nível do reservatório for >= a 200 o alarme mínimo desliga
    noTone (Alarme_Min); // desliga alarme mínimo
  }

  if (nivel == 900) { // Se o nível do reservatório for == a 900, a bomba 2 desliga
    digitalWrite (Bomba2_LED, LOW);
  }

  if (nivel >= 950) { // Se o nível do reservatório for >= 950 o alarme máximo aciona
    tone (Alarme_Max, 440); // toca alarme em 440 Hz
    lcd.setCursor(0, 0);

    lcd.print("Reservatorio Cheio");
  }

  else if (nivel < 950) { // Se não o nível do reservatório for < que 950 o alarme máximo desliga
    noTone (Alarme_Max); // desliga alarme máximo
  }
}