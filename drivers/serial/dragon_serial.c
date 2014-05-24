/*
 * stm32f10x_serial.c
 *
 *  Created on: 1 maj 2014
 *      Author: grzybek
 */

#include "stm32f10x.h"
#include "serial.h"

/*
 * Initialize the serial port.
 */
int serial_init(void)
{
	USART_InitTypeDef USART_InitStructure;
	USART_ClockInitTypeDef USART_InitClockStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_TypeDef * USARTx = USART1;

	/* Enable USART1 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA,
			ENABLE);

	/* Configure USART1 Rx (PA10) as input floating */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA9) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	USART_InitStructure.USART_BaudRate = 115200;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_InitClockStructure.USART_Clock = USART_Clock_Disable;
	USART_InitClockStructure.USART_CPOL = USART_CPOL_Low;
	USART_InitClockStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_InitClockStructure.USART_LastBit = USART_LastBit_Disable;

	USART_Init(USARTx, &USART_InitStructure);
	USART_ClockInit(USARTx, &USART_InitClockStructure);

	USART_Cmd(USARTx, ENABLE);

	return 0;
}

/*
 * Set new baudrate.
 */
void serial_setbrg(void)
{

}

/*
 * Read a single character from the serial port.
 */
int serial_getc(void)
{
	while(USART_GetFlagStatus( USART1, USART_FLAG_RXNE ) == RESET);
	return USART_ReceiveData(USART1);
}

/*
 * Put a single character to the serial port.
 */
void serial_putc(const char c)
{
	if (c == '\n')
		serial_putc('\r');

	while(USART_GetFlagStatus( USART1, USART_FLAG_TXE ) == RESET);
	USART_SendData(USART1,(uint16_t)c);
}

/*
 * Put a string ('\0'-terminated) to the serial port.
 */
void serial_puts(const char *s)
{
	while (*s)
		serial_putc(*s++);
}

/*
 * Test whether a character in in the RX buffer.
 */
int serial_tstc(void)
{
	return (USART_GetFlagStatus(USART1,USART_FLAG_RXNE) == SET ? 1:0);
	//return (usart_regs->sr & STM32_USART_SR_RXNE) ? 1 : 0;
}
