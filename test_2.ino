#include <Wire.h>
#include <Adafruit_NeoPixel.h>
#include <math.h>
int BH1750address = 0x23; //i2c address 

const int pixnum = 15;
const int pixpin = 10;
int count = 0;
int xA;
int yA;
int zA;
int a;

Adafruit_NeoPixel pix = Adafruit_NeoPixel(pixnum, pixpin, NEO_GBR + NEO_KHZ800);

/*void on() {
  for(int p = 0; p < pixnum; p++) {
    pix.setPixelColor(p, pix.Color(100, 100, 100));
  }
  pix.show();
} */

/*void off() {
  for(int p = 0; p < pixnum; p++) {
      pix.setPixelColor(p, pix.Color(0, 0, 0));  
  } 
  pix.show();
}*/

/*void blink1() {
 for(int b = 0; b < 5; b++) {
  for(int p = 0; p < pixnum; p++) {
    pix.setPixelColor(p, pix.Color(0, 0, 150));
    pix.show();
  }
  for(int p = 0; p < pixnum; p++) {
    pix.setPixelColor(p, pix.Color(0, 0, 0));
    pix.show();
  }
 }
}*/

byte buff[2];

void setup()
{
  Wire.begin();
  Serial.begin(9600);
  pix.begin();
  pix.show();
}

void loop()
{
  int i;                      
  uint16_t val=0;
  BH1750_Init(BH1750address);
  delay(200);
 
  if(2==BH1750_Read(BH1750address))
  {
    val=((buff[0]<<8)|buff[1])/1.2;
    Serial.print(val,DEC);     
    Serial.println("lux"); 
  }
  delay(150);

  //if(val<50){
  //  on();
  //} else off();

  xA = analogRead(A0);
  yA = analogRead(A1);
  zA = analogRead(A2);
 
  /*Serial.print(xA);
  Serial.print(",");
  Serial.print(yA);
  Serial.print(",");
  Serial.print(zA);
  Serial.println();
  delay(20);*/

  //if (xA < 355 || xA > 375) {
  //  blink1();
  //} 
}
 
int BH1750_Read(int address)
{
  int i=0;
  Wire.beginTransmission(address);
  Wire.requestFrom(address, 2);
  while(Wire.available()) //
  {
    buff[i] = Wire.read();  // receive one byte
    i++;
  }
  Wire.endTransmission();  
  return i;
}
 
void BH1750_Init(int address)
{
  Wire.beginTransmission(address);
  Wire.write(0x10);//1lx reolution 120ms
  Wire.endTransmission();
}
