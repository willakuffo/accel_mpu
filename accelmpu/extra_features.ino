#include "mpu.h"
#include "ultrasonic_3d.h"


void angle_from_accel(){
  //euler angles
  pitch = atan2(ayp, sqrt(pow(axp, 2) + pow(azp, 2))) * RAD_TO_DEG; 
  roll = atan2(axp, sqrt(pow(ayp, 2) + pow(azp, 2))) * RAD_TO_DEG; 
  
  }

 void angle_from_gyro(float elapsed_time){
  //integrate gyro rates to get gyro angles
  gyro_angle_pitch += (gxp-GYRO_OFFSET_X)*(elapsed_time);
  gyro_angle_roll += (gyp-GYRO_OFFSET_Y)*(elapsed_time);
  gyro_angle_yaw += (gzp-GYRO_OFFSET_Z)*(elapsed_time);

  
  }

 void complimentary_angles(){
  //complimentary angles, 96% gyro, 4% accel
  COM_PITCH = 0.96* gyro_angle_pitch + 0.04*pitch;
  COM_ROLL = 0.96* gyro_angle_roll + 0.04*roll;
  COM_YAW = gyro_angle_yaw;
  }
  
