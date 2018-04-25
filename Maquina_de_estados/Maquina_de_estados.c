#include <stdio.h>
#include <avr/io.h>
#include <util/delay.h>

enum leds {led1, led2, led3, led12, led23, led31, led123};  //Enumerando os estados possiveis

int main(){

  DDRB |= (1 << DDB2 & 1 << DDB1 & 1 << DDB0);  // setando as porta PB2(D10), PB1(D9), PB0(D8) como saída

  enum leds estado=led1;    //Configurando o estado inicial da máquina de estados
  while(1){
    switch(estado) {            //Estrutura da máquina de estados
      //Bloco de ação referente ao estado led1
      case led1:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB2);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB2);
      _delay_ms(500);
      estado = led2;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led2
      case led2:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB1);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB1);
      _delay_ms(500);
      estado = led3;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led3
      case led3:             //Condicional para a entrada nesse estado
      PORTB = (1 << PORTB0);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB0);
      _delay_ms(500);
      estado = led12;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led12
      case led12:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB0);
      PORTB |= (1 << PORTB1);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB1);
      PORTB &= ~(1 << PORTB0);
      _delay_ms(500);
      estado = led23;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led23
      case led23:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB3);
      PORTB |= (1 << PORTB1);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB1);
      PORTB &= ~(1 << PORTB3);
      _delay_ms(500);
      estado = led31;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led31
      case led31:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB2);
      PORTB |= (1 << PORTB0);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB2);
      PORTB &= ~(1 << PORTB0);
      _delay_ms(500);
      estado = led123;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
      //Bloco de ação referente ao estado led123
      case led123:             //Condicional para a entrada nesse estado
      PORTB |= (1 << PORTB0);
      PORTB |= (1 << PORTB1);
      PORTB |= (1 << PORTB2);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB1);
      PORTB &= ~(1 << PORTB0);
      PORTB &= ~(1 << PORTB2);
      _delay_ms(500);
      estado = led1;         //Próximo estado a ser assumido
      break;                  //Finlização e saída do estado atual
    }
  }
}
