/* version 4.x del tablero de LEDS 8x8 que incorpora:
* 8 circuitos de desplazamiento 74HC595 para escritura
* 8 registros de desplazamiento 74LS165 para lectura
* Utilizacion del protocolo SPI 
* @autor: Jose Antonio Gonzales jzgonzales@gmail.com
* @date: julio 2020
*/

/*
******************************************** Librerias ********************************************
*/

#include <SPI.h>

/*
******************************************** Variables y constantes ********************************************
*/

const byte LATCH = 9;
const int rowSize = 8;

byte switchArray1 = B00000000;
byte switchArray2 = B00000000;
int bin = 0;

int state[rowSize] = { 0,0,0,0,0,0,0,0 };

/*
******************************************** Funciones ********************************************
*/

void viejaFuncion(){
  
  switchArray1 = SPI.transfer(0);
  switchArray2 = SPI.transfer(0);

  Serial.print(" 1 ");
  Serial.print(" Decimal ");
  Serial.print(switchArray1);
  Serial.print(" Binario: ");
  Serial.print(switchArray1, BIN);
  Serial.print(" Hexadecimal : ");
  Serial.println(switchArray1, HEX);

  Serial.print(" 2 ");
  Serial.print(" Decimal ");
  Serial.print(switchArray2);
  Serial.print(" Binario: ");
  Serial.print(switchArray2, BIN);
  Serial.print(" Hexadecimal : ");
  Serial.println(switchArray2, HEX);

}

int inputArrayState(){

  digitalWrite (LATCH, LOW); 
  digitalWrite (LATCH, HIGH);

  SPI.setBitOrder(LSBFIRST);
  switchArray1 = SPI.transfer(0);
  switchArray2 = SPI.transfer(0);
  for(byte i = 0; i<rowSize; i++){

    bin = bitRead(switchArray1,i); 
    Serial.print((String)"Estado pin " +  i + " : " );
    Serial.println(bin);
    
  }

  Serial.println("Arreglo: 1");
  return bin;
  delay (5000);  
}

/*
******************************************** Funciones ejecucion de Arduino ********************************************
*/

//funcion de inicializacion general Arduino - Hardware y software

void setup ()
{
  SPI.begin ();
  Serial.begin (115200);
  Serial.println ("Begin switch test.");
  pinMode (LATCH, OUTPUT);
  digitalWrite (LATCH, HIGH);
}
 


//funcion ciclica Arduino 

void loop ()
{
  inputArrayState();

} 