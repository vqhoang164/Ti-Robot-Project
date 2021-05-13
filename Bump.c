// Negative logic bump sensors
// P4.7 Bump5, left side of robot
// P4.6 Bump4
// P4.5 Bump3
// P4.3 Bump2
// P4.2 Bump1
// P4.0 Bump0, right side of robot

#include <stdint.h>
#include "msp.h"
// Initialize Bump sensors
// Make six Port 4 pins inputs
// Activate interface pullup
// pins 7,6,5,3,2,0
void Bump_Init(void){
    P4->SEL0 &= ~0xED;
    P4->SEL1 &= ~0xED;                 // configure P4.0 to P4.7 as GPIO
    P4->DIR &= ~0xED;                  // make P4.0 to P4.7 in
    P4->REN |= 0xED;                   // enable pull resistors
    P4->OUT |= 0xED;                   // P4.0 to P4.7 are pull-up
}
