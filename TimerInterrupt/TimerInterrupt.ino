
#include <avr/sleep.h>
#include <avr/power.h>
#include <avr/wdt.h>
#define LED_PIN 3
#define MINUTES 1               // change this to your desired period
#define TIMER ((MINUTES*60)/8)
volatile int f_wdt=1;
volatile int counter = 0;

/**
 * I've adapted this code that I found online to (hopefully) work with our application. Unless we purchase an external clock,
 * the only way to have a 60 minute timer is to count ~7 watch dog timer cycles, where the maximum for the watch dog timer is 8 s. 
 * 
 * This basically means that the arduino is gonna wake up every 8 s and check if the counter is at an hour yet. 
 * If it is, it will execute the motor code, if it isn't, it will go back to sleep
 * 
 * 
 * 
 * 
 * 
 */



/***************************************************
 *  Name:        ISR(WDT_vect)
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Watchdog Interrupt Service. This
 *               is executed when watchdog timed out.
 *
 ***************************************************/
ISR(WDT_vect)
{
  counter++;
  if(f_wdt == 0)
  {
    f_wdt=1;
    
  }
  else
  {
    Serial.println("WDT Overrun!!!");
  }
}


/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Enters the arduino into sleep mode.
 *
 ***************************************************/
void enterSleep(void)
{
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);   /* EDIT: could also use SLEEP_MODE_PWR_DOWN for lowest power consumption. */
  sleep_enable();
  
  /* Now enter sleep mode. */
  sleep_mode();
  
  /* The program will continue from here after the WDT timeout*/
  sleep_disable(); /* First thing to do is disable sleep. */
  
  /* Re-enable the peripherals. */
  power_all_enable();
}



/***************************************************
 *  Name:        setup
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Setup for the serial comms and the
 *                Watch dog timeout. 
 *
 ***************************************************/
void setup()
{
  Serial.begin(9600);
  Serial.println("GETTING READY...");
  delay(100); //Allow for serial print to complete.

  pinMode(LED_PIN,OUTPUT);

  /*** Setup the WDT ***/
  
  /* Clear the reset flag. */
  MCUSR &= ~(1<<WDRF);
  
  /* In order to change WDE or the prescaler, we need to
   * set WDCE (This will allow updates for 4 clock cycles).
   */
  WDTCSR |= (1<<WDCE) | (1<<WDE);

  /* set new watchdog timeout prescaler value */
  WDTCSR = 1<<WDP0 | 1<<WDP3; /* 8.0 seconds */
  
  /* Enable the WD interrupt (note no reset). */
  WDTCSR |= _BV(WDIE);
  
  Serial.println("WATCH DOG IS READY");
  delay(100); //Allow for serial print to complete.
}



/***************************************************
 *  Name:        enterSleep
 *
 *  Returns:     Nothing.
 *
 *  Parameters:  None.
 *
 *  Description: Main application loop.
 *
 ***************************************************/
void loop()
{
  if(f_wdt == 1)
  {
    
    /* Don't forget to clear the flag. */
    f_wdt = 0;

    if (counter != TIMER){
      enterSleep();
    }

    else{
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // execute servo control code here instead of LED code
      counter = 0;                                  // reset counter
      enterSleep();
      
    }
  }

 
  else
  {
    /* Do nothing. */
  }
}
