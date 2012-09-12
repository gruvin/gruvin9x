@echo off
cls
echo "Firmware Flasher for gprog ATmega88P version"
echo.
echo "Ready to write configuration fuses"
pause
avrdude -c usbasp -P usb -p atmega88p -B8 -u -U hfuse:w:0xdd:m -U lfuse:w:0xff:m
echo.

echo "Ready to write Flash firmware"
pause
avrdude -c usbasp -P usb -p atmega88p -U flash:w:fw-v120-88.hex
echo.

echo "Done"
pause

