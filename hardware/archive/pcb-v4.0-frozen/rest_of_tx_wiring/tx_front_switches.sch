EESchema Schematic File Version 2  date 22/06/2011 14:28:16
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:gruvin
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "noname.sch"
Date "22 jun 2011"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text Label 2950 4850 0    60   ~ 0
GND
Text Label 10350 3400 0    60   ~ 0
GND
Text Label 9100 4600 0    60   ~ 0
AGND
Text Label 9100 4800 0    60   ~ 0
VCC
Wire Wire Line
	10100 4500 9750 4500
Wire Wire Line
	9750 4500 9750 3050
Wire Wire Line
	9750 3050 10100 3050
Wire Wire Line
	10100 3050 10100 2300
Connection ~ 10000 1050
Wire Wire Line
	10900 1050 10000 1050
Wire Wire Line
	10000 1050 9050 1050
Wire Wire Line
	10900 1050 10900 3400
Wire Wire Line
	10900 3400 10100 3400
Wire Wire Line
	10100 3400 10100 4300
Wire Wire Line
	10100 4700 8200 4700
Wire Wire Line
	8200 4700 8200 2050
Wire Wire Line
	3300 2250 3300 4650
Wire Wire Line
	3300 4650 1900 4650
Wire Wire Line
	1900 4450 2500 4450
Wire Wire Line
	2500 4450 2500 2250
Connection ~ 3200 950 
Wire Wire Line
	1900 4850 4350 4850
Wire Wire Line
	4350 4850 4350 950 
Wire Wire Line
	4350 950  3200 950 
Wire Wire Line
	3200 950  2400 950 
Wire Wire Line
	2400 950  1650 950 
Wire Wire Line
	2400 1250 2400 950 
Wire Wire Line
	1650 950  1650 1250
Wire Wire Line
	10000 1050 10000 1300
Wire Wire Line
	9050 1050 9050 1300
Wire Wire Line
	3200 950  3200 1250
Connection ~ 2400 950 
Wire Wire Line
	1750 2250 1750 3850
Wire Wire Line
	1750 3850 2600 3850
Wire Wire Line
	2600 3850 2600 4750
Wire Wire Line
	2600 4750 1900 4750
Wire Wire Line
	3100 2250 3100 4550
Wire Wire Line
	3100 4550 1900 4550
Wire Wire Line
	10100 4800 7950 4800
Wire Wire Line
	7950 4800 7950 1900
Wire Wire Line
	8450 1900 8450 4600
Wire Wire Line
	8450 4600 10100 4600
Wire Wire Line
	9150 2300 9150 4400
Wire Wire Line
	9150 4400 10100 4400
Text Notes 5450 2700 0    60   ~ 0
Layout as viewed from rear
Text Notes 9800 950  0    60   ~ 0
Rud D/R
Text Notes 8900 950  0    60   ~ 0
Ele D/R
Text Notes 8050 950  0    60   ~ 0
Pit Trim
Text Notes 3050 900  0    60   ~ 0
F Mode
Text Notes 2250 900  0    60   ~ 0
Ail D/R
Text Notes 1450 900  0    60   ~ 0
Gear SW
$Comp
L CONN_5 P1
U 1 1 4DCB2FE7
P 1500 4650
F 0 "P1" V 1450 4650 50  0000 C CNN
F 1 "CONN_5" V 1550 4650 50  0000 C CNN
	1    1500 4650
	-1   0    0    -1  
$EndComp
$Comp
L CONN_6 P2
U 1 1 4DCB2F53
P 10450 4550
F 0 "P2" V 10400 4550 60  0000 C CNN
F 1 "CONN_6" V 10500 4550 60  0000 C CNN
	1    10450 4550
	1    0    0    1   
$EndComp
$Comp
L POT RV1
U 1 1 4DCB2F1B
P 8200 1900
F 0 "RV1" H 8200 1800 50  0000 C CNN
F 1 "POT" H 8200 1900 50  0000 C CNN
	1    8200 1900
	-1   0    0    1   
$EndComp
$Comp
L SPDT_SW SW5
U 1 1 4DCB2F0D
P 9800 1800
F 0 "SW5" H 9600 2150 50  0000 C CNN
F 1 "SPDT_SW" H 10100 2250 50  0000 C CNN
	1    9800 1800
	0    1    1    0   
$EndComp
$Comp
L SPDT_SW SW4
U 1 1 4DCB2EFF
P 8850 1800
F 0 "SW4" H 8650 2150 50  0000 C CNN
F 1 "SPDT_SW" H 9150 2250 50  0000 C CNN
	1    8850 1800
	0    1    1    0   
$EndComp
$Comp
L SPDT_SW SW1
U 1 1 4DCB2EF6
P 1450 1750
F 0 "SW1" H 1250 2100 50  0000 C CNN
F 1 "SPDT_SW" H 1750 2200 50  0000 C CNN
	1    1450 1750
	0    1    1    0   
$EndComp
$Comp
L SPDT_SW SW3
U 1 1 4DCB2EEC
P 3000 1750
F 0 "SW3" H 2800 2100 50  0000 C CNN
F 1 "SPDT_SW" H 3300 2200 50  0000 C CNN
	1    3000 1750
	0    1    1    0   
$EndComp
$Comp
L SPDT_SW SW2
U 1 1 4DCB2EDE
P 2200 1750
F 0 "SW2" H 2000 2100 50  0000 C CNN
F 1 "SPDT_SW" H 2500 2200 50  0000 C CNN
	1    2200 1750
	0    1    1    0   
$EndComp
$EndSCHEMATC
