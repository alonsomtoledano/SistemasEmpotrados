#include <MKL25Z4.h>
#define MASK(x) (1UL << (x))

#define led_azul (1)		//PORTD
#define led_rojo (18)		//PORTB
#define led_verde (19)	//PORTB


int main(void){
	//PASO1: CONECTAR EL RELOJ AL PUERTO
	SIM->SCGC5|=SIM_SCGC5_PORTB_MASK|SIM_SCGC5_PORTD_MASK; //conectamos el reloj al puerto
	
	//PASO 2: CONECTAR EL GPIO AL PIN DEL MICROCONTROLADOR
	PORTD->PCR[led_azul]&=~PORT_PCR_MUX_MASK; //ponemos a cero el campo MUX
	PORTB->PCR[led_rojo]&=~PORT_PCR_MUX_MASK;
	PORTB->PCR[led_verde]&=~PORT_PCR_MUX_MASK;
	
	PORTD->PCR[led_azul]|=PORT_PCR_MUX(1); //ponemos el campo MUX a '1' para conectar el GPIO con el pin
	PORTB->PCR[led_rojo]|=PORT_PCR_MUX(1);
	PORTB->PCR[led_verde]|=PORT_PCR_MUX(1);
	
	//PASO 3: CONFIGURAR DIRECCION
	PTD->PDDR|=MASK(led_azul); //configuramos direccion de entrada o salida
	PTB->PDDR|=MASK(led_rojo)|MASK(led_verde);
	
	//PASO 4: R/W
	PTD->PCOR=MASK(led_azul); //ponemos a '0' la salida (no se enciende el led, clear)
	PTB->PCOR=MASK(led_rojo);
	PTB->PCOR=MASK(led_verde);
	PTD->PSOR=mASK(led_azul);
	PTB->PSOR=MASK(led_rojo); //ponemos a '1' la salida (se enciende el led, set)
	PTB->PSOR=MASK(led_verde);
}
