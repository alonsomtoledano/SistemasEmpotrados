#include <MKL25Z4.h>
#define MASK(x) (1UL << (x))

#define led_azul (1)		//PORTD
#define led_rojo (18)		//PORTB
#define led_verde (19)	//PORTB


int main(void){
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK;		//conectamos el reloj
	
	PORTD->PCR[led_azul]&=~PORT_PCR_MUX_MASK;	//ponemos a cero el campo MUX
	PORTB->PCR[led_rojo]&=~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_verde]&=~PORT_PCR_MUX_MASK;
	
	
	PORTD->PCR[led_azul]|=PORT_PCR_MUX(1);	//ponemos el campo MUX a '1' para conectar el GPIO con el pin
	PORTB->PCR[led_rojo]|=PORT_PCR_MUX(1);
	PORTB->PCR[led_verde]|=PORT_PCR_MUX(1);
	
	PTD->PDDR|=MASK(led_azul);
	PTB->PDDR|=MASK(led_rojo)|MASK(led_verde);
	
	
	PTD->PCOR=MASK(led_azul);
	PTB->PCOR=MASK(led_rojo);
	PTB->PCOR=MASK(led_verde);
	PTB->PSOR=MASK(led_rojo);
	PTB->PSOR=MASK(led_verde);
}
