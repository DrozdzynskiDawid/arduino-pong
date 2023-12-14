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

int scoreLeft;
int scoreRight;

uint8_t oled_buf[WIDTH * HEIGHT / 8];

char result[48];

int leftPos;
int rightPos;

bool xDirection;
bool yDirection;
int xPos;
int yPos;

void gameStart(){
  //ustawienie wartości początkowych gry
    leftPos = 35;
    rightPos = 35;

    xDirection = random(0, 2);
    yDirection = random(0, 2);
    xPos = 64;
    yPos = 32;
    scoreRight = 0;
    scoreLeft = 0;
}

void setup() {
  //ustawienie pinów dla diod
  pinMode(LEFT_DIOD, OUTPUT);
  digitalWrite(LEFT_DIOD, LOW);
  pinMode(RIGHT_DIOD, OUTPUT);
  digitalWrite(RIGHT_DIOD, LOW);

  /* logo producenta */
  SH1106_begin();
  SH1106_clear(oled_buf);
  SH1106_bitmap(0, 0, Waveshare12864, 128, 64, oled_buf);
  SH1106_display(oled_buf);
  delay(500);
  SH1106_clear(oled_buf);
  gameStart();
}

void loop() {
//wyczyszczenie zawartości ekranu
  SH1106_clear(oled_buf);

//przesuwanie paletek
  if(analogRead(LEFT_JOYSTICK) == 1023 && leftPos < 48) {
    leftPos += 1; 
  } else if(analogRead(LEFT_JOYSTICK) == 0 && leftPos > 15) {
    leftPos -= 1; 
  } else if(analogRead(RIGHT_JOYSTICK) == 1023 && rightPos < 48) {
    rightPos += 1; 
  } else if(analogRead(RIGHT_JOYSTICK) == 0 && rightPos > 15) {
    rightPos -= 1; 
  }

// zmiana pozycji piłeczki
  if(xDirection && yDirection){
    xPos += 1;
    yPos += 1;
  } else if(!xDirection && yDirection){
    xPos -= 1;
    yPos += 1;
  } else if(xDirection && !yDirection){
    xPos += 1;
    yPos -= 1;
  } else if(!xDirection && !yDirection){
    xPos -= 1;
    yPos -= 1;
  }

// zmiana kierunku piłeczki w osi y
  if(yPos == 17 || yPos == 63) yDirection = !yDirection;

//wyświetlenie wyniku
  sprintf(result, "Player1:%d   %d:Player2", scoreLeft, scoreRight);
  SH1106_string(0,13,"______________________________________________________________________________________________________________________________",2,0,oled_buf);
  SH1106_string(0,0,result,12,1,oled_buf);

//rysowanie paletek
  for(int i=0; i<15; i++){
    SH1106_pixel(0,i+leftPos,'b',oled_buf);
  }
  for(int i=0; i<15; i++){
    SH1106_pixel(127,i+rightPos,'b',oled_buf);
  }

// odbicie paletką
  if((xPos == 1 && leftPos <= yPos && leftPos + 15 >= yPos) ||
    (xPos == 126 && rightPos <= yPos && rightPos + 15 >= yPos)) xDirection = !xDirection;

//gol
  if(xPos == 0){
    xPos = 64;
    yPos = 32;
    digitalWrite(LEFT_DIOD, HIGH);
    delay(100);
    digitalWrite(LEFT_DIOD, LOW);
    scoreRight += 1;
  } else if(xPos == 127){
    xPos = 64;
    yPos = 32;
    digitalWrite(RIGHT_DIOD, HIGH);
    delay(100);
    digitalWrite(RIGHT_DIOD, LOW);
    scoreLeft += 1;
  }

//koniec gry
  if(scoreRight == MAX_POINTS){
    SH1106_clear(oled_buf);
    SH1106_string(10,25,"Winner Player2",15,1,oled_buf);
    SH1106_display(oled_buf);  
    delay(1000);
    gameStart();
  } else if(scoreLeft == MAX_POINTS){
    SH1106_clear(oled_buf);
    SH1106_string(10,25,"Winner Player1",15,1,oled_buf);
    SH1106_display(oled_buf);  
    delay(1000);
    gameStart();
  }

// rysowanie piłeczki
  SH1106_pixel(xPos, yPos,'b',oled_buf);

//wyświetlenie treści na ekranie
  SH1106_display(oled_buf); 
}

