#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F, 16, 2);
float calibration_value = 21.34 - 8.4;//0.928;
int phval = 0;
const int Pump1 = 4;
const int Pump2 = 5;
unsigned long int avgval; 
int buffer_arr[10],temp;
void setup() 
{
 Serial.begin(9600);
  lcd.init(); 
  lcd.begin(16, 2);
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("pH Regulator");
  lcd.setCursor(0, 1);
  lcd.print("System");
  delay(2000);
  lcd.clear();
  
  pinMode(Pump1, OUTPUT);
  pinMode(Pump2, OUTPUT);
}
void loop() {
  
 for(int i=0;i<10;i++) 
 { 
 buffer_arr[i]=analogRead(A0);
 delay(30);
 }
 for(int i=0;i<9;i++)
 {
 for(int j=i+1;j<10;j++)
 {
 if(buffer_arr[i]>buffer_arr[j])
 {
 temp=buffer_arr[i];
 buffer_arr[i]=buffer_arr[j];
 buffer_arr[j]=temp;
 }
 }
 }
 
 avgval=0;
 for(int i=2;i<8;i++)
 avgval+=buffer_arr[i];
 float volt=(float)avgval*5.0/1024/6;
 float ph_act = -5.70 * volt + calibration_value;
 lcd.setCursor(0, 0);
 lcd.print("pH Val:");
 lcd.setCursor(8, 0);
 lcd.print(ph_act);
 delay(1000);

 if (ph_act <= 6.5){
  WorkPump1();
 }
 else if(ph_act >=9){
  WorkPump2();
 }
 else{
  WorkPump3();
 }
}

void WorkPump1(){
  digitalWrite(Pump1, HIGH);
  digitalWrite(Pump2, LOW);
}

void WorkPump2(){
  digitalWrite(Pump1, LOW);
  digitalWrite(Pump2, HIGH);
}

void WorkPump3(){
  digitalWrite(Pump1, LOW);
  digitalWrite(Pump2, LOW);
}
