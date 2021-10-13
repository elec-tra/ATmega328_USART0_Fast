/*
 * main.c
 *
 *  Created on: Oct 13, 2021
 *      Author: saranyan
 */

#include <avr/io.h>
#include <util/delay.h>
#include "common_preprocessors.h"
#include "power_management.h"
#include "usart0.h"

#define FOSC 16000000 					/*MCU Clock Speed*/
#define BAUD 115200						/*Required Baud Rate*/
#define MYUBRR ((FOSC/16/BAUD)-1)

int main(void)
{
	//-------------Inits-------------//
	/*POWER MANAGEMENT*/
	DISABLE_ADC; DISABLE_I2C;			/*Disable ADC*/ /*DISABLE I2C*/
	DISABLE_SPI; DISABLE_TIMER0;		/*Disable SPI*/ /*DISABLE TIMER0*/
	DISABLE_TIMER1; DISABLE_TIMER2;		/*Disable TIMER1*/ /*DISABLE TIMER2*/
	ENABLE_USART0;						/*Enable USART0*/
	/*GPIO*/
	SET_BIT(DDRB, PB5);					/*Pin PB5 as Output*/
	CLEAR_BIT(PORTB, PB5);				/*Clear PB5 Bit*/
	/*UART0*/
	USART0_Init(MYUBRR);
	/*Interrupt*/
	SET_BIT(SREG, 7);					/*Enable Interrupt*/

	/*USART0 Transmit Example*/
	USART0_Send_Data("This is a simple string literal for testing UART0 in ATMEGA328P");
	_delay_ms(6);
	USART0_Send_Data("With this test we can find performance of UART0 in ATMEGA328P");

	//-----------Event loop----------//
	while (1)
	{
		/*Blink LED Example*/
		TOGGLE_BIT(PORTB, PB5);
		_delay_ms(1000);
	}
	return(0);
}
