#ifndef MPU_ADDED
#define MPU_ADDED

#define GYRO_SENSITIVITY 131 //gyro sensitivity val -> 250deg/s
#define ACCEL_SENSITIVITY 16384 //accel sensitivity val -> 2g
#define GRAVITY 9.81

//gyro offsets
#define GYRO_OFFSET_X 0 
#define GYRO_OFFSET_Y -2
#define GYRO_OFFSET_Z 1


int16_t ax, ay, az, gx, gy, gz; //collect raw gyro and accel values as global
float axp, ayp, azp;//processed accel m/s values as global
int16_t gxp, gyp, gzp; //collect processed gyro deg/s values as global

bool mpu_ready  = false; //is mpu ready?

void accel_as_raw(); //accel raw
void accel_as_ms(); ///accel m/s
void gyro_as_deg(); //gyro deg/s angle rates
void gyro_as_raw(); //gyro raw vals
void mpu_setup(); //set up mpu6050 on addr 0x68

#endif
