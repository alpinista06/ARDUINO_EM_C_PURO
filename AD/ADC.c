#include <avr/io.h>
#include <stdio.h>


void configura(){


  ADMUX |= ((1 << REFS1) | (1 << REFS0) | (1 << MUX0)); //Configura a tensao de referencia como interna do arduino
                                                        //Habilita a porta analogica PC1(A0) a fazer a conversão como
  ADCSRA |= ((1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0)); //Habilita a conversão AD
                                                                        //Seta o prescaler como 128, valor tabelado
  DDRB |= ((1 << DDB2) | (1 << DDB1) | (1 << DDB0));  //Seta portas digitais como sendo saida
  DDRC &= ~(1 << DDC1);   //Seta a porta analogica como entrada
}

uint16_t leitura(){

    ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
    uint8_t alto, baixo;
    while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
    baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
    alto = ADCH;  //Este bit deve ser lido por ultimo
    return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits
}

int main (void)
{

  //Serial.begin(9600);
  uint16_t VALOR = 0;
  configura();    //A configuração dos registradores deve ocorrer apenas uma vez

  while(1) {

    uint8_t alto, baixo;
    VALOR = leitura();    //A leitura deve ser feita em todo ciclo, isso torna o processo dinamico
                          //pois a conversao e leitura n acontecem ao mesmo tempo
    //Serial.println(VALOR);

  /*
    if (VALOR < 225){
      PORTB |= (1 << PORTB2);
    }else if (VALOR < 450){
      PORTB |= (1 << PORTB1);
    }else{
      PORTB |= (1 << PORTB0);
  }*/
  }
}
