#include "ultrasonic_3d.h"
#include "mpu.h"
#include "extra_features.h"
#include "config.h"

#include <I2Cdev.h>
#include "MPU6050.h"
#include <Wire.h>



//These data types are specifically chosen to achieve the best results
float current_time = 0,previous_time = 0;
float elapsed_time = 0;

void setup() {
 Serial.begin(9600);
 mpu_setup();
 ultrasonic_3d_setup();
 Serial.println(mpu_ready? "MPU connection true":"mpu connection failure");
 
}

void loop() {
//clock
previous_time = current_time;
current_time = millis();
elapsed_time = (current_time- previous_time)/1000; //get loop time (sample time)
#ifdef PRINT_TIME
Serial.print("t:");
Serial.print((uint32_t)current_time);
Serial.print("  dt:");
Serial.print(elapsed_time);
#endif

#ifdef ULTRASONIC
SonarSensor(XTRIG, XECHO);
#ifdef PRINT_ULTRASONIC
Serial.print("\tX:");
Serial.print(distance);
#endif
#ifdef PRINT_ULTRASONIC
SonarSensor(YTRIG, YECHO);
Serial.print(" Y:");
Serial.print(distance);
#endif
#ifdef PRINT_ULTRASONIC
SonarSensor(ZTRIG, ZECHO);
Serial.print(" Z:");
Serial.print(distance);
#endif
#endif

#ifdef ACCEL_AS_MS
accel_as_ms();
#ifdef PRINT_ACCEL_AS_MS
Serial.print("\tacc:");
Serial.print(axp); Serial.print("  "); 
Serial.print(ayp); Serial.print("  ");
Serial.print(azp); Serial.print("  ");
#endif
#endif

#ifdef ACCEL_AS_RAW
accel_as_raw();
#ifdef PRINT_ACCEL_AS_RAW
Serial.print("\tAR: ");
Serial.print(ax); Serial.print(" "); 
Serial.print(ay); Serial.print(" ");
Serial.print(az); Serial.println(" ");
#endif
#endif

#ifdef ACCEL_ANGLE
angle_from_accel();
#ifdef PRINT_ACCEL_ANGLE
Serial.print("\tANG_acc:");
Serial.print(pitch);Serial.print(" ");
Serial.print(roll);Serial.print(" ");
Serial.print(yaw);
#endif
#endif

#ifdef GYRO_AS_RAW
gyro_as_raw();
#ifdef PRINT_GYRO_AS_RAW
Serial.print("\tGR:");
Serial.print(gx); Serial.print(" "); 
Serial.print(gy); Serial.print(" ");
Serial.print(gz); Serial.print(" ");
#endif
#endif

#ifdef GYRO_AS_DEG//gyro rates deg/s
gyro_as_deg();
#ifdef PRINT_GYRO_AS_DEG
Serial.print("\tgyro(deg/s): ");
Serial.print(gxp); Serial.print("  "); 
Serial.print(gyp); Serial.print("  ");
Serial.print(gzp); Serial.print("  ");
#endif
#endif

#ifdef GYRO_ANGLE
angle_from_gyro(elapsed_time);
#ifdef PRINT_GYRO_ANGLE
Serial.print("\t");
Serial.print(gyro_angle_pitch);Serial.print("\t");
Serial.print(gyro_angle_roll);Serial.print("\t");
Serial.print(gyro_angle_yaw);
#endif
#endif

#ifdef COMPLIMETARY_FILTER
complimentary_angles();
#ifdef PRINT_COMP;
Serial.print("\tCOMP:");
Serial.print(COM_PITCH);Serial.print("  ");
Serial.print(COM_ROLL);Serial.print("  ");
Serial.println(COM_YAW);
#endif
#endif

#ifdef TEMP
temperature();
#ifdef PRINT_TEMP
Serial.print("\ttmp:");
Serial.println(tmp);
#endif
#endif
}