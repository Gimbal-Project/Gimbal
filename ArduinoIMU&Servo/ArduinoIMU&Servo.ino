#include "MPU6050.h" //Mpu6050 kütüphanesi
#include "Wire.h"
#include <Servo.h>

Servo servo1;
Servo servo2;
MPU6050 accelgyro; // Mpu6050 sensör tanımlama
int16_t ax, ay, az; //ivme tanımlama
int16_t gx, gy, gz; //gyro tanımlama

int16_t x=90;
int16_t y=90;
  
void setup() {
  servo1.attach(9);
  servo2.attach(10);
  Wire.begin();
  Serial.begin(9600);
  Serial.println("I2C cihazlar başlatılıyor...");
  accelgyro.initialize();
  Serial.println("Test cihazı bağlantıları...");
  Serial.println(accelgyro.testConnection() ? "MPU6050 bağlantı başarılı" : "MPU6050 bağlantısı başarısız");
}
  
void loop() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz); // ivme ve gyro değerlerini okuma
  ax=map(ax,-16384,16384,0,180);
  //Serial.println(ax);
  ay=map(ay,-16384,16384,0,180);
  //Serial.println(ay);

  if(ax>90){
    x=x-1;
    servo1.write(x);
  }
  else if(ax<90){
    x=x+1;
    servo1.write(x);
  }
  if(x>=180){
    x=180;
  }
  else if(x<=0){
    x=0;
  }
  //servo1.write(90);
  servo2.write(90);// y ekseni sabit durması için
  Serial.print("ax=");Serial.println(ax);
  Serial.print("ay=");Serial.println(ay);
  Serial.print("servo1=");Serial.println(x);


  /*Serial.print(ay); Serial.print("\t");
  Serial.print(az); Serial.print("\t");
  Serial.print(gx); Serial.print("\t");
  Serial.print(gy); Serial.print("\t");
  Serial.println(gz);*/
  delay(100);
}