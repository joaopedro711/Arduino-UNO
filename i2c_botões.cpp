// MENU COM TRÊS BOTÕES e I2C, usando display LCD


// Biblioteca para o display 
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

// Biblioteca para o TimerOne 
#include <TimerOne.h>

#define botao_MAIS 2                  //define o botão no pino 2 (MAIS)
#define botao_ENTER 3                 //define o botão no pino 3 (ENTER/VOLTAR)
#define botao_MENOS 4                 //define o botão no pino 4 (MENOS)
bool L_botao_MAIS = 1;                //variável para fazer a leitura do botão              (MAIS)
bool LA_botao_MAIS = 1;               //variável para verificar a leitura anterior do botão (MAIS)
bool L_botao_ENTER = 1;               //variável para fazer a leitura do botão              (ENTER/VOLTAR)
bool LA_botao_ENTER = 1;              //variável para verificar a leitura anterior do botão (ENTER/VOLTAR)
bool L_botao_MENOS = 1;               //variável para fazer a leitura do botão              (MENOS)
bool LA_botao_MENOS = 1;              //variável para verificar a leitura anterior do botão (MENOS)

int tela = 1;                         //variável para controlar a mudança de tela no menu

 
void setup(){ 
 pinMode(botao_MAIS, INPUT_PULLUP);   //define o botao (MAIS) como uma entrada pull up
 pinMode(botao_ENTER, INPUT_PULLUP);  //define o botao (ENTER/VOLTAR) como uma entrada pull up
 pinMode(botao_MENOS, INPUT_PULLUP);  //define o botao (MENOS) como uma entrada pull up
 lcd.begin (16,2);                    //inicia o display 16x2
   lcd.clear();                       //limpa todos os caracteres do lcd
   lcd.setCursor(0,0);                //posiciona o cursor no display (caracter, linha)      
   lcd.print(" SEJA BEM VINDO ");  //imprime o texto entre aspas  
   lcd.setCursor(0,1);                //posiciona o cursor no display (caracter, linha)      
   lcd.print(" Iniciando...   ");  //imprime o texto entre aspas 
 delay (3000);                        //pausa o programa por 3 segundos
}
 
void loop(){
 
 // === Ações no display LCD === // 
   if (tela==1){                          //se a variável tela for igual a MAIS, faça...
    lcd.setCursor(0,0);                    //posiciona o cursor no display (caracter, linha)      
    lcd.print("   << MENU >>   ");         //imprime o texto entre aspas 
    lcd.setCursor(0,1);                    //posiciona o cursor no display (caracter, linha)      
    lcd.print(">Primeira Opcao ");      //imprime o texto entre aspas 
   }
   else if (tela==2){                            
    lcd.setCursor(0,0);                     
    lcd.print("   << MENU >>   ");      
    lcd.setCursor(0,1);                     
    lcd.print(">Segunda Opcao  ");     
   }
   else if (tela==3){                            
    lcd.setCursor(0,0);                     
    lcd.print("   << MENU >>   ");      
    lcd.setCursor(0,1);                     
    lcd.print(">Terceira Opcao  ");     
   }
   else if (tela==10){                            
    lcd.setCursor(0,0);                     
    lcd.print(" :: PRIMEIRO :: ");      
    lcd.setCursor(0,1);                     
    lcd.print("  ESTUDE   ");     
   }
   else if (tela==20){  
    lcd.setCursor(0,0);                           
    lcd.print(" :: SEGUNDO ::  ");      
    lcd.setCursor(0,1);                     
    lcd.print("   SE PREPARE   ");     
   }
   else if (tela==30){
    lcd.setCursor(0,0);                              
    lcd.print(" :: TERCEIRO :: ");      
    lcd.setCursor(0,1);                     
    lcd.print(" NAO DESISTA ");     
   }
   
 /////////////////////////////////////////////////

 //  Ações do Botão MAIS 
  L_botao_MAIS = digitalRead(botao_MAIS);
  if (!L_botao_MAIS && LA_botao_MAIS) {
    if (tela==1)tela=2; 
    else if (tela==2)tela=3;
    else if (tela==3)tela=1;    
    delay(30);}                         
  LA_botao_MAIS = L_botao_MAIS; 


 /////////////////////////////////////////////////

 //  Ações do Botão MENOS 
  L_botao_MENOS = digitalRead(botao_MENOS);
  if (!L_botao_MENOS && LA_botao_MENOS) {
    if (tela==1)tela=3; 
    else if (tela==2)tela=1;
    else if (tela==3)tela=2;  
    delay(30);
  }                         
  LA_botao_MENOS = L_botao_MENOS;

     
 /////////////////////////////////////////////////

 // Ações do Botão ENTER 
  L_botao_ENTER = digitalRead(botao_ENTER);
  if (!L_botao_ENTER && LA_botao_ENTER) {
    if (tela==1)tela=10; 
    else if (tela==2)tela=20;
    else if (tela==3)tela=30;
    else if (tela==10)tela=1;
    else if (tela==20)tela=2;
    else if (tela==30)tela=3;         
    delay(30);
  }                         
  LA_botao_ENTER = L_botao_ENTER;
     
    

}
    
