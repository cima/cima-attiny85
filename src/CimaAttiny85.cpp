#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
/*

#include <avr/sleep.h>
#include <util/delay.h>
*/

int main() {
    DDRB |= (1<<PB1);
    PORTB|= (1<<PB1);     //PortB1 high 
    //PORTB&=~(1<<PB1);     //PORTB1 low 
    int i = 0;
    while(true) {
        i++;
    }
}
