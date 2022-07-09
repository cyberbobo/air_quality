EESchema Schematic File Version 4
EELAYER 30 0
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
$Comp
L ESP8266:NodeMCU_1.0_(ESP-12E) U?
U 1 1 62C60BD2
P 5850 3900
F 0 "U?" H 5850 4987 60  0000 C CNN
F 1 "NodeMCU_1.0_(ESP-12E)" H 5850 4881 60  0000 C CNN
F 2 "" H 5250 3050 60  0000 C CNN
F 3 "" H 5250 3050 60  0000 C CNN
	1    5850 3900
	1    0    0    -1  
$EndComp
$Comp
L Sensor_Gas:MQ-135_shield U??
U 1 1 62C629D1
P 4300 2300
F 0 "U??" H 4630 2289 50  0000 L CNN
F 1 "MQ-135_shield" H 4630 2198 50  0000 L CNN
F 2 "Sensor:MQ-6" H 4350 1850 50  0001 C CNN
F 3 "https://www.winsen-sensor.com/d/files/semiconductor/mq-6.pdf" H 4300 2550 50  0001 C CNN
	1    4300 2300
	1    0    0    -1  
$EndComp
$Comp
L Device:R R?
U 1 1 62C9A46A
P 8250 3450
F 0 "R?" H 8320 3496 50  0000 L CNN
F 1 "220" H 8320 3405 50  0000 L CNN
F 2 "" V 8180 3450 50  0001 C CNN
F 3 "~" H 8250 3450 50  0001 C CNN
	1    8250 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 62C9ACDF
P 7350 3300
F 0 "D?" H 7343 3045 50  0000 C CNN
F 1 "LED ORANGE" H 7343 3136 50  0000 C CNN
F 2 "" H 7350 3300 50  0001 C CNN
F 3 "~" H 7350 3300 50  0001 C CNN
	1    7350 3300
	-1   0    0    1   
$EndComp
$Comp
L Device:LED D?
U 1 1 62C9B27C
P 7600 3500
F 0 "D?" H 7593 3245 50  0000 C CNN
F 1 "LED GREEN" H 7593 3336 50  0000 C CNN
F 2 "" H 7600 3500 50  0001 C CNN
F 3 "~" H 7600 3500 50  0001 C CNN
	1    7600 3500
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62C9EA27
P 7050 3800
F 0 "#PWR?" H 7050 3550 50  0001 C CNN
F 1 "GND" H 7055 3627 50  0000 C CNN
F 2 "" H 7050 3800 50  0001 C CNN
F 3 "" H 7050 3800 50  0001 C CNN
	1    7050 3800
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62C9EE4D
P 4600 4600
F 0 "#PWR?" H 4600 4450 50  0001 C CNN
F 1 "+5V" H 4615 4773 50  0000 C CNN
F 2 "" H 4600 4600 50  0001 C CNN
F 3 "" H 4600 4600 50  0001 C CNN
	1    4600 4600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D?
U 1 1 62C9A926
P 7100 3100
F 0 "D?" H 7093 2845 50  0000 C CNN
F 1 "LED RED" H 7093 2936 50  0000 C CNN
F 2 "" H 7100 3100 50  0001 C CNN
F 3 "~" H 7100 3100 50  0001 C CNN
	1    7100 3100
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62CA878C
P 8250 3650
F 0 "#PWR?" H 8250 3400 50  0001 C CNN
F 1 "GND" H 8255 3477 50  0000 C CNN
F 2 "" H 8250 3650 50  0001 C CNN
F 3 "" H 8250 3650 50  0001 C CNN
	1    8250 3650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6650 3300 7200 3300
$Comp
L Sensor:DHT11 U?
U 1 1 62C615A2
P 8950 4050
F 0 "U?" H 8706 4004 50  0000 R CNN
F 1 "DHT11" H 8706 4095 50  0000 R CNN
F 2 "Sensor:Aosong_DHT11_5.5x12.0_P2.54mm" H 8950 3650 50  0001 C CNN
F 3 "http://akizukidenshi.com/download/ds/aosong/DHT11.pdf" H 9100 4300 50  0001 C CNN
	1    8950 4050
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR?
U 1 1 62CAD8D0
P 9700 3850
F 0 "#PWR?" H 9700 3600 50  0001 C CNN
F 1 "GND" H 9705 3677 50  0000 C CNN
F 2 "" H 9700 3850 50  0001 C CNN
F 3 "" H 9700 3850 50  0001 C CNN
	1    9700 3850
	1    0    0    -1  
