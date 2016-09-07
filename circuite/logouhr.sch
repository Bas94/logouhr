EESchema Schematic File Version 2
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
LIBS:ESP8266
LIBS:logouhr-cache
EELAYER 25 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
Text GLabel 1300 950  0    60   Input ~ 0
230V1-In
Text GLabel 1300 1350 0    60   Input ~ 0
230V2-In
$Comp
L TRANSFO T1
U 1 1 57B878F2
P 2200 1150
F 0 "T1" H 2200 1400 50  0000 C CNN
F 1 "TRANSFO" H 2200 850 50  0000 C CNN
F 2 "" H 2200 1150 50  0001 C CNN
F 3 "" H 2200 1150 50  0000 C CNN
	1    2200 1150
	1    0    0    -1  
$EndComp
$Comp
L Diode_Bridge D1
U 1 1 57B87A74
P 3350 1200
F 0 "D1" H 3100 1500 50  0000 C CNN
F 1 "Diode_Bridge" H 3700 850 50  0000 C CNN
F 2 "" H 3350 1200 50  0001 C CNN
F 3 "" H 3350 1200 50  0000 C CNN
	1    3350 1200
	1    0    0    -1  
$EndComp
$Comp
L LM117K U1
U 1 1 57B87BFD
P 4350 1250
F 0 "U1" H 4150 1450 50  0000 C CNN
F 1 "LM117K" H 4350 1450 50  0000 L CNN
F 2 "TO-3" H 4350 1350 50  0000 C CIN
F 3 "" H 4350 1250 50  0000 C CNN
	1    4350 1250
	1    0    0    -1  
$EndComp
$Comp
L CP C1
U 1 1 57B881DD
P 3200 2050
F 0 "C1" H 3225 2150 50  0000 L CNN
F 1 "100µF" H 3225 1950 50  0000 L CNN
F 2 "Capacitors_ThroughHole:C_Radial_D10_L13_P5" H 3238 1900 50  0001 C CNN
F 3 "" H 3200 2050 50  0000 C CNN
	1    3200 2050
	0    1    1    0   
$EndComp
$Comp
L C C2
U 1 1 57B8830F
P 3450 2400
F 0 "C2" H 3475 2500 50  0000 L CNN
F 1 "100nF" H 3475 2300 50  0000 L CNN
F 2 "" H 3488 2250 50  0001 C CNN
F 3 "" H 3450 2400 50  0000 C CNN
	1    3450 2400
	1    0    0    -1  
$EndComp
$Comp
L C C3
U 1 1 57B883B1
P 4900 1500
F 0 "C3" H 4925 1600 50  0000 L CNN
F 1 "10nF" H 4925 1400 50  0000 L CNN
F 2 "" H 4938 1350 50  0001 C CNN
F 3 "" H 4900 1500 50  0000 C CNN
	1    4900 1500
	1    0    0    -1  
$EndComp
$Comp
L ESP8266EX U2
U 1 1 57B889F6
P 7250 1550
F 0 "U2" H 6350 2250 60  0000 C CNN
F 1 "ESP8266EX" H 6400 2150 60  0000 C CNN
F 2 "" H 6350 2250 60  0001 C CNN
F 3 "" H 6350 2250 60  0000 C CNN
	1    7250 1550
	1    0    0    1   
$EndComp
$Comp
L RELAY_2RT K1
U 1 1 57B8A417
P 9900 3050
F 0 "K1" H 9850 3450 50  0000 C CNN
F 1 "RELAY_2RT" H 10050 2550 50  0000 C CNN
F 2 "" H 9900 3050 50  0001 C CNN
F 3 "" H 9900 3050 50  0000 C CNN
	1    9900 3050
	0    1    1    0   
$EndComp
$Comp
L BC818-40 Q1
U 1 1 57B8A763
P 9550 1800
F 0 "Q1" H 9750 1875 50  0000 L CNN
F 1 "BC818-40" H 9750 1800 50  0000 L CNN
F 2 "TO_SOT_Packages_SMD:SOT-23" H 9750 1725 50  0000 L CIN
F 3 "" H 9550 1800 50  0000 L CNN
	1    9550 1800
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 57B8C658
P 8800 1800
F 0 "R1" V 8880 1800 50  0000 C CNN
F 1 "150" V 8800 1800 50  0000 C CNN
F 2 "" V 8730 1800 50  0001 C CNN
F 3 "" H 8800 1800 50  0000 C CNN
	1    8800 1800
	0    1    1    0   
$EndComp
Wire Wire Line
	2950 1200 2950 2550
Wire Wire Line
	2950 2550 9550 2550
Wire Wire Line
	4350 1500 4350 2550
Wire Wire Line
	3750 1200 3950 1200
Wire Wire Line
	3350 800  2800 800 
Wire Wire Line
	2800 800  2800 950 
Wire Wire Line
	2800 950  2600 950 
Wire Wire Line
	2600 1350 2750 1350
Wire Wire Line
	2750 1350 2750 1700
Wire Wire Line
	2750 1700 3350 1700
Wire Wire Line
	3350 1700 3350 1600
Wire Wire Line
	3050 2050 2950 2050
