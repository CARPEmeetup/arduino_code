 #include <Adafruit_NeoPixel.h>
#include <Wire.h>

byte nunchuck_data[6];
int count = 0;

#define PIN            6
#define NUMPIXELS      16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;


void setup ()
{
//Serial.begin (19200);
Wire.begin();
nunchuk_init ();
pixels.begin();
pixels.setBrightness(150);
}

void nunchuk_init ()
{
Wire.beginTransmission (0x52);
Wire.write ((byte)0xF0);
Wire.write ((byte)0x55);
Wire.write ((byte)0xFB);
Wire.write ((byte)0x00);
Wire.endTransmission ();
}

void loop ()
{
Wire.requestFrom (0x52, 6);
while (Wire.available ())
{
  
nunchuck_data[count] = (Wire.read ());
count++;
}
if (count >= 5)
{
print ();
}
count = 0;
nunchuck_send_request ();
delay (100);    
}

void accel_pixels(uint32_t color)
{

for(int i=0;i<NUMPIXELS;i++){    
    pixels.setPixelColor(i, color);
    pixels.show();    
  }
}



void theaterChase(uint32_t color, uint8_t wait) {
  
    for (int q=0; q < 3; q++) {
      for (int i=0; i < NUMPIXELS; i=i+3) {
        pixels.setPixelColor(i+q, color);    //turn every third pixel on
      }
      pixels.show();

      delay(wait);

      for (int i=0; i < NUMPIXELS; i=i+3) {
        pixels.setPixelColor(i+q, 0);        //turn every third pixel off
      }
    }
  }
  
 
 void flashyFlash(uint32_t color, uint8_t wait) {       
      for (int i=0; i < NUMPIXELS; i++){
        pixels.setPixelColor(i, color);    
      }    
      pixels.show();
      delay(wait);  
      for (int i=0; i < NUMPIXELS; i++) {
        pixels.setPixelColor(i, 0);        
      }
      pixels.show();
      delay(wait);   
    }

void print ()
{
int joy_x_axis = nunchuck_data [0];
int joy_y_axis = nunchuck_data [1];
int accel_x_axis = nunchuck_data[2] * 2 * 2;
int accel_y_axis = nunchuck_data[3] * 2 * 2;
int accel_z_axis = nunchuck_data[4] * 2 * 2;
int z_button = 0;
int c_button = 0;
if ((nunchuck_data[5] >> 0) & 1)
{
z_button = 1;
}
if ((nunchuck_data[5] >> 1) & 1)
{
c_button = 1;
}
if ((nunchuck_data[5] >> 2)& 1)
{
 accel_x_axis += 2;
}
if ((nunchuck_data[5] >> 3)& 1)
{
 accel_x_axis += 1;
}
if ((nunchuck_data[5] >> 4)& 1)
{
 accel_y_axis += 2;
}
if ((nunchuck_data[5] >> 5)& 1)
{
 accel_y_axis += 1;
}
if ((nunchuck_data[5] >> 6)& 1)
{
 accel_z_axis += 2;
}
if ((nunchuck_data[5] >> 7)& 1)
{
 accel_z_axis += 1;
}
Serial.print(joy_x_axis);
Serial.print(" , ");
Serial.print(joy_y_axis);
Serial.print(" \n ");
if (z_button == 0)
{theaterChase(pixels.Color(accel_x_axis/2 - 150, accel_y_axis/2 - 150, accel_z_axis/2 - 150), 50);}

else if (c_button == 0)
{{flashyFlash(pixels.Color(accel_x_axis/2 - 150, accel_y_axis/2 - 150, accel_z_axis/2 - 150), 50);}}
else
{accel_pixels(pixels.Color(accel_x_axis/2 - 150, accel_y_axis/2 - 150, accel_z_axis/2 - 150));}
}

void nunchuck_send_request()
{
Wire.beginTransmission(0x52);
Wire.write((byte)0x00);
Wire.endTransmission();
}


