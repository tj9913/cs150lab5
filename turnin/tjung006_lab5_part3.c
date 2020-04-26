/*	Author: terry
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
//Demo: https://drive.google.com/open?id=1huEeAjdELogMCxMNFUzcIQglbthr9N-h
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
unsigned short one = 1;
unsigned short i = 3;
enum states{start, r, odd, even}state;
void tick(){
	switch(state){
		case start:
			state = r;
			tmpC = 0x00;
			break;
		case r:
			if(tmpA == 0x01){
				if(i % 2 == 1){
					state = odd;
					tmpC = 0x15;
					i++;
				}
				else{
					state = even;
					tmpC = 0x2A;
					i++;
				}
			}
			else{
				state = r;
			}
			break;
		case odd:
			if(tmpA == 0x00){
				state = r;
			}
			else{
				state = odd;
			}
			break;
		case even:
			if(tmpA == 0x00){
				state = r;
			}
			else{
				state = even;
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
	tmpA = ~PINA & 0x01;
	tick();
    }
    return 0;
}
