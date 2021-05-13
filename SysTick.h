/**
 * Initialize SysTick with busy wait running at bus clock
 *
 * @param  none
 * @return none
 * @note   The system bus clock affects this module
 * @brief  Initialize SysTick
 */
void SysTick_Init(void);


/**
 * Time delay using busy wait
 *
 * @param   delay is the number of bus cycles to wait
 * @return  none
 * @note    The system bus clock affects this module
 * @warning SysTick_Init must be called before calling this function
 * @brief   Time delay using SysTick
 */
void SysTick_Wait(uint32_t delay);

/**
 * Time delay using busy wait
 *
 * @param   delay is the time in 10-ms units
 * @return  none
 * @note    assumes 48 MHz bus clock
 * @warning SysTick_Init must be called before calling this function
 * @brief   Time delay using SysTick
 */
void SysTick_Wait10ms(uint32_t delay);

void SysTick_Wait1us(uint32_t delay);
