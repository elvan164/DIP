//0 is max light, 999 is max dark
int REDPin = 4;    // RED pin of the LED to PWM pin 4
int GREENPin = 5;  // GREEN pin of the LED to PWM pin 5
int BLUEPin = 6;   // BLUE pin of the LED to PWM pin 6

void setup()
{
  pinMode(REDPin, OUTPUT);
  pinMode(GREENPin, OUTPUT);
  pinMode(BLUEPin, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  unsigned int AnalogValue;
  AnalogValue = analogRead(A0);
  Serial.println(AnalogValue);

  if (AnalogValue>700)
  {
    analogWrite(REDPin, 255);
    analogWrite(GREENPin, 255);
    analogWrite(BLUEPin, 255);
  }

  if (AnalogValue<=700)
  {
    analogWrite(REDPin, 0);
    analogWrite(GREENPin, 0);
    analogWrite(BLUEPin, 0);
  }
}
