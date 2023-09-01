/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "mcp3208.h"

// Maximum number of element the application buffer can contain
#define MAXIMUM_BUFFER_SIZE                                                  32
// Create a BufferedSerial object with a default baud rate.
static BufferedSerial serial_port(USBTX, USBRX);

// Blinking rate in milliseconds
#define BLINKING_RATE     500ms
#define ADC_FREQUENCY     500000

int main()
{
    // Set desired properties (9600-8-N-1).
    serial_port.set_baud(9600);
    serial_port.set_format(8, BufferedSerial::None, 1); //8bit


    // Application buffer to receive the data
    char buf[MAXIMUM_BUFFER_SIZE] = {0};

    // Initialise the digital pin LED1 as an output
    //DigitalOut led(LED1);
    MCP3208 myADC(PB_5, PB_4, PB_3,PA_8);//frequency,mosi,miso,sck,cs
    
    int v[8];
    //float a=0.1;
    int i,num;

    num = sprintf(buf, "MCP3208 test");
    serial_port.write(buf, num);

    myADC.setFrequency(ADC_FREQUENCY);

    while (true) {
        //led = !led;
        ThisThread::sleep_for(BLINKING_RATE);
        for ( i = 0; i < 8; i++) {
            v[i] = (int)((myADC.read_input(i))*3309.0/4096.0);
            num = sprintf(buf, "ch%d: %dmV  ",i, v[i]);
            serial_port.write(buf, num);
        }
        num = sprintf(buf, "\n");
        serial_port.write(buf, num);
    }
}
