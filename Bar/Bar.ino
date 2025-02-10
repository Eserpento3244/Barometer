#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;

void setup() {
  Serial.begin(9600); 
    Wire.begin(); 

  if (!bmp.begin(0x76)) 
  { 
    Serial.println("Ошибка подключения BMP280!");
    while (1);
  }
}
float calculateAltitude(float pressure, float temperatureC) 
{
    const float P0 = 101325.0;  
    const float L = 0.0065;      
    const float R = 8.314;       
    const float g = 9.80665;     
    const float M = 0.0289644;   

    float T = temperatureC + 273.15;  

    float exponent = (R * L) / (g * M);  
    float altitude = (T / L) * (1 - pow(pressure / P0, exponent));

    return altitude; 
}

void loop() 
{
  float temp = bmp.readTemperature();
  float pressure = bmp.readPressure() / 100.0F; 
  float altitude = calculateAltitude(pressure*100,temp);

  Serial.print("Температура: "); Serial.print(temp); Serial.print(" °C ");
  Serial.print("Давление: "); Serial.print(pressure); Serial.print(" hPa ");
  Serial.print("Высота: "); Serial.print(altitude); Serial.println(" м");
  
  delay(100);

}
