
/* version 3.2 del tablero de LEDS 8x8 que incorpora 2 circuitos de desplazamiento de registro 74HC595
*  @autor: Jose Antonio Gonzales
*  @date: 3 junio 2020
*/

/*
******************************************** Librerias ********************************************
*/

#include <Arduino.h>


/*
******************************************** Entradas y salidas ********************************************
*/

//Asignacion de pines del 74HC595 que controla la salida de las filas
/*
  74HC595 & 74HC165 Shift Register Demonstration
  74hc595-to-74ch165.ino
  Input for 8 pushbuttons using 74HC165
  Output to 0 LEDs using 74HC595

  DroneBot Workshop 2020
  https://dronebotworkshop.com
*/

// Define Connections to 74HC165

// PL pin 1
int load = 7;
// CE pin 15
int clockEnablePin = 4;
// Q7 pin 7
int dataIn = 5;
// CP pin 2
int clockIn = 6;

// Define Connections to 74HC595

// ST_CP pin 12
const int latchPin = 10;
// SH_CP pin 11
const int clockPin = 11;
// DS pin 14
const int dataPin = 12;

void setup () {

  // Setup Serial Monitor
  Serial.begin(9600);

  // 74HC165 pins
  pinMode(load, OUTPUT);
  pinMode(clockEnablePin, OUTPUT);
  pinMode(clockIn, OUTPUT);
  pinMode(dataIn, INPUT);

  // 74HC595 pins
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

}


void loop() {

  // Read Switches

  // Write pulse to load pin
  digitalWrite(load, LOW);
  delayMicroseconds(5);
  digitalWrite(load, HIGH);
  delayMicroseconds(5);

  // Get data from 74HC165
  digitalWrite(clockIn, HIGH);
  digitalWrite(clockEnablePin, LOW);
  byte incoming = shiftIn(dataIn, clockIn, LSBFIRST);
  digitalWrite(clockEnablePin, HIGH);

  // Print to serial monitor
  Serial.print("Pin States:\r\n");
  Serial.println(incoming, BIN);


  // Write to LEDs

  // ST_CP LOW to keep LEDs from changing while reading serial data
  digitalWrite(latchPin, LOW);

  // Shift out the bits
  shiftOut(dataPin, clockPin, LSBFIRST, ~incoming);

  // ST_CP HIGH change LEDs
  digitalWrite(latchPin, HIGH);

  millis();

}