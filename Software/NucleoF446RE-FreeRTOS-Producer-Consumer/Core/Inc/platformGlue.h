#ifndef PLATFORM_GLUE_H
#define PLATFORM_GLUE_H

#define PLATFORM_STM32F446

#define PLATFORM_HAS_UART
//#define PLATFORM_HAS_TIMER
//#define PLATFORM_HAS_I2C
//#define PLATFORM_HAS_SPI
//#define PLATFORM_HAS_WATCHDOG
//#define PLATFORM_HAS_CAN
//#define PLATFORM_HAS_RTC
//#define PLATFORM_HAS_ADC
//#define PLATFORM_HAS_USB
//#define PLATFORM_HAS_DAC

//#define PLATFORM_SAVE_ENERGY // in scheduler loop sleep instead of pull for sys-tick

#include "main.h" // -> includes "stm32f4xx_hal.h" and all drivers
#include "gpio.h"

/* *** Platform delay (polling) ******************************************************** */
#define MAX_DELAY		HAL_MAX_DELAY
#define DELAY(ms)       HAL_Delay(ms)
#define GET_TICK()      HAL_GetTick() 	// Provides a tick value in millisecond.
#define GET_CPU_TICKS()	DWT->CYCCNT		// Provides amount of CPU Clock tick, depending on main oscillator frequency.
#define DO_NOTHING()	__NOP()			// asm("nop") same as __NOP()

/* *** Platform return codes ********************************************************** */
#define DEVICE_STATUS_DEFINITION        HAL_StatusTypeDef
#define DEVICE_OK                       HAL_OK
#define DEVICE_ERROR                    HAL_ERROR
#define DEVICE_BUSY                     HAL_BUSY
#define DEVICE_TIMEOUT                  HAL_TIMEOUT

/* *** GPIO *************************************************************************** */
#define SW_NUCLEO   				B1_Pin
#define NUCLEO_BUTTON_READ()		HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)

#define NUCLEO_LED_turn_on()		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1)
#define NUCLEO_LED_turn_off()		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0)
#define NUCLEO_LED_toggle()			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin)

// green
#define LED_GREEN_ON() 				HAL_GPIO_WritePin(	LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET)
#define LED_GREEN_OFF()				HAL_GPIO_WritePin(	LED1_GPIO_Port, LED1_Pin, GPIO_PIN_RESET)
#define LED_GREEN_TOGGLE()			HAL_GPIO_TogglePin(	LED1_GPIO_Port, LED1_Pin)

#define SPI_CS_HIGH()				HAL_GPIO_WritePin(SPI1_nCS_GPIO_Port, SPI1_nCS_Pin, GPIO_PIN_SET)
#define SPI_CS_LOW()				HAL_GPIO_WritePin(SPI1_nCS_GPIO_Port, SPI1_nCS_Pin, GPIO_PIN_RESET);

#define TOGGLE_PIN(PORT, PIN)		HAL_GPIO_TogglePin(PORT, PIN)			/* void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin) */
#define WRITE_PIN(PORT, PIN, STATE)	HAL_GPIO_WritePin(PORT, PIN, STATE); 	/* void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState) */
#define READ_PIN(PORT, PIN)			HAL_GPIO_ReadPin(PORT, PIN)

/* *** UART *************************************************************************** */
#ifdef PLATFORM_HAS_UART
#include "usart.h"
#define UART_TERMINAL_HANDLER 	            			huart2
#define UART_TERMINAL_INSTANCE 	            			USART2
#define UART_TERMINAL_SEND(string, size)    			HAL_UART_Transmit(&UART_TERMINAL_HANDLER, string, size, HAL_MAX_DELAY)

#define UART_TERMINAL_READ_BYTE_IRQ(buffer)				HAL_UART_Receive_IT(&UART_TERMINAL_HANDLER, buffer, 1)
//#define UART_TERMINAL_READ_LINE_IRQ_DMA(buffer, size)	HAL_UARTEx_ReceiveToIdle_DMA(&UART_TERMINAL_HANDLER, buffer, size)

#define UART_TERMINAL_READ_LINE_IRQ(buffer, size)		HAL_UARTEx_ReceiveToIdle_IT(&UART_TERMINAL_HANDLER, buffer, size)

#define UART_RS485_HANDLER 	            				huart4
#define UART_RS485_INSTANCE 	            			UART4
#define UART_RS485_SEND(string, size)    				HAL_UART_Transmit(&UART_RS485_HANDLER, string, size, HAL_MAX_DELAY)
#define UART_RS485_READ_LINE_IRQ(buffer, size)			HAL_UARTEx_ReceiveToIdle_IT(&UART_RS485_HANDLER, buffer, size)

#endif

/* *** I2C ********************************************************************************/
#ifdef PLATFORM_HAS_I2C
#include "i2c.h"
#define I2C_HANDLER 				        								hi2c1
#define I2C_INSTANCE				        								I2C1
#define I2C_IS_DEVICE_READY(dev_address)    								HAL_I2C_IsDeviceReady(&I2C_HANDLER, dev_address, 1, 100)

#define I2C_READ_MEMORY(dev_address, mem_address, pRead_buffer, length) 	HAL_I2C_Mem_Read(	&I2C_HANDLER, dev_address, mem_address, I2C_MEMADD_SIZE_8BIT, pRead_buffer, length, 100)
#define I2C_WRITE_MEMORY(dev_address, mem_address, pWrite_buffer, length)	HAL_I2C_Mem_Write(	&I2C_HANDLER, dev_address, mem_address, I2C_MEMADD_SIZE_8BIT, pWrite_buffer, length, 100);

