#include "xc.h"
#include "stdint.h"
#include <stdio.h>
#include "hamza_lab3_asmb_v001.h"

// Define digit positions
//const static int LEFT =  0b0000100000000000;
//const static int RIGHT = 0b0000010000000000;

#define LEFT 1
#define RIGHT 0


// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select (Emulator EMUC1/EMUD1 pins are shared with PGC1/PGD1)
#pragma config FWDTEN = OFF        // Watchdog Timer Enable (Watchdog Timer is disabled)
#pragma config GWRP = OFF          // General Code Segment Write Protect (Writes to program memory are allowed)
#pragma config GCP = OFF           // General Code Segment Code Protect (Code protection is disabled)
#pragma config JTAGEN = OFF        // JTAG Port Enable (JTAG port is disabled)


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // I2C1 Pin Location Select (Use default SCL1/SDA1 pins)
#pragma config IOL1WAY = OFF       // IOLOCK Protection (IOLOCK may be changed via unlocking seq)
#pragma config OSCIOFNC = ON       // Primary Oscillator I/O Function (CLKO/RC15 functions as I/O pin)
#pragma config FCKSM = CSECME      // Clock Switching and Monitor (Clock switching is enabled, 
                                       // Fail-Safe Clock Monitor is enabled)
#pragma config FNOSC = FRCPLL      // Oscillator Select (Fast RC Oscillator with PLL module (FRCPLL))

void delay(int delay_in_ms);
//void showChar7seg(char myChar, int myDigit);


void setup(void) {
    CLKDIVbits.RCDIV = 0;  // Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16MHz
}

int main(void) {
    setup();
    init7seg();

    while (1) {
        showChar7seg('.', RIGHT);

    }
    
}

void test(void){
    showChar7seg('0', RIGHT);
    delay(2000);
    showChar7seg('1', LEFT);
    delay(1000);
    showChar7seg('2', RIGHT);
    delay(1000);
    showChar7seg('3', LEFT);
    delay(1000);
    showChar7seg('4', RIGHT);
    delay(1000);
    showChar7seg('5', LEFT);
    delay(1000);
    showChar7seg('6', RIGHT);
    delay(1000);
    showChar7seg('7', LEFT);
    delay(1000);
    showChar7seg('8', RIGHT);
    delay(1000);
    showChar7seg('9', LEFT);
    delay(1000);
    showChar7seg('A', RIGHT);
    delay(1000);
    showChar7seg('b', LEFT);
    delay(1000);
    showChar7seg('C', RIGHT);
    delay(1000);
    showChar7seg('d', LEFT);
    delay(1000);
    showChar7seg('E', RIGHT);
    delay(1000);
    showChar7seg('F', LEFT);
    delay(1000);
    showChar7seg('.', RIGHT);
    delay(1000);
}

// Setting up output
void init7seg(void){
    CLKDIVbits.RCDIV = 0;  // Set RCDIV=1:1 (default 2:1) 32MHz or FCY/2=16MHz
    AD1PCFG = 0x9fff;      // Set all pins to digital mode
    
    TRISB = 0xF000;  // Set RB-12-15 as INPUT and RB0-11 as OUTPUT
    LATB = 0b0000111111111100;   // Set RB2 - RB11 to OFF

}

void showChar7seg(char myChar, int myDigit) {

    LATB |= 0x0FFF;

    switch (myChar) {
        case '0': LATB &= 0b1111000000001100; break;
        case '1': LATB &= 0b1111001001111100; break;
        case '2': LATB &= 0b1111000010010100; break;
        case '3': LATB &= 0b1111000000110100; break;
        case '4': LATB &= 0b1111001001100100; break;
        case '5': LATB &= 0b1111000100100100; break;
        case '6': LATB &= 0b1111000100000100; break;
        case '7': LATB &= 0b1111000001111100; break;
        case '8': LATB &= 0b1111000000000100; break;
        case '9': LATB &= 0b1111000000100100; break;
        case 'A': LATB &= 0b1111000001000100; break;
        case 'b': LATB &= 0b1111001100000100; break;
        case 'C': LATB &= 0b1111000110001100; break;
        case 'd': LATB &= 0b1111001000010100; break;
        case 'E': LATB &= 0b1111000110000100; break;
        case 'F': LATB &= 0b1111000111000100; break;
        case '.': LATB &= 0b1111001111111011; break;
        default:  LATB |= 0b0000000000000000;  
   }
    
    if (myDigit == LEFT) {
        LATB |= 0b0000100000000000; 
    } else {
        LATB |= 0b0000010000000000; 
    }
}




void delay(int delay_in_ms) {
    int i = 0;
    for (i = 0; i <= delay_in_ms; i++){
        wait_1ms();
    }
    
}