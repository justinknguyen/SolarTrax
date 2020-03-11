#include <Servo.h>      //including the library of servo motor 
Servo sg90;             //initializing a variable for servo named sg90
int initial_position = 60;   //Declaring the initial position 
int LDR1 = A0;          //Pin at which LDR is connected
int LDR2 = A1;          //Pin at which LDR is connected
int error = 5;          //initializing variable for error
int servopin=6;
void setup() 
{ 

  sg90.attach(servopin);  // attaches the servo on pin 9
  pinMode(LDR1, INPUT);   //Making the LDR pin as input
  pinMode(LDR2, INPUT);
  sg90.write(initial_position);   //Move servo at 90 degree
  delay(2000);            // giving a delay of 2 seconds
}  
 
void loop() 
{ 

  if (digitalRead(2) == HIGH){
    
  
  int R1 = analogRead(LDR1); // reading value from LDR 1
  int R2 = analogRead(LDR2); // reading value from LDR 2
  int diff1= abs(R1 - R2);   // Calculating the difference between the LDR's
  int diff2= abs(R2 - R1);
  
  if((diff1 <= error) || (diff2 <= error)) {
    //if the difference is under the error then do nothing
  } else {    
    if(R1 > R2)
    {
      sg90.write(0);  //Move the servo towards 0 degree
    }
    if(R1 < R2) 
    {
      sg90.write(180); //Move the servo towards 180 degree
    }
  }
  //sg90.write(initial_position); // write the position to servo
  delay(100);
  }
}
