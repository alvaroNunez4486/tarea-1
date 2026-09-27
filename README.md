"
Proyecto Simón Dice - Arduino UNO

Este repositorio contiene la implementación del juego de memoria secuencial "Simón Dice" sobre la plataforma Arduino UNO. El sistema procesa secuencias aleatorias, recibe las entradas del usuario y genera respuestas visuales y auditivas.

Esquema de Hardware y Conexiones
LEDs (Salidas): 
    Pin 2: LED Rojo (Resistencia limitadora 220 Ω)
    Pin 3: LED Azul (Resistencia limitadora 220 Ω)
    Pin 4: LED Amarillo (Resistencia limitadora 220 Ω)
Pulsadores (Entradas): 
   Pines 5, 6 y 7 conectados a GND utilizando la resistencia interna "INPUT_PULLUP".
Buzzer: 
   Pin 8 para frecuencias de audio (PWM).

Lógica de Software y Optimización
Antirrebote: Filtro por software de 50 ms para evitar lecturas falsas mecánicas.
Gestión de Memoria: Variables de control tipo "uint8_t" (1 byte) para optimizar el uso de SRAM en el ATmega328P.
Aleatoriedad: Semilla inicializada mediante lectura analógica flotante en "A0".

"
