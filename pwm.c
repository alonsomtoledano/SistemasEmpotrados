#include <MKL25Z4.h>
#include <core_cm0plus.h>
#define led_red 18
#define mask(x)	(1UL << (x))

void Init_Red_LED_PWM(uint16_t period){
	//Enable clock to PORTB, TPM0
	SIM->SCGC5|= SIM_SCGC5_PORTB_MASK;
	SIM->SCGC6|= SIM_SCGC6_TPM2_MASK;
	
	PORTB->PCR[led_red]&= ~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_red]|= PORT_PCR_MUX(7);
	
	SIM->SOPT2 &= ~SIM_SOPT2_PLLFLLSEL_MASK;
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);


	TPM2->MOD = period-1;
	
	TPM2->SC = TPM_SC_PS(1);
	
	TPM2->CONF |= TPM_CONF_DBGMODE(3);
	
	TPM2->CONTROLS[0].CnSC = TPM_CnSC_MSB_MASK | TPM_CnSC_ELSA_MASK;
	
	TPM2->CONTROLS[0].CnV = 0;
	
	TPM2->SC |= TPM_SC_CMOD(1);
		
}

#define PWM_PERIOD (48000)

int main (void) {
	uint16_t i=0;
	volatile int32_t delay;
	Init_Red_LED_PWM(PWM_PERIOD);
	
	
	//TPM0->CONTROLS[1].CnV = 1;
	//flash forever
	while(1) {
		//Brihten LED
		for (i=0; i<PWM_PERIOD; i++) {
			TPM2->CONTROLS[0].CnV = i;
			for (delay=0; delay<150; delay++)
									;
		}
		//Dim LED
		for (i=PWM_PERIOD-1; i>0; i--) {
			TPM2->CONTROLS[0].CnV = i;
			for(delay=0; delay<10; delay++)
									;
		}
	}
}
