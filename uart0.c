#include "MKL05Z4.h"
#include "uart0.h"

void UART0_Init(void)
{//BR 1100
	SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;		//UART0 dolaczony do zegara
	SIM_SCGC5 |=  SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTA_MASK;
	PORTB_PCR1 |= PORT_PCR_MUX(2);     //PTB1 - UART0_TX                  
	PORTB_PCR2 |= PORT_PCR_MUX(2);			//PTB2 - UART0_RX
	
	SIM_SOPT2 |= SIM_SOPT2_UART0SRC(3);	//Zegar 4MHz - MCGIRCLK clock
	UART0_C1 = 0; //brak loop mode, brak paritu, 8-bitow danych,...
	UART0_C2 = 0;
	UART0_C2 &= ~(UART0_C2_TE_MASK | UART0_C2_RE_MASK );		//Blokada nadajnika i o dbiornika
	UART0_BDH = UART0_BDH_SBR(0x0);
    UART0_BDL = UART0_BDL_SBR(0x2);
	UART0_C4 |= UART0_C4_OSR(15);
	UART0_C5 |= UART0_C5_BOTHEDGE_MASK;
	//UART0->C2 |= UART0_C2_RIE_MASK;
	UART0_C2 |= (UART0_C2_TE_MASK | UART0_C2_RE_MASK);		//Wlacz nadajnik i odbiornik
}

void uart_sendCh(uint8_t data){ //wysylanie bajtu danych
	while(!(UART0_S1 & UART0_S1_TDRE_MASK) && !UART0_S1 & UART0_S1_TC_MASK);
UART0_D = data;
}

