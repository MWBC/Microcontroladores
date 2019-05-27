/* 
 * File:   semaforo7segm.c
 * Author: marcelo
 *
 * Created on 27 de Maio de 2019, 15:07
 */

#include "SanUSB1.h"

unsigned char set_seg[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
int i;

void interrupcao(){}

void main(){

    clock_int_4MHz();
    TRISB = 0b00000000;
    
    while(1){
    
        if(!entrada_pin_e3){
        
            Reset();
        }
        
        nivel_alto(pin_a0);
        
        for(i = 9; i >= 0; i--){
        
            PORTB = set_seg[i];
            tempo_ms(1000);
        }
        
        nivel_baixo(pin_a0);
        
        nivel_alto(pin_a2);
        tempo_ms(1500);
        nivel_baixo(pin_a2);
        
        nivel_alto(pin_a1);
        tempo_ms(1000);
        nivel_baixo(pin_a1);
    }
}

