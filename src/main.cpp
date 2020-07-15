/* Programa Demo para leer desde 74HC165
   Autor: Nick Gammon
   Fecha: 23 Marzo 2013

   Conexiones para Uno y similares:
   Chip pin 1 (SH/LD)  conectado a LATCH (8) queda igual
   Chip pin 2 (CLK)   conectado a SCK (13) antes en 12
   Chip pin 9 (QH)   conectado a MISO (12) antes en 11

   Conexiones para Mega2560:
   Chip pin 1 (SH/LD)  conectado a LATCH (8)
   Chip pin 2 (CLK)   conectado a (52)
   Chip pin 9 (QH)   conectado a (50)
*/

#include <SPI.h>

const byte LATCH = 8;

void setup()
{
  SPI.begin();
  Serial.begin(9600);
  Serial.println ("Comienza la prueba de entradas");
  pinMode(LATCH, OUTPUT);
  digitalWrite(LATCH, HIGH);
}

byte bancoEntradas1;
// agregar declaracion: byte bancoEntradas2;
// agregar declaracion: byte bancoEntradas3;
// agregar declaracion: byte bancoEntradas4;
byte bancoEntradas1Viejo; // estado previo

void loop()
{
  digitalWrite (LATCH, LOW);
  digitalWrite (LATCH, HIGH); // pulso en carga paralela
  bancoEntradas1 = SPI.transfer(0);
  //  donde se debe agregar: bancoEntradas2 = SPI.transfer(0);
  //  donde se debe agregar: bancoEntradas3 = SPI.transfer(0);
  //  donde se debe agregar: bancoEntradas4 = SPI.transfer(0);
  
  byte mascara = 1;
  for (int i = 1; i <= 8; i++) {
    if ((bancoEntradas1 & mascara) != (bancoEntradas1Viejo & mascara))
      {
      Serial.print ("Llave ");
      Serial.print (i);
      Serial.print (" ahora ");
      Serial.println ((bancoEntradas1 & mascara) ? "cerrada" : "abierta");
      }  // fin de "el bit ha cambiado"
    mascara <<= 1;  
    }  // final para cada bit
  
  bancoEntradas1Viejo = bancoEntradas1;
  delay (1000);
}