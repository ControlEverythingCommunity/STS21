// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// STS21
// This code is designed to work with the STS21_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=STS21_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class STS21
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, STS21 I2C address is 0x4A(74)
		I2CDevice device = bus.getDevice(0x4A);
		
		// Write Temperature measurement trigger with NO HOLD mode
		device.write((byte)0xF3);
		Thread.sleep(300);
		
		// Read 2 bytes of data, msb first
		byte[] data = new byte[2];
		device.read(data, 0, 2);
		
		// Convert data 
		int temp = ((data[0] & 0xFF) * 256) + (data[1] & 0xFF);
		double cTemp = -46.85 + (175.72 * temp) / 65536.0;
		double fTemp = (cTemp * 1.8) + 32;
		
		// Output to screen
		System.out.printf("Temperature in Celsius is : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit is : %.2f F %n", fTemp);
	}
}
