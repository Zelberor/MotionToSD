#include "Button.hpp"
#include "pins_arduino.h"
#include <Arduino.h>
/*MPU6050*/
#include <TinyMPU6050.h>
/*MPU6050 end*/
/*SDFAT*/
#include <FreeStack.h>
#include <SdFat.h>
#include <sdios.h>
/*SDFAT end*/

/*Input*/
const int submitPin = 3;
Input::Button submitButton{submitPin};

/*MPU6050*/
MPU6050 mpu(Wire);
/*MPU6050 end*/

/*SDFAT*/
// SD_FAT_TYPE = 0 for SdFat/File as defined in SdFatConfig.h,
// 1 for FAT16/FAT32, 2 for exFAT, 3 for FAT16/FAT32 and exFAT.
#define SD_FAT_TYPE 1
// SDCARD_SS_PIN is defined for the built-in SD on some boards.
#ifndef SDCARD_SS_PIN
const uint8_t SD_CS_PIN = SS;
#else  // SDCARD_SS_PIN
// Assume built-in SD is used.
const uint8_t SD_CS_PIN = SDCARD_SS_PIN;
#endif // SDCARD_SS_PIN

// Try max SPI clock for an SD. Reduce SPI_CLOCK if errors occur.
#define SPI_CLOCK SD_SCK_MHZ(50)

// Try to select the best SD card configuration.
#if HAS_SDIO_CLASS
#define SD_CONFIG SdioConfig(FIFO_SDIO)
#elif ENABLE_DEDICATED_SPI
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, DEDICATED_SPI, SPI_CLOCK)
#else // HAS_SDIO_CLASS
#define SD_CONFIG SdSpiConfig(SD_CS_PIN, SHARED_SPI, SPI_CLOCK)
#endif // HAS_SDIO_CLASS

// Size of read/write.
const size_t BUF_SIZE = 512;

// Ensure 4-byte alignment.
uint32_t buf32[(BUF_SIZE + 3) / 4];
char *buf = (char *)buf32;

#if SD_FAT_TYPE == 0
SdFat sd;
File file;
#elif SD_FAT_TYPE == 1
SdFat32 sd;
File32 file;
#elif SD_FAT_TYPE == 2
SdExFat sd;
ExFile file;
#elif SD_FAT_TYPE == 3
SdFs sd;
FsFile file;
#else // SD_FAT_TYPE
#error Invalid SD_FAT_TYPE
#endif // SD_FAT_TYPE
/*SDFAT end*/

/*Control*/
enum ControlMode {
  Starting,
  Idle,
  Writing,
  Error,
};
ControlMode mode{Starting};

unsigned long recordingNum = 0;
const long floatMult = 100000;
uint8_t ledState = LOW;
const unsigned long ledBlinkDelta = 100;
unsigned long ledBlinkTime = 0;
/*Control end*/

ArduinoOutStream cout(Serial);
// Store error strings in flash to save RAM.
#define error(s) sd.errorHalt(&Serial, F(s))

void cardInfo() {
  if (sd.fatType() == FAT_TYPE_EXFAT) {
    cout << F("Type is exFAT") << endl;
  } else {
    cout << F("Type is FAT") << int(sd.fatType()) << endl;
  }
  cout << F("Card size: ") << sd.card()->sectorCount() * 512E-9;
  cout << F(" GB (GB = 1E9 bytes)") << endl;
  cid_t cid;
  if (!sd.card()->readCID(&cid)) {
    error("readCID failed");
  }
  cout << F("\nManufacturer ID: ");
  cout << hex << int(cid.mid) << dec << endl;
  cout << F("OEM ID: ") << cid.oid[0] << cid.oid[1] << endl;
  cout << F("Product: ");
  for (uint8_t i = 0; i < 5; i++) {
    cout << cid.pnm[i];
  }
  cout << F("\nVersion: ");
  cout << int(cid.prv_n) << '.' << int(cid.prv_m) << endl;
  cout << F("Serial number: ") << hex << cid.psn << dec << endl;
  cout << F("Manufacturing date: ");
  cout << int(cid.mdt_month) << '/';
  cout << (2000 + cid.mdt_year_low + 10 * cid.mdt_year_high) << endl;
  cout << endl;
}

void setup() {
  mpu.Initialize();
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  ledState = LOW;

  Serial.begin(9600);
  if (!ENABLE_DEDICATED_SPI) {
    cout << F("\nSet ENABLE_DEDICATED_SPI nonzero in\n"
              "SdFatConfig.h for best Sdcard performance.\n");
  }

  Serial.println("=====================================");
  Serial.println("MPU6050: Starting calibration...");
  mpu.Calibrate();
  Serial.println("MPU6050: Calibration complete!");
  Serial.println("=====================================");
  Serial.println("SDFAT: Initializing sd card...");
  if (!sd.begin(SD_CONFIG)) {
    sd.initErrorHalt(&Serial);
    mode = Error;
    return;
  }
  Serial.println("SDFAT: CardInfo:");
  cardInfo();
  Serial.println("SDFAT: Initialization complete!");
  Serial.println("=====================================");
  Serial.println("Startup finished!");
  mode = Idle;
}

void loop() {
  switch (mode) {
  case Starting:
    error("Startup failed");
    digitalWrite(LED_BUILTIN, LOW);
    while (true)
      ;
  case Error:
    error("Exiting...");
    digitalWrite(LED_BUILTIN, LOW);
    while (true)
      ;
  case Idle:
    if (ledState != HIGH) {
      digitalWrite(LED_BUILTIN, HIGH);
      ledState = HIGH;
    }
    if (submitButton.Pressed()) {
      if (!file.open("gyro.csv", O_WRONLY | O_APPEND | O_CREAT)) {
        error("File open failed");
        mode = Error;
        return;
      }
      Serial.println("Opened file! Now writing...");
      recordingNum = millis();
      sprintf(buf,
              "##########\n# Recording %lu start\n# Format: >Millis Micros "
              "AccelX AccelY "
              "AccelZ RotX RotY RotZ<\n# All multiplied x%ld\n##########\n",
              recordingNum, floatMult);
      file.write(buf);
      mode = Writing;
      return;
    }
  case Writing:
    unsigned long timeMillis = millis();
    unsigned long timeMicros = micros();
    if (submitButton.Pressed()) {
      if (!file.close()) {
        error("File close failed");
        mode = Error;
        return;
      }
      Serial.println("Closed file! Now idle...");
      mode = Idle;
      return;
    }
    if (timeMillis - ledBlinkTime > ledBlinkDelta) {
      if (ledState == HIGH) {
        digitalWrite(LED_BUILTIN, LOW);
        ledState = LOW;
      } else {
        digitalWrite(LED_BUILTIN, HIGH);
        ledState = HIGH;
      }
      ledBlinkTime = timeMillis;
    }
    mpu.Execute();
    sprintf(
        buf, "%lu %lu %ld %ld %ld %ld %ld %ld\n", timeMillis, timeMicros,
        (long)(mpu.GetAccX() * floatMult), (long)(mpu.GetAccY() * floatMult),
        (long)(mpu.GetAccZ() * floatMult), (long)(mpu.GetAngX() * floatMult),
        (long)(mpu.GetAngY() * floatMult), (long)(mpu.GetAngZ() * floatMult));
    file.write(buf);
  }
}
