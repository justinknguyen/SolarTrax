#include <Servo.h>
#include <avr/sleep.h>

#define SAMPLINGTIME 5000
#define INTERRUPTPIN 3
//900000 - 15 minutes
//

volatile byte state = LOW;

/**
 * @author Branden Wong
 *         Savipal Jessel
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  pinMode(INTERRUPTPIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN), flash, CHANGE);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  delay(1000);
  goSleep();
  digitalWrite(4, LOW);
  delay(1000);
  

}

void goSleep(){
  sleep_enable();
  set_sleep_mode(011);
  //sleep_mode();
  delay(1000);
  Serial.print("1");
  sleep_cpu();
  Serial.print("2");
  //sleep_disable();
}

void flash(){
  state = !state;
  Serial.print("interrupt");
  //sleep_disable();
}
