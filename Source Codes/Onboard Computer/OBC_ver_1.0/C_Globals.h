#ifndef C_GLOBALS_H
#define C_GLOBALS_H

    // ============================ BUS OBJECTS ======================================

    TwoWire                 I2C2                = TwoWire(1);
    HardwareSerial          GNSS(1);

    // ========================== SENSOR OBJECTS =====================================
    TinyGPSPlus             gps;
    MS5611                  ms5611; 
    Adafruit_AS7341         as7341;
    Adafruit_TSL2591        tsl                 = Adafruit_TSL2591(2591);
    SensirionI2cScd4x       scd4x;
    Adafruit_MCP9808        mcp                 = Adafruit_MCP9808();
    MPU9250_asukiaaa        mpu;

    static          char    scdErrorMessage[64];
    static          int16_t scdError            = 0;

    // ============================ STATUS FLAGS ====================================
                    bool    hasSPIFFS           = false;
                    bool    hasMS5611           = false;
                    bool    hasAS7341           = false;
                    bool    hasTSL2591          = false;
                    bool    hasSCD41            = false;
                    bool    hasMCP9808          = false;
                    bool    hasMPU9250          = false;
                    bool    hasLoRa             = false;

    // =============================== TIMERS =======================================
    unsigned long           prevTime_Sample_MS  = 0;
    unsigned long           prevTime_SCD41_MS   = 0;
    unsigned long           prevTime_MCP_MS     = 0;
    unsigned long           prevTime_INA_MS     = 0;
    unsigned long           prevTime_Buzzer_MS  = 0;

    // ============================= BUZZER STATE ===================================
                    bool    buzzerState         = false;

    // ============================ BARO REFERENCE ==================================
                    double  referencePressure   = 101325.0;

    // ========================== TELEMETRY VALUES ==================================
    long                    pressure            = 0;
                    float   altitude            = 0.0f;
                    float   baroTemp            = 0.0f;

                    float   lat                 = 0.0f;
                    float   lon                 = 0.0f;
                    float   gpsAlt              = 0.0f;
                    
                    int     sats                = 0;
                    int     saveState           = 0;
                    float   elapsedTime_S       = 0.0f;

    // ================================ IMU =========================================
                    float       accX    = 0.0f,     accY     = 0.0f,    accZ     = 0.0f;
                    float       gyroX   = 0.0f,     gyroY    = 0.0f,    gyroZ    = 0.0f;
                    float       magX    = 0.0f,     magY     = 0.0f,    magZ     = 0.0f;

    // ===========================  SPECTRAL / LUX ================================= 
                    uint16_t    nir                 = 0;
                    uint16_t    red                 = 0;
                    float       lux                 = 0.0f;
                    float       ndvi                = 0.0f;

    // ============================== SCD41 =======================================
                    float       co2                 = 0.0f;
                    float       scdTemp             = 0.0f;
                    float       scdHumid            = 0.0f;

    // =============================== UV =========================================
                    float       uv1                 = 0.0f;
                    float       uv2                 = 0.0f;
                    float       uv3                 = 0.0f;
                    float       uv4                 = 0.0f;
                    float       uv5                 = 0.0f;
                    float       uvAvg               = 0.0f;

    // ============================= MCP9808 =======================================
                    float       mcpTemp             = 0.0f;

    // ============================= INA226 ========================================
                    float       busVoltage          = 0.0f;
                    float       current             = 0.0f;
                    float       power               = 0.0f;

    // ============================ STORAGE / TX ====================================
                    char        telemetryBuffer[TELEMETRY_BUFFER_SIZE];

#endif