#define I2C_TRANSMIT(dev_address, pTXbuffer, length)						HAL_I2C_Master_Transmit(&I2C_HANDLER, dev_address, pTXbuffer, length, 100)
#define I2C_RECEIVE(dev_address, pRXbuffer, length)							HAL_I2C_Master_Receive( &I2C_HANDLER, dev_address, pRXbuffer, length, 100)

#endif
/* *** SPI ********************************************************************************/
#ifdef PLATFORM_HAS_SPI
#include "spi.h"
#define SPI_HANDLER 	            				hspi1
#define SPI_INSTANCE 	            				SPI1
#define SPI_SEND_RECEIVE(pTXData, pRXData, length)	HAL_SPI_TransmitReceive(&SPI_HANDLER, pTXData, pRXData, length, HAL_MAX_DELAY);
#endif
/* *** Hardware Timer *********************************************************************/
#ifdef PLATFORM_HAS_TIMER
#include "tim.h"
#define TIMER_HANLDER 								htim12
#define TIMER_INSTANCE								TIM12
#define TIMER_START_PWM_CH1()						HAL_TIM_PWM_Start(&TIMER_HANLDER, TIM_CHANNEL_1);
#define TIMER_START_PWM_CH2()						HAL_TIM_PWM_Start(&TIMER_HANLDER, TIM_CHANNEL_2);
#define TIMER_SET_PWM_DUTY_CYCLE_CH1(dutyCycle) 	__HAL_TIM_SET_COMPARE(&TIMER_HANLDER, TIM_CHANNEL_1, dutyCycle);
#define TIMER_SET_PWM_DUTY_CYCLE_CH2(dutyCycle) 	__HAL_TIM_SET_COMPARE(&TIMER_HANLDER, TIM_CHANNEL_2, dutyCycle);

/* *** Watch Dog **************************************************************************/
#ifdef PLATFORM_HAS_WATCHDOG
#include "iwdg.h"
#define WATCHDOG_REFRESH()							HAL_IWDG_Refresh(&hiwdg);
#endif

#endif
/* *** Real Time Clock ********************************************************************/
#ifdef PLATFORM_HAS_RTC
#include "rtc.h"
#define RTC_HANDLER             hrtc
#define RTC_INSTANCE            RTC
#define SET_DEVICE_TIME(sTime)  HAL_RTC_SetTime( &RTC_HANDLER, sTime, RTC_FORMAT_BIN)
#define SET_DEVICE_DATE(sDate)  HAL_RTC_SetDate( &RTC_HANDLER, sDate, RTC_FORMAT_BIN)
#define GET_DEVICE_TIME(sTime)  HAL_RTC_GetTime( &RTC_HANDLER, sTime, RTC_FORMAT_BIN)
#define GET_DEVICE_DATE(sDate)  HAL_RTC_GetDate( &RTC_HANDLER, sDate, RTC_FORMAT_BIN)
#endif

/* *** CAN ********************************************************************/
/* also consider to adjust the CAN-driver functions! */
#ifdef PLATFORM_HAS_CAN
#include "can.h"
#define CAN_HANDLER 							hcan2
#define CAN_INSTANCE            				CAN2
#define CAN_CONFIGURE_FILTER(canFilterConfig)	HAL_CAN_ConfigFilter(	&CAN_HANDLER, &canFilterConfig)
#define CAN_START_PERIPHERAL() 					HAL_CAN_Start(			&CAN_HANDLER)
#define CAN_STOP_PERIPHERAL() 					HAL_CAN_Stop(  			&CAN_HANDLER)
#define CAN_ACTIVATE_RX_INTERRUPT() 			HAL_CAN_ActivateNotification(	&CAN_HANDLER, CAN_IT_RX_FIFO0_MSG_PENDING)
static uint32_t  TxMailbox1;
#define SEND_CAN_MESSAGE(txHeader, txData) 		HAL_CAN_AddTxMessage(&CAN_HANDLER, &txHeader, txData, &TxMailbox1);
#endif

/* *** ADC ********************************************************************/
#ifdef PLATFORM_HAS_ADC
#include "adc.h"
#define ADC_HANDLER 				hadc1
#define ADC_INSTANCE				ADC1
#define ADC_NO_OF_CHANNELS 			7

#define ADC_START_DMA(pADC_raw_data_buffer)		HAL_ADC_Start_DMA(&ADC_HANDLER, (uint32_t*) pADC_raw_data_buffer, ADC_NO_OF_CHANNELS)

#define ADC_CALC_REF_VOLTAGE(int_ref_volt_sample)					__LL_ADC_CALC_VREFANALOG_VOLTAGE(int_ref_volt_sample, 		LL_ADC_RESOLUTION_12B)
#define ADC_CALC_DATA_TO_MILLI_VOLT(ref_milli_volt, adc_raw_data)	__LL_ADC_CALC_DATA_TO_VOLTAGE(ref_milli_volt, adc_raw_data, LL_ADC_RESOLUTION_12B)
#endif

/* *** UID ********************************************************************/
typedef union {
	uint32_t uid[3];
	uint8_t uid_byte[12]; // 3 * uint32 = 3 * 4bytes = 12 uint8
} cpu_uid_t;

#define READ_CPU_UID(cpu_uid_type)	{cpu_uid_type.uid[0] = HAL_GetUIDw0(); cpu_uid_type.uid[1] = HAL_GetUIDw1(); cpu_uid_type.uid[2] = HAL_GetUIDw2();}


#endif /* PLATFORM_GLUE_H */
