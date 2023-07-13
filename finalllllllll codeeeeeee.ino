
#include <Servo.h> //includes the servo library
#include <Wire.h> 
#include <LiquidCrystal_I2C.h> //includes LiquidCrystal_I2C library
LiquidCrystal_I2C lcd(0x27, 16, 2);

Servo myservo;

#define ir_enter 2
#define ir_back  4

int flag1=0, flag2=0; 
int slot = 0;  
 
void setup()
{
Serial.begin(9600);

pinMode(ir_enter, INPUT);
pinMode(ir_back, INPUT);
  
myservo.attach(9); // Servo motor pin connected to D9
myservo.write(0); // sets the servo at 0 degree position
   
lcd.begin();  
lcd.setCursor (0,0);
lcd.print("      Car     ");
lcd.setCursor (0,1);
lcd.print(" Parking System ");
delay (2000);
lcd.clear();   
 

}
 
void loop()
{

lcd.setCursor (0,0);
lcd.print("   Have Slot: "); 
lcd.print(slot);
lcd.setCursor (0,1);
lcd.print("                     ");
lcd.print("    ");  
 
    
/* Servo Motor Control*/

  if(digitalRead (ir_enter) == 0 && flag1==0) // read degital data from ir_enter
   {
    if(slot>0)
     {
      flag1=1;
      if(flag2==0)
       {
        myservo.write(150); 
        Serial.println("Open gate ");
        slot = slot-1;
        }
     }
    else
     {
      lcd.setCursor (0,0);
      lcd.print("      Sorry     ");
      lcd.setCursor (0,1);
      lcd.print(" Parking Full... ");  
      delay(2500);
      }   
   }
 
  if(digitalRead (ir_back) == 0 && flag2==0) // read degital data from ir_back
   {
    flag2=1;
    if(flag1==0)
     {
      myservo.write(150); // sets the servo at 180 degree position
       Serial.println("close gate ");
      slot = slot+1;
      }
   }
 
    if(flag1==1 && flag2==1)
    {
      delay (1000);
      myservo.write(0); // sets the servo at 90 degree position
      flag1=0, flag2=0;
      Serial.println("flag reset to zero");
    }
    delay(2);
}
 
