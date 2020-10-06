#include <Arduino.h>                           

String data; //Consohlen Input
String VERSION = "1-08-2020-Human  Dome-Controller_Human-01-L298";

byte debug = false;
long randNumber;
long zeit;
unsigned long previousMillis = 0;        // will store last time LED was updated
// constants won't change:
const long interval = 1000;           // interval at which to blink (milliseconds)

//Move Sensor
byte NachL = false;
byte NachR = false;
byte Mitte = false;

int Sdiff = 0;

///Motor L298 Anschluss
///Eine Richtung
//int links = 6; //Pin 6
//int rechts = 5; //Pin 5

//Umgedreht
int links = 5; //Pin 5
int rechts = 6; //Pin 6


int tempo = 200;
int Htempo = 150; //Human Tracking
int Rtempo = 200;
int faktor = 100;
unsigned long Rpos = 35;  //Zeit von Center to Zielposition in Millisec
int durchlauf = 0;
int sensorValue = 1500;
int sensorCenter = 8; //vorher auf 16
int rotime;
unsigned long zeit1, zeit2;
int sensorRC = 21; ///von 2 auf 21 geänder wg I2C
//int sensorRC_out = 10;
int Mode = 2;// 0=RandMove // 1=RCMove  //2=human //3=Service
int moving = 0;
int SendStatus = 16; /// StatusSignal to PowerControl
int stat=0;

int vpos = 1000;

int centerState = 0;
const int ledPinC =  20;  
const int ledPin1 =  18;  
const int ledPin2 =  19;  

//int ledStateC = LOW;
int ledState1 = LOW; 
int ledState2 = LOW; 

#define PIE_PANEL          0
//#define TOP_PIE_PANEL      0x0010
//#define PIE_PANELS_MASK    (PIE_PANEL)


const ServoSettings servoSettings[] PROGMEM = {
    { 10,  PIE_PANEL,     1000, 1650 },  /* 0: pie panel 1 */
    };
