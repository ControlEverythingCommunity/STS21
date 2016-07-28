// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// STS21
// This code is designed to work with the STS21_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=STS21_I2CS#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
    // Create I2C bus
    int file;
    char *bus = "/dev/i2c-1";
    if ((file = open(bus, O_RDWR)) < 0)
    {
        printf("Failed to open the bus. \n");
        exit(1);
    }
    // Get I2C device, SHT25 I2C address is 0x4A(74)
    ioctl(file, I2C_SLAVE, 0x4A);
    
    // Send temperature measurement command, NO HOLD master
    char config[1] = {0};
    config[0] = 0xF3;
    write(file, config, 1);
    sleep(1);
    
    // Read 2 bytes of data
    // temp msb, temp lsb
	char data[2] = {0};
    if(read(file, data, 2) != 2)
    {
        printf("Error : Input/Output error \n");
    }
    else
    {
        // Convert the data
        int temp = ((data[0]) * 256) + (data[1]);
        float cTemp = -46.85 + (175.72 * temp) / 65536.0;
        float fTemp = (cTemp * 1.8) + 32;
        
        //Output data to screen
        printf("Temperature in Celsius is : %.2f C \n", cTemp);
        printf("Temperature in Fahrenheit is : %.2f F \n", fTemp);
    }
}
