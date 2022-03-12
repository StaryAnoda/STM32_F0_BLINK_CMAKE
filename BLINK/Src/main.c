#include <stdbool.h>
#include <stdlib.h>

#include "stm32f030x6.h"

//STM32_Programmer_CLI.exe -c port=SWD -d XXX.bin 0x08000000

#define PIN_BUTTON              GPIO_IDR_0

#define PIN_LED_1               GPIO_ODR_1
#define PIN_LED_2               GPIO_ODR_2
#define PIN_LED_3               GPIO_ODR_3

#define TICK_PER_SECOND 10
#define UART_BAUDRATE 115200

void USART1_GPIO_Config(void);
void USART1_Config(void);
void USART1_Send_Char(const char c);
void USART1_Send_String(const char * string);

void LED_GPIO_Config(void);
void BUTTON_GPIO_Config(void);

int main(void)
{
	LED_GPIO_Config();
	BUTTON_GPIO_Config();

	USART1_GPIO_Config();
	USART1_Config();

	SysTick_Config(SystemCoreClock / TICK_PER_SECOND);

	for(;;)
	{
	}
	return EXIT_SUCCESS;
}


void SysTick_Handler(void)
{
	if(!(GPIOA -> IDR & PIN_BUTTON))
	{
		GPIOA -> ODR ^= PIN_LED_1;
	}

	GPIOA -> ODR ^= PIN_LED_2;
	GPIOA -> ODR ^= PIN_LED_3;
	USART1_Send_String("TEST CMAKE \r\n");
}

void LED_GPIO_Config(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA -> MODER |= GPIO_MODER_MODER1_0 | GPIO_MODER_MODER2_0 | GPIO_MODER_MODER3_0;
}

void BUTTON_GPIO_Config(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA -> PUPDR |= GPIO_PUPDR_PUPDR0_0;
}

void USART1_GPIO_Config(void)
{
	RCC -> AHBENR |= RCC_AHBENR_GPIOAEN;

	GPIOA -> MODER |= GPIO_MODER_MODER9_1 | GPIO_MODER_MODER10_1;
	GPIOA -> AFR[1] |= (1 << (1 * 4)) | (1 << (2 * 4));
}

void USART1_Config(void)
{
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;

	USART1 -> BRR = SystemCoreClock / UART_BAUDRATE;
	USART1 -> CR1 = USART_CR1_TE | USART_CR1_UE;
}

void USART1_Send_Char(const char c)
{
	USART1 -> TDR = c;
	while(!(USART1 -> ISR & USART_ISR_TC));
}

void USART1_Send_String(const char * string)
{
	while(*string)
	{
		USART1_Send_Char(*string++);
	}
}
