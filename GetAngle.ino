#include <Servo.h>
#include "Wire.h"
#include <MPU6050_light.h>


MPU6050 mpu(Wire);
unsigned long timer = 0;
Servo SERVOY;
Servo SERVOX;
Servo SERVOYY;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  SERVOY.attach(9);
  SERVOYY.attach(10);
  SERVOX.attach(5);
  SERVOY.write(45);
  SERVOYY.write(45);
  SERVOX.write(45);
  delay(1000);
  SERVOY.write(135);
  SERVOYY.write(135);
  SERVOX.write(135);
  delay(1000);
  SERVOY.write(90);
  SERVOYY.write(90);
  SERVOX.write(90);



  byte status = mpu.begin();
  Serial.print(F("MPU6050 status: "));
  Serial.println(status);
  while (status != 0) {}  

  Serial.println(F("Calculating offsets, do not move MPU6050"));
  delay(1000);
  // mpu.upsideDownMounting = true; 
  mpu.calcOffsets();  // gyro and accelero
  Serial.println("Done!\n");
}

void loop() {
  mpu.update();

  if ((millis() - timer) > 10) {  // print data every 10ms
    Serial.print("X : ");
    Serial.print(mpu.getAngleX());
    Serial.print("\tY : ");
    Serial.print(mpu.getAngleY());
    Serial.print("\tZ : ");
    Serial.println(mpu.getAngleZ());
    timer = millis();
  }

  if (mpu.getAngleY() < -1) {
    SERVOY.write(SERVOY.read() - 1);
    //SERVOYY.write(SERVOYY.read()-1);
  }
  if (mpu.getAngleY() < -1) {
    SERVOYY.write(SERVOYY.read() - 1);
  }
  //if(mpu.getAngleY() >= -1 && mpu.getAngleY() <= 1){
  //  SERVOY.write(90);
  //  }
  if (mpu.getAngleY() > 1) {
    SERVOY.write(SERVOY.read() + 1);
  }
  if (mpu.getAngleY() > 1) {
    SERVOYY.write(SERVOYY.read() + 1);
  }
  if (mpu.getAngleX() > 1) {
    SERVOX.write(SERVOX.read() + 1);
  }
  if (mpu.getAngleX() < -1) {
    SERVOX.write(SERVOX.read() - 1);
  }
}
