#include <Arduino.h>
//Asignacion de pines del 74HC595 que controla las filas
const int rowData  = 2;
const int rowLatch = 3;
const int rowClock = 4;

//Asignacion de pines del 74HC595 que controla las columnas
const int colData  = 5;
const int colLatch = 6;
const int colClock = 7;

//Tamano matriz
const byte rowSize = 8;
const byte colSize = 8;
const byte matrixArea = 64;

/*pin de lectura para switch
const int readA = 10;
const int readB = 11;
*/
const int readPinA = 13;
const int readPinB = 12;

/*
byte rowData [rowSize] = {};
byte colData [colSize] = {};
*/
byte switchState = B00000000;

//variables genericas
byte blankData = B00000000;
byte data = B00000000;

/*matriz de prueba escaneo completo 8x8, se implementan 2 arreglos separados uno para las filas y otro para las columnas
* los valores de bits de fila-columna para un pixel cualquiera son opuestos.
*/
byte scanTestRow[rowSize] = {    B10000000,
                                 B01000000,
                                 B00100000,
                                 B00010000,
                                 B00001000,
                                 B00000100,
                                 B00000010,
                                 B00000001
                                 }; 

byte scanTestCol[colSize] = {    B01111111,
                                 B10111111,
                                 B11011111,
                                 B11101111,
                                 B11110111,
                                 B11111011,
                                 B11111101,
                                 B11111110
                                 }; 


//Arreglo para filas y columnas
byte dataRow = B00000000;
byte dataCol = B00000000;

#define t 100

//Funcion de inicializacion del IC 74HC595 usado para las filas
void writeRow(byte blankData){
  
   shiftOut(rowData, rowClock, LSBFIRST, blankData);
   digitalWrite(rowLatch, HIGH);
   digitalWrite(rowLatch, LOW);
   
}

//Funcion de inicializacion del IC 74HC595 usado para las columnas
void writeCol(int blankData){
  
   shiftOut(colData, colClock, LSBFIRST, blankData);
   digitalWrite(colLatch, LOW);
   digitalWrite(colLatch, HIGH);
  
}

/*

funcion para probar todos los leds de la matrix, establece los valores de las filas en 1 y de cada una de las columnas en 0, de este modo la dupla fila 1,columna 0 enciende cada fila.
Si por ejemplo se cambia el valor de la n-fila a 0 y se mantiene todos los valores de la columna en 0 se apagara la n-fila colocada en 0 esto es:

   writeRow(B01111111);
   writeCol(B00000000);

   Resultado en la matriz de leds

      C1  C2  C3  C4  C5  C6  C7  C8
    F1 0   0   0   0   0   0   0   0
    F2 1   1   1   1   1   1   1   1
    F3 1   1   1   1   1   1   1   1
    F4 1   1   1   1   1   1   1   1
    F5 1   1   1   1   1   1   1   1
    F6 1   1   1   1   1   1   1   1
    F7 1   1   1   1   1   1   1   1
    F8 1   1   1   1   1   1   1   1

  La configuracion "opuesta" es decir, todas las filas en 1 y la primera columna en 1 resultara:

   writeRow(B11111111);
   writeCol(B10000000);

   Resultado en la matriz de leds

      C1  C2  C3  C4  C5  C6  C7  C8
    F1 0   1   1   1   1   1   1   1
    F2 0   1   1   1   1   1   1   1
    F3 0   1   1   1   1   1   1   1
    F4 0   1   1   1   1   1   1   1
    F5 0   1   1   1   1   1   1   1
    F6 0   1   1   1   1   1   1   1
    F7 0   1   1   1   1   1   1   1
    F8 0   1   1   1   1   1   1   1

  De este modo hemos establecido cual es la fila y columna 1 respecto de la matriz de LEDS.

  Es importante tener en cuenta que esta configuracion depende de los valores que determinenos para la combinacion de la dupla de paramtros LSBFIRST/MSBFIRST, MSBFIRST/LSBFIRST, MSBFIRST/MSBFIRST, LSBFIRST/LSBFIRST
   sobre las funciones writeRow/writeCol determinara el orden de punto de coordenadas (0,0) para la orientacion de tablero en particular.
*/
void turnOnFullMatrix(){
  
  // Se enciende todo el tablero 8x8 para probar la matriz de leds
  // La funcion asigna el bit del primer estado binario para las filas - enciende una esquina cruza estados fila/columna
  // La funcion asigna el bit de primer estado binario para las columnas

   writeRow(B11111111);
   writeCol(B00000000);
   delay(3000);
  
}

