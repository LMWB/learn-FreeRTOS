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
#include "platformGlue.h"
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
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
/* Definitions for myPrintfTask1 */
osThreadId_t myPrintfTask1Handle;
const osThreadAttr_t myPrintfTask1_attributes = {
  .name = "myPrintfTask1",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myPrintfTask2 */
osThreadId_t myPrintfTask2Handle;
const osThreadAttr_t myPrintfTask2_attributes = {
  .name = "myPrintfTask2",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for myPrintfTask3 */
osThreadId_t myPrintfTask3Handle;
const osThreadAttr_t myPrintfTask3_attributes = {
  .name = "myPrintfTask3",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityLow,
};
/* Definitions for printfMutex */
osMutexId_t printfMutexHandle;
const osMutexAttr_t printfMutex_attributes = {
  .name = "printfMutex"
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);
void startMyPrintfTask1(void *argument);
void startMyPrintfTask2(void *argument);
void startMyPrintfTask3(void *argument);

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
  /* creation of printfMutex */
  printfMutexHandle = osMutexNew(&printfMutex_attributes);

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* creation of myPrintfTask1 */
  myPrintfTask1Handle = osThreadNew(startMyPrintfTask1, NULL, &myPrintfTask1_attributes);

  /* creation of myPrintfTask2 */
  myPrintfTask2Handle = osThreadNew(startMyPrintfTask2, NULL, &myPrintfTask2_attributes);

  /* creation of myPrintfTask3 */
  myPrintfTask3Handle = osThreadNew(startMyPrintfTask3, NULL, &myPrintfTask3_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */

  printf("Starting FreeRTOS Demo 1\r\n");
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
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
  for(;;)
  {
    osDelay(1);
  }
  /* USER CODE END StartDefaultTask */
}

/* USER CODE BEGIN Header_startMyPrintfTask1 */
/**
* @brief Function implementing the myPrintfTask1 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startMyPrintfTask1 */
void startMyPrintfTask1(void *argument)
{
  /* USER CODE BEGIN startMyPrintfTask1 */
  /* Infinite loop */
	// Converts 500ms safely into the correct number of ticks
	uint32_t t1 = (500U * osKernelGetTickFreq()) / 1000U;
	uint32_t t2 = pdMS_TO_TICKS(500);
  for(;;)
  {
	  NUCLEO_LED_toggle();


	  // https://arm-software.github.io/CMSIS_6/main/RTOS2/group__CMSIS__RTOS__Wait.html
	  osDelay(t1);

	  //osDelayUntil(500);
  }
  /* USER CODE END startMyPrintfTask1 */
}

/* USER CODE BEGIN Header_startMyPrintfTask2 */
/**
* @brief Function implementing the myPrintfTask2 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startMyPrintfTask2 */
__weak void startMyPrintfTask2(void *argument)
{
  /* USER CODE BEGIN startMyPrintfTask2 */
  /* Infinite loop */
  for(;;)
  {
	  osMutexAcquire(printfMutexHandle, osWaitForever);
	  printf("Hello From Task 2\n");
	  osMutexRelease(printfMutexHandle);
    osDelay(250);
  }
  /* USER CODE END startMyPrintfTask2 */
}

/* USER CODE BEGIN Header_startMyPrintfTask3 */
/**
* @brief Function implementing the myPrintfTask3 thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_startMyPrintfTask3 */
__weak void startMyPrintfTask3(void *argument)
{
  /* USER CODE BEGIN startMyPrintfTask3 */
  /* Infinite loop */
	uint32_t cnt = 0;
  for(;;)
  {
	  osMutexAcquire(printfMutexHandle, osWaitForever);
	  printf("\tHello From Task 3: %ld\n", cnt);
	  osMutexRelease(printfMutexHandle);

	  cnt++;
    osDelay(500);
  }
  /* USER CODE END startMyPrintfTask3 */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

/* USER CODE END Application */

