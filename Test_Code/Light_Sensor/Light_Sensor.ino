//0 is max light, 999 is max dark

void setup()
{
Serial.begin(9600);
}
void loop()
{
unsigned int AnalogValue;
AnalogValue = analogRead(A0);
Serial.println(AnalogValue);
}
