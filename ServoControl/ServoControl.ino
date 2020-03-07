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
  pinMode(INTERRUPTPIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(INTERRUPTPIN), flash, CHANGE);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, state);
  goSleep();
  

}

void goSleep(){
  sleep_enable();
  set_sleep_mode(011);
}

void flash(){
  state = !state;
}
