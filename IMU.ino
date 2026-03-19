#define TFT_DC 7
#define TFT_RST 8 
#define SCR_WD 240
#define SCR_HT 240   

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <Wire.h>
#include <MPU6050.h>

// Display and MPU
Arduino_ST7789 lcd = Arduino_ST7789(TFT_DC, TFT_RST);
MPU6050 mpu;

bool initialized = false;

// Timing
unsigned long prevTime = 0;
unsigned long lastDisplay = 0;

// Angles
float roll = 0;
float pitch = 0;
float yaw = 0;

// Accel angles
float accel_roll = 0;
float accel_pitch = 0;

void setup() {
  Serial.begin(115200);

  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_8G)) { //2000 degrees and 8G
    Serial.println("Sensor not found!");
    delay(500);
  }
  mpu.setDLPFMode(MPU6050_DLPF_4); 

  // Gyro calibration
  mpu.calibrateGyro();
  mpu.setThreshold(0);

  prevTime = millis();

  lcd.init();
  lcd.fillScreen(BLACK);
}

void loop() {
  unsigned long now = millis();
  float dt = (now - prevTime) / 1000.0;
  prevTime = now;

  // Read sensors
  Vector gyro = mpu.readNormalizeGyro();
  Vector accel = mpu.readNormalizeAccel();

  // Compute accel angles
  accel_roll = atan2(accel.YAxis, accel.ZAxis) * 180.0 / M_PI;
  accel_pitch = -atan2(accel.XAxis, sqrt(accel.YAxis * accel.YAxis + accel.ZAxis * accel.ZAxis)) * 180.0 / M_PI;

  // Initialize
  if (!initialized) {
    roll = accel_roll;
    pitch = accel_pitch;
    yaw = 0;
    initialized = true;
  } 
  
  else {
    float alpha = 0.98;

    //sensor fusion
    roll = alpha * (roll + gyro.XAxis * dt) + (1 - alpha) * accel_roll;
    pitch = alpha * (pitch + gyro.YAxis * dt) + (1 - alpha) * accel_pitch;

    //Yaw
    yaw += gyro.ZAxis * dt;
  }

  sendTeapotPacket(roll, pitch, yaw);

  /*
  // Serial output
  Serial.print("Pitch = ");
  Serial.print(pitch);
  Serial.print(" | Roll = ");
  Serial.print(roll);
  Serial.print(" | Yaw = ");
  Serial.println(yaw);

  // Update display at lower rate (important!)
  if (millis() - lastDisplay > 100) {
    lcd.fillScreen(BLACK);

    lcd.setTextSize(2);

    lcd.setCursor(20, 60);
    lcd.setTextColor(RED);
    lcd.print("Roll: ");
    lcd.print(roll);

    lcd.setCursor(20, 110);
    lcd.setTextColor(GREEN);
    lcd.print("Pitch: ");
    lcd.print(pitch);

    lcd.setCursor(20, 160);
    lcd.setTextColor(BLUE);
    lcd.print("Yaw: ");
    lcd.print(yaw);

    lastDisplay = millis();
  }
  */
  
}

void sendTeapotPacket(float roll, float pitch, float yaw) {
  // Convert to radians
  float rollRad  = roll  * M_PI / 180.0;
  float pitchRad = pitch * M_PI / 180.0;
  float yawRad   = yaw   * M_PI / 180.0;

  // Half angles
  float cr = cos(rollRad * 0.5);
  float sr = sin(rollRad * 0.5);
  float cp = cos(pitchRad * 0.5);
  float sp = sin(pitchRad * 0.5);
  float cy = cos(yawRad * 0.5);
  float sy = sin(yawRad * 0.5);

  // Quaternion
  float qw = cr * cp * cy + sr * sp * sy;
  float qx = sr * cp * cy - cr * sp * sy;
  float qy = cr * sp * cy + sr * cp * sy;
  float qz = cr * cp * sy - sr * sp * cy;

  // Normalize (important)
  float norm = sqrt(qw*qw + qx*qx + qy*qy + qz*qz);
  qw /= norm;
  qx /= norm;
  qy /= norm;
  qz /= norm;

  // Scale to int16 (MPU6050 style)
  int16_t qw_i = qw * 16384;
  int16_t qx_i = qx * 16384;
  int16_t qy_i = qy * 16384;
  int16_t qz_i = qz * 16384;

  // Teapot packet
  uint8_t packet[14] = {
    '$', 0x02,
    0,0, 0,0, 0,0, 0,0,
    0x00, 0x00,
    '\r', '\n'
  };

  // Fill quaternion (big endian)
  packet[2] = (qw_i >> 8) & 0xFF;
  packet[3] = qw_i & 0xFF;

  packet[4] = (qx_i >> 8) & 0xFF;
  packet[5] = qx_i & 0xFF;

  packet[6] = (qy_i >> 8) & 0xFF;
  packet[7] = qy_i & 0xFF;

  packet[8] = (qz_i >> 8) & 0xFF;
  packet[9] = qz_i & 0xFF;

  // Packet counter
  static uint8_t counter = 0;
  packet[11] = counter++;

  // Send
  Serial.write(packet, 14);
}
