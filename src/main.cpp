#include <Arduino.h>

// 📌 Configuración de Pines
const uint8_t LED_PINS[3]    = {2, 3, 4}; // Pins para LEDs: Rojo(2), Azul(3), Amarillo(4)
const uint8_t BUTTON_PINS[3] = {5, 6, 7}; // Pins para Botones: Rojo(5), Azul(6), Amarillo(7)
const uint8_t BUZZER_PIN     = 8;        // Pin para el Zumbador

const int TONOS[3] = {261, 329, 392};    // Tonos para cada color (Do, Mi, Sol)

uint8_t secuencia[100];                  // Arreglo para guardar la secuencia
uint8_t nivelActual = 0;                 // Contador de nivel del juego


// SETUP: CONFIGURACIÓN INICIAL DEL HARDWARE
void setup() {
  for (byte i = 0; i < 3; i++) {
    pinMode(LED_PINS[i], OUTPUT);
    digitalWrite(LED_PINS[i], LOW);
    
    // INPUT_PULLUP activa la resistencia interna del Arduino
    pinMode(BUTTON_PINS[i], INPUT_PULLUP);
  }
  
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Usar entrada analógica no conectada para aleatoriedad
  randomSeed(analogRead(A0));
}

void loop() {
  // Se completará en los siguientes commits
}