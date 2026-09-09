#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#include "platformGlue.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

/* Producer Consumer Example
 * cubeIDE FreeRTOS project generation with cmsis v2 wrapper
 *
 * 4 producer threads with generates data (e.g. dummy to adc sampling)
 * 4 consumer threads that processes the data (e.g. filter, calculator, ...) and send to UART
 * 4 queues that connects producer and consumer
 *
 * Mutex that reserve hardware resources
 *
 * Semaphore not relevant?
 *
 * todo
 * activate float on freeRTOS
 * activate float on CortexF4
 *
 *
 * */

#include "app_main.h"

#define SIZE 20

static float A[SIZE][SIZE];
static float B[SIZE][SIZE];
static float C[SIZE][SIZE];

static void HeavyTask1(void);
static void HeavyTask2(void);

#define FREQUENCY 		1 	// Hz
#define SAMPLING_MS 	100	// milli seconds


// Overwrite
// the define to make this callback work lives in FreeRTOS.h line 398
// #define configCHECK_FOR_STACK_OVERFLOW
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
	printf("STACK OVERFLOW: %s\r\n", pcTaskName);
	while (1) {}
}

// static implementation of watermark measurement
// shows remaining stack in unit words and bytes
static void PrintStackWatermark(const char *name, osThreadId_t handle) {
	UBaseType_t watermark;

	watermark = uxTaskGetStackHighWaterMark((TaskHandle_t) handle);

	printf("%s: %lu words (%lu bytes)\r\n",
			name,
			(unsigned long) watermark,
			(unsigned long) (watermark * sizeof(StackType_t)));
}

void StartDefaultTask(void *argument)
{
    while (1)
    {
        osMutexAcquire(uart_mutexHandle, osWaitForever);
        printf("remaining stack \r\n");
        PrintStackWatermark("producer_01", producer_01Handle);
        PrintStackWatermark("producer_02", producer_02Handle);
        PrintStackWatermark("producer_03", producer_03Handle);
        PrintStackWatermark("producer_04", producer_04Handle);

        PrintStackWatermark("consumer_01", consumer_01Handle);
        PrintStackWatermark("consumer_02", consumer_02Handle);
        PrintStackWatermark("consumer_03", consumer_03Handle);
        PrintStackWatermark("consumer_04", consumer_04Handle);
        printf("\r\n");

        osMutexRelease(uart_mutexHandle);

        NUCLEO_LED_toggle();

        osDelay(1000);
    }
}

void start_producer_01(void *argument) {
	static uint32_t t = 0; // time in milli seconds
	while (1) {
		float s = sinf( 2*M_PI*FREQUENCY*t/1000 );
		int32_t s1 = s*1000;

		osMessageQueuePut(producer_01_queueHandle, &s1, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void start_producer_02(void *argument) {
	static uint32_t t = 0;
	while (1) {
		float s = cosf(2 * M_PI * FREQUENCY * t / 1000);
		int32_t s1 = s * 1000;

		osMessageQueuePut(producer_02_queueHandle, &s1, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void start_producer_03(void *argument) {
	static uint32_t t = 0;
	while (1) {
		float s = tanf(2 * M_PI * FREQUENCY * t / 1000);
		int32_t s1 = s * 1000;

		osMessageQueuePut(producer_03_queueHandle, &s1, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void start_producer_04(void *argument) {
	while (1) {
		HeavyTask1();
		HeavyTask2();
		osDelay(SAMPLING_MS);
	}
}

void start_consumer_01(void *argument) {
	int32_t value = 0;

	while (1) {
		if (osMessageQueueGet(producer_01_queueHandle, &value, NULL,osWaitForever) == osOK) {
			osMutexAcquire(uart_mutexHandle, osWaitForever);
			printf("Consumer 01 %ld\n", value);
			osMutexRelease(uart_mutexHandle);
		}
		osDelay(10);
	}

}

void start_consumer_02(void *argument)
{
	int32_t value = 0;

	while (1) {
		if (osMessageQueueGet(producer_02_queueHandle, &value, NULL,osWaitForever) == osOK) {
			osMutexAcquire(uart_mutexHandle, osWaitForever);
			printf("\tConsumer 02 %ld\n", value);
			osMutexRelease(uart_mutexHandle);
		}
		osDelay(10);
	}
}

void start_consumer_03(void *argument)
{
	int32_t value = 0;

	while (1) {
		if (osMessageQueueGet(producer_03_queueHandle, &value, NULL,osWaitForever) == osOK) {
			osMutexAcquire(uart_mutexHandle, osWaitForever);
			printf("\t\tConsumer 03 %ld\n", value);
			osMutexRelease(uart_mutexHandle);
		}
		osDelay(10);
	}
}

void start_consumer_04(void *argument)
{
  for(;;)
  {
    osDelay(10);
  }
}

/* A simple version is a Monte-Carlo estimation of π: */
void HeavyTask1(void) {
	uint32_t inside = 0;
	uint32_t total = 0;

	for (uint32_t i = 0; i < 100000; i++) {
		float x = (float) rand() / RAND_MAX;
		float y = (float) rand() / RAND_MAX;

		if ((x * x + y * y) <= 1.0f) {
			inside++;
		}

		total++;
	}

	float pi = 4.0f * (float) inside / (float) total;

	// Do something with pi so the compiler can't optimize everything away
	pi = pi;
}

/* Matrix multiplication repeatedly multiply two matrices: */
void HeavyTask2(void) {

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			float sum = 0.0f;

			for (int k = 0; k < SIZE; k++) {
				sum += A[i][k] * B[k][j];
			}

			C[i][j] = sum;
		}
	}
}
