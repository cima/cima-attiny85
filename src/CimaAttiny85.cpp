#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

//#include <avr/sleep.h>
//#include <util/delay.h>


uint32_t messageR = 0b00000101010001110111011100010101;
uint32_t messageG = 0b10101010101010101111111111111111;
uint32_t messageB = 0b01111111111111110000000000000001;

uint32_t position = 1;
uint16_t phase16bit = 0;

bool stop = false;

void initTimer1(){
  PLLCSR |= (1 << PLLE) | (1 << PCKE);

  TCCR1 |= (1 << CTC1);  // clear timer on compare match
  TCCR1 |= (1 << CS13) | (1 << CS12); //clock prescaler 4096
  //TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11); //clock prescaler 8192
  //TCCR1 |= (1 << CS13) | (1 << CS12) | (1 << CS11) | (1 << CS10); //clock prescaler 16k
  OCR1C = 255; // compare match value: if TCNT1 == 122 => compare match => call interupt
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
/*
  GTCCR &= ~(1 << COM1B0); //Disable time compare match output to pin PB4
  GTCCR &= ~(1 << COM1B1);
  GTCCR &= ~(1 << FOC1B);
*/
}

void initPWM0() {
    /* - set OC0A on match, clear at bottom (inverting mode) 
       - set OC0B on match, clear at bottom (inverting mode) 
       - Fast PWM mode */
    TCCR0A = 0b11 << COM0A0 | 0b11 << COM0B0 | 0b011 << WGM00;

    /* TODO comments */
    TCCR0B = 0b0 << WGM02 | 0b010 << CS00;

    /* - Enable PWM on global timer  
       - set the OC1B output line when comparison matches*/
    GTCCR = 1 << PWM1B | 0b11 << COM1B0;

    /* - enable PWM (1 << PWM1A)
       - This must be set with respect to HW design bug */
    TCCR1 |= 1 << PWM1A | 0b11 << COM1A0;
}

uint8_t phaseToIntensity(uint16_t phase){
    uint8_t down = (0b1 & (phase >> 8));
    
    return 255 - (down ? (255 - phase) : phase);
}

ISR(TIMER1_COMPA_vect){
    uint8_t phase = phase16bit & 0xFF;

    if(phase % 8 == 0){
        /**
        if(position & messageR){
            PORTB |= (1<<PB1);      //PortB1 high 
        } else {
            PORTB &= ~(1<<PB1);     //PORTB1 low   
        }
        */
/*
        if(position & messageB){
            PORTB |= (1<<PB4);      //PortB4 high 
        } else {
            PORTB &= ~(1<<PB4);     //PORTB4 low   
        }
*/
        if(position & messageG){
            PORTB |= (1<<PB2);      //PortB2 high 
        } else {
            PORTB &= ~(1<<PB2);     //PORTB2 low   
        }

        position = position << 1;
        position = position ? position : 1;
    }
    
    OCR0A = phaseToIntensity(phase16bit);
    OCR0B = phaseToIntensity(phase16bit + 70);
    OCR1B = phaseToIntensity(phase16bit + 180);
    
    phase16bit++;
}



int main() {
    
    DDRB  |= (1<<PB0);
    DDRB  |= (1<<PB1);
    DDRB  |= (1<<PB4);
    DDRB  |= (1<<PB2);

    PORTB |= (1<<PB0);
    OCR0A = 128;

    PORTB |= (1<<PB1);      //PortB1 high 
    OCR0B = 128;

    PORTB |= (1<<PB4);      //PortB4 high 
    OCR1B = 128;

    PORTB |= (1<<PB2);      //PortB2 high 

    //PORTB&=~(1<<PB1);     //PORTB1 low 
    //PORTB^= (1<<PB1);     //PortB1 toggle

    initTimer1();
    initPWM0();
    sei();

    while( ! stop) {
    }
}
