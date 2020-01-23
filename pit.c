#include "MKL05Z4.h"
#include "pit.h"
#include "led.h"
#include "uart0.h"
#include "buzzer.h"

#define PIT_IRQ 22

//char pamiec_znakow[5];

void pitInit(void)
{
	SIM_SCGC6 |=  SIM_SCGC6_PIT_MASK;     
	PIT_MCR = 0x00;
		PIT_TCTRL_REG(PIT_BASE_PTR,0) = 
						PIT_TCTRL_TEN_MASK|  // enable PIT
						PIT_TCTRL_TIE_MASK;  // enable interrupt

}

void setPit(uint32_t time_val){
	PIT_BASE_PTR->CHANNEL[0].TFLG = PIT_TFLG_TIF_MASK;
	PIT_BASE_PTR->CHANNEL[0].LDVAL = time_val; //wartosc poczatkowa timera
	
	PIT_BASE_PTR->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK; //uruchomienie timera
}


void PIT_IRQHandler(void){

	
	PIT_BASE_PTR->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK;	//zatrzymanie timera
	PIT_BASE_PTR->CHANNEL[0].TFLG &= PIT_TFLG_TIF_MASK;	//clear the irq flag
}