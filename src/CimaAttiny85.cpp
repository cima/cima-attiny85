// https://blog.podkalicki.com/how-to-compile-and-burn-the-code-to-avr-chip-on-linuxmacosxwindows/

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>

#  define TIMER1_OVF_vect_cima TIMER1_OVF_vect

ISR ( _VECTOR(4) ) 
{
    int i = 10;
    i++;
}

int main() {

    int i = 0;
    while (true) {
        i++;
        sleep_mode();
    }    
}
