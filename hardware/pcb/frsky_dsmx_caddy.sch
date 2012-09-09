EESchema Schematic File Version 2  date 10/09/2012 10:45:55 a.m.
LIBS:gruvin
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
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title "Fr-Sky / DSMX TX Moudle Caddy"
Date "9 sep 2012"
Rev "1.0"
Comp ""
Comment1 ""
Comment2 "Copyright 2012 B.Rentoul"
Comment3 ""
Comment4 "Licensed under the TAPR Open Hardware License (see file,  LICENSE)"
$EndDescr
Wire Wire Line
	3800 4150 3800 4450
Connection ~ 4000 1750
Wire Wire Line
	4000 1750 4000 2100
Wire Wire Line
	4000 2100 4100 2100
Connection ~ 5050 3500
Wire Wire Line
	5050 3500 5050 3850
Wire Wire Line
	5050 3850 5150 3850
Wire Wire Line
	5800 2250 5800 1850
Wire Wire Line
	6750 3800 6750 3900
Connection ~ 5450 1750
Wire Wire Line
	5800 2250 5450 2250
Wire Wire Line
	1400 3850 1400 3600
Wire Wire Line
	1400 3600 1250 3600
Wire Wire Line
	3100 4750 2700 4750
Wire Wire Line
	6350 3500 6150 3500
Wire Wire Line
	6150 3500 5950 3500
Wire Wire Line
	2550 2650 2550 1650
Wire Wire Line
	10150 2650 9550 2650
Connection ~ 8000 3900
Wire Wire Line
	10150 2250 9350 2250
Wire Wire Line
	9350 2250 9350 3500
Wire Wire Line
	1250 3200 2200 3200
Wire Wire Line
	2200 3200 2200 1550
Wire Wire Line
	2200 1550 6100 1550
Wire Wire Line
	1250 3400 1750 3400
Wire Wire Line
	1750 3400 2550 3400
Wire Wire Line
	2550 1650 6100 1650
Wire Wire Line
	3300 3500 3600 3500
Wire Wire Line
	3600 3500 4650 3500
Wire Wire Line
	4650 3500 5050 3500
Wire Wire Line
	5050 3500 5550 3500
Connection ~ 4750 2100
Wire Wire Line
	4600 2100 4750 2100
Connection ~ 3600 3500
Wire Wire Line
	3600 3500 3600 1750
Wire Wire Line
	5750 4400 5750 4450
Wire Wire Line
	5750 4450 3800 4450
Wire Wire Line
	5750 3900 5750 3850
Wire Wire Line
	5750 3850 5750 3800
Connection ~ 7400 3500
Wire Wire Line
	8000 3900 8000 3800
Wire Wire Line
	6100 1750 5450 1750
Wire Wire Line
	5450 1750 4950 1750
Connection ~ 7400 3900
Connection ~ 6150 3500
Wire Wire Line
	4750 3150 4750 3250
Connection ~ 6750 3900
Wire Wire Line
	4750 2050 4750 2100
Wire Wire Line
	4750 2100 4750 2150
Wire Wire Line
	3600 1750 4000 1750
Wire Wire Line
	4000 1750 4550 1750
Wire Wire Line
	9350 3500 9000 3500
Wire Wire Line
	9000 3500 8600 3500
Wire Wire Line
	8600 3500 8400 3500
Wire Wire Line
	4650 3500 4650 3600
Wire Wire Line
	7600 3500 7400 3500
Wire Wire Line
	7400 3500 7150 3500
Connection ~ 4650 3500
Wire Wire Line
	5650 3850 5750 3850
Connection ~ 5750 3850
Wire Wire Line
	1250 3500 2800 3500
Wire Wire Line
	5800 1850 6100 1850
Wire Wire Line
	1250 3100 2100 3100
Wire Wire Line
	2100 3100 2100 1450
Wire Wire Line
	2100 1450 6100 1450
Wire Wire Line
	4750 2750 4750 2650
Wire Wire Line
	4450 2950 4450 2950
Wire Wire Line
	9100 2350 9100 2150
Wire Wire Line
	9100 2150 10150 2150
Wire Wire Line
	2550 3400 2550 3050
Connection ~ 1750 3400
Wire Wire Line
	9000 3900 8600 3900
Wire Wire Line
	8600 3900 8000 3900
Wire Wire Line
	8000 3900 7400 3900
Wire Wire Line
	7400 3900 6750 3900
Wire Wire Line
	6750 3900 6150 3900
Connection ~ 9000 3500
Connection ~ 8600 3500
Connection ~ 8600 3900
Wire Wire Line
	9550 2650 9550 4750
Wire Wire Line
	9550 4750 3600 4750
Wire Wire Line
	2300 4750 1750 4750
Wire Wire Line
	1750 4750 1750 3400
Wire Wire Line
	4650 4000 4650 4100
Wire Wire Line
	9000 3900 9000 4000
Wire Wire Line
	6150 3900 6150 4000
Connection ~ 5450 2250
Wire Wire Line
	5450 2150 5450 2250
Wire Wire Line
	5450 2250 5450 2350
Wire Wire Line
	1250 3300 3800 3300
