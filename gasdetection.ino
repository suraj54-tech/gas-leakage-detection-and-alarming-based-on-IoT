#include "config.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
const int buzzer=D0;
int warm_up;

const int gas=D5;
// photocell state
int current = 0;
int last = -1;
// set up the 'analog' feed
AdafruitIO_Feed *analog = io.feed("gas");

void setup() {

  // start the serial connection
  Serial.begin(115200);
       lcd.begin();
       lcd.backlight();
       lcd.clear();
       lcd.setCursor(0,0);
  lcd.print("gas robot");
lcd.setCursor(0,1);
lcd.print("DETECTION..");
  pinMode(gas, INPUT_PULLUP);
 
  pinMode(buzzer, OUTPUT);

 delay(1500);
  // wait for serial monitor to open
  while(! Serial);

  // connect to io.adafruit.com
  Serial.print("Connecting to Adafruit IO");
  io.connect();

  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  // we are connected
  Serial.println();
  Serial.println(io.statusText());

}

void loop() {

   io.run();
 current = digitalRead(gas);
     digitalWrite(buzzer,LOW);

  // save the current state to the analog feed
  Serial.print("sending -> ");
  Serial.println(current);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS");
  lcd.setCursor(0,1);
  lcd.print(current);
 
  //delay(3000);
  analog->save("Monitoring");
  delay(3000);
if(current==LOW){
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("GAS detected");
  lcd.setCursor(0,1);
  lcd.print(current);
  analog->save("gas detected");
  digitalWrite(buzzer,HIGH);
  
  delay(3000);
  digitalWrite(buzzer,LOW);
  
  }
  
}
