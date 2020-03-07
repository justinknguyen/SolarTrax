#include <Servo.h>
#include <avr/sleep.h>

#define SAMPLINGTIME 5000
//900000 - 15 minutes
//

/**
 * @author Branden Wong
 *         Savipal Jessel
 */
void setup() {
  // put your setup code here, to run once:
  pinMode(4, OUTPUT);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  

}

void goSleep(){
  sleep_enable();
  set_sleep_mode(011);
}
