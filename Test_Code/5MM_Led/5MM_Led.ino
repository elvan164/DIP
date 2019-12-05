#define ledPin 10

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int randOn;
  randOn = random(0,3);
  Serial.println(randOn);
  if (randOn == 0) {
    digitalWrite(ledPin, HIGH);
  }
  else
  {
    digitalWrite(ledPin, LOW);
  }

  delay(250);
}
