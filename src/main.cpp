// Demo sketch to read from a 74HC165 input shift register
// Author: Nick Gammon
// Date:   23 March 2013

// Pin connections for Uno and similar:

// Chip pin 1 (/PL)  goes to LATCH (D9)  (or any other pin by changing LATCH below)
// Chip pin 2 (CP)   goes to SCK   (D13)
// Chip pin 9 (Q7)   goes to MISO  (D12)

// Pin connections for Mega2560:

// Chip pin 1 (/PL)  goes to LATCH (D9)  (or any other pin by changing LATCH below)
// Chip pin 2 (CP)   goes to SCK   (D52)
// Chip pin 9 (Q7)   goes to MISO  (D50)


#include <SPI.h>

const byte LATCH = 9;

const int rowSize = 8;

int state[rowSize] = { 0,0,0,0,0,0,0,0 };



void setup ()
{
  SPI.begin ();
  Serial.begin (115200);
  Serial.println ("Begin switch test.");
  pinMode (LATCH, OUTPUT);
  digitalWrite (LATCH, HIGH);
}

byte switchArray1;
byte switchArray2; // previous state

void loop ()
{
  digitalWrite (LATCH, LOW);    // pulse the parallel load latch
  digitalWrite (LATCH, HIGH);
  
  SPI.setBitOrder(LSBFIRST);
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

  delay (30);   // debounce
}  // end of loop