//funcion para apagar todos los leds de la matriz, establece todas las filas y columnas en bits de valor 0
void turnOffFullMatrix(){
  
  // Se borra todo el tablero 8x8
   writeRow(B00000000);
   writeCol(B00000000);
   delay(1000);
  
}

//funcion que realiza el recorrido de todos los pixels de la matriz
void scanMatrix(){
   //escaneo de la primera fila
   writeRow(B10000000);
   writeCol(B01111111);
   delay(t);
   writeRow(B10000000);
   writeCol(B10111111);
   delay(t);
   writeRow(B10000000);
   writeCol(B11011111);
   delay(t);
   writeRow(B10000000);
   writeCol(B11101111);
   delay(t);
   writeRow(B10000000);
   writeCol(B11110111);
   delay(t);
   writeRow(B10000000);
   writeCol(B11111011);
   delay(t);   
   writeRow(B10000000);
   writeCol(B11111101);
   delay(t);
   writeRow(B10000000);
   writeCol(B11111110);
   delay(t);
   //escaneo de la segunda fila
   writeRow(B01000000);
   writeCol(B01111111);
   delay(t);
   writeRow(B01000000);
   writeCol(B10111111);
   delay(t);
   writeRow(B01000000);
   writeCol(B11011111);
   delay(t);
   writeRow(B01000000);
   writeCol(B11101111);
   delay(t);
   writeRow(B01000000);
   writeCol(B11110111);
   delay(t);
   writeRow(B01000000);
   writeCol(B11111011);
   delay(t);   
   writeRow(B01000000);
   writeCol(B11111101);
   delay(t);
   writeRow(B01000000);
   writeCol(B11111110);
   delay(t);  
   //escaneo de la tercera fila
   writeRow(B00100000);
   writeCol(B01111111);
   delay(t);
   writeRow(B00100000);
   writeCol(B10111111);
   delay(t);
   writeRow(B00100000);
   writeCol(B11011111);
   delay(t);
   writeRow(B00100000);
   writeCol(B11101111);
   delay(t);
   writeRow(B00100000);
   writeCol(B11110111);
   delay(t);
   writeRow(B00100000);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00100000);
   writeCol(B11111101);
   delay(t);
   writeRow(B00100000);
   writeCol(B11111110);
   delay(t);
   //escaneo de la cuarta fila
   writeRow(B00010000);
   writeCol(B01111111);
   delay(t);
   writeRow(B00010000);
   writeCol(B10111111);
   delay(t);
   writeRow(B00010000);
   writeCol(B11011111);
   delay(t);
   writeRow(B00010000);
   writeCol(B11101111);
   delay(t);
   writeRow(B00010000);
   writeCol(B11110111);
   delay(t);
   writeRow(B00010000);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00010000);
   writeCol(B11111101);
   delay(t);
   writeRow(B00010000);
   writeCol(B11111110);
   delay(t);   
   //escaneo de la quinta fila
   writeRow(B00001000);
   writeCol(B01111111);
   delay(t);
   writeRow(B00001000);
   writeCol(B10111111);
   delay(t);
   writeRow(B00001000);
   writeCol(B11011111);
   delay(t);
   writeRow(B00001000);
   writeCol(B11101111);
   delay(t);
   writeRow(B00001000);
   writeCol(B11110111);
   delay(t);
   writeRow(B00001000);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00001000);
   writeCol(B11111101);
   delay(t);
   writeRow(B00001000);
   writeCol(B11111110);
   delay(t);   
   //escaneo de la sexta fila
   writeRow(B00000100);
   writeCol(B01111111);
   delay(t);
   writeRow(B00000100);
   writeCol(B10111111);
   delay(t);
   writeRow(B00000100);
   writeCol(B11011111);
   delay(t);
   writeRow(B00000100);
   writeCol(B11101111);
   delay(t);
   writeRow(B00000100);
   writeCol(B11110111);
   delay(t);
   writeRow(B00000100);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00000100);
   writeCol(B11111101);
   delay(t);
   writeRow(B00000100);
   writeCol(B11111110);
   delay(t); 
   //escaneo de la septima fila
   writeRow(B00000010);
   writeCol(B01111111);
   delay(t);
   writeRow(B00000010);
   writeCol(B10111111);
   delay(t);
   writeRow(B00000010);
   writeCol(B11011111);
   delay(t);
   writeRow(B00000010);
   writeCol(B11101111);
   delay(t);
   writeRow(B00000010);
   writeCol(B11110111);
   delay(t);
   writeRow(B00000010);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00000010);
   writeCol(B11111101);
   delay(t);
   writeRow(B00000010);
   writeCol(B11111110);
   delay(t); 
   //escaneo de la octava fila
   writeRow(B00000001);
   writeCol(B01111111);
   delay(t);
   writeRow(B00000001);
   writeCol(B10111111);
   delay(t);
   writeRow(B00000001);
   writeCol(B11011111);
   delay(t);
   writeRow(B00000001);
   writeCol(B11101111);
   delay(t);
   writeRow(B00000001);
   writeCol(B11110111);
   delay(t);
   writeRow(B00000001);
   writeCol(B11111011);
   delay(t);   
   writeRow(B00000001);
   writeCol(B11111101);
   delay(t);
   writeRow(B00000001);
   writeCol(B11111110);
   delay(t);            

}

