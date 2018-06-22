#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

int num = 0;
char snum[10]="abcdefghi"; // "abcdefghi" = Trash Emulation


void inicializa(void) {

	UBRR0H = 0;
	UBRR0L = 103; // Estes dois registradores setam o Baudrate da comunicação valores tabelados

//	UCSR0A |= (1 << U2X0); //Setando esse registrador se dobra o Bauderate
	UCSR0A &= ~(1 << U2X0);  // _BV(U2X0) = (1 << U2X0)	Essa linha configura o canal da comunicação


	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // configura o tamanho do dado da comunicação neste caso 1 bit por ciclo
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);  // Essa linha habilta o rx e o tx para a comunicação
}
void uart_putchar(char c) {
	do {} while (!(UCSR0A & (1 << UDRE0))); // Dá uma pausa enquanto o buffer, registrador UCSR0A está vazio,
          	//Neste registrador, se == 1 o buffer está vazio, caso contrário a comunicação está completa naquele ciclo
	UDR0 = c;   // Enviando a dado atual da vaiável c parâmetro que já deve ser enviado como caractere
}


int main(void)
{

   int i = 0; // Variável de loop
   inicializa(); // Inicializando a comunicação USART0


   while(1)
   {
//Conversão de tipo inteiro para caractere//
  	itoa(num, snum, 10); // Conversão de caractere para inteiro
    uart_putchar(' '); // Envia um espaço em branco

      	i=0;

      	do
      	{
           	uart_putchar(snum[i]); //envia o caractere de indice i do vetor de caracteres
           	i++;
      	}
      	//while(i < 10);
      	while((snum[i] >= 48 && snum[i] <= 57) && (i < 10)); // Esse bagulho eu não entendi tb.

      	_delay_ms(1000);


      	num++;
      	uart_putchar('\n'); // Envia uma quebra de linha para a comunicação.
				//É necessário para que o Serial monitor não plote um valor sempre na frente do anterior mas sim abaixo

    	}

    }
