#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN 5 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 300 // Popular NeoPixel ring size

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 50 // Time (in milliseconds) to pause between pixels


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

int axeCount = 4;


void setup()
{
  Serial.begin(9600);

   // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

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
    pixels.clear(); // Set all pixel colors to 'off'
    start = 1;
}

if ((myDHT22.getHumidity() > humidity) && (start == 1) ) //blowing will cause each group to turn green, inside out
  {
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(0,150,0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
    
    start = 2;
    axeCount = 4;
  }
  
  if ((LightValue<lightThreshold) && (start == 2)) //shining light will cause each group to turn red, inside out then turn off
  {
    //delay(500);
    for(int i=0; i<NUMPIXELS; i++) { // For each pixel...

    // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(150, 0, 0));

    pixels.show();   // Send the updated pixel colors to the hardware.

    delay(DELAYVAL); // Pause before next pass through loop
    }
    delay(10000);
    start = 1;

    delay(10000);
  }

  /* Has a card been detected? */
  if ((RC522.isCard()) && (start == 2) ) //will turn off from green, outside in
  {
    switch(axeCount){
      case 4:
      for(int i=0; i<75; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(DELAYVAL); // Pause before next pass through loop
      }
      axeCount--;
      break;
      case 3:
      for(int i=75; i<150; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(DELAYVAL); // Pause before next pass through loop
      }
      axeCount--;
      break;
      case 2:
      for(int i=150; i<225; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(DELAYVAL); // Pause before next pass through loop
      }
      axeCount--;
      break;
      case 1:
      for(int i=225; i<300; i++) { // For each pixel...

      // pixels.Color() takes RGB values, from 0,0,0 up to 255,255,255
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));

      pixels.show();   // Send the updated pixel colors to the hardware.

      delay(DELAYVAL); // Pause before next pass through loop
      }
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