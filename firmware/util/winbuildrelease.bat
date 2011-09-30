cd src

make clean  
make 
mv gruvin9x.hex ../gruvin9x.hex

make clean
make EXT=STD BEEPER=BUZZER USART1=STD
mv gruvin9x.hex ../gruvin9x-stock.hex

make clean
make BEEPER=SPEAKER USART1=STD
mv gruvin9x.hex ../gruvin9x-std-speaker.hex

make clean
make EXT=FRSKY BEEPER=BUZZER USART1=STD
mv gruvin9x.hex ../gruvin9x-frsky-nospeaker.hex

make clean
make EXT=FRSKY BEEPER=SPEAKER USART1=STD
mv gruvin9x.hex ../gruvin9x-frsky-speaker.hex

make clean
