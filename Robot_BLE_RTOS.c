/*
 * Final Project ECE 6336
 * Team17: Vinh Hoang
 * Student ID 1022918
 */

#include <stdint.h>
#include "msp.h"
#include "SysTick.h"
#include "LaunchPad.h"
#include "Clock.h"
#include "MotorDC.h"
#include "Bump.h"
#include "CortexM.h"
#include "AP.h"

uint8_t  MotorData;
uint8_t  lineresult;

// Edge trigger interupt for bumper switches
void EdgeTrigger_Init(void){
    P4->SEL0 &= ~0xED;
    P4->SEL1 &= ~0xED;                 // configure P4.0 to P4.7 as GPIO
    P4->DIR &= ~0xED;                  // make P4.0 to P4.7 in
    P4->REN |= 0xED;                   // enable pull resistors
    P4->OUT |= 0xED;                   // P4.0 to P4.7 are pull-up
    P4->IES |= 0xED;                   // falling edge event
    P4->IFG &= ~0xED;                  // clear flag
    P4->IE |= 0xED;                    // arm interrupt
    NVIC->IP[9] = (NVIC->IP[9]&0xFF00FFFF)|0x00D00000; // priority 2
    NVIC->ISER[1] = 0x00000040;        // enable interrupt 38 on port 4
}

void PORT4_IRQHandler(void){
    Motor_Stop();
    SysTick_Wait10ms(100);
    Motor_Backward(4000,100);
    P4->IE &= ~0xED;  // disarm
}

void EdgeTrigger_Restart(void){
    P4->IFG &= ~0xED;                  // clear flag
    P4->IE |= 0xED;                    // rearm
}

void WriteMotorData(void){ // called on a SNP Characteristic Write Indication on characteristic ByteData
    switch (MotorData){
        case 8:
            //LaunchPad_Output(0x00);
            Motor_Forward(4000,100);  // 1 seconds and stop
            EdgeTrigger_Restart();
            break;
        case 6:
            //LaunchPad_Output(0x03);
            Motor_Left(4000,75);  // 0.75 seconds and stop
            EdgeTrigger_Restart();
            break;
        case 4:
            //LaunchPad_Output(0x00);
            Motor_Right(4000,75);  // 0.75 seconds and stop
            EdgeTrigger_Restart();
            break;
        case 2:
            Motor_Left(4000,75);  // 0.75 seconds and stop
            EdgeTrigger_Restart();
            break;

        default:
            Motor_Stop();

    }
}

void Reflectance_Init(void){
  P5->SEL0 &= ~0x08;
  P5->SEL1 &= ~0x08;    // configure P5.3 as GPIO
  P5->DIR |= 0x08;      // make P5.3 out
  P5->OUT &= ~0x08;     // turn off LEDs
  P7->SEL0 = 0x00;
  P7->SEL1 = 0x00;      // configure P7.7-P7.0 as GPIO
  P7->DIR = 0x00;       // make P7.7-P7.0 in
}

void Reflectance_Start(void){
  P5->OUT |= 0x08;      // turn on 8 IR LEDs
  P7->DIR = 0xFF;       // make P7.7-P7.0 out
  P7->OUT = 0xFF;       // prime for measurement
  Clock_Delay1us(10);   // wait 10 us
  P7->DIR = 0x00;       // make P7.7-P7.0 in
}

uint8_t Reflectance_End(void){
  uint8_t result;
  result = P7->IN;      // 0 means white
  P5->OUT &= ~0x08;     // turn off 8 IR LEDs
  return result;
}

int main(void){volatile int r;
    DisableInterrupts();
    Clock_Init48MHz();
    LaunchPad_Init();     // input from switches, output to LEDs on LaunchPad
    Bump_Init();          // bump switches
    Motor_Init();         // initialization motor
    Reflectance_Init();   // line sensor
    SysTick_Init();
    EdgeTrigger_Init();
    EnableInterrupts();
    r = AP_Init();
    AP_AddService(0xFFF0);

    //Add characteristic write only
    MotorData = 0;  // write-only parameter
    AP_AddCharacteristic(0xFFF3,4,&MotorData,0x02,0x08,"Motor Command",0,&WriteMotorData);  // permission == 2 write-only

    AP_RegisterService();
    AP_StartAdvertisement();

    while(1){
      AP_BackgroundProcess();  // handle incoming SNP frames

      // find black line
      Reflectance_Start();
      Clock_Delay1us(1000); // wait time 1ms
      lineresult = Reflectance_End();
      if (lineresult!=0){
          LaunchPad_Output(0x04); // turn on Blue LED
      }
      else{
          LaunchPad_Output(0x00); // turn off LED
      }
      Clock_Delay1ms(10);
    }
}

