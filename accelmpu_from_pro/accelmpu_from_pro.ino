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
 Serial.println(mpu_ready ?"MPU connection true":"mpu connection failure");
 if (mpu_ready){
  Serial.println("callibrating gyros...");
  gyro_offset_callibrate(10000);

  Serial.print("xmax->");Serial.println(gyro_rate_xmax);
  Serial.print("xmin->");Serial.println(gyro_rate_xmin);
  Serial.print("ymax->");Serial.print(gyro_rate_ymax);Serial.print("ymin->");Serial.println(gyro_rate_ymin);
  Serial.print("GYRO_OFFSET_X:");Serial.print(GYRO_OFFSET_X);
  Serial.print("GYRO_OFFSET_Y:");Serial.print(GYRO_OFFSET_Y);
  Serial.print("GYRO_OFFSET_Z:");Serial.println(GYRO_OFFSET_Z);
  Serial.println("_GYRO callibration complete_");
  }

  #ifdef TRAVEL
  Serial.println("Getting Starting Point (avgx,avgy,avgz)");
  inital_plane_distance();
  Serial.print("Starting point:(avgx,avgy,avgz)");Serial.print("(");Serial.print(avgx);Serial.print(", ");
  Serial.print(avgy);Serial.print(", ");Serial.print(avgz);Serial.println(")");
  #endif 
  delay(1000);
 
 
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
  #ifdef TRAVEL
    travel_dist_sonar(distance, avgx);
    #ifdef PRINT_TRAVEL
    Serial.print("\t[x]:");Serial.print(travel);    
    #endif
  #endif
  #ifdef PRINT_ULTRASONIC
    Serial.print("\tX:");
    Serial.print(distance);
  #endif


  SonarSensor(YTRIG, YECHO);
  #ifdef TRAVEL
    travel_dist_sonar(distance, avgy);
    #ifdef PRINT_TRAVEL
    Serial.print(" [y]:");Serial.print(travel);    
    #endif
  #endif

  #ifdef PRINT_ULTRASONIC  
    Serial.print("\tY:");
    Serial.print(distance);
  #endif


  SonarSensor(ZTRIG, ZECHO);
  #ifdef TRAVEL
    travel_dist_sonar(distance, avgz);
    #ifdef PRINT_TRAVEL
    Serial.print(" [z]:");Serial.print(travel);    
    #endif
  #endif
  
  #ifdef PRINT_ULTRASONIC
    Serial.print("\tZ:");
    Serial.print(distance);
  #endif
#endif


#ifdef UNANGLED_POS
SonarSensor(XTRIG, XECHO);
#ifdef PRINT_UNANGLED_POS
unangled_position(distance,2);
Serial.print("\tuX:");Serial.print(unangled_pos);
#endif
#ifdef PRINT_UNANGLED_POS
SonarSensor(YTRIG, YECHO);
unangled_position(distance,2);
Serial.print("\tuY:");Serial.print(unangled_pos);
#endif
#ifdef PRINT_UNANGLED_POS
SonarSensor(ZTRIG, ZECHO);
unangled_position(distance,2);
Serial.print("\tuZ:");Serial.print(unangled_pos);
#endif
#endif

#ifdef ACCEL_AS_MS
accel_as_ms();
#ifdef PRINT_ACCEL_AS_MS
Serial.print("\tacc[m/s]:");
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
Serial.print("\tANGacc:");
Serial.print(pitch);Serial.print(" ");
Serial.print(roll);Serial.print(" ");
//Serial.print(yaw);
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
Serial.print("\tANGgyro");
Serial.print(gyro_angle_pitch);Serial.print(" ");
Serial.print(gyro_angle_roll);Serial.print(" ");
Serial.print(gyro_angle_yaw);
#endif
#endif

#ifdef COMPLIMETARY_FILTER
complimentary_angles();
#ifdef PRINT_COMP
Serial.print("\tCOMP:");
Serial.print(COM_PITCH);Serial.print("  ");
Serial.print(COM_ROLL);Serial.print("  ");
Serial.print(COM_YAW);
#endif
#endif

#ifdef TEMP
temperature();
#ifdef PRINT_TEMP
Serial.print("\ttmp:");
Serial.print(tmp);
#endif
#endif

#ifdef IMU_DIST_VEL
IMU_vel_dist(elapsed_time);
#ifdef PRINT_IMU_DIST_VEL
Serial.print("\tvel: ");Serial.print(IMU_vel_x);Serial.print(" ");Serial.print(IMU_vel_y);Serial.print(" ");Serial.print(IMU_vel_z);
Serial.print("\tdist: ");Serial.print(IMU_dist_x);Serial.print(" ");Serial.print(IMU_dist_y);Serial.print(" ");Serial.println(IMU_dist_z);
#endif
#endif
/*
#ifdef LINEAR_ACC
linear_acc();
#ifdef PRINT_LINEAR_ACC
Serial.print("ln: ");Serial.print(l_acx);Serial.print(" ");Serial.print(l_acy);Serial.print(" ");Serial.println(l_acz);
#endif
#endif
*/
}
