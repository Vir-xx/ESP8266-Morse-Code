#include <ESP8266WiFi.h>

#define LED D5

void blinkMorse(String text);
void dot();
void dash();
void space();

struct MorseCode {
  char letter;
  const char* code;
};

MorseCode morseTable[] = {
  {'A', ".-"},   {'B', "-..."}, {'C', "-.-."}, {'D', "-.."},  {'E', "."},  
  {'F', "..-."}, {'G', "--."},  {'H', "...."}, {'I', ".."},   {'J', ".---"},
  {'K', "-.-"},  {'L', ".-.."}, {'M', "--"},   {'N', "-."},   {'O', "---"},  
  {'P', ".--."}, {'Q', "--.-"}, {'R', ".-."},  {'S', "..."},  {'T', "-"},    
  {'U', "..-"},  {'V', "...-"}, {'W', ".--"},  {'X', "-..-"}, {'Y', "-.--"}, 
  {'Z', "--.."}, {'1', ".----"}, {'2', "..---"}, {'3', "...--"}, {'4', "....-"},
  {'5', "....."}, {'6', "-...."}, {'7', "--..."}, {'8', "---.."}, {'9', "----."},
  {'0', "-----"}
};

void setup() {
  pinMode(LED, OUTPUT);
  Serial.begin(115200);

  Serial.println("Enter a name to convert to Morse Code:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');  
    input.trim();  

    Serial.print("Morse Code for '");
    Serial.print(input);
    Serial.println("':");

    blinkMorse(input);  
  }
}

void blinkMorse(String text) {
  for (int i = 0; i < text.length(); i++) {
    char upperChar = toupper(text[i]);  

    if (upperChar == ' ') {  
      space();  
      continue;
    }

    for (MorseCode mc : morseTable) {
      if (mc.letter == upperChar) {
        Serial.print(upperChar);
        Serial.print(" -> ");
        Serial.println(mc.code);

        
        const char* morse = mc.code;
        while (*morse) {
          if (*morse == '.') {
            dot();
          } else if (*morse == '-') {
            dash();
          }
          morse++;
        }
        space();  
        break;
      }
    }
  }
}

void dot() {
  digitalWrite(LED, HIGH);
  delay(200);  
  digitalWrite(LED, LOW);
  delay(200);
}

void dash() {
  digitalWrite(LED, HIGH);
  delay(600);  
  digitalWrite(LED, LOW);
  delay(200);
}

void space() {
  delay(600);  
}