/*
void readState(){


   Serial.println("entra caso 1");
   if (readA == 0 && readB == 0){
      Serial.print("0,0:");
   }
   Serial.println("entra caso 2");
   if (readA == 0 && readB == 1){
      Serial.print("0,1:");
   }
   Serial.println("entra caso 3");
   if (readA == 1 && readB == 0){
      Serial.print("1,0:"); 
   }
   Serial.println("entra caso 4");
   if (readA == 1 && readB == 1){
      Serial.print("0,0:");
   }
   
}
*/

/*funcion para probar el recorrido de filas y columnas por medio de ciclos
* reemplaza a la funcion scanMatrix
*/
void scanArray(){

   for(int i = 0; i< rowSize; i++){

      dataRow = scanTestRow[i];
      writeRow(dataRow);
      dataCol = scanTestCol[i];
      writeCol(dataCol);
      delay(t);

      for(int j = 0; j<colSize; j++){

         dataRow = scanTestRow[i];
         writeRow(dataRow);
         dataCol = scanTestCol[j];
         writeCol(dataCol);
         delay(t);

      }
   }

}

//Funcion para determinar visualmente cual es la coordenada (0,0) del tablero de lEDS
void cornerTest(){
  
   int readA = 0;
   int readB = 0;

  //identifica el primer led prendiendo mas tiempo
   writeRow(B00000001);
   writeCol(B01111111);
   delay(t);
   /*writeRow(B00000001);
   writeCol(B11111110);
   delay(300);
   */
   readA = digitalRead(readPinA);
   Serial.println("---");
   Serial.print("A"); 
   Serial.print(readA);
   Serial.println("***");
   readB = digitalRead(readPinB);
   Serial.print("B");
   Serial.print(readB);
   Serial.println("***");
}

//funcion setup arduino se ejecuta al inicio una vez
void setup(){
  
  Serial.begin(9600);
  Serial.print("inicia lectura");
  //Asignacion puertos IC 74HC595 como salida para el control de filas
   pinMode(rowData, OUTPUT);
   pinMode(rowLatch, OUTPUT);
   pinMode(rowClock, OUTPUT);
  //Asignacion puertos IC 74HC595 como salida para el control de columnas
   pinMode(colData, OUTPUT);
   pinMode(colLatch, OUTPUT);
   pinMode(colClock, OUTPUT);
   // Asignacion de los puertos para lectura del estado del led
   pinMode(readPinA, INPUT);
   pinMode(readPinB, INPUT);
   //Prueba de tablero
   turnOnFullMatrix();
   delay(t*10);
   turnOffFullMatrix();
  
}

//Funcion ciclica de arduino
void loop(){
   scanArray();   
}