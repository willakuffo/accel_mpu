#include "mpu.h"
#include "ultrasonic_3d.h"


void angle_from_accel(){
  //euler angles
  //pitch is along y-axis of IMU, roll is along x-axis (orientation on uav)
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
  
  //recallibrate gyro if drift is more than 10 degrees
  //if(abs(COM_PITCH-pitch)>10){recallibrate_gyro_x();Serial.println("rp");}
  //if(abs(COM_ROLL-roll)>10){recallibrate_gyro_y();Serial.println("rr");}
  
  }


void inital_plane_distance(){
  //get average distance from planes
  //distance travelled from planes
  //get average distance from x,y, z planes
  //cal tavel distance from plane = avg_dist - travel
   
    for(int i = 0;i<500;i++){
        SonarSensor(XTRIG,XECHO); avgx += distance;
        SonarSensor(YTRIG,YECHO); avgy += distance;
        SonarSensor(ZTRIG,ZECHO); avgz += distance; 
       // Serial.print(avgx);Serial.print(" ");Serial.print(avgy);Serial.print(" ");Serial.println(avgz); 
      }
    avgx = avgx/500;
    avgy = avgy/500;
    avgz = avgz/500;
    }

void travel_dist_sonar(int plane_distance,int avg){
   travel = plane_distance - avg;

}
/* void recallibrate_gyro_x(){
//recallibrate when accelerometer is in long term, less rates in axis
if ((gxp<gyro_rate_xmax) and (gxp>gyro_rate_xmin)){gyro_angle_pitch = pitch;Serial.print("rp**");} // recallibrate pitch
}
void recallibrate_gyro_y(){
  if((gyp<gyro_rate_ymax)and(gyp>gyro_rate_ymin)){gyro_angle_roll = roll;Serial.print("r**");}//recallibrate roll

}*/

void unangled_position(int16_t pos, uint8_t whichangle){
  switch(whichangle){
  case 1://use complimentary filter angles
    unangled_pos = pos*cos(COM_PITCH/(RAD_TO_DEG))*cos(COM_ROLL/(RAD_TO_DEG))*cos(COM_YAW/(RAD_TO_DEG));
    break;
  case 2: //use accel angles
    unangled_pos = pos*cos(pitch/(RAD_TO_DEG))*cos(roll/(RAD_TO_DEG))*cos(gyro_angle_yaw/(RAD_TO_DEG));
    break;
  }
  
  }


void IMU_vel_dist(float elapsed_time){
  //currently using processed nonlinear accelrations
  //calc velociety (single time integral) and position (double time integral) from IMU
  //initial velocity IMU velocites / previous velocities at time t-1 (x,y,z)
  static float previous_vel_x = 0;
  static float previous_vel_y = 0;
  static float previous_vel_z = 0;

  //initial IMU positions with respect to starting point ->(avgx,avgy,avgz)
  static float previous_dist_x = 0;
  static float previous_dist_y = 0;
  static float previous_dist_z = 0;

  //assign previous IMU dist
  previous_dist_x = IMU_dist_x;
  previous_dist_y = IMU_dist_y;
  previous_dist_z = IMU_dist_z;
  
 //instantaneous velocity and change in distance within sampled time
  //calculate current velocity at time t -> v = u+at
  IMU_vel_x = previous_vel_x + axp*elapsed_time;
  IMU_vel_y = previous_vel_y + ayp*elapsed_time;
  IMU_vel_z = previous_vel_z + (azp+GRAVITY)*elapsed_time; //normalize z-axis gravity. IMU is inverted so default g = -ve, therefore add to norm

  //calculate current IMU position at time t with respect to starting point -> (avgx,avgy,avgz) -> s = ut+0.5at^2
  IMU_dist_x += previous_vel_x*elapsed_time + 0.5*axp*pow(elapsed_time,2);
  IMU_dist_y += previous_vel_y*elapsed_time + 0.5*ayp*pow(elapsed_time,2);
  IMU_dist_z += previous_vel_z*elapsed_time + 0.5*(azp+GRAVITY)*pow(elapsed_time,2);

  //3-axis  magnitude chnage in velocity
  chng_velx = IMU_vel_x - previous_vel_x;
  chng_vely = IMU_vel_y - previous_vel_y;
  chng_velz = IMU_vel_z - previous_vel_z;

  //calc 3-axis magnitude IMU change in distance
  chng_distx = IMU_dist_x - previous_dist_x;
  chng_disty = IMU_dist_y - previous_dist_y;
  chng_distz = IMU_dist_z - previous_dist_z;

  //update previous velocities
  previous_vel_x = IMU_vel_x;
  previous_vel_y = IMU_vel_y;
  previous_vel_z = IMU_vel_z;

  
}

/*
void linear_acc(){
  //use complimentary filter angles to compute linear acc -> 4% accel angle, 96% gyro angle
  //accel angle itself is affected by the  linear component of acc since its comes from the accelerometers
  //therefore is accelerometer accelerates, angle is affected 
  // but the comp filter will only be affected by the magnitude of fraction component of thehe accel's contribution
  //to the angle


  //compute true acc along the reference frame's axes (x,y,z) when quadcoptor pitched or is rolled
  l_acx = axp*cos(COM_PITCH/RAD_TO_DEG);
  l_acy = ayp*cos(COM_ROLL/RAD_TO_DEG);
  l_acz = (azp+GRAVITY)*cos(COM_PITCH/RAD_TO_DEG)*cos(COM_ROLL/RAD_TO_DEG); 


}*/
