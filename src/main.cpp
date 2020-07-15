
/* version 4.1 del tablero de LEDS 8x8 que incorpora:
*  8 circuitos integrados 74HC595 para escritura
*  8 circuitos integrados 74LS165 para lectura 
*  @autor: Jose Antonio Gonzales
*  @date: 7 julio 2020
*/

/*
******************************************** Librerias ********************************************
*/

#include <Arduino.h>

/*
******************************************** Entradas y salidas hardware ********************************************
*/

//Asignacion de pines del 74LS165 que controla la funcion general de lectura - DATA INPUT
const byte read_74HC165_01 = 5;  //Entrada carga en paralelo. Conecta el pin 5 de Arduino con el pin 1 del 74LS165
const byte read_74HC165_02 = 6;  //Entrda del pulso de reloj. Conecta el pin 6 de Arduino con el pin 2 del 74LS165
const byte read_74HC165_07 = 7;  //Entrada de datos - valor negado. Conecta el pin 7 de Arduino con el pin 7 del 74LS165
const byte read_74HC165_15 = 8;  //Habilita pulso reloj. Conecta el pin 8 de Arduino con el pin 15 del 74LS165

//Asignacion de pines del 74HC595 que controla la funcion general de escritura - DATA OUTPUT
const byte write_74HC595_14 = 2; //Salida serial. Conecta el pin 2 de Arduino con el pin 14 del 74HC595
const byte write_74HC595_12 = 3; //Seguro del pulso de salida. Latch. Conecta el pin 3 de Arduino con el pin 12 del 74HC595
const byte write_74HC595_11 = 4; // Pulso del reloj. Conecta el pin 4 del Arduino con el pin 11 del 74HC595

/*
******************************************** Definicion de constantes ********************************************
*/

const byte rows = 8; //Definicion del numero de filas de la matriz
const byte cols = 8; //Definicion del numero de colomunas de la matriz

#define t 1000 

/*
******************************************** Definicion de variables globales ********************************************
*/

byte row0 = B00000000;
byte row1 = B00000000;
byte row2 = B00000000;
byte row3 = B00000000;
byte row4 = B00000000;
byte row5 = B00000000;
byte row6 = B00000000;
byte row7 = B00000000;

byte bitValues[rows][cols] = {{B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000},
                              {B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000,B00000000}};

/*
******************************************** Funciones ********************************************
*/

// Prueba general, enciende todos los pixels del tablero
void test(){
  
  for(byte i = 0; i<rows; i++){
    for(byte j = 0; j<cols; j++){
      bitValues[i][j] = B11111111; 
    }
    delay(t);
  }

  for(byte i = 0; i<rows; i++){
    for(byte j = 0; j<cols; j++){
      bitValues[i][j] = B00000000; 
    }
    delay(t);
  }
}

// 

void test_write(byte row7, byte row6, byte row5, byte row4, byte row3, byte row2, byte row1, byte row0){
  
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row0);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row1);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row2);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row3);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row4);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row5);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row6);
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, row7); 
  
  digitalWrite(write_74HC595_12, HIGH);
  digitalWrite(write_74HC595_12, LOW);

/*
  shiftOut(write_74HC595_14, write_74HC595_11, LSBFIRST, 0);
  digitalWrite(write_74HC595_12, HIGH);
  digitalWrite(write_74HC595_12, LOW);
  delay(t);
  digitalWrite(write_74HC595_12, LOW);
  digitalWrite(write_74HC595_12, HIGH);  
  delay(t);
*/
}

void read(){

  digitalRead()

}


void read_2(){
  // Write pulse to load pin
  digitalWrite(read_74HC165_01,LOW);
  delayMicroseconds(5);
  digitalWrite(read_74HC165_01,HIGH);
  delayMicroseconds(5);
    // Get data from 74HC165
  digitalWrite(read_74HC165_02,HIGH);
  digitalWrite(read_74HC165_15,LOW);
  byte incoming = shiftIn(read_74HC165_07, read_74HC165_02, LSBFIRST);
  digitalWrite(read_74HC165_15,HIGH);

  // Print to serial monitor
  Serial.print("Pin States:\r\n");
  Serial.println(incoming, BIN);

}


/*
******************************************** Funcion iniciacion Arduino ********************************************
*/

void setup () {

  // Inicializacion del puerto serial
  Serial.begin(9600);

  // Asignacion entradas-salidas 74HC165
  pinMode(read_74HC165_01, OUTPUT);
  pinMode(read_74HC165_02, OUTPUT);
  pinMode(read_74HC165_07, INPUT);
  pinMode(read_74HC165_15, OUTPUT);

  // Asignacion entradas-salidas 74HC595
  pinMode(write_74HC595_11, OUTPUT);
  pinMode(write_74HC595_12, OUTPUT);
  pinMode(write_74HC595_14, OUTPUT);

}

/*
******************************************** Funcion ciclica Arduino ********************************************
*/

void loop() {

  test_write(row0, row1, row2, row3, row4, row5, row6, row7);
  delay(t);
  test_write(B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111, B11111111);
  delay(t);
  read_2();




}