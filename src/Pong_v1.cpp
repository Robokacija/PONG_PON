#include <Arduino.h>
#include "cyberpi.h"

CyberPi cyber;

#define S_W 127
#define S_H 127
#define P_W 4
#define P_H 16
#define BALL_SIZE 4

uint16_t w = 0xFFFF;

int scoreA = 0;
int scoreB = 0;
float gameSpeed =1.5;
float timer =0;

uint16_t paddleImage[4][16] = {
    {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w},
    {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w},
    {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w},
    {w, w, w, w, w, w, w, w, w, w, w, w, w, w, w, w}};

uint16_t ballImage[4][4] = {
    {w, w, w, w},
    {w, w, w, w},
    {w, w, w, w},
    {w, w, w, w}};

Sprite paddleL;
Sprite paddleR;
Sprite ball;
void draw()
{
  cyber.clean_lcd();
  
  cyber.set_bitmap(paddleL.x, paddleL.y, &paddleL);
  cyber.set_bitmap(paddleR.x, paddleR.y, &paddleR);
  cyber.set_bitmap(ball.x, ball.y, &ball);

  Sprite score1 = cyber.create_text(cyber.num_to_text(scoreA), 0xFFFF, 14);
  cyber.set_bitmap(50, 5, &score1);
  Sprite score2 = cyber.create_text(cyber.num_to_text(scoreB), 0xFFFF, 14);
  cyber.set_bitmap(70, 5, &score2);

  cyber.render_lcd();
}
void calculateMovement()
{
  if (cyber.get_button_a() && paddleR.y > 0)
  {
    paddleR.y -= gameSpeed;
  }
  if (cyber.get_button_b() && paddleR.y < S_H - 16)
  {
    paddleR.y += gameSpeed;
  }
  if (cyber.get_joystick_y() > 0 && paddleL.y < S_H - 16)
  {
    paddleL.y += gameSpeed;
  }
  if (cyber.get_joystick_y() < 0 && paddleL.y > 0)
  {
    paddleL.y -= gameSpeed;
  }

  if (timer>1){
  ball.x = ball.xSpeed*gameSpeed + ball.x;
  ball.y += ball.ySpeed*gameSpeed;
  }
 

  if (ball.y > S_H - BALL_SIZE || ball.y < 0)
  {
    ball.ySpeed = -ball.ySpeed;
    ball.y += ball.ySpeed*gameSpeed;
  }

  if (ball.x + BALL_SIZE >= paddleR.x)
  {
gameSpeed=gameSpeed*1.2;
    if (ball.y >= (paddleR.y) && ball.y <= (paddleR.y + paddleR.height))
    {
      ball.xSpeed *= -1;
    }
    else
    {
      scoreA++;
      ball.x = S_W / 4;
      ball.y = S_W / 2;
      draw();
      timer=0;
      gameSpeed =1.5;
      
    }
  }

  if (ball.x < paddleL.x + P_W)
  {

    if (ball.y >= paddleL.y-BALL_SIZE  && ball.y <= paddleL.y + P_H)
    {
      ball.xSpeed *= -1;
    }
    else
    {
      scoreB++;
      ball.x = (S_W / 4)*3;
      ball.y = S_W / 2;
      draw();
      timer=0;
      gameSpeed =1.5;
    }
  }

 
}



void setup()
{

  cyber.begin();

  // Stvaranje likova:

  paddleL.width = P_W;
  paddleL.height = P_H;
  paddleL.buffer = (uint16_t *)paddleImage;
  paddleL.x = 10;
  paddleL.y = 67;

  paddleR.x = 118;
  paddleR.y = 67;
  paddleR.width = P_W;
  paddleR.height = P_H;
  paddleR.buffer = (uint16_t *)paddleImage;

  ball.xSpeed = 1;
  ball.ySpeed = 1;
  ball.x = S_W / 2;
  ball.y = S_H / 2;

  ball.width = BALL_SIZE;
  ball.height = BALL_SIZE;
  ball.buffer = (uint16_t *)ballImage;
 draw();
 delay(1000); 
}

void loop()
{
  calculateMovement();
  draw();
  delay(20);
  timer+=0.02;
}
