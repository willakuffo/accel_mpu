 #include <I2Cdev.h>
#include "MPU6050.h"
#include <Wire.h>
#include "mpu.h"

MPU6050 mpu;


void mpu_setup(){

 mpu.initialize();
 mpu.setSleepEnabled(false);
 mpu.setFullScaleAccelRange(0); // 0=> +-250deg/s ; 1=> +-500deg/s ; 2=> +-1000deg/s ; 3=> 2000deg/s
 mpu.setFullScaleGyroRange(0);  // 0=> +-2g ; 1=> +-4g ; 2=> +-8g ; 3=> +-16g
 mpu.setDLPFMode(6);
 mpu_ready = mpu.testConnection();
}

void accel_as_raw(){
        ax = (int16_t)mpu.getAccelerationX();
        ay = (int16_t)mpu.getAccelerationY();
        az = (int16_t)mpu.getAccelerationZ();
}

void accel_as_ms(){
        static float previous_axp = 0;
        static float previous_ayp = 0;
        static float previous_azp = 0; 

        previous_axp = axp; previous_ayp = ayp; previous_azp = azp;//assign previous 3-axis acc

        //get current 3-axis acc
        axp = mpu.getAccelerationX();
        ayp = mpu.getAccelerationY();
        azp = mpu.getAccelerationZ();//-ve because IMU is upside down (make z +ve)
        
        axp = (axp/ACCEL_SENSITIVITY)*GRAVITY;
        ayp = (ayp/ACCEL_SENSITIVITY)*GRAVITY;
        azp = (azp/ACCEL_SENSITIVITY)*GRAVITY;

        //calc this 3-axis accel chng after accel mean filter callibration
        if(calc_accel_chng){//apply mean filter to smoothen and reduce drift
          axp = axp-ACCEL_MEAN_X; 
          ayp = ayp-ACCEL_MEAN_Y;
          azp = azp-(ACCEL_MEAN_Z+GRAVITY);//+ because IMU is upside downnn

        chng_axp = axp - previous_axp; chng_ayp = ayp - previous_ayp; chng_azp = azp - previous_azp;}
          
  }

void gyro_as_raw(){
        gx = (int16_t)mpu.getRotationX();
        gy = (int16_t)mpu.getRotationY();
        gz = (int16_t)mpu.getRotationZ();
}

void gyro_as_deg(){
  
        gxp = mpu.getRotationX();
        gyp = mpu.getRotationY();
        gzp = mpu.getRotationZ();
        
        gxp = (gxp/GYRO_SENSITIVITY);
        gyp = (gyp/GYRO_SENSITIVITY);
        gzp = (gzp/GYRO_SENSITIVITY);
          
  }


void temperature(){
  tmp = mpu.getTemperature();
  tmp = tmp/340+36.53;
  
  }


 void gyro_offset_callibrate(int sample){
    float sx = 0;
    float sy = 0; 
    float sz = 0;
    //max and minimum still rates
   
    
  for(int i = 0;i<sample;i++){//sum sample rates
    gyro_as_deg();
    sx += gxp;
    sy += gyp ;
    sz += gzp;

    gyro_rate_ymax = max(gyp,gyro_rate_ymax);gyro_rate_ymin = min(gyp,gyro_rate_ymin);
    gyro_rate_xmax = max(gxp,gyro_rate_xmax);gyro_rate_xmin = min(gxp,gyro_rate_xmin);
    } //find mean offset rates
    GYRO_OFFSET_X = sx/sample;
    GYRO_OFFSET_Y = sy/sample;
    GYRO_OFFSET_Z = sz/sample;
    //calc mean offset rate
   
  
  }


 void acc_mean_filter_callibrate(int sample){
    float sax = 0;
    float say = 0; 
    float saz = 0;
    //max and minimum still rates
    
  for(int i = 0;i<sample;i++){//sum sample rates
    accel_as_ms();
    sax += axp;
    say += ayp ;
    saz += azp;

    } //find mean offset rates
    ACCEL_MEAN_X = sax/sample;
    ACCEL_MEAN_Y = say/sample;
    ACCEL_MEAN_Z = saz/sample;
    calc_accel_chng = true;// after mean filter constants have been derived
    //calc mean offset accel 
  
  
  
  }
