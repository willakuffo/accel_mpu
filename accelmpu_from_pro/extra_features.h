#ifndef EXTRA
#define EXTRA

//#define RAD_TO_DEG 57.3 //radians to degrees
int16_t pitch, yaw, roll; //accel angles only

float gyro_angle_pitch,gyro_angle_roll,gyro_angle_yaw; //gyro angles only

float COM_PITCH,COM_YAW,COM_ROLL; //complimentary filter angles 

int16_t unangled_pos;//unangled 3d positions. Gets true pos when pitch, roll or yaw

uint16_t avgx = 0, avgy = 0,avgz = 0; //average distance from x,y,z planes

int travel; //actual distance travelled from (avgx,avgy,avgz)-> starting point

float IMU_dist_x = 0, IMU_dist_y = 0, IMU_dist_z = 0; //current IMU positions with respect to starting point (avgx,avgy,avgz) at time t
float IMU_vel_x = 0,IMU_vel_y = 0,IMU_vel_z = 0; ////current IMU velocities at time t



void angle_from_gyro(float elapsed_time); //calculate gyro angles

void angle_from_accel(void);//calculate accel angles

void complimetary_angles(void); //complimentary filter angles

void unangled_position(int16_t pos, uint8_t whichangle);//unangled positions, true when yaw, pitch or roll

void travel_dist_sonar(int plane_distance,int avg); //travel distance from starting point (avgx,avgy,avgz)

void inital_plane_distance(void); //get initial plane distance/starting point (avgx,avgy,avgz)

void IMU_vel_dist(float elapsed_time);

//void recallibrate_gyro_x();
//void recallibrate_gyro_y();
#endif
