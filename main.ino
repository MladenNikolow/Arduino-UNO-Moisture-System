#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//Initialize the LCD
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//Global variables
bool SensorOnOff = false;
int count1 = 0;
int count2 = 0;
double moistureValue = 0;
bool lcdd = false;
bool lcdBegin = false;

void initIO(){

    DDRD &= ~ (1 << DDD2); // INT0 pin to INPUT (set to 0) 
    DDRC &= ~ (1 << DDC2); // Set Port C Pin 2 as input (Sensor - Analog sygnal)
    DDRB |= 1<<DDB0; //Set Port B Pin 0 as output (green Led)
    DDRB |= 1<<DDB1; //Set Port B Pin 1 as output (red led)
    
}


void initADC()
{
ADMUX |= 2; //Set up pin ADC2
ADMUX |= 1 << REFS0 | 1 << ADLAR; //V ref = 3.3V // Set up ADCH and ADCL bits
ADCSRA |= 1 << ADEN; //Enable ADC
}

void TWIInit()
{
    //set SCL to 400kHz = CPU Clock Frequency / 16 * 2 (TWBR x Prescaller) = 16 000 000 / 16 + 2 * (12 * 1)
    TWSR = 0x00; // prescaller 1
    TWBR = 0x0C; // 0000 1100 (12)
    TWAR = 0x27; //Slave Adress
    TWCR = (1<<TWEN);     //enable TWI
} 


  
//button push
void initInt0()
{ 
  EICRA |= 3; //What even will be the interrupt - rising edge
  EIMSK |= 1; //Only INT0 will have interrupt
  
}

//Interrupt
ISR(INT0_vect)
{ 
  Serial.println("enter IN0");
  TCCR1B |= 2; // Turn on Timer 1 // 1 - prescaller 1, OverFlow - 4ms and 2 - presacller 8, OverFlow - 32 ms (target - 50 for deboucing)
  
}

//button debouncing
void initTimer1() 
{
  TCCR1A = 0; //don't use this register
  TCCR1B &= ~7; // disable timer 1 
  TIMSK1 |=  1<<0; //Enabling Overflow Interrupt
  TIFR1 = 0; //Setting interrupt flags to 0
}

ISR(TIMER1_OVF_vect)
{

Serial.println("enter ISR TMR1");

TCCR1B &= ~7; // disable timer 1
if ((PIND & 1 << 2) == 1 << 2){

  if(SensorOnOff)
  {
    SensorOnOff = false; //button pushed for off
    lcdBegin = false; //Change the message for the display
    TCCR2B = 0; //Turn off TMR2
    ADCSRA |= 0 << ADSC; //turn off the ADC
    PORTB |= 0 << DDB0; // turn off pin 0 port B (green led)
    PORTB = 0 << DDB1; // turn off pin 1 port B (green led)
    
   }else 
   {
     SensorOnOff = true; //button pushed for on
     lcdBegin = true; ////Change the message for the display
     TCCR2B = 7; //prescaller 1024 - turn on TMR2
     ADCSRA |= 1 << ADSC; //Turn on ADC (if don't use it here write 100% at the beginning)
   }
      

  }
}

 //TMR2: Frequency of the measurement
void initTMR2(){

  TCCR2A = 0; //Useless regisrer
  TCCR2B = 0; //No prescaller
  TIMSK2 = 1; //TOIE - Enable Overflow Interrupt
  }

  
ISR (TIMER2_OVF_vect){
   // Serial.println("OVF TMR2");
    count2 ++;

    
    if (count2 == 62)
    { 
      // 1 second (1024/16 000 000 = 0.000064 * 254 = 0.016256s for TMR2 overflow * 62 = 1.007872 sec for TMR2 OVF)
      lcdd = true;
      ADCSRA |= 1 << ADSC; //Turn on ADC (if don't use it here - measure only 1 time)

      moistureValue = 100-(((ADCH * 4) / 1023.0) * 100); //*4 - << 2 bits
      Serial.println (moistureValue);

      if (moistureValue <= 30 || moistureValue >= 70)
      {
          PORTB = 0 << DDB0;
          PORTB = 1 << DDB1; //Turn on RED LED
      } else 
      {   
          PORTB = 0 << DDB1;
          PORTB = 1 << DDB0; //Turn on GREEN LED  
       }

       count2 = 0;
    } 
}


void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.backlight();
  initIO();
  TWIInit();
  initInt0();
  initTimer1();
  initADC();
  initTMR2();
  Serial.begin (9600);
}

void loop() 
{
  // put your main code here, to run repeatedly:

  if (lcdd == true)
  { 
    //Change the lcd text from beginnig state to showing Moisture values
      lcd.clear();
      String text = "Moisture: " + (String)moistureValue + "%";
      lcd.print (text);
      lcdd = false; 
      
  } 
    
  if ( lcdBegin == false)
  { 
    //Change the text from Moisture value to Welcome
    lcd.clear();
    lcd.print ("Welcome!");
    lcdBegin = true;
    
  }
}
