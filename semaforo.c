#include "SanUSB1.h"

#pragma interrupt interrupcao

void interrupcao(){

}

void main(){

	clock_int_4MHz();

	while(1){

		if(!entrada_pin_e3){

			Reset();
		}

		nivel_alto(pin_b5);
		tempo_ms(2000);
		nivel_baixo(pin_b5);

		nivel_alto(pin_b6);
		tempo_ms(1000);
		nivel_baixo(pin_b6);

		nivel_alto(pin_b7);
		tempo_ms(2000);
		nivel_baixo(pin_b7);
		
	}
}
