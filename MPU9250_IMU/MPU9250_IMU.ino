  #include <MPU9250.h>
  #include <Wire.h>
  #include <I2Cdev.h>
  
  
  //MPU settings
  MPU9250 mpu;
  MPU9250Setting setting;
  setting.accel_fs_sel = ACCEL_FS_SEL::A8G;
  setting.gyro_fs_sel = GYRO_FS_SEL::G2000DPS;
  setting.mag_output_bits = MAG_OUTPUT_BITS::M16BITS;
  setting.fifo_sample_rate = FIFO_SAMPLE_RATE::SMPL_200HZ;
  setting.gyro_fchoice = 0x03;
  setting.gyro_dlpf_cfg = GYRO_DLPF_CFG::DLPF_41HZ;
  setting.accel_fchoice = 0x01;
  setting.accel_dlpf_cfg = ACCEL_DLPF_CFG::DLPF_45HZ;
  
  //Variables
  float roll = 0;
  float pitch = 0;
  float yaw = 0;
  
  void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    Wire.begin();
    delay(3000);
  
    mpu.setup(0x0C, setting); //Address for the GY-91
    while(!mpu.isConnected()){ 
      mpu.setup(0x0C, setting);
      delay(200);
    }
  
    
    //mpu.setMagneticDeclination();
    mpu.selectFilter(QuatFilterSel MAHONY);
    mpu.setFilterIterations(15);
    mpu.calibrateAccelGyro();
    mpu.calibrateMag();
    delay(2000);
  }
  
  void loop() {
    // put your main code here, to run repeatedly:
    roll = mpu.getRoll();
    pitch = mpu.getPitch();
    yaw = mpu.getYaw();
  }
