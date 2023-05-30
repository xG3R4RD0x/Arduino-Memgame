#include <Arduino.h>
#include <stdlib.h>
#include <LED.h>


const int buttonPins[] = {PB0, PB1, PB2, PB3}; // Pin Buttons Definition
const int ledPins[] = {PA0, PA1, PA8, PA9, PA5, PA6}; // Pin Leds Definition
const int resetButtonPin = PB4; // Reset Pin definition
const int timerLedPin = PA4; // Timer Led Definition
const int numButtons = sizeof(buttonPins) / sizeof(int); // Number of Game Buttons

void setup() {
  for (int i = 0; i < numButtons; i++) {
    pinMode(buttonPins[i], INPUT); // Button Pins as Pull-Up input configuration
  }
  
  pinMode(resetButtonPin, INPUT); // Reset Button Pins as Pull-Up input configuration
  pinMode(timerLedPin, OUTPUT); // Timer Led as Output configuration

  for (int i = 0; i < numButtons; i++) {
    pinMode(ledPins[i], OUTPUT); // Game Leds as output configuration
  }

  randomSeed(analogRead(PA4)); // Random Number seed generation
}

void loop() {
  bool reset = false;
  while (digitalRead(resetButtonPin) == LOW) {
    reset = true;
  }

  if (reset) {
    for (int i = 0; i < numButtons; i++) {
      digitalWrite(ledPins[i], LOW); // Apagamos todos los LEDs
    }
    digitalWrite(timerLedPin, LOW); // Apagamos el LED del temporizador
    delay(1000); // Esperamos un segundo para asegurarnos de que el botón de reinicio se haya soltado
  } else {
    int sequenceLength = random(3, 11); // Generamos un número aleatorio de 3 a 10 para determinar la longitud de la secuencia
    int sequence[sequenceLength]; // Creamos un array para guardar la secuencia
    for (int i = 0; i < sequenceLength; i++) {
      sequence[i] = random(0, numButtons); // Generamos un número aleatorio del 0 al 3 para representar un botón/LED
    }

    for (int i = 0; i < sequenceLength; i++) {
      digitalWrite(ledPins[sequence[i]], HIGH); // Encendemos el LED correspondiente al número generado
      delay(500); // Esperamos medio segundo
      digitalWrite(ledPins[sequence[i]], LOW); // Apagamos el LED
      delay(500); // Esperamos otro medio segundo
    }

    bool success = true;
    int timerDelay = 10000 / sequenceLength; // Calculamos el tiempo límite para ingresar la secuencia
    int timerBlinkDelay = timerDelay / 10; // Calculamos el tiempo de parpadeo del LED del temporizador
    for (int i = 0; i < sequenceLength; i++) {
           int buttonPressed = waitForButtonPress(timerDelay); // Esperamos a que se presione un botón, con un límite de tiempo
      
      if (buttonPressed != sequence[i]) { // Si el botón presionado no es el que corresponde en la secuencia
        success = false;
        break;
      }
      
      digitalWrite(ledPins[sequence[i]], HIGH); // Encendemos el LED correspondiente al número generado
      delay(500); // Esperamos medio segundo
      digitalWrite(ledPins[sequence[i]], LOW); // Apagamos el LED
      delay(500); // Esperamos otro medio segundo
    }
    
    if (success) { // Si se ingresó correctamente la secuencia
      digitalWrite(timerLedPin, LOW); // Apagamos el LED del temporizador
      digitalWrite(ledPins[numButtons - 1], HIGH); // Encendemos el LED verde
      delay(1000); // Esperamos un segundo
      digitalWrite(ledPins[numButtons - 1], LOW); // Apagamos el LED verde
    } else { // Si no se ingresó correctamente la secuencia
      digitalWrite(timerLedPin, LOW); // Apagamos el LED del temporizador
      digitalWrite(ledPins[numButtons - 2], HIGH); // Encendemos el LED rojo
      delay(1000); // Esperamos un segundo
      digitalWrite(ledPins[numButtons - 2], LOW); // Apagamos el LED rojo
    }
  }
}

int waitForButtonPress(int timeout) {
  int timer = 0;
  while (timer < timeout) { // Mientras no se haya superado el límite de tiempo
    for (int i = 0; i < numButtons; i++) {
      if (digitalRead(buttonPins[i]) == LOW) { // Si se presiona un botón
        return i;
      }
    }
    digitalWrite(timerLedPin, HIGH); // Encendemos el LED del temporizador
    delay(100); // Esperamos 100 ms
    digitalWrite(timerLedPin, LOW); // Apagamos el LED del temporizador
    delay(100); // Esperamos otros 100 ms
    timer += 200; // Incrementamos el temporizador
  }
  return -1; // Si no se presionó ningún botón en el tiempo límite, devolvemos -1
}

