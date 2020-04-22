/*	Author: terry
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char SetBit(unsigned char x, unsigned char k, unsigned char b) {
    return (b ?  (x | (0x01 << k))  :  (x & ~(0x01 << k)) );
}

unsigned char add(unsigned char a, unsigned char b){
    while(b != 0){
        unsigned char x = a & b;
        a = a ^ b;
        b = x << 1;
    }
    return a;
}

unsigned char subtract(unsigned char a, unsigned char b){
	while(b != 0){
		unsigned char x = (~a) & b;
		a = a ^ b;
		b = x << 1;
	}
	return a;
}
unsigned char tmpC = 0x00;
unsigned char tmpA = 0x00;
unsigned char one = 0x01;
enum states{start, r, a0p, a1p, doublep}state;
void tick(){
	switch(state){
		case start:
			state = r;
			tmpC = 0x00;
			break;
		case r:
			if(tmpA == 0x01){
				state = a0p;
				if(tmpC < 15){
					tmpC += one;
				}
			}
			else if(tmpA == 0x02){
				state = a1p;
				if(tmpC >0){
					tmpC -= one;
				}
			} 
			else if(tmpA == 0x03){
				state = doublep;
			}	
			else{
				state = r;
			}
			break;
		case a0p:
			if(tmpA == 0x00){
				state = r;
			}
			else if(tmpA == 0x03){
				state = doublep;
			}
			else{
				state = a0p;
			}
			break;
		case a1p:
			if(tmpA == 0x03){
				state = doublep;
			}
			else if(tmpA == 0x00){
				state = r;
			}
			else{
				state = a1p;
			}
			break;
		case doublep:
			if(tmpA == 0x00){
				state = r;
				tmpC = 0x00;
			}
			else{
				state = doublep;
			}
			break;
		default:
			break;
	}
	PORTC = tmpC;
}
int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
    state = start;
    while (1) {
	tmpA = ~PINA & 0x03;
	tick();
    }
    return 0;
}
