#include "MKL05Z4.h"
#include "buzzer.h"
#include "uart0.h"


#define BUZZ 1UL << 9

void init_buzzer(void){
	
				SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK;
        
        PORTA_PCR9 = PORT_PCR_MUX(1UL);
        PTA_BASE_PTR->PDDR |= BUZZ;
				PTA_BASE_PTR->PCOR = BUZZ;
}

void buzzer(char dlugosc){ //porta pin9
	
	if(dlugosc == 1){ //dlugi sygnal
		PTA_BASE_PTR->PSOR = BUZZ;
		for(int i = 0; i < 0x2fffff; i++); //delay
		PTA_BASE_PTR->PCOR = BUZZ;
	for(int i = 0; i < 0x1fffff; i++); //delay
	}
	if(dlugosc == 0){ //krotki sygnal
		PTA_BASE_PTR->PSOR = BUZZ;
		for(int i = 0; i < 0x1fffff; i++); //delay
		PTA_BASE_PTR->PCOR = BUZZ;
	for(int i = 0; i < 0x1fffff; i++); //delay
	}
	
}

void wpisz_do_pamieci(char znak){
	
	char temp1;
	char temp2;
	
	temp1 = pamiec_znakow[4];	
	pamiec_znakow[4] = znak;
	temp2 = pamiec_znakow[3];
	pamiec_znakow[3] = temp1;
	temp1 = pamiec_znakow[2];
	pamiec_znakow[2] = temp2;
	temp2 = pamiec_znakow[1];
	pamiec_znakow[1] = temp1;
	pamiec_znakow[0] = temp2;	
}

void kasowanie_pamieci(void){
	
	for(int i = 0; i<5 ; i++){
		pamiec_znakow[i] = 2;
	}
	
}
	
void wypisz_znak(void){
	
	if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 2 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('A'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('B'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('C'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('D'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 2 && pamiec_znakow[3] == 2 && pamiec_znakow[4] == 0){
	uart_sendCh('E'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('F'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('G'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('H'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 2 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('I'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 1){
	uart_sendCh('J'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('K'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('L'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 2 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 1){
	uart_sendCh('M'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 2 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('N'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 1){
	uart_sendCh('O'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('P'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('Q'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 0){
	uart_sendCh('R'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('S'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('U'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('V'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 2 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 1){
	uart_sendCh('W'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 1){
	uart_sendCh('X'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 1 && pamiec_znakow[4] == 1){
	uart_sendCh('Y'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 2 && pamiec_znakow[1] == 1 && pamiec_znakow[2] == 1 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	uart_sendCh('Z'); // 2-> brak, 1 -> dlugi, 0 -> krotki
}
if(pamiec_znakow[0] == 0 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){
	//uart_sendCh{'VOK'); // 2-> brak, 1 -> dlugi, 0 -> krotki

		accel_slider = !accel_slider;

		if(accel_slider == 0){
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('a'); //testowo
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('c'); //testowo
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('c'); //testowo
			for(int i = 0; i < 0xffff; i++);
		}
		
		if(accel_slider == 1){
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('s'); //testowo
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('l'); //testowo
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('i'); //testowo
			for(int i = 0; i < 0xffff; i++);
		}


		kasowanie_pamieci();
}



	
}



