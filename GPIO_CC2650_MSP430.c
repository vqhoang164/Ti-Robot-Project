// GPIO.c
// Runs on MSP432
// Digital input/output from MSP432 LaunchPad to CC2650

#include <GPIO_CC2650_MSP430.h>
#include "msp.h"
// Legend    TI part number
// CC2650BP  BOOSTXL-CC2650MA
// CC2650LP  LAUNCHXL-CC2650
// MSP432    MSP-EXP432P401R
// TM4C123   EK-TM4C123GXL
// MKII      BOOSTXL-EDUMKII

#ifdef DEFAULT
// Option 4) Use this setup with CC2650BP without an MKII 
// Two board stack: CC2650BP+MSP432 
// Acceptable projects:
//     VerySimpleApplicationProcessor_MSP432
//     ApplicationProcessor_MSP432
// This runs with the default version of SNP that ships on the BOOSTXL-CC2650MA
// signal  MSP432                           CC2650BP       comment
//  3V3    J1.1  3.3V                       J1.1  3.3V     Power from MSP432 to CC2650BP 
//  GND    J2.20 ground                     J2.20 ground   Connect ground together
//  NRESET J4.35 TM4C123 PC6, MSP432 P6.7   J4.35          Reset from MSP432 to CC2650BP  
//  TX     J1.3  TM4C123 PB0, MSP432 P3.2   J1.3  DIO0_TXD UART from CC2650BP to MSP432  
//  RX     J1.4  TM4C123 PB1, MSP432 P3.3   J1.4  DIO1_RXD UART from MSP432 to CC2650BP
//  MRDY   J1.2  TM4C123 PB5, MSP432 P6.0   J1.2  IOID_7   Master ready from MSP432 to CC2650BP 
//  SRDY   J2.19 TM4C123 PB2, MSP432 P2.5   J2.19 IOID_8   Slave ready from CC2650BP to MSP432 

//------------GPIO_Init------------
// Initialize MRDY (out), SRDY (in), RESET (out) GPIO pins
// Input: none
// Output: none
void GPIO_Init(void){
  P2->SEL0 &= ~0x20;  // SRDY is P2.5, J2.19
  P2->SEL1 &= ~0x20;  // 1) configure P2.5 GPIO
  P2->DIR &= ~0x20;   // 2) make P2.5 in
  P2->REN |= 0x20;    // 3) enable pull resistors on P2.5
  P2->OUT |= 0x20;    //    P2.5 are pull-up
  
  P6->SEL0 &= ~0x01;  // J1.2 MRDY {TM4C123 PB5, MSP432 P6.0}
  P6->SEL1 &= ~0x01;  // 1) configure P6.0 as GPIO
  P6->DIR |= 0x01;    // 2) make P6.0 out
  P6->DS |= 0x01;     // 3) activate increased drive strength
  SetMRDY();        //   MRDY=1  
  
  P6->SEL0 &= ~0x80;  // J4.35 Reset to CC2650 {TM4C123 PC6, MSP432 P6.7}
  P6->SEL1 &= ~0x80;  // 1) configure P6.7 as GPIO
  P6->DIR |= 0x80;    // 2) make P6.7 out
  P6->DS |= 0x80;     // 3) activate increased drive strength
  ClearReset();     // RESET=0    
}
#endif
