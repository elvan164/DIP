#include <Adafruit_NeoPixel.h>

//0 is max light, 999 is max dark
/*int REDPin1 = 2;    // RED pin of the LED1 to PWM pin 2
int GREENPin1 = 3;  // GREEN pin of the LED1 to PWM pin 3

int REDPin2 = 4;    // RED pin of the LED2 to PWM pin 4
int GREENPin2 = 5;  // GREEN pin of the LED2 to PWM pin 5

int REDPin3 = 6;    // RED pin of the LED3 to PWM pin 6
int GREENPin3 = 7;  // GREEN pin of the LED3 to PWM pin 7

int REDPin4 = 8;    // RED pin of the LED4 to PWM pin 8
int GREENPin4 = 9;  // GREE7N pin of the LED4 to PWM pin 9

int REDPin5 = 10;    // RED pin of the LED5 to PWM pin 10
int GREENPin5 = 11;  // GREEN pin of the LED5 to PWM pin 11*/

double humidity = 70.0;
int LEDdelay = 500;
double lightThreshold = 200;

int start = 0; // start of project


#include <DHT22.h>
#include <stdio.h>
// Green of Humidity Sensor to pin 22
#define DHT22_PIN 22

// Setup a DHT22 instance
DHT22 myDHT22(DHT22_PIN);

//LED 0 is max on, 255 is max off

/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D49
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D49
3.3V            3.3V         3.3V
*/

/* Include the standard Arduino SPI library */
#include <SPI.h>
/* Include the RFID library */
#include <RFID.h>
/* Define the DIO used for the SDA (SS) and RST (reset) pins. */
#define SDA_DIO 49
#define RESET_DIO 48
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 

int axeCount = 5;


void setup()
{
  /*pinMode(REDPin1, OUTPUT);
  pinMode(GREENPin1, OUTPUT);
  pinMode(REDPin2, OUTPUT);
  pinMode(GREENPin2, OUTPUT);
  pinMode(REDPin3, OUTPUT);
  pinMode(GREENPin3, OUTPUT);
  pinMode(REDPin4, OUTPUT);
  pinMode(GREENPin4, OUTPUT);
  pinMode(REDPin5, OUTPUT);
  pinMode(GREENPin5, OUTPUT);*/

  
  Serial.begin(9600);

  /* Enable the SPI interface */
  SPI.begin(); 
  /* Initialise the RFID reader */
  RC522.init();
}
void loop()
{

  unsigned int LightValue;
  LightValue = analogRead(A0);//pin of light sensor
  //Serial.println(AnalogValue); 

DHT22_ERROR_t errorCode;
  
  // The sensor can only be read from every 1-2s, and requires a minimum
  // 2s warm-up after power-on.
  //delay(1000);
  
  //Serial.print("Requesting data...");
  errorCode = myDHT22.readData();
  switch(errorCode)
  {
    case DHT_ERROR_NONE:
      //Serial.print("Got Data ");
      //Serial.print(myDHT22.getTemperatureC());
      //Serial.print("C ");
      //Serial.print(myDHT22.getHumidity());
      //Serial.println("%");
      // Alternately, with integer formatting which is clumsier but more compact to store and
    // can be compared reliably for equality:
    //    
      char buf[128];
      sprintf(buf, "Humidity %i.%01i %%",
                   myDHT22.getHumidityInt()/10, myDHT22.getHumidityInt()%10);
      Serial.println(buf);
      Serial.print("Light Value is ");
      Serial.println(LightValue);
      Serial.print("Axe Value is ");
      Serial.println(axeCount);
      Serial.println();
      break;
  }

if (start == 0){
   /* analogWrite(REDPin1,255);
    analogWrite(GREENPin1,255);
    analogWrite(REDPin2,255);
    analogWrite(GREENPin2,255);
    analogWrite(REDPin3,255);
    analogWrite(GREENPin3,255);
    analogWrite(REDPin4,255);
    analogWrite(GREENPin4,255);
    analogWrite(REDPin5,255);
    analogWrite(GREENPin5,255);*/
    start = 1;
}

if ((myDHT22.getHumidity() > humidity) && (start == 1) ) //blowing will cause each group to turn green, inside out
  {
    /*analogWrite(REDPin1,255);
    analogWrite(REDPin2,255);
    analogWrite(REDPin3,255);
    analogWrite(REDPin4,255);
    analogWrite(REDPin5,255);
    
    analogWrite(GREENPin1,0);
    delay(LEDdelay);
    analogWrite(GREENPin2,0);
    delay(LEDdelay);
    analogWrite(GREENPin3,0);
    delay(LEDdelay);
    analogWrite(GREENPin4,0);
    delay(LEDdelay);
    analogWrite(GREENPin5,0);
    delay(LEDdelay);*/
    start = 2;
    axeCount = 5;
  }
  
  if ((LightValue<lightThreshold) && (start == 2)) //shining light will cause each group to turn red, inside out then turn off
  {
    delay(500);
    /*analogWrite(GREENPin1,255);
    analogWrite(GREENPin2,255);
    analogWrite(GREENPin3,255);
    analogWrite(GREENPin4,255);
    analogWrite(GREENPin5,255);
    
    analogWrite(REDPin1,0);
    delay(LEDdelay);
    analogWrite(REDPin2,0);
    delay(LEDdelay);
    analogWrite(REDPin3,0);
    delay(LEDdelay);
    analogWrite(REDPin4,0);   
    delay(LEDdelay);
    analogWrite(REDPin5,0);
    delay(LEDdelay);

    analogWrite(REDPin5,255);
    delay(LEDdelay);
    analogWrite(REDPin4,255);
    delay(LEDdelay);
    analogWrite(REDPin3,255);
    delay(LEDdelay);
    analogWrite(REDPin2,255);
    delay(LEDdelay);
    analogWrite(REDPin1,255);*/
    start = 1;

    delay(5000);
  }

  /* Has a card been detected? */
  if ((RC522.isCard()) && (start == 2) )
  {
    switch(axeCount){
      case 5:
      //analogWrite(GREENPin5,255);
      axeCount--;
      break;
      case 4:
      //analogWrite(GREENPin4,255);
      axeCount--;
      break;
      case 3:
      //analogWrite(GREENPin3,255);
      axeCount--;
      break;
      case 2:
      //analogWrite(GREENPin2,255);
      axeCount--;
      break;
      case 1:
      //analogWrite(GREENPin1,255);
      axeCount--;
      delay(5000);
      start = 1;
      break;
      default:
      break;
      
    }
    /* If so then get its serial number */
    /*RC522.readCardSerial();
    Serial.println("Card detected:");
    for(int i=0;i<5;i++)
    {
    Serial.print(RC522.serNum[i],DEC);
    //Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
    }
    Serial.println();
    Serial.println();*/
  }
  delay(1000);
  
}
