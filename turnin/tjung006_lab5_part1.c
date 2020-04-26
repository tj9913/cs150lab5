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
unsigned char GetBit(unsigned char x, unsigned char k) {
   return ((x & (0x01 << k)) != 0);
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRC = 0xFF; PORTC = 0x00;

    unsigned char tmpA = 0x00;
    unsigned char tmpC = 0x00;
    /* Insert your solution below */
    while (1) {
	tmpA = ~PINA & 0x0F;
	tmpC = 0x00;
	if(tmpA > 0){
		tmpC = SetBit(tmpC,5,1);
	}
	if(tmpA > 2){
                tmpC = SetBit(tmpC,4,1);
        }
	if(tmpA > 4){
                tmpC = SetBit(tmpC,3,1);
        }
	if(tmpA > 6){
                tmpC = SetBit(tmpC,2,1);
        }
	if(tmpA > 9){
                tmpC = SetBit(tmpC,1,1);
        }
	if(tmpA > 12){
                tmpC = SetBit(tmpC,0,1);
        }
	if(tmpA < 5){
                tmpC = SetBit(tmpC,6,1);
        }
	PORTC = tmpC;
    }
    return 0;
}
