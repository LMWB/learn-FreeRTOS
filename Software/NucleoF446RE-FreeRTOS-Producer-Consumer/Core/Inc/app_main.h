#ifndef INC_APP_MAIN_H_
#define INC_APP_MAIN_H_


extern osThreadId_t producer_01Handle;
extern osThreadId_t producer_02Handle;
extern osThreadId_t producer_03Handle;
extern osThreadId_t producer_04Handle;

extern osThreadId_t consumer_01Handle;
extern osThreadId_t consumer_02Handle;
extern osThreadId_t consumer_03Handle;
extern osThreadId_t consumer_04Handle;

extern osMessageQueueId_t producer_01_queueHandle;
extern osMessageQueueId_t producer_02_queueHandle;
extern osMessageQueueId_t producer_03_queueHandle;

extern osMutexId_t uart_mutexHandle;
extern osMutexId_t spi_mutexHandle;
extern osMutexId_t i2c_mutexHandle;


#endif /* INC_APP_MAIN_H_ */
