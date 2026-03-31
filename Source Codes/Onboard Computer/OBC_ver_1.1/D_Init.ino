void initPins() {
  pinMode         (UV1_PIN, INPUT);
  pinMode         (UV2_PIN, INPUT);
  pinMode         (UV3_PIN, INPUT);
  pinMode         (UV4_PIN, INPUT);
  pinMode         (UV5_PIN, INPUT);

  pinMode         (LED1_PIN, OUTPUT);
  pinMode         (LED2_PIN, OUTPUT);
  pinMode         (LED3_PIN, OUTPUT);

  digitalWrite    (LED1_PIN, LOW);
  digitalWrite    (LED2_PIN, LOW);
  digitalWrite    (LED3_PIN, LOW);

  analogReadResolution(12); 
}

void initBuzzer() {
  ledcAttach      (BUZZER_PIN, 3500, 8);
  ledcWrite       (BUZZER_PIN, 0);
}

void initI2CBuses() {
  Wire.begin      (I2C1_SDA, I2C1_SCL);
  I2C2.begin      (I2C2_SDA, I2C2_SCL);
}

void initGNSS() {
  GNSS.begin      (GNSS_BAUD, SERIAL_8N1, GNSS_RX, GNSS_TX);
}

void initSPIFFSStorage() {
  hasSPIFFS = SPIFFS.begin(true);
}

void initSensors() {
  hasMS5611 = ms5611.begin();
  if (hasMS5611) {
    referencePressure = ms5611.getPressure();
  }

  hasAS7341 = as7341.begin(AS7341_I2CADDR_DEFAULT, &Wire);
  if (hasAS7341) {
    as7341.setATIME                 (50);
    as7341.setASTEP                 (500);
    as7341.setGain                  (AS7341_GAIN_4X);
    as7341.enableSpectralInterrupt  (false);
  }

  hasTSL2591 = tsl.begin(&I2C2);
  if (hasTSL2591) {
    tsl.setGain                     (TSL2591_GAIN_MED);
    tsl.setTiming                   (TSL2591_INTEGRATIONTIME_100MS);
  }

  scd4x.begin     (I2C2, SCD41_I2C_ADDR_62);

  hasMCP9808 = mcp.begin(0x18, &I2C2);

  initINA226();

  mpu.setWire     (&Wire);
  mpu.beginAccel  ();
  mpu.beginGyro   ();
  mpu.beginMag    ();
  hasMPU9250 = true;
}

void initLoRaRadio() {
  SPI.begin       (LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
  LoRa.setSPI     (SPI);
  LoRa.setPins    (LORA_CS, LORA_RST, LORA_DIO0);

  hasLoRa = LoRa.begin(LORA_FREQ);
  if (hasLoRa) {
    LoRa.setTxPower                 (17);
    LoRa.setSpreadingFactor         (7);
    LoRa.setSignalBandwidth         (250E3);
    LoRa.setCodingRate4             (5);
    LoRa.enableCrc                  ();
  }
}