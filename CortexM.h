/**
 * @file      CortexM.h
 * @brief     Basic functions used in these labs
 * @details   Used for enabling and disabling interrupts
 * @version   TI-RSLK MAX v1.1
 * @author    Daniel Valvano and Jonathan Valvano
 * @copyright Copyright 2019 by Jonathan W. Valvano, valvano@mail.utexas.edu,
 * @warning   AS-IS
 * @note      For more information see  http://users.ece.utexas.edu/~valvano/
 * @date      June 28, 2019

 ******************************************************************************/



#define STCTRL          (*((volatile uint32_t *)0xE000E010))
#define STRELOAD        (*((volatile uint32_t *)0xE000E014))
#define STCURRENT       (*((volatile uint32_t *)0xE000E018))
#define INTCTRL         (*((volatile uint32_t *)0xE000ED04))
#define SYSPRI1         (*((volatile uint32_t *)0xE000ED18))
#define SYSPRI2         (*((volatile uint32_t *)0xE000ED1C))
#define SYSPRI3         (*((volatile uint32_t *)0xE000ED20))
#define SYSHNDCTRL      (*((volatile uint32_t *)0xE000ED24))
#define FAULTSTAT       (*((volatile uint32_t *)0xE000ED28))
#define HFAULTSTAT      (*((volatile uint32_t *)0xE000ED2C))
#define MMADDR          (*((volatile uint32_t *)0xE000ED34))
#define FAULTADDR       (*((volatile uint32_t *)0xE000ED38))


/**
 * Disables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  Sets the I bit in the PRIMASK to disable interrupts.
 */
void DisableInterrupts(void); // Disable interrupts


/**
 * Enables Interrupts
 *
 * @param  none
 * @return none
 *
 * @brief  clears the I bit in the PRIMASK to enable interrupts
 */
void EnableInterrupts(void);  // Enable interrupts


/**
 * Start a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  none
 * @return copy of the PRIMASK (I bit) before StartCritical called
 *
 * @brief  Saves a copy of PRIMASK and disables interrupts
 */
long StartCritical(void);    


/**
 * End a critical section. Code between StartCritical and EndCritical is run atomically
 *
 * @param  sr is PRIMASK (I bit) before StartCritical called
 * @return none
 *
 * @brief  Sets PRIMASK with value passed in
 */
void EndCritical(long sr);    // restore I bit to previous value


/**
 * Enters low power sleep mode waiting for interrupt (WFI instruction)
 * processor sleeps until next hardware interrupt
 * returns after ISR has been run
 *
 * @param  none
 * @return none
 *
 * @brief  Enters low power sleep mode waiting for interrupt
 */
void WaitForInterrupt(void);  

