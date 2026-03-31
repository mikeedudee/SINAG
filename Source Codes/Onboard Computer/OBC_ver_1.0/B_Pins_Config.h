#ifndef B_PINS_CONFIG_H
#define B_PINS_CONFIG_H

    // ==================================
    // I2C BUS 1
    // ==================================
    #define     I2C1_SDA    8           
    #define     I2C1_SCL    9

    // ==================================
    // I2C BUS 2
    // ==================================
    #define     I2C2_SDA    1
    #define     I2C2_SCL    2

    // ==================================
    // GNSS UART
    // ==================================
    #define     GNSS_RX     17
    #define     GNSS_TX     18
    #define     GNSS_BAUD   9600

    // ==================================
    // LORA SPI
    // ==================================
    #define     LORA_CS     10
    #define     LORA_MOSI   11
    #define     LORA_SCK    12
    #define     LORA_MISO   13
    #define     LORA_RST    16
    #define     LORA_DIO0   21
    #define     LORA_FREQ   433E6

    // ==================================
    // UV SENSORS
    // ==================================
    #define     UV1_PIN     4
    #define     UV2_PIN     5
    #define     UV3_PIN     6
    #define     UV4_PIN     7
    #define     UV5_PIN     15

    // ==================================
    // BUZZER + LEDS
    // ==================================
    #define     BUZZER_PIN  47
    #define     BUZZER_CH   0

    #define     LED1_PIN    35
    #define     LED2_PIN    36
    #define     LED3_PIN    37

    // ==================================
    // INA226
    // ==================================
    #define     INA226_ADDR             0x40
    #define     INA226_REG_CONFIG       0x00
    #define     INA226_REG_SHUNTVOLT    0x01
    #define     INA226_REG_BUSVOLT      0x02

    // ==================================
    // INA226 module  shunt resistor
    // ==================================
    const           float   INA226_SHUNT_OHMS       = 0.1f;

    // ==================================
    // TIMING
    // ==================================
    const unsigned  long    SAMPLE_INTERVAL_MS      = 300;
    const unsigned  long    SCD41_INTERVAL_MS       = 5000;
    const unsigned  long    MCP_INTERVAL_MS         = 1000;
    const unsigned  long    INA_INTERVAL_MS         = 500;
    const unsigned  long    BUZZER_TOGGLE_MS        = 80;
        

    // =========================
    // TELEMETRY BUFFER SIZE
    // =========================
    const           size_t  TELEMETRY_BUFFER_SIZE   = 700;

#endif