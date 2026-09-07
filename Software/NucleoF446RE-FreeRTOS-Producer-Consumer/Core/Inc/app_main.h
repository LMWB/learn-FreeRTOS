#ifndef INC_APP_MAIN_H_
#define INC_APP_MAIN_H_

extern osMessageQueueId_t producer_01_queueHandle;
extern osMessageQueueId_t producer_02_queueHandle;
extern osMessageQueueId_t producer_03_queueHandle;

extern osMutexId_t uart_mutexHandle;
extern osMutexId_t spi_mutexHandle;
extern osMutexId_t i2c_mutexHandle;


#endif /* INC_APP_MAIN_H_ */