Wire Wire Line
	3950 2950 3800 2950
Wire Wire Line
	3800 2950 3800 3300
Wire Wire Line
	3800 3300 3800 3750
Connection ~ 3800 3300
$Comp
L GND #PWR6
U 1 1 504D1983
P 9000 4000
F 0 "#PWR6" H 9000 4000 30  0001 C CNN
F 1 "GND" H 9000 3930 30  0001 C CNN
	1    9000 4000
	1    0    0    -1  
$EndComp
$Comp
L C C2
U 1 1 504D1961
P 5450 1950
F 0 "C2" H 5200 1950 50  0000 L CNN
F 1 "0u1" H 5200 2050 50  0000 L CNN
	1    5450 1950
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR2
U 1 1 504D1897
P 4650 4100
F 0 "#PWR2" H 4650 4100 30  0001 C CNN
F 1 "GND" H 4650 4030 30  0001 C CNN
	1    4650 4100
	1    0    0    -1  
$EndComp
Text Label 10150 2650 2    60   ~ 0
Serial 125K
Text Label 10150 2150 2    60   ~ 0
GND
Text Label 10150 2250 2    60   ~ 0
+3.3V
$Comp
L C C3
U 1 1 4E203190
P 6150 3700
F 0 "C3" H 5900 3700 50  0000 L CNN
F 1 "0u1" H 5900 3800 50  0000 L CNN
	1    6150 3700
	-1   0    0    1   
$EndComp
Text Notes 2050 4050 0    60   ~ 0
Spare1 = 1 = Fr-Sky selected\nSpare1 = 0 = DSMX selected
$Comp
L DIODESCH D1
U 1 1 504D150C
P 2500 4750
F 0 "D1" H 2500 4850 40  0000 C CNN
F 1 "DIODESCH" H 2500 4650 40  0000 C CNN
	1    2500 4750
	-1   0    0    -1  
$EndComp
$Comp
L DIODESCH D2
U 1 1 504D14E4
P 2550 2850
F 0 "D2" H 2550 2950 40  0000 C CNN
F 1 "DIODESCH" H 2550 2750 40  0000 C CNN
	1    2550 2850
	0    -1   1    0   
$EndComp
Text Notes 9900 2850 0    60   ~ 0
DSM2/X Module
$Comp
L C C6
U 1 1 504D1418
P 9000 3700
F 0 "C6" H 8750 3700 50  0000 L CNN
F 1 "0u1" H 8750 3800 50  0000 L CNN
	1    9000 3700
	-1   0    0    1   
$EndComp
$Comp
L R R1
U 1 1 504D1401
P 3350 4750
F 0 "R1" V 3430 4750 50  0000 C CNN
F 1 "5K1" V 3350 4750 50  0000 C CNN
	1    3350 4750
	0    1    1    0   
$EndComp
$Comp
L GND #PWR7
U 1 1 504D13B3
P 9100 2350
F 0 "#PWR7" H 9100 2350 30  0001 C CNN
F 1 "GND" H 9100 2280 30  0001 C CNN
	1    9100 2350
	1    0    0    -1  
$EndComp
Text Label 1350 3100 0    60   ~ 0
Rx
Text Label 1350 3200 0    60   ~ 0
Tx
Text Notes 6250 2050 0    60   ~ 0
Fr-Sky DHT
Text Label 5850 1850 0    60   ~ 0
GND
Text Label 5850 1750 0    60   ~ 0
B+
Text Label 5850 1650 0    60   ~ 0
PPM
Text Label 5850 1550 0    60   ~ 0
Rxd
Text Label 5850 1450 0    60   ~ 0
Txd
Text Label 1350 3400 0    60   ~ 0
PPM
$Comp
L GND #PWR4
U 1 1 504D1165
P 5450 2350
F 0 "#PWR4" H 5450 2350 30  0001 C CNN
F 1 "GND" H 5450 2280 30  0001 C CNN
	1    5450 2350
	1    0    0    -1  
$EndComp
$Comp
L CONN_5 P2
U 1 1 504D1155
P 6500 1650
F 0 "P2" V 6450 1650 50  0000 C CNN
F 1 "CONN_5" V 6550 1650 50  0000 C CNN
	1    6500 1650
	1    0    0    1   
$EndComp
$Comp
L CONN_6X2 P3
U 1 1 504D1127
P 10550 2400
F 0 "P3" H 10550 2750 60  0000 C CNN
F 1 "CONN_6X2" V 10550 2400 60  0000 C CNN
	1    10550 2400
	1    0    0    -1  
$EndComp
Text Label 1350 3300 0    60   ~ 0
Spare1
Text Label 1350 3500 0    60   ~ 0
BATT+
$Comp
L GND #PWR1
U 1 1 504D1086
P 1400 3850
F 0 "#PWR1" H 1400 3850 30  0001 C CNN
F 1 "GND" H 1400 3780 30  0001 C CNN
	1    1400 3850
	1    0    0    -1  
$EndComp
$Comp
L CONN_6 P1
U 1 1 504D1054
P 900 3350
F 0 "P1" V 850 3350 60  0000 C CNN
F 1 "CONN_6" V 950 3350 60  0000 C CNN
	1    900  3350
	-1   0    0    1   
