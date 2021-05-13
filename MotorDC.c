// Control motor movement

#include <stdint.h>
#include "msp.h"
#include "SysTick.h"
#include "Bump.h"

// Left motor direction connected to P5.4 (J3.29)
// Left motor PWM connected to P2.7/TA0CCP4 (J4.40)
// Left motor enable connected to P3.7 (J4.31)
// Right motor direction connected to P5.5 (J3.30)
// Right motor PWM connected to P2.6/TA0CCP3 (J4.39)
// Right motor enable connected to P3.6 (J2.11)

void Motor_Init(void){
// Initializes the 6 GPIO lines and puts driver to sleep

    P5->SEL0 &= ~0x30;
    P5->SEL1 &= ~0x30;    //  P5.4 and P5.5 as GPIO direction
    P5->DIR |= 0x30;      //  make P5.4 and P5.5 out

    P2->SEL0 &= ~0xC0;
    P2->SEL1 &= ~0xC0;    //  P2.6 and P2.7 as GPIO Enable
    P2->DIR |= 0xC0;      //  make P5.5 out

    P3->SEL0 &= ~0xC0;
    P3->SEL1 &= ~0xC0;    //  P3.6 and P3.7 as GPIO no_sleep
    P3->DIR |= 0xC0;      //  make P2.7 out

    P2->OUT &= ~0xC0;     // enable = 0
}

void Motor_Stop(void){
// Stops both motors, puts driver to sleep
    P2->OUT &= ~0xC0;   // enable = 1
    P5->OUT &= ~0x30;   // off
    P3->OUT &= ~0xC0;   // sleep mode
}
void Motor_Forward(uint16_t duty, uint32_t time){
// time unit is 10ms
    uint32_t timecount;
    timecount=0;

    P3->OUT |= 0xC0;    // no_sleep = 1
    while (timecount<=time) {
        P2->OUT |= 0xC0;    // enable = 1
        SysTick_Wait1us(duty);
        P2->OUT &= ~0xC0;    // enable = 0
        SysTick_Wait1us(10000-duty);
        timecount=timecount + 5;
    }
//    SysTick_Wait10ms(time);
    Motor_Stop();

}
void Motor_Backward(uint16_t duty, uint32_t time){
// time unit is 10ms
    uint32_t timecount;
    timecount=0;
    P3->OUT |= 0xC0;    // no_sleep = 1
    P5->OUT |= 0x30;    // change direction
    while (timecount<=time) {
        P2->OUT |= 0xC0;    // enable = 1
        SysTick_Wait1us(duty);
        P2->OUT &= ~0xC0;    // enable = 0
        SysTick_Wait1us(10000-duty);
        timecount=timecount + 5;
    }
    Motor_Stop();

}
void Motor_Left(uint16_t duty, uint32_t time){
// time unit is 10ms
// only turn on left motor
    uint32_t timecount;
    timecount=0;
    P3->OUT |= 0x80;    // no_sleep = 1 pin P3.7
    while (timecount<=time) {
        P2->OUT |= 0x80;    // enable = 1 pin P2.7
        SysTick_Wait1us(duty);
        P2->OUT  &= ~0x80;  // enable = 0
        SysTick_Wait1us(10000-duty);
        timecount=timecount + 5;
    }
    Motor_Stop();

}
void Motor_Right(uint16_t duty, uint32_t time){
 // time unit is 10ms
 // only turn on right motor
    uint32_t timecount;
    timecount=0;
    P3->OUT |= 0x40;    // no_sleep = 1 pin P3.6
    while (timecount<=time) {
        P2->OUT |= 0x40;    // enable = 1 pin P2.6
        SysTick_Wait1us(duty);
        P2->OUT &= ~0x40;
        SysTick_Wait1us(10000-duty);
        timecount=timecount + 5;
    }
    Motor_Stop();
}
