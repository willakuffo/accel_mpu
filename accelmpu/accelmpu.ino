#include "ultrasonic_3d.h"
#include "mpu.h"
#include "extra_features.h"

#include <I2Cdev.h>
#include "MPU6050.h"
#include <Wire.h>


/*uncomment to read accelerometer (x,y,z) as raw, with sensitivity -> 2g*/
//#define ACCEL_AS_RAW
/*uncomment to read accelerometer (x,y,z) as m/s with sensitivity -> 2g */
#define ACCEL_AS_MS
/*uncomment to read angle in deg -> This angle is in degrees and is dependent on ACCEL_AS_MS, therefore uncomment ACCEL_AS_MS before 
//this angle can be read. This angle is calculated from the accelerometer only using euler's formula*/
#define ACCEL_ANGLE
/*uncomment to read ultrasonic sensor 3d positions (x,y,z)*/
//#define ULTRASONIC
/*uncomment to read gyroscope (roll,pitch,yaw) as raw, with sensitivity -> 250deg/s */
//#define GYRO_AS_RAW
/*uncomment to read gyro angle rates (roll,pitch,yaw) in deg/s.*/
#define GYRO_AS_DEG 
/* uncomment to read gyro angles in degrees. These angles are integrated from GYRO_AS_DEG angle rate values, 
  therefore dependent on GYRO_AS_DEG. Use with GYRO_AS_DEG, therefore uncomment GYRO_AS_DEG*/
#define GYRO_ANGLE //gyro angles in degrees dependent on GYRO_AS_DEG
/*This is a complimentary filter using 96% of GYRO angles and 4% of ACCEL angles. GYRO is not reliable in long term but in short term.
ACCEL is reliable in long term but not in short term. Removes noise and smoothens out the angle signal. Best of both worlds :)*/
#define COMPLIMETARY_FILTER 

//THese data types are specifically chosen to achieve the best results
float current_time = 0,previous_time = 0;
float elapsed_time = 0;

void setup() {
// put your setup code here, to run once:
 Serial.begin(38400);
 mpu_setup();
 ultrasonic_3d_setup();
}

void loop() {
  // put your main code here, to run repeatedly:
//clock
previous_time = current_time;
current_time = millis();
elapsed_time = (current_time- previous_time)/1000; //get loop time (sample time)

//Serial.print("t:");
//Serial.print((uint32_t)current_time);
//Serial.print("  dt:");
//Serial.print(elapsed_time);
#ifdef ULTRASONIC
SonarSensor(XTRIG, XECHO);
/*Serial.print("   X:");
Serial.print(distance);

SonarSensor(YTRIG, YECHO);
Serial.print(" Y:");
Serial.print(distance);

SonarSensor(ZTRIG, ZECHO);
Serial.print(" Z:");
Serial.print(distance);*/
#endif

#ifdef ACCEL_AS_MS
accel_as_ms();/*
Serial.print("   acc:");
Serial.print(axp); Serial.print("  "); 
Serial.print(ayp); Serial.print("  ");
Serial.print(azp); Serial.print("  ");*/
#endif

#ifdef ACCEL_AS_RAW
accel_as_raw();
Serial.print("  AR:");
Serial.print(ax); Serial.print(" "); 
Serial.print(ay); Serial.print(" ");
Serial.print(az); Serial.println(" ");
#endif

#ifdef ACCEL_ANGLE
angle_from_accel();
Serial.print("   ANG_acc:");
Serial.print(pitch);Serial.print(" ");
Serial.print(roll);Serial.print(" ");
Serial.print(yaw);
#endif

#ifdef GYRO_AS_RAW
gyro_as_raw();
Serial.print("  GR:");
Serial.print(gx); Serial.print(" "); 
Serial.print(gy); Serial.print(" ");
Serial.print(gz); Serial.print(" ");
#endif

#ifdef GYRO_AS_DEG
//gyro rates deg/s
gyro_as_deg();/*
Serial.print("   gyro(deg/s): ");
Serial.print(gxp); Serial.print("  "); 
Serial.print(gyp); Serial.print("  ");
Serial.print(gzp); Serial.print("  ");*/
#endif

#ifdef GYRO_ANGLE
angle_from_gyro(elapsed_time);

Serial.print(elapsed_time);Serial.print("\t");
Serial.print(gyro_angle_pitch);Serial.print("\t");
Serial.print(gyro_angle_roll);Serial.print("\t");
Serial.print(gyro_angle_yaw);
#endif

#ifdef COMPLIMETARY_FILTER
complimentary_angles();
Serial.print("   COMP:");
Serial.print(COM_PITCH);Serial.print("  ");
Serial.print(COM_ROLL);Serial.print("  ");
Serial.println(COM_YAW);
#endif
}
