/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */

/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for producer_01 */
osThreadId_t producer_01Handle;
const osThreadAttr_t producer_01_attributes = {
  .name = "producer_01",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for producer_02 */
osThreadId_t producer_02Handle;
const osThreadAttr_t producer_02_attributes = {
  .name = "producer_02",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for producer_03 */
osThreadId_t producer_03Handle;
const osThreadAttr_t producer_03_attributes = {
  .name = "producer_03",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for producer_04 */
osThreadId_t producer_04Handle;
const osThreadAttr_t producer_04_attributes = {
  .name = "producer_04",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal1,
};
/* Definitions for consumer_01 */
osThreadId_t consumer_01Handle;
const osThreadAttr_t consumer_01_attributes = {
  .name = "consumer_01",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for consumer_02 */
osThreadId_t consumer_02Handle;
const osThreadAttr_t consumer_02_attributes = {
  .name = "consumer_02",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for consumer_03 */
osThreadId_t consumer_03Handle;
const osThreadAttr_t consumer_03_attributes = {
  .name = "consumer_03",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for consumer_04 */
osThreadId_t consumer_04Handle;
const osThreadAttr_t consumer_04_attributes = {
  .name = "consumer_04",
  .stack_size = 128 * 4 * 2,
  .priority = (osPriority_t) osPriorityNormal2,
};
/* Definitions for producer_01_queue */
osMessageQueueId_t producer_01_queueHandle;
const osMessageQueueAttr_t producer_01_queue_attributes = {
  .name = "producer_01_queue"
};
/* Definitions for producer_02_queue */
osMessageQueueId_t producer_02_queueHandle;
const osMessageQueueAttr_t producer_02_queue_attributes = {
  .name = "producer_02_queue"
};
/* Definitions for producer_03_queue */
osMessageQueueId_t producer_03_queueHandle;
const osMessageQueueAttr_t producer_03_queue_attributes = {
  .name = "producer_03_queue"
};
/* Definitions for producer_04_queue */
osMessageQueueId_t producer_04_queueHandle;
const osMessageQueueAttr_t producer_04_queue_attributes = {
  .name = "producer_04_queue"
};
/* Definitions for uart_mutex */
osMutexId_t uart_mutexHandle;
const osMutexAttr_t uart_mutex_attributes = {
  .name = "uart_mutex"
};
/* Definitions for spi_mutex */
osMutexId_t spi_mutexHandle;
const osMutexAttr_t spi_mutex_attributes = {
  .name = "spi_mutex"
};
/* Definitions for i2C_mutex */
osMutexId_t i2C_mutexHandle;
const osMutexAttr_t i2C_mutex_attributes = {
  .name = "i2C_mutex"
};
/* Definitions for buttonSemaphore */
osSemaphoreId_t buttonSemaphoreHandle;
const osSemaphoreAttr_t buttonSemaphore_attributes = {
  .name = "buttonSemaphore"
};
/* Definitions for producer_01_semaphore */
osSemaphoreId_t producer_01_semaphoreHandle;
const osSemaphoreAttr_t producer_01_semaphore_attributes = {
  .name = "producer_01_semaphore"
};
/* Definitions for producer_02_semaphore */
osSemaphoreId_t producer_02_semaphoreHandle;
const osSemaphoreAttr_t producer_02_semaphore_attributes = {
  .name = "producer_02_semaphore"
};
/* Definitions for producer_03_semaphore */
osSemaphoreId_t producer_03_semaphoreHandle;
const osSemaphoreAttr_t producer_03_semaphore_attributes = {
  .name = "producer_03_semaphore"
};
/* Definitions for producer_04_semaphore */
osSemaphoreId_t producer_04_semaphoreHandle;
const osSemaphoreAttr_t producer_04_semaphore_attributes = {
  .name = "producer_04_semaphore"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void start_producer_01(void *argument);
void start_producer_02(void *argument);
void start_producer_03(void *argument);
void start_producer_04(void *argument);
void start_consumer_01(void *argument);
void start_consumer_02(void *argument);
void start_consumer_03(void *argument);
void start_consumer_04(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */
  /* Create the mutex(es) */
  /* creation of uart_mutex */
  uart_mutexHandle = osMutexNew(&uart_mutex_attributes);

  /* creation of spi_mutex */
  spi_mutexHandle = osMutexNew(&spi_mutex_attributes);

  /* creation of i2C_mutex */
  i2C_mutexHandle = osMutexNew(&i2C_mutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* creation of buttonSemaphore */
  buttonSemaphoreHandle = osSemaphoreNew(1, 0, &buttonSemaphore_attributes);

  /* creation of producer_01_semaphore */
  producer_01_semaphoreHandle = osSemaphoreNew(1, 0, &producer_01_semaphore_attributes);

  /* creation of producer_02_semaphore */
  producer_02_semaphoreHandle = osSemaphoreNew(1, 0, &producer_02_semaphore_attributes);

  /* creation of producer_03_semaphore */
  producer_03_semaphoreHandle = osSemaphoreNew(1, 0, &producer_03_semaphore_attributes);

  /* creation of producer_04_semaphore */
  producer_04_semaphoreHandle = osSemaphoreNew(1, 0, &producer_04_semaphore_attributes);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* Create the queue(s) */
  /* creation of producer_01_queue */
  producer_01_queueHandle = osMessageQueueNew (8, sizeof(uint32_t), &producer_01_queue_attributes);

  /* creation of producer_02_queue */
  producer_02_queueHandle = osMessageQueueNew (8, sizeof(uint32_t), &producer_02_queue_attributes);

  /* creation of producer_03_queue */
  producer_03_queueHandle = osMessageQueueNew (8, sizeof(uint32_t), &producer_03_queue_attributes);

  /* creation of producer_04_queue */
  producer_04_queueHandle = osMessageQueueNew (8, sizeof(uint32_t), &producer_04_queue_attributes);

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of producer_01 */
  producer_01Handle = osThreadNew(start_producer_01, NULL, &producer_01_attributes);

  /* creation of producer_02 */
  producer_02Handle = osThreadNew(start_producer_02, NULL, &producer_02_attributes);

  /* creation of producer_03 */
  producer_03Handle = osThreadNew(start_producer_03, NULL, &producer_03_attributes);

  /* creation of producer_04 */
  producer_04Handle = osThreadNew(start_producer_04, NULL, &producer_04_attributes);

  /* creation of consumer_01 */
  consumer_01Handle = osThreadNew(start_consumer_01, NULL, &consumer_01_attributes);

  /* creation of consumer_02 */
  consumer_02Handle = osThreadNew(start_consumer_02, NULL, &consumer_02_attributes);

  /* creation of consumer_03 */
  consumer_03Handle = osThreadNew(start_consumer_03, NULL, &consumer_03_attributes);

  /* creation of consumer_04 */
  consumer_04Handle = osThreadNew(start_consumer_04, NULL, &consumer_04_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  printf("Starting FreeRTOS Demo 2\r\n");
  printf("FreeRTOS version: %s\r\n", tskKERNEL_VERSION_NUMBER);
  /* USER CODE END RTOS_EVENTS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
__weak void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_start_producer_01 */
/**
* @brief Function implementing the producer_01 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_producer_01 */
__weak void start_producer_01(void *argument)
{
  /* USER CODE BEGIN start_producer_01 */
  /* Infinite loop */
  for(;;)
  {


    osDelay(1);
  }
  /* USER CODE END start_producer_01 */
}

/* USER CODE BEGIN Header_start_producer_02 */
/**
* @brief Function implementing the producer_02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_producer_02 */
__weak void start_producer_02(void *argument)
{
  /* USER CODE BEGIN start_producer_02 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_producer_02 */
}

/* USER CODE BEGIN Header_start_producer_03 */
/**
* @brief Function implementing the producer_03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_producer_03 */
__weak void start_producer_03(void *argument)
{
  /* USER CODE BEGIN start_producer_03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_producer_03 */
}

/* USER CODE BEGIN Header_start_producer_04 */
/**
* @brief Function implementing the producer_04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_producer_04 */
__weak void start_producer_04(void *argument)
{
  /* USER CODE BEGIN start_producer_04 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_producer_04 */
}

/* USER CODE BEGIN Header_start_consumer_01 */
/**
* @brief Function implementing the consumer_01 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_consumer_01 */
__weak void start_consumer_01(void *argument)
{
  /* USER CODE BEGIN start_consumer_01 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_consumer_01 */
}

/* USER CODE BEGIN Header_start_consumer_02 */
/**
* @brief Function implementing the consumer_02 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_consumer_02 */
__weak void start_consumer_02(void *argument)
{
  /* USER CODE BEGIN start_consumer_02 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_consumer_02 */
}

/* USER CODE BEGIN Header_start_consumer_03 */
/**
* @brief Function implementing the consumer_03 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_consumer_03 */
__weak void start_consumer_03(void *argument)
{
  /* USER CODE BEGIN start_consumer_03 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_consumer_03 */
}

/* USER CODE BEGIN Header_start_consumer_04 */
/**
* @brief Function implementing the consumer_04 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_start_consumer_04 */
__weak void start_consumer_04(void *argument)
{
  /* USER CODE BEGIN start_consumer_04 */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END start_consumer_04 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

