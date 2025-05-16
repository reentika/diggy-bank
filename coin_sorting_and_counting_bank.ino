#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7); // 0x27 is the I2C bus address for an unmodified module

const int coi100n  = A0;    //input from ir sensor
const int coi200n = A1;
const int coi500n  = A2; 

int ir100,ir200,ir500 = 0;
int cnt100r,cnt200r,cnt500r,cnttotal = 0;
void setup() {
  Serial.begin(9600); 
 pinMode(coi100n , INPUT);
  pinMode(coi200n ,INPUT);
  pinMode(coi500n,INPUT);
  
 
 lcd.setBacklightPin(3,POSITIVE);
 lcd.setBacklight(LOW); // You can turn the backlight off by setting it to LOW instead of HIGH
 lcd.begin(16, 2);
lcd.write(EEPROM.read(5));
}

void loop() {
 ir100 =digitalRead(coi100n);  //read the state of coi100n and store it as ir100
  ir200 =digitalRead(coi200n); //read the state of coi100n and store it as ir200
  ir500=digitalRead(coi500n);  //read the state of coi100n and store it as ir500
  
 if(ir100 ==LOW){cnt100r+=100;  delay(100);}
 if(ir200 ==LOW){cnt200r+=200;  delay(100);}
 if(ir500 ==LOW){cnt500r+=500;  delay(100);}
 
 cnttotal =cnt100r+cnt200r+cnt500r;
 
EEPROM.write(5,cnttotal);
Serial.println(EEPROM.read(5)); 


lcd.setCursor(0,0);
lcd.print("TOTAL:");
lcd.setCursor(0,1);
lcd.print(cnttotal);
}