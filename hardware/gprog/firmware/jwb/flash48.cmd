@echo off
cls
echo "Firmware Flasher for gprog ATmega48P version"
echo.
echo "Ready to write configuration fuses"
pause
avrdude -c usbasp -P usb -p atmega48 -F -B8 -u -U hfuse:w:0xdd:m -U lfuse:w:0xff:m
echo.

echo "Ready to write Flash firmware"
pause
avrdude -c usbasp -P usb -p atmega48 -F -U flash:w:fw-v120-48.hex
echo.


echo "Done"
pause
