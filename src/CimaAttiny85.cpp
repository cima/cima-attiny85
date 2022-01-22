#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

// #include <avr/sleep.h>
// #include <util/delay.h>

uint32_t message = 0b00000101010001110111011100010101;
uint32_t position = 1;

bool stop = false;

void initTimer0()
{
  TCCR1 |= (1 << CTC1);  // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11); //clock prescaler 8192
  OCR1C = 122; // compare match value 
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}

ISR(TIMER1_COMPA_vect){
    
    if(position & message){
        PORTB |= (1<<PB1);      //PortB1 high 
    } else {
        PORTB &= ~(1<<PB1);     //PORTB1 low   
    }

    position = position << 1;
    position = position ? position : 1;
}

int main() {
    
    DDRB  |= (1<<PB1);
    PORTB |= (1<<PB1);      //PortB1 high 
    //PORTB&=~(1<<PB1);     //PORTB1 low 
    //PORTB^= (1<<PB1);     //PortB1 toggle

    initTimer0();
    sei();

    while( ! stop) {
    }
}
