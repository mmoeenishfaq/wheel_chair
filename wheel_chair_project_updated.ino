#include <NewPing.h>
#include "Wire.h"
#define SONAR_NUM 6     // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define IN1_PIN 10
#define IN2_PIN 11
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int16_t accelerometer_x, accelerometer_y, accelerometer_z,accelerometer_x1,accelerometer_y1; // variables for accelerometer raw data
//int16_t gyro_x, gyro_y, gyro_z; // variables for gyro raw data
//int16_t temperature; // variables for temperature data
char tmp_str[7]; // temporary variable used in convert function
char* convert_int16_to_str(int16_t i) { // converts int16 to string. Moreover, resulting strings will have the same length in the debug monitor.
  sprintf(tmp_str, "%6d", i);
  return tmp_str;
}
String x,y,x1,y1;

  NewPing sonar[SONAR_NUM] = {   // Sensor object array.
   NewPing(12, 13, MAX_DISTANCE),  // (trigger echo max)//fl
   NewPing(8, 9, MAX_DISTANCE),    //f
   NewPing(23, 22, MAX_DISTANCE),   //fr
   NewPing(11, 10, MAX_DISTANCE),  //(trigger echo max)//bl
   NewPing(52, 53, MAX_DISTANCE),    //b
   NewPing(50, 51, MAX_DISTANCE),//br
};

//int x; // x axis variable
//int y; // y axis variable
//int z; // z axis variable
//int x1; // x axis variable
//int y1; // y axis variable
//int z1; // z axis variable
int difX;
int difY;

//int sleepStatus = 0;
int relay=48;
const int ledf  = 24; //left
const int ledb  = 4; //right
const int ledfl  = 7; //left
const int ledfr  = 25; //right
const int ledbr  = 41; //left
const int ledbl  = 3; //right

const int vibrator  = 2;
//const int led  = 2;
int distancefL=0, distancefR=0, distanceF=0;
int distancebL=0, distancebR=0, distanceB=0;
//const int xpin = 8;                  // x-axis of the accelerometer
//const int ypin = 9;                  // y-axis
//const int zpin = 11;                  // z-axis (only on 3-axis models)
int buzzer=8;
int buzzer2=9;
int d=150;
int count=0;
float g;
float yg;


void setup(){
    pinMode(relay, OUTPUT);
  digitalWrite(relay, HIGH);
    pinMode(ledfr, OUTPUT);
    pinMode(ledfl, OUTPUT);
    pinMode(ledf, OUTPUT);
    pinMode(ledb, OUTPUT);
    pinMode(ledbr, OUTPUT);
    pinMode(ledbl, OUTPUT);
    pinMode(vibrator, OUTPUT);
    //digitalWrite(vibrator,LOW);
     Serial.begin(9600);
//       attachInterrupt(digitalPinToInterrupt(2),led ,RISING);
      // pinMode(4, OUTPUT);
}



void calcDistfL()
{
  delay(20);
  distancefL=(sonar[0].ping_cm()/2.54);

}
void calcDistF()
{
  delay(20);
  distanceF=(sonar[1].ping_cm()/2.54);
}
void calcDistfR()
{
  delay(20);
  distancefR=(sonar[2].ping_cm()/2.54);
}
void calcDistbL()
{
  delay(20);
  distancebL=(sonar[3].ping_cm()/2.54);

}
void calcDistB()
{
  delay(20);
  distanceB=(sonar[4].ping_cm()/2.54);
}
void calcDistbR()
{
  delay(20);
  distancebR=(sonar[5].ping_cm()/2.54);
}



void frhigh(){
   analogWrite(buzzer,d);
   delay(1000);
   analogWrite(buzzer,LOW);
   delay(1000);
}

void frmedium(){
   analogWrite(buzzer,d);
   delay(500);
   analogWrite(buzzer,LOW);
   delay(500);
}
void frlow(){
    analogWrite(buzzer,d);
   delay(250);
   analogWrite(buzzer,LOW);
   delay(250);
}


