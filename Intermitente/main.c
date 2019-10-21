#include <MKL25Z4.h>
#define MASK(x) (1UL << (x))

#define led_rojo (18)		//PORTB

void Delay(volatile unsigned int time_del);

int main(){

	SIM->SCGC5|=SIM_SCGC5_PORTD_MASK;	//conectar el reloj

	PORTB->PCR[led_rojo]&=~PORT_PCR_MUX_MASK;	//ponemos a cero el campo MUX

	PORTB->PCR[led_rojo]|=PORT_PCR_MUX(1);

	PTB->PDDR|=MASK(led_rojo);

	while(1){
		PTB->PCOR=MASK(led_rojo);
		Delay(2000000);
		PTB->PSOR=MASK(led_rojo);
		Delay(2000000);
	}


}

void Delay(volatile unsigned int time_del){
	while(time_del--){
	}
}
