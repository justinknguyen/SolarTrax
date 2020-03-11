 #include <Servo.h>
 #define SERVO_PIN 6
 #define ANALOG_PIN A0
 #define NUM_SAMP 300
 Servo myServo;
 int samples = 0;
 long int sum = 0;
 boolean flag = true;

/**
 * @author Branden Wong
 *         Savipal Jessel
 */
void setup() {
  myServo.attach(SERVO_PIN,0,360);
  myServo.write(60);
  pinMode(3,INPUT);
  Serial.begin(9600);
}

void loop() {

if (digitalRead(2) == HIGH){
  myServo.write(180);
}

else{
  myServo.write(60);
}


    
 
  //delay(1000);
  //myServo.write(60);
  //delay(2000);
  
 
  
    //Serial.println(pulseIn(3, HIGH));

if (samples == NUM_SAMP){
  sum = sum/NUM_SAMP;
  Serial.println(sum);
  sum = 0;
  samples = 0;
}

else{

  sum += pulseIn(3, HIGH);
  samples++;
}



  

 
 

}
