#include "MKL05Z4.h"
#include "tsi.h"





int tsi_init(void){
	
	int offset; //wartosc przy kalibracji
	
	SIM_SCGC5 |= (SIM_SCGC5_TSI_MASK) | (SIM_SCGC5_PORTB_MASK); 
	PORTB_PCR12 = PORT_PCR_MUX(0);   
	PORTB_PCR13 = PORT_PCR_MUX(0);   	


//Konfiguracja TSI
	TSI0_GENCS |= (TSI_GENCS_ESOR_MASK                   
		| TSI_GENCS_REFCHRG(4)                   
		| TSI_GENCS_DVOLT(0)                  
		| TSI_GENCS_EXTCHRG(6)                    
		| TSI_GENCS_PS(2)                   
		| TSI_GENCS_NSCN(11)                 
		| TSI_GENCS_TSIIEN_MASK                
		| TSI_GENCS_STPE_MASK                   
		//| TSI_GENCS_STM_MASK                 
	); 
	// Clear End of scan and Out of Range Flags 
	TSI0_GENCS |= (TSI_GENCS_OUTRGF_MASK) | (TSI_GENCS_EOSF_MASK);
	//Select Desired Channel to Scan 
	TSI0_DATA |= (TSI_DATA_TSICH(10u)); 
	// Choose channel 2 
	// Enables TSI 
	TSI0_GENCS |= (TSI_GENCS_TSIEN_MASK); 
	
	//kalibracja
	TSI0_DATA = 	TSI_DATA_TSICH(8u); // channel 8 TSI
	TSI0_DATA |= TSI_DATA_SWTS_MASK; // Software trigger
	
	while((TSI0_GENCS & TSI_GENCS_EOSF_MASK) == 0); //czeka na zakonczenie skanowania
	offset = TSI0_DATA & TSI_DATA_TSICNT_MASK; //skan
		
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK ; // Reset end of scan flag

	TSI0_GENCS &= ~(TSI_GENCS_TSIEN_MASK); //tsi disable
	
	
	return offset; //wartosc poczatkowa odczytu ze slidera (nidotknietego slidera)
}
int tsi_scan(int offset)
{
	int scan;
	TSI0_GENCS |= (TSI_GENCS_TSIEN_MASK);
	TSI0_DATA = 	TSI_DATA_TSICH(8u); // channel 8 TSI
	TSI0_DATA |= TSI_DATA_SWTS_MASK; // Software trigger
	
	while((TSI0_GENCS & TSI_GENCS_EOSF_MASK) == 0); //czeka na zakonczenie skanowania
	scan = SCAN_DATA;
	TSI0_GENCS |= TSI_GENCS_EOSF_MASK ; // Reset end of scan flag
	
	return scan - offset + 2; //zwrocenie wyniku z uwzglednieniem kalibracji
}