void flhigh(){
    analogWrite(buzzer2,d);
   delay(1000);
   analogWrite(buzzer2,LOW);
   delay(1000);
}
void flmedium(){
    analogWrite(buzzer2,d);
   delay(500);
   analogWrite(buzzer2,LOW);
   delay(500);
}
void fllow(){
    analogWrite(buzzer2,d);
   delay(250);
   analogWrite(buzzer2,LOW);
   delay(250);
}




void brhigh(){
    digitalWrite(ledbr,HIGH);
  delay(50);
   digitalWrite(ledbr,LOW);
  delay(50);
}
void brmedium(){
    digitalWrite(ledbr,HIGH);
  delay(100);
   digitalWrite(ledbr,LOW);
  delay(100);
}
void brlow(){
    digitalWrite(ledbr,HIGH);
  delay(200);
   digitalWrite(ledbr,LOW);
  delay(200);
}


void blhigh(){
    digitalWrite(ledbl,HIGH);
  delay(50);
   digitalWrite(ledbl,LOW);
  delay(50);
}
void blmedium(){
    digitalWrite(ledbl,HIGH);
  delay(100);
   digitalWrite(ledbl,LOW);
  delay(100);
}
void bllow(){
    digitalWrite(ledbl,HIGH);
  delay(200);
   digitalWrite(ledbl,LOW);
  delay(200);
}



void bhigh(){
    digitalWrite(ledb,HIGH);
  delay(50);
   digitalWrite(ledb,LOW);
  delay(50);
}
void bmedium(){
    digitalWrite(ledb,HIGH);
  delay(100);
   digitalWrite(ledb,LOW);
  delay(100);
}
void blow(){
    digitalWrite(ledb,HIGH);
  delay(200);
   digitalWrite(ledb,LOW);
  delay(200);
}



void fhigh(){
    digitalWrite(ledf,HIGH);
  delay(50);
   digitalWrite(ledf,LOW);
  delay(50);
}
void fmedium(){
    digitalWrite(ledf,HIGH);
  delay(100);
   digitalWrite(ledf,LOW);
  delay(100);
}

void flow(){
    digitalWrite(ledf,HIGH);
  delay(200);
   digitalWrite(ledf,LOW);
  delay(200);
}



void alert()
{
      if(distanceF<=4&&distanceF!=0)
    {

      digitalWrite(vibrator,HIGH);
      fhigh();
     // rhigh();
      
    } 
    else if(distanceF>=4&&distanceF<=10)
    {
      digitalWrite(vibrator,HIGH);
      fmedium();
      //lmedium();
    } 
      else if(distanceF>=10&&distanceF<=16)
    {
      digitalWrite(vibrator,HIGH);
      flow();
      //llow();
    } 
    
       if(distancefL<=4&&distancefL!=0)
    {
      digitalWrite(vibrator,HIGH);
      flhigh();
    } 
    else if(distancefL>=4&&distancefL<=10)
    {
      digitalWrite(vibrator,HIGH);
      flmedium();
    } 
      else if(distancefL>=10&&distancefL<=16)
    {
      digitalWrite(vibrator,HIGH);
      fllow();
    } 
        if(distancefR<=4&&distancefR!=0)
    {
      digitalWrite(vibrator,HIGH);
      frhigh();
    } 
    else if(distancefR>=4&&distancefR<=10)
    {
      digitalWrite(vibrator,HIGH);
      frmedium();
    } 
      else if(distancefR>=10&&distancefR<=16)
    {
      digitalWrite(vibrator,HIGH);
      frlow();
    }  
     if(distanceB<=4&&distanceB!=0)
    {
      digitalWrite(vibrator,HIGH);
      bhigh();
     // rhigh();
    } 
    else if(distanceB>=4&&distanceB<=10)
    {
      digitalWrite(vibrator,HIGH);
      bmedium();
      //lmedium();
    } 
      else if(distanceB>=10&&distanceB<=16)
    {
      digitalWrite(vibrator,HIGH);
      blow();
      //llow();
    } 
       if(distancebL<=4&&distancebL!=0)
    {
      digitalWrite(vibrator,HIGH);
      blhigh();
    } 
    else if(distancebL>=4&&distancebL<=10)
    {
      digitalWrite(vibrator,HIGH);
      blmedium();
     
    } 
      else if(distancebL>=10&&distancebL<=16)
    {
      digitalWrite(vibrator,HIGH);
      bllow();
    } 
        if(distancebR<=4&&distancebR!=0)
    {
      digitalWrite(vibrator,HIGH);
      brhigh();
    } 
    else if(distancebR>=4&&distancebR<=10)
    {
      digitalWrite(vibrator,HIGH);
      brmedium();
    } 
      else if(distancebR>=10&&distancebR<=16)
    {
      digitalWrite(vibrator,HIGH);
      brlow();
    }
    else
    digitalWrite(vibrator,LOW);
  }

