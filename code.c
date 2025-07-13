// code for the st7789V tft screen using a 4 wire serial comunication
// use SPI 0

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"

#define SPI_PORT spi0 // spi port to use for communication
#define MISO 0// MISO Pin (Recieve pin in pico)
#define MOSI 3// MOSI Pin (Transmit pin in pico)
#define SCK 2 // Clock output of SPI
#define CS 1// Chip Select pin
#define DC 4// Data/Command Pin
#define BAUD_RATE 10 * 1000 * 1000 // define baud rate to use in SPI

// define the start adress of the display memory
#define XS 0
#define YS 0

// define the end adress of the display memory
#define XE 100
#define YE 100

// commands
#define SWRESET 0x01 // software Reset
#define RDDST 0x09 // read Display Status
#define DISPOFF 0x28 // display Off
#define DISPON 0x29 // display on
#define CASET 0x2A // column Address Set
#define RASSET 0x2B // row address set
#define RAMWR 0x2C // memory write
#define RAMRD 0x2E // memory read
#define WRDISBV 0x51 // write display brightness
#define RDDISBV 0x52 // read display brightness
#define COLMOD 0x3A // color mode
#define SLPOUT 0x11 // sleep out

// colors RGB 666
#define MAX 0x1FC // max brightness of a color




void send_command(uint8_t CMD) {
    gpio_put(DC, 0);// Commnad mode
    gpio_put(CS, 0);// select display
    spi_write_blocking(SPI_PORT, &CMD, 1);// send the data over SPI
    gpio_put(CS,1);// unselect display
}

void send_data(uint8_t *DATA, size_t SIZE) {
    gpio_put(DC, 1);// data mode
    gpio_put(CS, 0);// select display
    spi_write_blocking(SPI_PORT, DATA, SIZE);// send data
    gpio_put(CS,1);// unselect display
}

void set_ends() {
    uint8_t ENDS[4] = {0,0,0,19};

    // set columns to modify
    send_command(CASET);
    send_data(ENDS,4);
    
    // set rows to modify
    send_command(RASSET);
    send_data(ENDS,4);
}

int main() {
    // initialize all pins and SPI
    spi_init(SPI_PORT,BAUD_RATE);// init SPI

    gpio_set_function(MISO, GPIO_FUNC_SPI);
    gpio_set_function(MOSI, GPIO_FUNC_SPI);
    gpio_set_function(SCK, GPIO_FUNC_SPI);

    gpio_init(CS);
    gpio_init(DC);
    gpio_set_dir(CS, true);
    gpio_set_dir(DC, true);

    // initialize display

    send_command(SWRESET);// software reset
    sleep_ms(200);

    send_command(SLPOUT);// end sleep
    sleep_ms(200);

    send_command(COLMOD);// set color mode
    uint8_t fmt = 0x66;// mask for RGB666
    send_data(&fmt,1);
    sleep_ms(200);

    send_command(DISPON);// display On
    sleep_ms(200);

    // communication
    // test by turning the whole screen red, then blue

    // define a list of 20 red pixels and 20 blue pixels
    uint8_t RED[1200];
    uint8_t BLUE[1200];

    // fill both lists with red and blue
    for (int i = 0; i < 400; i++) {
        RED[3*i] = MAX;
        RED[3*i + 1] = 0x0;
        RED[3*i + 2] = 0x0;

        BLUE[3*i] = 0x0;
        BLUE[3*i + 1] = 0x0;
        BLUE[3*i + 2] = MAX;
    }

    while (true) {
        // fill block in RED
        set_ends();// set start and end rows and columns
        send_command(RAMWR);
        send_data(RED,1200);
        sleep_ms(50);

        set_ends();// set start and end rows and columns
        send_command(RAMWR);
        send_data(BLUE,1200);
        sleep_ms(50);
    }
}