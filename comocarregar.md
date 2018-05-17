# Como carregar códigos bare metal para ATMEGA328P pelo linux com avr gcc e avr dude

## compilar
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o controle_digital.o controle_digital.c

## arquivo sem formato

avr-gcc -mmcu=atmega328p analogRead.o -o analogRead

## arquivo .hex

avr-objcopy -O ihex -R .eeprom analogRead  analogRead.hex

## carregar

avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:analogRead.hex


## BIRL:
```

avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o nome_do_arquivo.o nome_do_arquivo.c && avr-gcc -mmcu=atmega328p nome_do_arquivo.o -o nome_do_arquivo && avr-objcopy -O ihex -R .eeprom nome_do_arquivo  nome_do_arquivo.hex && avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:nome_do_arquivo.hex

```

## Ou use o script

```
echo "digite o nome do arquivo"
read nome
echo "Criando arquivo .o (objeto)"
avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p -c -o $nome.o $nome.c

echo "Criando arquivo nao sei"
 avr-gcc -mmcu=atmega328p $nome.o -o $nome

echo "Criando arquivo .hex (hexadecimal)"
avr-objcopy -O ihex -R .eeprom $nome  $nome.hex

echo "Carregando na placa"
avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyACM0 -b 115200 -U flash:w:$nome.hex


```
