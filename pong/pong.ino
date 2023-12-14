/*****************************************************************************
*
* File                : oled.ino
* Hardware Environment: Arduino UNO
* Build Environment   : Arduino
* Version             : V1.0.7
*
*                 (c) Copyright 2005-2017, WaveShare
*                      http://www.waveshare.com
*                      http://www.waveshare.net   
*                         All Rights Reserved
*
*****************************************************************************/
#include <SPI.h>
#include <Wire.h>
#include "sh1106.h"

#define VCCSTATE SH1106_SWITCHCAPVCC
#define WIDTH     128
#define HEIGHT     64
#define NUM_PAGE    8  /* number of pages */

#define OLED_RST    9 
#define OLED_DC     8
#define OLED_CS    10
#define SPI_MOSI   11    /* connect to the DIN pin of OLED */
#define SPI_SCK    13     /* connect to the CLK pin of OLED */

#define LEFT_DIOD 2
#define RIGHT_DIOD 3

#define RIGHT_JOYSTICK A0
#define LEFT_JOYSTICK A5

#define MAX_POINTS 5

int scoreLeft = 0;
int scoreRight = 0;

uint8_t oled_buf[WIDTH * HEIGHT / 8];

char result[48];

void setup() {
  pinMode(LEFT_DIOD, OUTPUT);
  digitalWrite(LEFT_DIOD, LOW);
  pinMode(RIGHT_DIOD, OUTPUT);
  digitalWrite(RIGHT_DIOD, LOW);


  Serial.begin(9600);
  Serial.print("OLED Example\n");

  /* display an image of bitmap matrix */
  SH1106_begin();
  SH1106_clear(oled_buf);
  SH1106_bitmap(0, 0, Waveshare12864, 128, 64, oled_buf);
  SH1106_display(oled_buf);
  delay(2000);
  SH1106_clear(oled_buf);

  /* display images of bitmap matrix */
  // SH1106_bitmap(0, 2, Signal816, 16, 8, oled_buf); 
  // SH1106_bitmap(24, 2,Bluetooth88, 8, 8, oled_buf); 
  // SH1106_bitmap(40, 2, Msg816, 16, 8, oled_buf); 
  // SH1106_bitmap(64, 2, GPRS88, 8, 8, oled_buf); 
  // SH1106_bitmap(90, 2, Alarm88, 8, 8, oled_buf); 
  // SH1106_bitmap(112, 2, Bat816, 16, 8, oled_buf); 

  //SH1106_string(0, 52, "MUSIC", 12, 0, oled_buf); 
  // SH1106_string(52, 52, "MENU", 12, 0, oled_buf); 
  // SH1106_string(98, 52, "PHONE", 12, 0, oled_buf);

  // SH1106_char3216(0, 16, '1', oled_buf);
  // SH1106_char3216(16, 16, '2', oled_buf);
  // SH1106_char3216(32, 16, ':', oled_buf);
  // SH1106_char3216(48, 16, '3', oled_buf);
  // SH1106_char3216(64, 16, '4', oled_buf);
  // SH1106_char3216(80, 16, ':', oled_buf);
  // SH1106_char3216(96, 16, '5', oled_buf);
  // SH1106_char3216(112, 16, '6', oled_buf);
  SH1106_string(0,13,"______________________________________________________________________________________________________________________________",2,0,oled_buf);
  SH1106_display(oled_buf); 
}

void loop() {
  // Serial.print(analogRead(RIGHT_JOYSTICK));
  // Serial.print("\n");
  // Serial.print(analogRead(LEFT_JOYSTICK));
  // Serial.print("\n");

  // digitalWrite(RIGHT_DIOD, HIGH); 
  // digitalWrite(LEFT_DIOD, HIGH);
  // delay(1000); 
  // digitalWrite(RIGHT_DIOD, LOW); 
  // digitalWrite(LEFT_DIOD, LOW);
  // delay(1000);
  sprintf(result, "Player1:%d   %d:Player2", scoreLeft, scoreRight);
  SH1106_string(0,0,result,12,1,oled_buf);
  SH1106_display(oled_buf); 
}
