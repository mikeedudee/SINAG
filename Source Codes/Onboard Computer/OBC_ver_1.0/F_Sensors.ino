float readUVVoltage(int pin) {
  int       raw         = analogRead(pin);
  return (raw * 3.3f) / 4095.0f;
}

  // ========================== GPS ===========================
void updateGPS() {
  while (GNSS.available() > 0) {
    gps.encode(GNSS.read());
  }
}
  // ========================= SCD41 ==========================
void updateSCD41() {
  if (!hasSCD41)      return;

  bool      dataReady   = false;
  scdError  = scd4x.getDataReadyStatus(dataReady); 
  if (scdError != 0)  return;
  if (!dataReady)     return;

  uint16_t  localCO2    = 0;
  float     localTemp   = 0.0f;
  float     localHumid  = 0.0f;

  scdError  = scd4x.readMeasurement(localCO2, localTemp, localHumid);
  if (scdError != 0)  return;

            co2         = localCO2;
            scdTemp     = localTemp;
            scdHumid    = localHumid;
}

// ======================= MCP9808 ============================
void updateMCP9808() {
  if (!hasMCP9808)    return;
            mcpTemp     = mcp.readTempC();
}


  // ================================================================
  // ======================== ALL SENSORS ===========================
  // ================================================================

void sampleAllSensors() {

  // ========================== BAROMETER ===========================
            pressure    = 0;
            altitude    = 0.0;
            baroTemp    = 0.0;
  if (hasMS5611) {
    pressure = ms5611.getPressure();
    baroTemp = ms5611.getTemperature();
    altitude = ms5611.getAltitude(pressure, referencePressure);
  }

  // ============================ GPS ===============================
            lat       = 0.0;
            lon       = 0.0;
            gpsAlt    = 0.0;
            sats      = 0;
  if (gps.location.isValid()) {
    lat     = gps.location.lat();
    lon     = gps.location.lng();
  }

  if (gps.altitude.isValid()) {
    gpsAlt  = gps.altitude.meters();
  }

  if (gps.satellites.isValid()) {
    sats    = gps.satellites.value();
  }

  elapsedTime_S     = millis() / 1000.0f;

  // ========================= IMU ==================================
            accX  = accY  = accZ  = 0.0;
            gyroX = gyroY = gyroZ = 0.0;
            magX  = magY  = magZ  = 0.0;

  if (hasMPU9250) {
    mpu.accelUpdate();
    mpu.gyroUpdate();
    mpu.magUpdate();

    accX    = mpu.accelX();
    accY    = mpu.accelY();
    accZ    = mpu.accelZ();

    gyroX   = mpu.gyroX();
    gyroY   = mpu.gyroY();
    gyroZ   = mpu.gyroZ();

    magX    = mpu.magX();
    magY    = mpu.magY();
    magZ    = mpu.magZ();
  }

  // ======================== AS7341 ==================================
            nir = 0;
            red = 0;
            ndvi = 0.0;

  if (hasAS7341) {
    uint16_t  readings[12];
    if (as7341.readAllChannels(readings)) {
      red   = readings[9];
      nir   = readings[11];

      if ((nir + red) > 0) {
        ndvi = (float)(nir - red) / (float)(nir + red);
      }
    }
  }

  // ======================== TSL2591 =================================

            lux = 0.0;
  if (hasTSL2591) {
    uint32_t  lum   = tsl.getFullLuminosity();
    uint16_t  ir    = lum >> 16;
    uint16_t  full  = lum & 0xFFFF;
              lux   = tsl.calculateLux(full, ir);
  }

  // ========================== UV ====================================
            uv1   = readUVVoltage(UV1_PIN);
            uv2   = readUVVoltage(UV2_PIN);
            uv3   = readUVVoltage(UV3_PIN);
            uv4   = readUVVoltage(UV4_PIN);
            uv5   = readUVVoltage(UV5_PIN);
            uvAvg = (uv1 + uv2 + uv3 + uv4 + uv5) / 5.0f;
}