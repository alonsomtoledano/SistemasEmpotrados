#include "MKL25Z4.h"
#define mask(x) (1UL << (x))


//Handler for the Systick
void SysTick_Handler() {
	PTB->PTOR = mask(18);
}

//Initialize clock timer
void Init_SysTick(void){
	//Load the value of how long to wait between each interrupts
	SysTick->LOAD = (48999999L/16); //This is the clock speed/16
	//Set the interrupt priority of the timer interrupt
	NVIC_SetPriority(SysTick_IRQn,3);
	//Enable the NVIC flags for the IRQ interrupt
	NVIC_EnableIRQ(SysTick_IRQn);
	//Set the value of the Systick to 0
	SysTick->VAL = 0;
	//Configure the control values of the Systick to acept the TICKINT and enable it
	SysTick->CTRL = SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_ENABLE_Msk;
}


int main(void){
	//Clock to each port
		//Clear
		SIM->SCGC5 &= ~SIM_SCGC5_PORTB_MASK;
		//Set
		SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	//Setting the MUX to the GPIO
		//Port for Red led
		PORTB -> PCR[18] &= ~PORT_PCR_MUX_MASK; //MUX Clear
		PORTB -> PCR[18] |= PORT_PCR_MUX(1); 		//MUX Set

	//Set the value of the ports to 0
		PTB->PSOR = 0xffffffff;
	
	//Configure pin as input/output ("|=" equals to output and "&= ~" equals to input)
		PTB->PDDR |= mask(18);	//Red led port output
		
	//Initialize the clock timer
		Init_SysTick();
	
	//Enable IRQ interrupts
		__enable_irq();

	//Loop forever
		while(1);
	
	//Returns a value of 0 to the main function of the program (CODING FOR NOOBS)
		return 0;
}