$EndComp
$Comp
L FUSE F1
U 1 1 504D0FDB
P 3050 3500
F 0 "F1" H 3150 3550 40  0000 C CNN
F 1 "FUSE" H 2950 3450 40  0000 C CNN
	1    3050 3500
	1    0    0    -1  
$EndComp
$Comp
L R R5
U 1 1 504D0D5C
P 5400 3850
F 0 "R5" V 5480 3850 50  0000 C CNN
F 1 "100K" V 5400 3850 50  0000 C CNN
	1    5400 3850
	0    1    1    0   
$EndComp
$Comp
L MOSFET_P Q3
U 1 1 504D0D5B
P 5750 3600
F 0 "Q3" V 5650 3750 60  0000 R CNN
F 1 "Si2319DS" V 6000 3750 60  0000 R CNN
	1    5750 3600
	0    1    -1   0   
$EndComp
$Comp
L R R6
U 1 1 504D0D5A
P 5750 4150
F 0 "R6" V 5830 4150 50  0000 C CNN
F 1 "5K1" V 5750 4150 50  0000 C CNN
	1    5750 4150
	-1   0    0    1   
$EndComp
$Comp
L CAPAPOL C1
U 1 1 504D0AFE
P 4650 3800
F 0 "C1" H 4550 3700 50  0000 L CNN
F 1 "10u" H 4450 3950 50  0000 L CNN
	1    4650 3800
	-1   0    0    1   
$EndComp
$Comp
L CAPAPOL C5
U 1 1 504D0A18
P 8600 3700
F 0 "C5" H 8500 3600 50  0000 L CNN
F 1 "22u" H 8400 3850 50  0000 L CNN
	1    8600 3700
	-1   0    0    1   
$EndComp
$Comp
L DIODESCH D3
U 1 1 504D08BE
P 3800 3950
F 0 "D3" H 3800 4050 40  0000 C CNN
F 1 "DIODESCH" H 3800 3850 40  0000 C CNN
	1    3800 3950
	0    1    -1   0   
$EndComp
$Comp
L GND #PWR3
U 1 1 4E7B4B20
P 4750 3250
F 0 "#PWR3" H 4750 3250 30  0001 C CNN
F 1 "GND" H 4750 3180 30  0001 C CNN
	1    4750 3250
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 4E7B4AFA
P 4200 2950
F 0 "R2" V 4280 2950 50  0000 C CNN
F 1 "5K1" V 4200 2950 50  0000 C CNN
	1    4200 2950
	0    -1   -1   0   
$EndComp
$Comp
L BC847C Q1
U 1 1 4E7B4ABC
P 4650 2950
F 0 "Q1" H 4500 2850 50  0000 C CNN
F 1 "BC847C" H 4450 3150 50  0000 C CNN
F 2 "SOT23-BCE" H 4840 2950 30  0001 C CNN
	1    4650 2950
	1    0    0    -1  
$EndComp
$Comp
L R R4
U 1 1 4E2033CE
P 4750 2400
F 0 "R4" V 4830 2400 50  0000 C CNN
F 1 "5K1" V 4750 2400 50  0000 C CNN
	1    4750 2400
	-1   0    0    1   
$EndComp
$Comp
L MOSFET_P Q2
U 1 1 4E2031C6
P 4750 1850
F 0 "Q2" V 4650 2000 60  0000 R CNN
F 1 "Si2319DS" V 4550 2300 60  0000 R CNN
	1    4750 1850
	0    1    -1   0   
$EndComp
$Comp
L C C4
U 1 1 4E203199
P 7400 3700
F 0 "C4" H 7150 3700 50  0000 L CNN
F 1 "0u1" H 7150 3800 50  0000 L CNN
	1    7400 3700
	-1   0    0    1   
$EndComp
$Comp
L 78L05 U1
U 1 1 4E203182
P 6750 3550
F 0 "U1" H 6900 3354 60  0000 C CNN
F 1 "78L05" H 6750 3750 60  0000 C CNN
F 2 "SOT89" H 6960 3294 60  0001 C CNN
	1    6750 3550
	1    0    0    -1  
$EndComp
$Comp
L R R3
U 1 1 4E1493CA
P 4350 2100
F 0 "R3" V 4430 2100 50  0000 C CNN
F 1 "100K" V 4350 2100 50  0000 C CNN
	1    4350 2100
	0    1    1    0   
$EndComp
$Comp
L GND #PWR5
U 1 1 4E1493B8
P 6150 4000
F 0 "#PWR5" H 6150 4000 30  0001 C CNN
F 1 "GND" H 6150 3930 30  0001 C CNN
	1    6150 4000
	1    0    0    -1  
$EndComp
$Comp
L 78L05 U2
U 1 1 4DC03E78
P 8000 3550
F 0 "U2" H 8150 3354 60  0000 C CNN
F 1 "LN-6206-30" H 8000 3750 60  0000 C CNN
F 2 "SOT89" H 8210 3294 60  0001 C CNN
	1    8000 3550
	1    0    0    -1  
$EndComp
$EndSCHEMATC
