#include "MKL05Z4.h"
#include "tsi.h"
#include "MMA8451.h"
#include "uart0.h"
#include "iic.h"
#include "led.h"
#include "pit.h"
#include "buzzer.h"


char pamiec_znakow[5];
char accel_slider; //1 -> tryb slider, 0 -> tryb accelrometer



int main(){	
	
	UART0_Init();
	init_buzzer();
	InitLed();
		Init_I2C();
	MMA8451_Initial();
	uint32_t timer_val = 0x1cfffff; //progi czasowe dla nacisniecia slidera dlugiego, sredniego, krotkiego
	uint32_t timer_val_3 = timer_val /3;
	uint32_t timer_val_2 = timer_val_3 * 2;
	pitInit();
	int offset = tsi_init();
  uint8_t skan = 0;
	int wcisniete = 0;
//	int end = 0;
	accel_slider = 1; //domyslnie program jest w trybie slider
	
	kasowanie_pamieci();
	
    while (1) {						
       
		skan = tsi_scan(offset);	//pobranie odczytu ze slidera		
			
	
		if(skan > 10){		//jezeli slider jest nacisniety				
			
			if(wcisniete == 0){
				
				setPit(timer_val);									
				 //uruchomienie timera
				wcisniete = 1; //oznacza, ze slider jest wcisniety
			}						
			
		}
		
		
		if(pamiec_znakow[0] == 0 && pamiec_znakow[1] == 0 && pamiec_znakow[2] == 0 && pamiec_znakow[3] == 0 && pamiec_znakow[4] == 0){

		accel_slider = !accel_slider;
		
		if(accel_slider == 0){  //wyswietlenie komunikaty acc
			for(int i = 0; i < 0xffff; i++); //delay
			uart_sendCh('a'); 
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('c'); 
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('c'); 
			for(int i = 0; i < 0xffff; i++);
		}
		
		if(accel_slider == 1){	//wyswietlenie komunikaty sli
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('s'); 
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('l'); 
			for(int i = 0; i < 0xffff; i++);
			uart_sendCh('i'); 
			for(int i = 0; i < 0xffff; i++);
		}
		
		kasowanie_pamieci();
	}
		
			
	if(skan <= 3){ //jezeli slider nie jest wcisniety
		
				BLUE_off();
				RED_off();			
				GREEN_off();
		
			if(wcisniete == 1 && PIT_BASE_PTR->CHANNEL[0].CVAL > timer_val_3 && PIT_BASE_PTR->CHANNEL[0].CVAL < (timer_val_2)){ //gdy slider wlasnie zostal puszczony, a timer jescze nie doliczyl do koncza i sie nie wyzerowal
							
				
			PIT_BASE_PTR->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK; //zatrzymanie timera
					
				
				if (accel_slider == 0){ //jezeli tryb accel
					
					MMA8451_Read_3axis_data();
					
					if(resultz >= 0x80){ //jezeli wartosc na osi z accelerometru jest  ujemna (plytka jest odwrocona)
						
						wpisz_do_pamieci(1);//wpisanie dlugiego znaku do pameci
						
						
					}
					else{ //jezeli wartosc na osi z accelerometru jest  dodatnia (plytka nie jest odwrocona)
							wpisz_do_pamieci(0);//wpisanie krotkiego znaku do pameci				
					}
						
					
				}
				else{//jezeli tryb slider
					wpisz_do_pamieci(1);//wpisanie dlugiego znaku do pameci
				}	

			}
		
			if(wcisniete == 1 && PIT_BASE_PTR->CHANNEL[0].CVAL > timer_val_2 && PIT_BASE_PTR->CHANNEL[0].CVAL < (timer_val-2)){ //gdy slider wlasnie zostal puszczony, a timer jescze nie doliczyl do koncza i sie nie wyzerowal
							
				wpisz_do_pamieci(0); //wpisanie krotkiego znaku do pameci
				PIT_BASE_PTR->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK; //zatrzymanie timera
			}	
			
			wcisniete = 0;	//to oznacza, ze slider nie jest wcisniety		
		}
	
		
		
	if(wcisniete == 1 && PIT_BASE_PTR->CHANNEL[0].CVAL < timer_val_3){ //zaswiecenie diody do sygnalizacji
				
				BLUE_on();
	}
	
		if(wcisniete == 1 && PIT_BASE_PTR->CHANNEL[0].CVAL < timer_val_2 ){//zaswiecenie diody do sygnalizacji
			
			RED_on();
			
		}
		if(wcisniete == 1 && PIT_BASE_PTR->CHANNEL[0].CVAL < (timer_val-2) ){ //zaswiecenie diody do sygnalizacji
								
				GREEN_on();
		
		}
		
		if(PIT_BASE_PTR->CHANNEL[0].CVAL < timer_val_3 ){ //dlugie przytrzymanie przycisku -> wypisanie litery na ekran i wybrzmienie kodu buzzerem
		PIT_BASE_PTR->CHANNEL[0].TCTRL &= ~PIT_TCTRL_TEN_MASK; //zatrzymanie timera
				
					wypisz_znak(); //wypisanie litery na ekran
					
				for(int i = 0; i < 5; i++){		//wybrzmienie kodu buzzerem
					
					buzzer(pamiec_znakow[i]);					
				}
					kasowanie_pamieci();
			}
	}
		
} 


	
