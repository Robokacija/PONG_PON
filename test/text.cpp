#include <Arduino.h>
#include <cyberpi.h>



CyberPi cyber;
uint8_t samples[128];
int idx = 0;

void setup() 
{
    Serial.begin(115200);
    Serial.setDebugOutput(true);
    delay(1000);
    cyber.begin();
    int font_size = 16;
    Bitmap *bitmap1 = cyber.create_text(L"你好",0xffff,font_size);
    cyber.set_bitmap(4,4,bitmap1);
    Bitmap *bitmap2 = cyber.create_text(L"Ilitiga: Pozdrav",0xff00,font_size);
    cyber.set_bitmap(4,24,bitmap2);
    Bitmap *bitmap3 = cyber.create_text(L"Robokacijo! :D",0xfb00,font_size);
    cyber.set_bitmap(4,44,bitmap3);
    cyber.render_lcd();
}

void loop() 
{
    
}