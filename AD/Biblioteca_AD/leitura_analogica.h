/**
* UNIVERSIDADE FEDERAL DE UBERLÂNDIA - UFU
* Autor: Mario Divino Borges Filho
* Data: 16/04/2018
* Git: github.com/alpinista06
*
* Descrição: Biblioteca para leitura analógica em bare metal
* utilizando o microcontrolador ATMEGA328P
*/
#ifndef _LEITURA_ANALOGICA_H_
#define _LEITURA_ANALOGICA_H_ //Previne quando multiplas inclusões

//////////////////////////////////////
//Dependencias (Outras Bibliotecas) //
//////////////////////////////////////
#include <avr/io.h>
#include <util/delay.h>

////////////
//Defines //
////////////
#define EXEMPLO_DE_DEFINE_DA_BIBLIOTECA 0x00

//////////////////////////
//Funções da Biblioteca //
//////////////////////////

/**
 * [configura_porta description]
 * @param u8_pino_adc [Configura a porta analógica à qual a leitura será realizada, default porta A0]
 * @param u8_referencia_adc [Configura a tensão de referencia para a conversão, default referencia interna]
 * @param u8_prescaler_adc [Configura o prescaler da conversão, default 128] 
 */
void configura_AD(uint8_t u8_pino_adc, uint8_t u8_referencia_adc, uint8_t u8_prescaler_adc);

/**
 * [realizar_leitura analógica]
 * @param   [sem parametros de entrada]
 * @return          [retorna o resultado da conversão AD]
 */
uint16_t leitura_AD();

#endif /*_LEITURA_ANALOGICA_H_*/
