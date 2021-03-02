#ifndef MPU_ADDED
#define MPU_ADDED

#define GYRO_SENSITIVITY 131 //gyro sensitivity val -> 250deg/s
#define ACCEL_SENSITIVITY 16384 //accel sensitivity val -> 2g
#define GRAVITY 9.81

//gyro offsets
float GYRO_OFFSET_X; 
float GYRO_OFFSET_Y;
float GYRO_OFFSET_Z;

float ACCEL_MEAN_X ;
float ACCEL_MEAN_Y ;
float ACCEL_MEAN_Z ;

int16_t ax, ay, az, gx, gy, gz; //collect raw gyro and accel values as global
float axp, ayp, azp;//processed accel m/s values as global
float gxp, gyp, gzp; //collect processed gyro deg/s values as global
int16_t tmp;

bool mpu_ready  = false; //is mpu ready?

float gyro_rate_ymax = 0;
float gyro_rate_ymin = 0;
float gyro_rate_xmax = 0;
float gyro_rate_xmin = 0;

float chng_axp,chng_ayp,chng_azp; //3-axis accel magnitude change
bool calc_accel_chng = false; //whether to calc immediate above. Ensures that mean filter constants are not affected or miscalulated because this is in accel_as_ms


void accel_as_raw(); //accel raw
void accel_as_ms(); ///accel m/s
void gyro_as_deg(); //gyro deg/s angle rates
void gyro_as_raw(); //gyro raw vals
void mpu_setup(); //set up mpu6050 on addr 0x68
void temperature();//get temp from mpu
void gyro_offset_callibrate(int);//callibrate gyro offsets
void acc_mean_filter_callibrate(int); //callibrate accelerometer mean filters

#endif
