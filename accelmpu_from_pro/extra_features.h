#ifndef EXTRA
#define EXTRA

//#define RAD_TO_DEG 57.3 //radians to degrees
int16_t pitch, yaw, roll; //accel angles only

float gyro_angle_pitch,gyro_angle_roll,gyro_angle_yaw; //gyro angles only

float COM_PITCH,COM_YAW,COM_ROLL; //complimentary filter angles 

int16_t unangled_pos;//unangled 3d positions. Gets true pos when pitch, roll or yaw

 int avgx, avgy,avgz; //average distance from x,y,z planes
 int travel; //actual distance travelled from (avgx,avgy,avgz)-> starting point

void angle_from_gyro(float elapsed_time); //calculate gyro angles

void angle_from_accel(void);//calculate accel angles

void complimetary_angles(void); //complimentary filter angles

void unangled_position(int16_t pos, uint8_t whichangle);//unangled positions, true when yaw, pitch or roll

void travel_dist(int plane_distance,int avg); //travel distance from starting point (avgx,avgy,avgz)

void inital_plane_distance(void); //get initial plane distance/starting point (avgx,avgy,avgz)


//void recallibrate_gyro_x();
//void recallibrate_gyro_y();
#endif
