#include <Servo.h>

//Servos
Servo servos[4];
int servoPins[] = {3, 5, 6, 9};
bool boxStates[] = {false, false, false, false};
int amountOpen = 0;

//LEDs
int leds[] = {10, 11, 12, 13};

//Piezo sensors
int piezos[] = {A0, A1, A2, A3};
const int threshold = 300; //might need two thresholds for different types


void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 4; i++){
    servos[i].attach(servoPins[i]);
    servos[i].write(0);
    pinMode(leds[i], OUTPUT);
    digitalWrite(leds[i], HIGH);
  }
}

void loop() {
  for (int i = 0; i < 4; i++) {
    if (!boxStates[i] && analogRead(piezos[i]) > threshold) {
      boxStates[i] = true;
      amountOpen++;
      digitalWrite(leds[i], LOW);
      if(amountOpen == 4){
        digitalWrite(leds[i], HIGH);
      }
      delay(500);
      servos[i].write(115);
    }
  }
  if(amountOpen == 4){
    delay(2000);
    for(int i = 0; i < 4; i++){
      servos[i].write(0);
      boxStates[i] = false;
      delay(250);
    }
    boolean finished = true;
    while (finished) {
      for (int i = 0; i < 4; i++) {
        if (analogRead(piezos[i]) > threshold) {
          finished = false;
        }
      }
    }
    delay(2000);
    for(int i = 0; i < 4; i++){
      digitalWrite(leds[i], HIGH);
    }
    amountOpen = 0;
  }
}

