/* 
 * File:   display7segmMult.c
 * Author: marcelo
 *
 * Created on 3 de Junho de 2019, 13:50
 */

#include "SanUSB1.h"
#define DIGIT1 PORTCbits.RC0
#define DIGIT2 PORTCbits.RC1
unsigned char Cnt = 0;
unsigned char Flag = 0;
unsigned char Display(unsigned char);
#pragma interrupt interrupcao
void interrupcao(){

    unsigned char Msd, Lsd;
    TMR0L = 100; // Recarrega TMR0 para contar 156 x 32 us
    INTCON = 0x20; // Set T0IE and clear T0IF
    Flag = ~ Flag; // Inverte a Flag

    if(Flag == 0){ // Do digit 1

        DIGIT2 = 0;
        Msd = Cnt / 10; // MSD digit
        PORTB = Display(Msd); // Send to PORT C
        DIGIT1 = 1; // Enable digit 1
    }else{
        
        // Faz o digito 2
        DIGIT1 = 0; // Disable digit 1
        Lsd = Cnt % 10; // LSD digit
        PORTB = Display(Lsd); // Send to PORT C
        DIGIT2 = 1; // Enable digit
    }
    }
    unsigned char Display(unsigned char i){
 
        unsigned char Pattern;
        unsigned char SEGMENT[ ] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};
        Pattern = SEGMENT[i]; // Pattern to return
        return (Pattern);
}

void main(){

    clock_int_4MHz();
    TRISB = 0; // PORT B are outputs
    TRISC = 0; // RC0, RC1 are outputs
    DIGIT1 = 0;
    //
    // Configura TMR0 timer interrupt
    //
    T0CON = 0xC4; // Prescaler = 32
    TMR0L = 100; // Load TMR0L with 156 x 32 us
    INTCON = 0xA0; // Enable TMR0 interrupt
    tempo_ms(1000);

    while(1){
    
        if(!entrada_pin_e3){

            nivel_baixo(pin_a3);
            nivel_alto(pin_a0);
            nivel_alto(pin_a4);
                
            for(Cnt = 0; Cnt <= 15; Cnt++){

                if(Cnt > 10){nivel_baixo(pin_a4); inverte_saida(pin_a3);}
                //acende led vermelho dos carros, apaga led vermellho e led verde dos pedestres
         
                if(Cnt == 16) Cnt = 0; // Conta de 0 a 99
                
                tempo_ms(1000);
            }
            //apaga led verde dos carros
            nivel_baixo(pin_a4);
            Cnt = 0;
            
            //acende led vermelho do pedestre e dos carros
        nivel_alto(pin_a3);
        nivel_alto(pin_a0);
        tempo_ms(500);
        
        nivel_baixo(pin_a0);
        nivel_alto(pin_a2);
        tempo_ms(3000);

        nivel_baixo(pin_a2);
        nivel_alto(pin_a1);
        tempo_ms(500);
        nivel_baixo(pin_a1);

        
        }
        //acende led vermelho do pedestre e dos carros
        nivel_alto(pin_a3);
        nivel_alto(pin_a0);
        tempo_ms(4000);
        
        //apaga led vermelho e acende lede verde
        nivel_baixo(pin_a0);
        nivel_alto(pin_a2);
        tempo_ms(3000);
        
        //apaga led verde, acende led amarelo e apaga led amarelo
        nivel_baixo(pin_a2);
        nivel_alto(pin_a1);
        tempo_ms(500);
        nivel_baixo(pin_a1);
        
    }
}
    
        

