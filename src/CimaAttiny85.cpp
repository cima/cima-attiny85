#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>

uint16_t phase16bit = 0;
uint16_t duty = 0;

bool stop = false;

void initTimer1(){
  PLLCSR |= (1 << PLLE) | (1 << PCKE);

  //TCCR1 - Timer/Counter1 Control Register 1
  TCCR1 |= (1 << CTC1);  // CTC - clear timer on compare match

  // Prescaler = 2^(pow)
  // Allowed pow is 0 to 15
  // CS = pow + 1
  int pow = 12; 
  TCCR1 |= ((pow + 1) << CS10);

  OCR1C = 255; // compare match value: if TCNT1 == 122 => compare match => call interupt
  TIMSK |= (1 << OCIE1A); // enable compare match interrupt
}

void initPWM0() {
    /* Timer/Counter Control Register A for Timer0
        - set OC0A on match, clear at bottom (inverting mode) 
        - set OC0B on match, clear at bottom (inverting mode) 
        - Fast PWM mode */
    TCCR0A = 0b11 << COM0A0 | 0b11 << COM0B0 | 0b011 << WGM00;

    /* Timer/Counter Control Register B for Timer0
         - Fast PWM mode
         - Prescaler 8
         CS0 = 0b110 = external clcok on pin T0 (falling edge)
         CS0 = 0b111 = external clcok on pin T0 (rising edge)
     */
    TCCR0B = 0b0 << WGM02 | 0b010 << CS00;

    /* - Enable PWM on global timer  
       - set the OC1B output line when comparison matches*/
    GTCCR = 1 << PWM1B | 0b11 << COM1B0;

    /* - enable PWM (1 << PWM1A)
       - This must be set with respect to HW design bug */
    TCCR1 |= 1 << PWM1A | 0b11 << COM1A0;
}

void initADC() {
    /* Set the reference voltage to AVcc and select ADC0 (pin P5)
       MUX 0b0000 = ADC0 (PB5), no difierential input, no gain
       MUX 0b0011 = ADC3 (PB3), no difierential input, no gain
       ADLAR - ADC Left Adjust Result */
    ADMUX = (0 << REFS2) | (0 << REFS1) | (0 << REFS0) | (1 << ADLAR) | (0b0011);
    

    // Enable the ADC and set the prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // ADEN = 1, ADPS2:0 = 111 for prescaler 128

    // Data direction Register for port B
    // Set PB3 (ADC3) as input
    DDRB &= ~(1 << PB3);

    // DIDR0 - Digital Input Disable Register 0  
    // Disable digital input buffer on PB3 to reduce power consumption
    DIDR0 |= (1 << ADC3D);
}

uint8_t phaseToIntensity(uint16_t phase){
    uint8_t down = (0b1 & (phase >> 8));
    
    return 255 - (down ? (255 - phase) : phase);
}

uint16_t adc_read() {
    // Start the conversion
    ADCSRA |= (1 << ADSC);

    // Wait for the conversion to complete - BUT NOT IN INTERRUPTION
    while (ADCSRA & (1 << ADSC));

    // Read the ADC value (ADCL must be read first)
    uint16_t adc_value = ADCL;
    adc_value |= (ADCH << 8);

    return adc_value;
}

/** 
 * Timer1 Compare Match A interrupt - a callback for timer1
 * 
 * Activate whenever confgured condition for timer 1 are met.
 * In our case when timer counts to value OCR1C (which we change to potentiometer value)
 */
ISR(TIMER1_COMPA_vect) {
    uint8_t subPhase = phase16bit & 0xFF;
       
    duty = adc_read();

    //Timer Period Duration = How many ticks to count between timer calls
    OCR1C = duty >> 8;

    //Turn off the led if subPhase is past the duty time - blinking proportionally to potentialmeter value
    if(subPhase > (duty >> 8)){
        PORTB |= (1 << PB2);      //PortB2 high
    } else {
        PORTB &= ~(1 << PB2);     //PORTB2 low   
    }

    // Output Compare Registers - value to trigger some event - in our case it is PWM duty end
    OCR0A = phaseToIntensity(phase16bit);
    OCR0B = phaseToIntensity(phase16bit + 70);
    OCR1B = phaseToIntensity(phase16bit + 180);
    
    phase16bit++;
}

int main() {
    
    // Data direction Register for port B
    // 1 = output, 0 = input
    DDRB  |= (1 << PB0); // Blue LED
    DDRB  |= (1 << PB1); // Red LED
    DDRB  |= (1 << PB4); // Green LED
    DDRB  |= (1 << PB2); // Orange LED

    // Light up all LEDs
    PORTB |= (1 << PB0);      //PortB0 high 
    OCR0A = 128;

    PORTB |= (1 << PB1);      //PortB1 high 
    OCR0B = 128;

    PORTB |= (1 << PB4);      //PortB4 high 
    OCR1B = 128;

    // Orange LED is wired in reverse. Must be grounded to light up.
    PORTB &= ~(1 << PB2);      //PortB2 high 

    initTimer1();
    initPWM0();
    initADC();
    sei();

    while( ! stop) {
     
    }
}