void c_main()
{
  calcDistbL();
  calcDistbR();
  calcDistF();
  calcDistfL();
  calcDistfR();
  calcDistB();
  
  Serial.print("fL : ");
  Serial.print(distancefL);
  Serial.print("   fR:");
  Serial.print(distancefR);
  Serial.print("   F:");
  Serial.println(distanceF);
   Serial.print("bL : ");
  Serial.print(distancebL);
  Serial.print("   bR:");
  Serial.print(distancebR);
  Serial.print("   B:");
  Serial.println(distanceB);
  Serial.print("\n");
  alert();
}

void check()
{ // delay(50);
//  x = analogRead(8); // read A5 input pin
//  y = analogRead(9); // read A4 input pin
//    delay(50);
//  x1 = analogRead(8); // read A5 input pin
//  y1 = analogRead(9); // read A4 input pin
//  difX=x-x1;
//  difY=y-y1;
//  
//  
//  Serial.print("X = "); // print x adc value
//  Serial.println(difX);
//  //Serial.print('\n');
//  Serial.print("Y = "); // print y adc value
//  Serial.println(difY);
//  
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
  // "Wire.read()<<8 | Wire.read();" means two registers are read and stored in the same variable
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  delay(1000);
    Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers

  accelerometer_x1 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y1 = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  // print out data
    x=convert_int16_to_str(accelerometer_x);
  y=convert_int16_to_str(accelerometer_y);
  x1=convert_int16_to_str(accelerometer_x1);
  y1=convert_int16_to_str(accelerometer_y1);
//  Serial.print("aX = "); Serial.print(x);
//  Serial.print(" | aY = "); Serial.print(y);
//    Serial.print("aX1 = "); Serial.print(x1);
//  Serial.print(" | aY1 = "); Serial.print(y1);
  
  difX=x.toInt()- x1.toInt();
  difY=y.toInt()-y1.toInt();
  
  
  Serial.print("X = "); // print x adc value
  Serial.println(difX);
  //Serial.print('\n');
  Serial.print("Y = "); // print y adc value
  Serial.println(difY);
  Serial.println();
  
  // delay
  delay(1000);

}

void sleeps()
{
  c_main();
  check();

while(difX>=-10&&difX<=10&&difY>=-10&&difY<=10)
{

   c_main();
  check();

  Serial.print("count: ");
  Serial.print(count);
  count++;
   
  if(count>=100)
  {
    Serial.print("OFF");
  digitalWrite(relay, LOW);
    Serial.print("\n");
    }
   
    Serial.print("\n");
 }
 digitalWrite(relay, HIGH);
 count=0;
}


void loop()
{   
 //c_main();
   sleeps(); 
   byte input1_state = digitalRead(IN1_PIN);
  byte input2_state = digitalRead(IN2_PIN);
  if(input1_state==HIGH)
  {
   analogWrite(9,d);
   delay(500);
   analogWrite(9,LOW);
   d=d+50;
   if(d>=255)
   {
d=255;
    
   }
  }
  if(input2_state==HIGH)
  {
   analogWrite(9,d);
   delay(500);
   analogWrite(9,LOW);
   d=d-50;
 if(d<=50)
 {
   d=0;
  }


  
  }
 }
