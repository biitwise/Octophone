/*
 * sara_g350.c
 *
 *  Created on: 14.12.2016
 *      Author: beat
 */

#include "../../../Board.h"

#include <ti/sysbios/knl/Task.h>
#include <ti/drivers/GPIO.h>
#include <ti/drivers/UART.h>

#include <string.h>

#include "sara_g350.h"

#define SARA_G350_BAUD_RATE 9600
#define SARA_G350_READ_TIMEOUT 3000
#define SARA_G350_RXBUFFER_SIZE 100

static UART_Handle uart;
static UART_Params uartParams;
static int sara_g350_initialised = 0;
//static int sara_g350_locked = 0;

int sara_g350_open(){

	UART_Params_init(&uartParams);
	uartParams.writeDataMode = UART_DATA_BINARY;
	uartParams.readDataMode = UART_DATA_BINARY;
	uartParams.readReturnMode = UART_RETURN_FULL;
	uartParams.readTimeout = SARA_G350_READ_TIMEOUT;
	uartParams.readEcho = UART_ECHO_OFF;
	uartParams.baudRate = SARA_G350_BAUD_RATE;

	uart = UART_open(Board_UART_GPRS, &uartParams);

	if (uart == NULL) {

		//debug
		GPIO_toggle(Board_LED0);
		Task_sleep(300);
		GPIO_toggle(Board_LED0);

		return 0;
	}else{
		return 1;
	}
}


//must be called from within a task - this function will block!
//returns 1 if modem responds with OK
int sara_g350_begin(){
	char rxBuffer[SARA_G350_RXBUFFER_SIZE];
	memset(&rxBuffer, 0, sizeof(rxBuffer));

	if(sara_g350_open()){
		memset(&rxBuffer, 0, sizeof(rxBuffer));
		//UART_write(uart, sim800_at_echo_off, sizeof(sim800_at_echo_off));
		UART_read(uart, rxBuffer, sizeof(rxBuffer));

		//serial_printf(cli_stdout, "%s", rxBuffer);
		//Task_sleep(500);

		if(!strcmp("\r\nOK\r\n", rxBuffer)){
			sara_g350_initialised = 1;
			return 1; //modem can now communicate with us
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}

void sara_g350_end(){
	UART_close(uart);
	uart = NULL;
}
