EESchema Schematic File Version 4
EELAYER 30 0
EELAYER END
$Descr A 11000 8500
encoding utf-8
Sheet 1 1
Title "Steam Punk Goggles from KnowHow187"
Date "2023-02-03"
Rev ""
Comp "MDO"
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L mdoLibrary:Arduino A?
U 1 1 63D469A7
P 9100 4950
F 0 "A?" H 9100 5937 60  0000 C CNN
F 1 "Arduino" H 9100 5831 60  0000 C CNN
F 2 "" H 9100 4950 60  0000 C CNN
F 3 "" H 9100 4950 60  0000 C CNN
	1    9100 4950
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:UBEC J?
U 1 1 63D4B50C
P 2200 5100
F 0 "J?" H 2300 5787 60  0000 C CNN
F 1 "UBEC" H 2300 5681 60  0000 C CNN
F 2 "" H 2200 5100 60  0001 C CNN
F 3 "" H 2200 5100 60  0001 C CNN
	1    2200 5100
	1    0    0    -1  
$EndComp
$Comp
L Device:Battery_Cell BT?
U 1 1 63D4C0E5
P 750 5100
F 0 "BT?" H 868 5196 50  0000 L CNN
F 1 "Battery_9V" H 868 5105 50  0000 L CNN
F 2 "" V 750 5160 50  0001 C CNN
F 3 "~" V 750 5160 50  0001 C CNN
	1    750  5100
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 2800 8950 3000
$Comp
L Device:R_POT RV?
U 1 1 63D49A93
P 8950 3150
F 0 "RV?" H 8881 3196 50  0000 R CNN
F 1 "R_POT" H 8881 3105 50  0000 R CNN
F 2 "" H 8950 3150 50  0001 C CNN
F 3 "~" H 8950 3150 50  0001 C CNN
	1    8950 3150
	1    0    0    -1  
$EndComp
Wire Wire Line
	750  4850 750  4900
Wire Wire Line
	750  5250 750  5200
$Comp
L mdoLibrary:SW_SPST SW?
U 1 1 63D6255A
P 1400 4850
F 0 "SW?" H 1400 5085 50  0000 C CNN
F 1 "SW_SPST" H 1400 4994 50  0000 C CNN
F 2 "" H 1400 4850 50  0001 C CNN
F 3 "" H 1400 4850 50  0001 C CNN
	1    1400 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	1200 4850 750  4850
$Comp
L mdoLibrary:LEDring_med Z?
U 1 1 63D744C6
P 3350 3550
F 0 "Z?" H 4178 3520 60  0000 L CNN
F 1 "LEDring_med" H 4178 3414 60  0000 L CNN
F 2 "" H 3350 3700 60  0001 C CNN
F 3 "" H 3350 3700 60  0001 C CNN
	1    3350 3550
	1    0    0    -1  
$EndComp
$Comp
L mdoLibrary:LEDring_med Z?
U 1 1 63D74B09
P 6350 3500
F 0 "Z?" H 7178 3470 60  0000 L CNN
F 1 "LEDring_med" H 7178 3364 60  0000 L CNN
F 2 "" H 6350 3650 60  0001 C CNN
F 3 "" H 6350 3650 60  0001 C CNN
	1    6350 3500
	1    0    0    -1  
$EndComp
Wire Wire Line
	3400 4500 3400 4850
Wire Wire Line
	6400 4450 6400 4850
Text Notes 2900 3400 0    79   ~ 0
WS2812B 5050\n 16 LED Ring
Text Notes 5900 3350 0    79   ~ 0
WS2812B 5050\n 16 LED Ring
Text Notes 8350 2550 0    79   ~ 0
Potentiometer between\n 10 KOhm to 50 KOhm
Wire Wire Line
	2900 4850 3400 4850
Wire Wire Line
	6200 4450 6200 4700
Wire Wire Line
	6200 4700 3500 4700
Wire Wire Line
	3500 4500 3500 4700
Wire Wire Line
	8500 4750 6500 4750
Wire Wire Line
	6500 4450 6500 4750
Wire Wire Line
	10100 3150 10100 4650
Wire Wire Line
	10100 4650 9700 4650
Wire Wire Line
	9100 3150 10100 3150
Wire Wire Line
	6400 4850 7900 4850
Wire Wire Line
	7900 4850 7900 6100
Connection ~ 6400 4850
Wire Wire Line
	1700 4850 1600 4850
Wire Wire Line
	1700 5250 750  5250
Connection ~ 3400 4850
Wire Wire Line
	8950 3300 8950 3550
Wire Wire Line
	8300 4550 8500 4550
Wire Wire Line
	10300 2800 10300 4550
Wire Wire Line
	7900 6100 10300 6100
Connection ~ 10300 4550
Wire Wire Line
	10300 4550 10300 6100
Wire Wire Line
	8950 2800 10300 2800
Wire Wire Line
	9700 4550 10300 4550
Wire Wire Line
	9700 4350 9900 4350
Wire Wire Line
	9900 4350 9900 3550
Wire Wire Line
	8950 3550 9900 3550
Wire Wire Line
	3300 4500 3300 5250
Connection ~ 6300 5250
Wire Wire Line
	6300 5250 8300 5250
Wire Wire Line
	6300 4450 6300 5250
Wire Wire Line
	8300 4550 8300 5250
Wire Wire Line
	3400 4850 6400 4850
Wire Wire Line
	3300 5250 6300 5250
Wire Wire Line
	2900 5250 3300 5250
Connection ~ 3300 5250
Text Notes 4350 5950 0    79   ~ 0
Cable between\n goggle sides
Text Notes 1750 1450 0    197  ~ 0
9V rechargeable battery and UBEC on one side\nArduino Nano and potentiometer on other side
Wire Bus Line
	4350 4350 5250 4350
Text Notes 3750 5650 0    1220 ~ 0
O
Text Notes 4600 5650 0    1220 ~ 0
O
Wire Bus Line
	4350 5600 5250 5600
Text Notes 1050 4550 0    79   ~ 0
Knife Switch
Text Notes 2000 6100 0    79   ~ 0
5 Volt\nUniversal\nBattery\nEliminator\nCircuit
Text Notes 750  5400 0    79   ~ 0
9V Battery
$EndSCHEMATC
