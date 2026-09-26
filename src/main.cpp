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

// FUNCIONES AUXILIARES DE SONIDO Y LUZ
void encenderElemento(byte indice, int duracion) {
  digitalWrite(LED_PINS[indice], HIGH);
  tone(BUZZER_PIN, TONOS[indice]);
  delay(duracion);
  digitalWrite(LED_PINS[indice], LOW);
  noTone(BUZZER_PIN);
}

void reproducirSecuencia() {
  for (int i = 0; i < nivelActual; i++) {
    encenderElemento(secuencia[i], 400);
    delay(200);
  }
}

// LECTURA DE BOTONES CON ANTIRREBOTE (DEBOUNCE)
int leerBotonConDebounce() {
  while (true) {
    for (byte i = 0; i < 3; i++) {
      // El botón presionado manda una señal LOW al estar en PULLUP
      if (digitalRead(BUTTON_PINS[i]) == LOW) {
        delay(50); // Tiempo de espera antirrebote
        
        if (digitalRead(BUTTON_PINS[i]) == LOW) {
          encenderElemento(i, 300);
          
          // Esperar a que el usuario suelte el botón
          while (digitalRead(BUTTON_PINS[i]) == LOW);
          delay(50);
          
          return i; // Devuelve el índice del botón presionado
        }
      }
    }
  }
}

// SECUENCIA DE PERDIDA (GAME OVER)
void juegoTerminado() {
  tone(BUZZER_PIN, 150, 600);
  
  for (int i = 0; i < 3; i++) {
    for (byte j = 0; j < 3; j++) {
      digitalWrite(LED_PINS[j], HIGH);
    }
    delay(150);
    for (byte j = 0; j < 3; j++) {
      digitalWrite(LED_PINS[j], LOW);
    }
    delay(150);
  }
  
  nivelActual = 0; // Reinicia el nivel
  delay(1000);
}


// BUCLE PRINCIPAL DEL JUEGO
void loop() {
  // 1. Agregar nuevo paso aleatorio a la secuencia
  secuencia[nivelActual] = random(0, 3);
  nivelActual++;

  delay(500);

  // 2. Mostrar la secuencia acumulada al usuario
  reproducirSecuencia();

  // 3. Esperar y verificar las entradas del usuario
  for (int i = 0; i < nivelActual; i++) {
    int botonPresionado = leerBotonConDebounce();

    if (botonPresionado != secuencia[i]) {
      juegoTerminado();
      return;
    }
  }

  // 4. Sonido de éxito al completar el nivel
  tone(BUZZER_PIN, 523, 150); delay(150);
  tone(BUZZER_PIN, 784, 300); delay(300);
  delay(500);
}