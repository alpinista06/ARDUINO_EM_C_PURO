#include <leitura_analogica.h>

/**
 * funcao para selecionar a porta do conversor AD
 * NOTE: funciona so pra porta A1
 * @param pino_adc porta selecionada
 */

 void configura_AD(uint8_t u8_pino_adc, uint8_t u8_referencia_adc, uint8_t u8_prescaler_adc) {
  switch (u8_pino_adc) {
    case 0:
    DDRC &= ~(1 << DDRC0); //Setting arduino port A0 like INPUT
    break;
    case 1:
    DDRC &= ~(1 << DDRC1); //Setting arduino port A1 like INPUT
    ADMUX |= (1 << MUX0);
    break;
    case 2:
    DDRC &= ~(1 << DDRC2); //Setting arduino port A2 like INPUT
    ADMUX |= (1 << MUX1);
    break;
    case 3:
    DDRC &= ~(1 << DDRC3); //Setting arduino port A3 like INPUT
    ADMUX |= (1 << MUX0) | (1 << MUX1);
    break;
    case 4:
    DDRC &= ~(1 << DDRC4); //Setting arduino port A4 like INPUT
    ADMUX |= (1 << MUX2);
    break;
    case 5:
    DDRC &= ~(1 << DDRC5); //Setting arduino port A5 like INPUT
    ADMUX |= (1 << MUX2) | (1 << MUX0);
    break;
    default:
    DDRC &= ~(1 << DDRC0); //Setting arduino port A0 like INPUT
    break;
  }
  switch (u8_referencia_adc) {
    case 1:
    ADMUX |= (1 << REFS0); //Tensão de referencia como default( 5V no caso do arduino uno)
    break;
    case 3:
    ADMUX |= (1 << REFS1 | 1 << REFS0);   //Tensão de referencia interna (1.1V no caso do arduino uno)
    break;
    default:
    ADMUX |= (1 << REFS0); //Tensão de referencia como default( 5V no caso do arduino uno)
    break;

  }
  switch (u8_prescaler_adc) {
    case 2:
    ADCSRA |= (1 << ADPS0);   //Configurando o prescaler como 8
    break;
    case 4:
    ADCSRA |= (1 << ADPS1);
    break;
    case 8:
    ADCSRA |= (1 << ADPS1) | (1 << ADPS1);
    break;
    case 16:
    ADCSRA |= (1 << ADPS2);
    break;
    case 32:
    ADCSRA |= (1 << ADPS2) | (1 << ADPS0);
    break;
    case 64:
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1);
    break;
    case 128:
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    break;
    default:
    ADCSRA |= (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2);
    break;

  }

}

/**
 * [realizar_leitura description]
 * @param  pino_adc [description]
 * @return          [description]
 */
uint16_t leitura_AD(){

  ADCSRA |= (1 << ADSC);  //Inicia a conversão AD, emqunto este bit for 1 a conversão ainda não terminou
  uint8_t alto, baixo;
  while (ADCSRA & (1 << ADSC)); //Aguarda o bit ADSC se tornar 0, neste momento a conversão terminou e o valor pode ser lido
  baixo = ADCL; //Este bit deve ser lido primeiro para que ñ impessa a leitura do proximo
  alto = ADCH;  //Este bit deve ser lido por ultimo
  return ((alto << 8) | baixo); //Como a conversão AD é de apenas 10 bits os bits que recebem os resultados devem ser combinados em uma palavra de 10 bits
 }
