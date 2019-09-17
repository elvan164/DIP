int inHealthy = 2; 
int inDet = 3; 
int inFail = 4;
int outHealthy = 5;
int outDet = 6;
int outFail = 7;

int state = HIGH;      // the current state of the output pin
int readingHealthy, readingDet, readingFail;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
unsigned long time = 0;           // the last time the output pin was toggled
unsigned long debounce = 200UL;   // the debounce time, increase if the output flickers

void setup()
{
  pinMode(inHealthy,  INPUT);
  pinMode(inDet,  INPUT);
  pinMode(inFail,  INPUT);
  pinMode(outHealthy, OUTPUT);
  pinMode(outDet, OUTPUT);
  pinMode(outFail, OUTPUT);
}

void loop()
{
 
  readingHealthy = digitalRead(inHealthy);
  readingDet = digitalRead(inDet);
  readingFail = digitalRead(inFail);

  if (readingHealthy == HIGH && previous == LOW && millis() - time > debounce)
  {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();
  }

  digitalWrite(outHealthy, state);

  previous = readingHealthy;
}
