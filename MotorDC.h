#ifndef MOTORDC_H_
#define MOTORDC_H_

/**
 * Initializes the 6 GPIO lines and puts driver to sleep.<br>
 * This simple set of drivers does not use hardware timer PWM.
 * Rather, it uses software delays with SysTick and consumes all the
 * processor time. This function assumes pin configuration of RSLK 1.1
 * @param none
 * @return none
 * @note Returns right away.
 * @brief  Initialize motor interface
 */
void Motor_Init(void);



/**
 * Stops both motors, puts driver to sleep.
 * This function assumes pin configuration of RSLK 1.1
 * @param none
 * @return none
 * @note Returns right away.
 * @brief  Stops the motors
 */
void Motor_Stop(void);


/**
 * Drives both motors forward at duty (100 to 9900).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * This function assumes pin configuration of RSLK 1.1
 * @param duty duty cycle of both wheels (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run both motors forward
 */
void Motor_Forward(uint16_t duty, uint32_t time);


/**
 * Drives both motors backward at duty (100 to 9900).
 * Runs for time duration (units=10ms), and then stops.
 * Runs even if any bumper switch is active.
 * Returns after time*10ms.
 * This function assumes pin configuration of RSLK 1.1
 * @param duty duty cycle of both wheels (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed.
 * @brief  Run both motors backward
 */
void Motor_Backward(uint16_t duty, uint32_t time);


/**
 * Drives just the left motor forward at duty (100 to 9900).
 * Right motor is stopped (sleeping).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * This function assumes pin configuration of RSLK 1.1
 * @param duty duty cycle of left wheel (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run left motor forward
 */
void Motor_Left(uint16_t duty, uint32_t time);


/**
 * Drives just the right motor forward at duty (100 to 9900).
 * Left motor is stopped (sleeping).
 * Runs for time duration (units=10ms), and then stops.
 * Stop the motors and return if any bumper switch is active.
 * Returns after time*10ms or if a bumper switch is hit.
 * This function assumes pin configuration of RSLK 1.1
 * @param duty duty cycle of right wheel (100 to 9900)
 * @param time duration (10ms) to run
 * @return none
 * @note Does not return until time has elapsed or any bumper switch is active.
 * @brief  Run right motor forward
 */
void Motor_Right(uint16_t duty, uint32_t time);



#endif /* MOTORDC_H_ */
