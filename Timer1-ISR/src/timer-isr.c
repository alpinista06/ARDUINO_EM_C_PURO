#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <stdbool.h>
#include <avr/interrupt.h>

#define SREG_GLOBAL_INT_ENABLE 7

bool ledON =false;

//ISR(TIMER1_OVF_vect)
ISR(TIMER1_COMPA_vect)
{
        if (ledON == true)
        {
                ledON =false;
                PORTB |= (1 <<PORTB5);   // Turn LED on
        }
        else
        {
                ledON =true;
                PORTB &= ~(1 <<PORTB5);  // Turn LED off
        }
}


void InitializeTimer1(void )
{
        // ICIE1: Timer/Counter1, Quando 1 habilita interrupção de Captura de Entrada
        // OCIE1B: Timer/Counter1,Quando 1 Ativação de interrupção de correspondência na Conexão de saída B
        // OCIE1A: Timer/Counter1,Quando 1 Ativação de interrupção de correspondência na Conexão de saída A
        // TOIE1: Timer/Counter1, Quando 1 hailita a interrupção por overflow
        TIMSK1 &= ~((1 << ICIE1) | (1 << OCIE1B) | (1 << OCIE1A) | (1 << TOIE1));
        //TIMSK1 |= (1 << TOIE1);
        TIMSK1 |= (1 << OCIE1A);


        //--- Configura para o modo Clear Timer on Compare or CTC ------------------
        // No modo CTC, o contador é zerado quando o valor do contador
        // coincide com o valor guardado no OCR1A
        TCCR1B |= (1<<WGM12);

        //--- Prescaler Configuration ------------------------------------
        TCCR1B |= (1 << CS12) | (1 << CS10);  // clk/1024 (From prescaler)
        //TCCR1B |= (1 << CS12);  // clk/256 (From prescaler)
        //TCCR1B |= (1 << CS11) | (1 << CS10);  // clk/64 (From prescaler)
        //TCCR1B |= (1 << CS11);  // clk/8 (From prescaler)
        //TCCR1B |= (1 << CS10);  // clkI/1 (No prescaling)
}


int main(void)
{

        DDRB |= (1 << DDB5); // habilita o pino 13 para saída digital (OUTPUT).

        InitializeTimer1();

        // compare match register = [16000000Hz/ (prescaler * desired interrupt frequency) ] - 1
        // compare match register = [16000000/(1024 * 1Hz)] -1
        // compare match register = 15624
        OCR1A = 15624;  //Guarda o valor de comparação para o timer 1Hz com clk/1024 (From prescaler)

        while(1)
        {
                // Restore the global interrupt bit to previous value.
                SREG |= (1 << SREG_GLOBAL_INT_ENABLE);
           }
}
