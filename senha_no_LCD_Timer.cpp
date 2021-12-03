// Fechadura com display LCD e Timer

 
#include <TimerOne.h>

//Biblioteca para o display 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

//Bibliotecas para a senha e teclado matricial 
#include <Password.h> // Biblioteca utilizada para controle de senha
#include <Keypad.h> // Biblioteca para controle do teclado de matrizes

#define rele 11                              //define o rele para o pino 11

const byte LINHAS = 4;                       // Linhas do teclado
const byte COLUNAS = 4;                      // Colunas do teclado

Password senha = Password( "12345" );  // Senha utilizada para liberacao

const char teclas[LINHAS][COLUNAS] = { // Matriz de caracteres (mapeamento do teclado)
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

const byte PINOS_LINHAS[LINHAS] = {10, 9, 8, 6};   // Pinos de conexao com as linhas do teclado
const byte PINOS_COLUNAS[COLUNAS] = {5, 4, 3, 2};  // Pinos de conexao com as colunas do teclado

Keypad teclado = Keypad(makeKeymap(teclas), PINOS_LINHAS, PINOS_COLUNAS, LINHAS, COLUNAS); // Inicia teclado

int tela;
char leitura_teclas;

int minutos = 3;
int segundos = 0;                      //variável para contagem do tempo


void setup() {
  Timer1.initialize(1000000);          //obs.: 1000000 é igual a 1 segundo. E, 1000  é igual a 1 milissegundo
  Timer1.attachInterrupt(Timer);       //TimerOne é anexado ao "void Timer ()"
  lcd.begin (16,2);                           //inicia o display LCD 16x2
  lcd.clear();                                //limpa as informações no display
  pinMode (rele, OUTPUT);                     //configura o pino do rele como saida
  digitalWrite (rele, 1);
}

void loop() {

 //Telas possíveis no LCD 
   if (tela == 0){                        
     lcd.setCursor(0,0);                  
     lcd.print("     SENHA      "); 
     lcd.setCursor(0,1);                  
     lcd.print("     _____      ");
   }
   else if (tela == 1){     
     lcd.setCursor(5,1);                  
     lcd.print("*");
   }   
   else if (tela == 2){     
     lcd.setCursor(5,1);                  
     lcd.print("**");
   } 
   else if (tela == 3){     
     lcd.setCursor(5,1);                 
     lcd.print("***");
   } 
   else if (tela == 4){     
     lcd.setCursor(5,1);                  
     lcd.print("****");
   }
   else if (tela == 5){     
     lcd.setCursor(5,1);                 
     lcd.print("*****");
   }                 
   else if (tela == 6){    
     lcd.setCursor(0,0);                  
     lcd.print("ACESSO LIBERADO "); 
     lcd.setCursor(0,1);                  
     lcd.print("      ");
     lcd.print(minutos);
     lcd.print(":");
     if (segundos<10){
      lcd.print("0"); 
     }
     lcd.print(segundos);
     lcd.print("      ");
     
   }
   else if (tela == 7){     
     lcd.setCursor(0,0);                 
     lcd.print(" ACESSO NEGADO  "); 
     lcd.setCursor(0,1);                  
     lcd.print(" SENHA INCORRETA");
     delay (3000);
     lcd.clear();
     tela = 0;
   }

 // Ações do teclado      
 
   leitura_teclas = teclado.getKey();       //faz a leitura das teclas e guarda na variável leitura_teclas
  
   if(leitura_teclas>0){                    //se alguma tecla foi pressionada
      if (tela<5)
         tela++;                   //se a tela for menor que 5, some 1 ao seu valor
      
      if(leitura_teclas == 'C' && tela == 5){ //se a tecla 'C' foi pressionada e estamos na tela 5, faça...
         if(senha.evaluate())               //se a senha digitada estiver correta, faça...
            tela = 6;                           //muda para a tela 6    
         else                               //caso a senha esteja incorreta, faça...
          tela = 7;                          //muda para a tela 7
         senha.reset();                           //limpa a variavel senha
      
      } 
      else                                   //caso outra tecla tenha sido pressionada
         senha.append(leitura_teclas);          //salva o valor da tecla pressionada na variavel senha
  
      if(leitura_teclas == 'A' && tela == 6){   //caso pressione A e esteja na tela 6
         lcd.clear();                            //limpa o LCD
         tela = 0;                               //retorna para a tela inicial 
      }    //fim do if(leitura_teclas == 'A' && tela == 6)
   }       //fim do if(leitura_teclas>0)
}         //fim do void loop


void Timer (){                                  //nesse void as ações ocorrem em paralelo com o void loop
    if (tela == 6){                             //se a tela for igual a 6, faça...
        if (segundos > 0) {                     //se segundos for maior que zero, faça...
            segundos--;                             //subrai 1 do valor dos segundos
        }
        if (segundos == 0 && minutos > 0){      //se segundos for igual e zero E minutos maior que zero, faça...
            digitalWrite (rele, 0);                 //liga o módulo do rele
            minutos--;                              //subrai 1 do valor dos minutos
            segundos = 59;                          //iguala os segundos à 59
        }
        if (segundos == 0 && minutos == 0){     //se segundos for igual e zero E minutos igual a zero, faça...
            digitalWrite (rele, 1);                 //desliga o módulo do rele                 
            tela = 0;                               //retorna para a tela inicial
            minutos = 3;                            //retorna os minutos para 3
        }
     }
}