$EndComp
Wire Wire Line
	8950 3750 9700 3750
Wire Wire Line
	9700 3750 9700 3850
Wire Wire Line
	8950 4350 7550 4350
Wire Wire Line
	7550 4350 7550 3700
Wire Wire Line
	7550 3700 6650 3700
Wire Wire Line
	6650 3800 7050 3800
Wire Wire Line
	5050 4600 4600 4600
$Comp
L Sensor_Gas:SDS011 U?
U 1 1 62CC6C5E
P 7150 5250
F 0 "U?" H 7527 5354 50  0000 L CNN
F 1 "SDS011" H 7527 5263 50  0000 L CNN
F 2 "" H 6800 5550 50  0001 C CNN
F 3 "" H 6800 5550 50  0001 C CNN
	1    7150 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7450 4950 7450 4300
Wire Wire Line
	7450 4300 6650 4300
$Comp
L power:GND #PWR?
U 1 1 62CCE0AE
P 6550 5300
F 0 "#PWR?" H 6550 5050 50  0001 C CNN
F 1 "GND" H 6555 5127 50  0000 C CNN
F 2 "" H 6550 5300 50  0001 C CNN
F 3 "" H 6550 5300 50  0001 C CNN
	1    6550 5300
	1    0    0    -1  
$EndComp
Wire Wire Line
	7250 4750 6550 4750
Wire Wire Line
	6550 4750 6550 5300
Wire Wire Line
	7250 4750 7250 4950
Wire Wire Line
	7350 4950 7350 4400
Wire Wire Line
	7350 4400 6650 4400
$Comp
L power:+5V #PWR?
U 1 1 62CD05A5
P 7050 4650
F 0 "#PWR?" H 7050 4500 50  0001 C CNN
F 1 "+5V" H 7065 4823 50  0000 C CNN
F 2 "" H 7050 4650 50  0001 C CNN
F 3 "" H 7050 4650 50  0001 C CNN
	1    7050 4650
	1    0    0    -1  
$EndComp
Wire Wire Line
	7050 4650 7050 4950
Wire Wire Line
	4250 2700 4250 3200
Wire Wire Line
	4250 3200 5050 3200
$Comp
L power:GND #PWR?
U 1 1 62CD794B
P 4400 2950
F 0 "#PWR?" H 4400 2700 50  0001 C CNN
F 1 "GND" H 4405 2777 50  0000 C CNN
F 2 "" H 4400 2950 50  0001 C CNN
F 3 "" H 4400 2950 50  0001 C CNN
	1    4400 2950
	1    0    0    -1  
$EndComp
$Comp
L power:+5V #PWR?
U 1 1 62CD7C74
P 4850 2750
F 0 "#PWR?" H 4850 2600 50  0001 C CNN
F 1 "+5V" H 4865 2923 50  0000 C CNN
F 2 "" H 4850 2750 50  0001 C CNN
F 3 "" H 4850 2750 50  0001 C CNN
	1    4850 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4550 2700 4550 2850
Wire Wire Line
	4550 2850 4850 2850
Wire Wire Line
	4850 2850 4850 2750
Wire Wire Line
	4400 2700 4400 2950
Wire Wire Line
	6650 3600 7750 3600
Wire Wire Line
	7750 3600 7750 4050
Wire Wire Line
	7750 4050 8650 4050
Wire Wire Line
	8250 3650 8250 3600
Wire Wire Line
	7500 3300 8000 3300
Wire Wire Line
	6650 3400 6850 3400
Wire Wire Line
	6850 3400 6850 3500
Wire Wire Line
	6850 3500 7450 3500
Wire Wire Line
	6650 3200 6850 3200
Wire Wire Line
	6850 3200 6850 3100
Wire Wire Line
	6850 3100 6950 3100
Wire Wire Line
	7750 3500 8000 3500
Wire Wire Line
	8000 3500 8000 3300
Connection ~ 8000 3300
Wire Wire Line
	8000 3300 8250 3300
Wire Wire Line
	7250 3100 8000 3100
Wire Wire Line
	8000 3100 8000 3300
Connection ~ 7350 4950
Connection ~ 7450 4950
$EndSCHEMATC
