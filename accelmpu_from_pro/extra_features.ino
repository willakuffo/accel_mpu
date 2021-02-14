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
      }
    avgx = avgx/500;
    avgy = avgy/500;
    avgz = avgz/500;
    }

void travel_dist(int plane_distance,int avg){
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
