#include<Wire.h>
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050
int AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
float v_pitch, v_roll, v_yaw;

int sensorPin = 15; // select the input pin for the potentiometer
int sensorValue = 0;
float i = 0;
float fixtemp = 20.;
int fixInput = 560;
float fixedDegreeValue = 5.5;
String allData;


void setup() {
   Serial.begin(115200);
   Wire.begin(21, 22, 100000); // sda, scl, clock speed
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x6B);  // PWR_MGMT_1 register
   Wire.write(0);     // set to zero (wakes up the MPU−6050)
   Wire.endTransmission(true);
   Serial.println("Setup complete");
}

void loop() {
   Wire.beginTransmission(MPU_ADDR);
   Wire.write(0x3B);  // starting with register 0x3B (ACCEL_XOUT_H)
   Wire.endTransmission(true);
   Wire.beginTransmission(MPU_ADDR);
   Wire.requestFrom(MPU_ADDR, 14, true); // request a total of 14 registers
   AcX = Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
   AcY = Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   AcZ = Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   Tmp = Wire.read()<<8|Wire.read(); // 0x41 (TEMP_OUT_H) &  0x42 (TEMP_OUT_L)
   GyX = Wire.read()<<8|Wire.read(); // 0x3B (ACCEL_XOUT_H) & 0x3C (ACCEL_XOUT_L)
   v_pitch=(GyX/131);

   GyY = Wire.read()<<8|Wire.read(); // 0x3D (ACCEL_YOUT_H) & 0x3E (ACCEL_YOUT_L)
   v_roll = (GyY/131);
   GyZ = Wire.read()<<8|Wire.read(); // 0x3F (ACCEL_ZOUT_H) & 0x40 (ACCEL_ZOUT_L)
   v_yaw = (GyZ/131);

    sensorValue = analogRead(sensorPin);
    sensorValue = map(sensorValue, 0, 4095, 0, 560);

    
   if (sensorValue > fixInput ){
    i = sensorValue - fixInput;
    i = i /fixedDegreeValue; 
    fixtemp = fixtemp - i;
  }
   
  else if(sensorValue < fixInput) 
  {
    i =  fixInput - sensorValue;
    i = i /fixedDegreeValue; 
    fixtemp = fixtemp + i;
  }
   
   allData = String(fixtemp)+" "+String((AcX/16384.0))+" "+String((AcY/16384.0))+" "+String((AcZ/16384.0))+" "+String(v_pitch)+" "+String(v_roll)+" "+String(v_yaw);
   Serial.println(allData);
   fixtemp = 20;

}