Connection ~ 2950 2050
Wire Wire Line
	3350 2050 3850 2050
Wire Wire Line
	3850 2050 3850 1200
Connection ~ 3850 1200
Wire Wire Line
	3450 2250 3450 2050
Connection ~ 3450 2050
Wire Wire Line
	4350 1650 4900 1650
Connection ~ 4350 1650
Wire Wire Line
	4900 1350 4900 1200
Connection ~ 4900 1200
Wire Wire Line
	5600 1900 6100 1900
Wire Wire Line
	5600 600  5600 1900
Wire Wire Line
	4750 1200 5600 1200
Wire Wire Line
	6800 2550 6800 2350
Connection ~ 4350 2550
Wire Wire Line
	9550 2550 9550 2650
Wire Wire Line
	8250 1800 8650 1800
Wire Wire Line
	8950 1800 9350 1800
Wire Wire Line
	9650 2000 9650 2650
Connection ~ 6800 2550
Text GLabel 10150 2150 0    60   Input ~ 0
230V1-In
Text GLabel 10700 2150 0    60   Input ~ 0
230V2-In
Wire Wire Line
	10150 2150 10150 2400
Wire Wire Line
	10150 2400 9850 2400
Wire Wire Line
	9850 2400 9850 2650
Wire Wire Line
	8250 1300 8500 1300
Wire Wire Line
	8500 1300 8500 3450
Wire Wire Line
	9750 3450 9750 3800
Wire Wire Line
	9750 3800 9000 3800
$Comp
L D D2
U 1 1 57B8E74F
P 9450 2300
F 0 "D2" H 9450 2400 50  0000 C CNN
F 1 "1N4148" H 9450 2200 50  0000 C CNN
F 2 "" H 9450 2300 50  0001 C CNN
F 3 "" H 9450 2300 50  0000 C CNN
	1    9450 2300
	-1   0    0    -1  
$EndComp
Wire Wire Line
	9600 2300 9650 2300
Connection ~ 9650 2300
Wire Wire Line
	9300 2300 9300 2550
Connection ~ 9300 2550
Wire Wire Line
	5600 600  9650 600 
Wire Wire Line
	9650 600  9650 1600
Connection ~ 5600 1200
$Comp
L F_Small F1
U 1 1 57B8F179
P 1550 950
F 0 "F1" H 1510 1010 50  0000 L CNN
F 1 "F_Small" H 1430 890 50  0000 L CNN
F 2 "" H 1550 950 50  0001 C CNN
F 3 "" H 1550 950 50  0000 C CNN
	1    1550 950 
	1    0    0    -1  
$EndComp
Wire Wire Line
	1300 950  1450 950 
Wire Wire Line
	1650 950  1800 950 
Wire Wire Line
	1800 1350 1300 1350
Text GLabel 8500 3450 2    60   Output ~ 0
LED-Signal
Text GLabel 9000 3800 0    60   Output ~ 0
230V1-Out
Text GLabel 9000 3950 0    60   Output ~ 0
230V2-Out
Wire Wire Line
	10050 3450 10050 3950
Wire Wire Line
	10050 3950 9000 3950
Wire Wire Line
	10150 2650 10700 2650
Wire Wire Line
	10700 2650 10700 2150
Text Label 5250 2550 0    60   ~ 0
GND
Text Label 5250 1200 0    60   ~ 0
VCC
$Comp
L CONN_01X03 P1
U 1 1 57D03E64
P 7450 3450
F 0 "P1" H 7450 3650 50  0000 C CNN
F 1 "CONN_01X03" V 7550 3450 50  0000 C CNN
F 2 "" H 7450 3450 50  0001 C CNN
F 3 "" H 7450 3450 50  0000 C CNN
	1    7450 3450
	-1   0    0    -1  
$EndComp
Wire Wire Line
	8500 3450 7650 3450
Text Label 7650 3350 0    60   ~ 0
GND
Text Label 7650 3550 0    60   ~ 0
5V12A
$Comp
L CONN_01X03 P2
U 1 1 57D04591
P 7450 3950
F 0 "P2" H 7450 4150 50  0000 C CNN
F 1 "CONN_01X03" V 7550 3950 50  0000 C CNN
F 2 "" H 7450 3950 50  0001 C CNN
F 3 "" H 7450 3950 50  0000 C CNN
	1    7450 3950
	1    0    0    -1  
$EndComp
Text GLabel 7250 3850 0    60   Input ~ 0
230V1-In
Text GLabel 7250 4050 0    60   Input ~ 0
230V2-In
$Comp
L CONN_01X03 P3
U 1 1 57D04700
P 7450 4400
F 0 "P3" H 7450 4600 50  0000 C CNN
F 1 "CONN_01X03" V 7550 4400 50  0000 C CNN
F 2 "" H 7450 4400 50  0001 C CNN
F 3 "" H 7450 4400 50  0000 C CNN
	1    7450 4400
	1    0    0    -1  
$EndComp
Text GLabel 7250 4300 0    60   Output ~ 0
230V2-Out
Text GLabel 7250 4500 0    60   Output ~ 0
230V2-Out
$EndSCHEMATC