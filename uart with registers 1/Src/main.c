/*
 * Application : UART Interfacing with Bare Metal Programming
 * Step 1:Write the function for all 0 to 9
 * Step 2:call them in sequential from 0 to 9
 * Step 3: give some delay
 * Author : Swadhin
 * Date : 25/04/23

 */

#include <stdint.h>

#if  !defined(_SOFT_FP) && defined(_ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

   /*Steps to follow UART  - Initialization
    *
    * Step 1:-Enable clock access to GPIO
    *
    * Ex:- uint32_t *portaAHB1ENR =(uint32_t *)0x40023830;
    *      uint32_t *APB1ENR =(uint32_t *)0x40023840;
    *
    * Step 2:- SET PA2 MODE to alternative mode
    *
    * Ex:- uint32_t *GPIOA_MODER  =(uint32_t *)0x40020000;
    *
    * Step 3:- SET PA2 Alternative Function type to UART-Tx (AF07)
    *
    * Step 4:- Configure UART Module
    *
    * Step 5:- Configure UART BaudRate
    *
    *
    *
    */

void delay(int T){

	while(T--)
	{
		for(int i=0;i<3000;i++);
	}
}

void UART2_Init(void){
    uint32_t *portaMODER =(uint32_t *)0x40020000; // PORT A enable
	uint32_t *portaAHB1ENR =(uint32_t *)0x40023830; // AHB1 BUS Enable
	uint32_t *portaAPB1ENR =(uint32_t *)0x40023840; // UART2 Bus enable
	uint32_t *GPIOaAFRL =(uint32_t *)0x40020020;
	uint32_t *USART2BRR =(uint32_t *)0x40004408;
	uint32_t *USART2CR1 =(uint32_t *)0x4000440c;
	uint32_t *USART2DR =(uint32_t *)0x40004404;
	uint32_t *USART2SR =(uint32_t *)0x40004400;




		*portaAHB1ENR =(0x01); //Enable Port A
		*portaAPB1ENR =(0X20000); // Enable USART1
		*portaMODER   =(0XA0); // Enable PA2 PA3 as Alternate mode
		*GPIOaAFRL	 =(0X7700); //  Alternate function low register
		*USART2BRR   =(0X683); // Setting the baud rate 9600
		*USART2CR1     =(0X300c);  // Enable UE,M,TX,RX

		//USART 2 TRansmmit
		//*USART2DR    =(0x02); //

}

int __io_putchar(unsigned char ch){
	Usart2_Transmit(ch);
	return ch;
}

void Usart2_Transmit(unsigned char ch)
{
	while(!(*USART2SR & 0x80));
	*USART2DR = (ch & 0xFF);

}



//#define portaAHB1ENR (1U<<0);
//#define

int main(void)
{
	UART2_Init();
	while(1){
		printf(" NIKITA SWAIN\r \n");
		delay(10);
	}
    /* Loop forever */
	//for(;;);
}
