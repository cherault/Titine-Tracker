#include <SoftwareSerial.h>
#include <TinyGPS.h>

#define RXPIN 2 // hardware 3
#define TXPIN 3 // hardware 2

#define GPSBAUD 9600

TinyGPS gps;

SoftwareSerial uart_gps(RXPIN, TXPIN);

void getgps(TinyGPS &gps);

void setup()
{
  Serial.begin(115200);
  
  uart_gps.begin(GPSBAUD);
}

void loop()
{
  for (unsigned long start = millis(); millis() - start < 100;)
  {
    while(uart_gps.available())    
    {
      int c = uart_gps.read();  
      
      if(gps.encode(c))     
      {
        getgps(gps);        
      }
    }
  }
}

void getgps(TinyGPS &gps)
{
  float latitude, longitude;
  
  /*
  gps.f_get_position(&latitude, &longitude);
  
  
  Serial.print("Lat/Long: ");
  Serial.print(latitude,5);
  Serial.print(", ");
  Serial.println(longitude,5);
  */
 
  int year;
  byte month, day, hour, minute, second, hundredths;
  gps.crack_datetime(&year,&month,&day,&hour,&minute,&second,&hundredths);
  
  Serial.print(gps.satellites());
  Serial.print(",");
  Serial.print(gps.f_altitude()); 
  Serial.print(",");
  
  /*
  Serial.print(gps.f_speed_kmph());
  Serial.print(",");
  Serial.print(day); 
  Serial.print(","); 
  Serial.print(month); 
  Serial.print(",");
  Serial.print(year);
  Serial.print(",");
  */
  
  Serial.print(hour); 
  Serial.print(",");
  Serial.print(minute); 
  Serial.print(","); 
  Serial.print(gps.f_speed_kmph()); 
  Serial.print(",");
}
