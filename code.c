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

void main() {
    
}