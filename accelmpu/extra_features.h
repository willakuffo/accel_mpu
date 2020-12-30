#ifndef EXTRA
#define EXTRA

#define RAD_TO_DEG 57.3 //radians to degrees
int16_t pitch, yaw, roll; //accel angles only

float gyro_angle_pitch,gyro_angle_roll,gyro_angle_yaw; //gyro angles only

float COM_PITCH,COM_YAW,COM_ROLL; //complimentary filter angles 

void angle_from_gyro(float elapsed_time); //calculate gyro angles

void angle_from_accel(void);//calculate accel angles

void complimetary_angles(); //complimentary filter angles
#endif
