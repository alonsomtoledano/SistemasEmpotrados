#include <MKL25Z4.h>
#define MASK(x) (1UL << (x))

#define led_rojo (18)		//PORTB

void Delay(volatile unsigned int time_del);

int main(){

	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK;	//conectamos el reloj al puerto

	PORTB->PCR[led_rojo]&=~PORT_PCR_MUX_MASK;	//ponemos a cero el campo MUX

	PORTB->PCR[led_rojo]|=PORT_PCR_MUX(1);	//ponemos el campo MUX a '1' para conectar el GPIO con el pin

	PTB->PDDR|=MASK(led_rojo);	//configuramos direccion de entrada o salida

	while(1){
		PTB->PCOR=MASK(led_rojo);	//ponemos a '0' la salida (no se enciende el led, clear)
		Delay(2000000);
		PTB->PSOR=MASK(led_rojo);	//ponemos a '1' la salida (se enciende el led, set)
		Delay(2000000);
	}
}

void Delay(volatile unsigned int time_del){
	while(time_del--){
	}
}
