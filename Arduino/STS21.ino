// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// STS21
// This code is designed to work with the STS21_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=STS21_I2CS#tabs-0-product_tabset-2

#include <Wire.h>

// STS21 I2C address is 0x4A(74)
#define addr 0x4A

void setup() 
{             
    // Initialise I2C communication as MASTER
    Wire.begin();  
    // Start serial communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission 
    Wire.beginTransmission(addr);   
    // Select no hold master
    Wire.write(0xF3);
    // End I2C Transmission
    Wire.endTransmission();
    delay(300);
}
  
void loop() 
{
    unsigned int data[2];
    // Start I2C Transmission
    Wire.beginTransmission(addr);   
    // Select data registers 
    Wire.write(addr);
    // End I2C Transmission
    Wire.endTransmission();
    
    // Request 2 bytes of data
    Wire.requestFrom(0x00, 2);       
   
    // Read 2 bytes of data
    if (Wire.available() == 2) 
    {                     
      data[0] = Wire.read();
      data[1] = Wire.read();
    }
    delay(300);
    
    // Convert the data
    float cTemp = (((data[0] * 256) + (data[1] & 0xFC)) * (175.72 / 65536.0)) - 46.85;
    float fTemp = cTemp * 1.8 + 32;
  
  // Output data to serial monitor
  Serial.print("Temperature in Celsius:  ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit:  ");
  Serial.print(fTemp);
  Serial.println(" F");  
  delay(300);
}

