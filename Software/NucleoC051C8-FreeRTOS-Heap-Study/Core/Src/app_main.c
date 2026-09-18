#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"

#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include "app_freertos.h"

#define FREQUENCY 		1 	// Hz
#define SAMPLING_MS 	100	// milli seconds


void StartDefaultTask(void *argument) {

	adc_message_t msg1 = { .adc = 1, .value = 12345 };

	adc_message_packed_t msg2 = { .adc = 1, .value = 12345 };

	uint16_t s = sizeof(msg1);
	printf("size is: %d bytes\n", s); // delivers 8 bytes because uint8 will be represented as 32uint

	s = sizeof(msg2);
	printf("size is: %d bytes\n", s);
	// delivers 5 bytes because uint8 will be represented as 8uint
	// In C, a packed structure instructs the compiler to remove
	// all automatic padding bytes between structure members, minimizing its memory footprint

	for (;;) {
		osDelay(1000);
	}
}

void StartTask02(void *argument) {
	static uint32_t t = 0;
	while (1) {
		float s = sinf(2 * M_PI * FREQUENCY * t / 1000);
		s = s;
		adc_message_packed_t msg = { .adc = 1, .value = t };

		osMessageQueuePut(myQueue01Handle, &msg, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void StartTask03(void *argument) {
	static uint32_t t = 0;
	while (1) {
		float s = cosf(2 * M_PI * FREQUENCY * t / 1000);
		s = s;
		adc_message_packed_t msg = { .adc = 2, .value = 10*t };

		osMessageQueuePut(myQueue01Handle, &msg, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void StartTask04(void *argument) {
	static uint32_t t = 0;

	while (1) {
		float s = tanf(2 * M_PI * FREQUENCY * t / 1000);
		s = s;
		adc_message_packed_t msg = { .adc = 3, .value = 100*t };

		osMessageQueuePut(myQueue01Handle, &msg, 0, osWaitForever);

		t += SAMPLING_MS;
		osDelay(SAMPLING_MS);
	}
}

void StartTask05(void *argument) {
	adc_message_packed_t msg;
	while (1) {
		if (osMessageQueueGet(myQueue01Handle, &msg, NULL, osWaitForever) == osOK) {
			switch (msg.adc) {
			case 1:
				osMutexAcquire(myMutex01Handle, osWaitForever); // does not need because inside switch case no concurrency
				printf("Consumer %d data: %ld\n", msg.adc, msg.value);
				osMutexRelease(myMutex01Handle);
				break;

			case 2:
				osMutexAcquire(myMutex01Handle, osWaitForever);
				printf("\tConsumer %d data: %ld\n", msg.adc, msg.value);
				osMutexRelease(myMutex01Handle);
				break;

			case 3:
				osMutexAcquire(myMutex01Handle, osWaitForever);
				printf("\t\tConsumer %d data: %ld\n", msg.adc, msg.value);
				osMutexRelease(myMutex01Handle);
				break;

			case 4:
				osMutexAcquire(myMutex01Handle, osWaitForever);
				printf("\t\t\tConsumer %d data: %ld\n", msg.adc, msg.value);
				osMutexRelease(myMutex01Handle);
				break;
			}
		}
	}
}

void StartTask06(void *argument) {

	for (;;) {
		HAL_GPIO_TogglePin(User_LED1_GPIO_Port, User_LED1_Pin);
		osDelay(500);
	}
}

void StartTask07(void *argument) {

	for (;;) {
		osDelay(100);
	}
}

void StartTask08(void *argument) {

	for (;;) {
		osDelay(100);
	}
}

