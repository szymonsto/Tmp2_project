#include "MKL05Z4.h"
#include "led.h"
 
#define RED 0
#define GREEN 1
#define BLUE 2
 
const uint32_t MaskLED[] = {1UL << 8, 1UL << 9, 1UL << 10};
 
 
void InitLed(void){
        SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
        
        PORTB_PCR8 = PORT_PCR_MUX(1UL);
        PTB_BASE_PTR->PDDR |= MaskLED[RED];
        
        PORTB_PCR9 = PORT_PCR_MUX(1UL);
        PTB_BASE_PTR->PDDR |= MaskLED[GREEN];
        
        PORTB_PCR10 = PORT_PCR_MUX(1UL);
        PTB_BASE_PTR->PDDR |= MaskLED[BLUE];
        
        PTB_BASE_PTR -> PSOR = MaskLED[RED];
        PTB_BASE_PTR -> PSOR = MaskLED[GREEN];
        PTB_BASE_PTR -> PSOR = MaskLED[BLUE];
}
 
void BlinkRED(uint16_t freq){
uint32_t i = 0;
        //PTB -> PTOR = MaskLED[RED];
        for( i =0; i <((freq * 0xfff) + 0xfff); i++){};
                PTB_BASE_PTR -> PTOR = MaskLED[RED];
}

void RED_on(void){

                PTB_BASE_PTR -> PCOR = MaskLED[RED];
}
void RED_off(void){

                PTB_BASE_PTR -> PSOR = MaskLED[RED];
}
void BLUE_on(void){

                PTB_BASE_PTR -> PCOR = MaskLED[BLUE];
}
void BLUE_off(void){

                PTB_BASE_PTR -> PSOR = MaskLED[BLUE];
}
void GREEN_on(void){

                PTB_BASE_PTR -> PCOR = MaskLED[GREEN];
}
void GREEN_off(void){

                PTB_BASE_PTR -> PSOR = MaskLED[GREEN];
}

void BLUE_toggle(void){
	
	 PTB_BASE_PTR -> PTOR = MaskLED[BLUE];
}
 
void BlinkGREEN(void){
uint32_t i = 0;
        PTB_BASE_PTR -> PTOR = MaskLED[GREEN];
        for( i =0; i <1000000; i++){};
                PTB_BASE_PTR -> PTOR = MaskLED[GREEN];
}
 
void BlinkBLUE(void){
uint32_t i = 0;
        PTB_BASE_PTR -> PTOR = MaskLED[BLUE];
        for( i =0; i <1000000; i++){};
       // PTB -> PTOR = MaskLED[BLUE];
}
 

 
        
        
        
 
