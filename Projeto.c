#define DECODE_NEC

#if !defined(RAW_BUFFER_LENGTH)
#define RAW_BUFFER_LENGTH 100
#define RAW_BUFFER_LENGTH  112    // MagiQuest requires 112 bytes.
#endif

#define EXCLUDE_UNIVERSAL_PROTOCOLS   // Saves up to 1000 bytes program space.
#define EXCLUDE_EXOTIC_PROTOCOLS      // saves around 650 bytes program space if all other protocols are active

#include <LiquidCrystal.h>
#include <math.h>

LiquidCrystal lcd_1(12, 11, 5, 4, 3, 2);

int response = 0;

void setup()
{
  	Serial.begin(115200);
  	lcd_1.begin(16, 2);
    
  	pinMode(A3, INPUT); // sensor de temperatura
  	pinMode(A2, INPUT); // sensor de umidade
  	pinMode(5, OUTPUT);
  	pinMode(10, OUTPUT); // piezo
  	pinMode(6, OUTPUT); // motor

  	lcd_1.noCursor();
}

void loop() {
  	int umidade = analogRead(A2);
  	float temperatura = get_temperatura();
  
  	lcd_1.setCursor(0, 0);
  	lcd_1.print(temperatura);
  	lcd_1.print(" C     ");
  	lcd_1.setCursor(0, 1);
  
    if (temperatura >= 25) {
      	digitalWrite(10, HIGH);
    } else {
      	digitalWrite(10, LOW);
    }
  	
  	if (umidade <= 292) {
      	lcd_1.print("Irrigando...");
      	digitalWrite(6, HIGH);
    } else {
      	digitalWrite(6, LOW);
    }
  
  	if (umidade >= 584) {
      	lcd_1.print("Alta umidade");
    }
  	
  
    _delay_ms(10);
}

float get_temperatura() {
 	float temp = analogRead(A3);
  
  	temp = (double)temp / 1024.0; // conversão A/D
  	temp = temp * 5;  // tensão
  	temp = temp - 0.5; // aproximação
  	temp = temp * 100;  // converte para Celsius
  
  	return round(temp);
}

void show_tmp(float temperatura) {
  	lcd_1.setCursor(0, 0);
  	lcd_1.print("1. Temperatura");
  	lcd_1.setCursor(0, 1);
  	lcd_1.print(" ");
  	lcd_1.print(temperatura);
  	lcd_1.print(" C     ");
}