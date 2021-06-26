#include<DHT.h>
#include <PulseSensorPlayground.h>
#include <TinyGPS.h>


//pin defines
#define DHTPIN 13
#define DHTTYPE DHT11
#define PULSE_PIN A0
int Signal;
float lattitude , longitude;
int year , month , date, hour , minute , second;
String date_str , time_str , lat_str , lng_str;
int pm;

TinyGPS gps;

DHT dht(DHTPIN, DHTTYPE);

void setup()
{
  Serial.begin(9600);
  Serial.println("TESTING NOW.....");
  dht.begin();
}

void loop()
{
  //Reading DHT
  delay(200);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.print("Humidity:");
  Serial.print(h);
  Serial.print("x");
  Serial.print("Temperature = ");
  Serial.print(t);
  Serial.print("x");

  Signal = analogRead(PULSE_PIN);
  if (Signal > 550)
  {
    Serial.print("Pulse Rate= ");
    Serial.println(Signal);


  }

  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

  
  for (unsigned long start = millis(); millis() - start < 1000;)
  {
    while (Serial.available())
    {
      char c = Serial.read();
      Serial.print(c);
      if (gps.encode(c))
        newData = true;
    }
  }

  if (newData)      //If newData is true
  {
    float flat, flon;
    gps.f_get_position(&flat, &flon);
    Serial.print("Latitude = ");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" Longitude = ");
    Serial.print("x");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.println();
  }
}
