#include  "A_Libraries.h"
#include  "B_Pins_Config.h"
#include  "C_Globals.h"

void setup() {
    Serial.begin(115200);
    initPins();
    initBuzzer();
    initI2CBuses();
    initGNSS();
    initSPIFFSStorage();
    initSensors();
    initLoRaRadio();
}

void loop() {
  updateBuzzer();
  updateGPS();

  unsigned long currTime_MS = millis();

  if (currTime_MS - prevTime_SCD41_MS >= SCD41_INTERVAL_MS) {
    prevTime_SCD41_MS = currTime_MS;
    updateSCD41();
  }

  if (currTime_MS - prevTime_MCP_MS >= MCP_INTERVAL_MS) {
    prevTime_MCP_MS = currTime_MS;
    updateMCP9808();
  }

  if (currTime_MS - prevTime_INA_MS >= INA_INTERVAL_MS) {
    prevTime_INA_MS = currTime_MS;
    updateINA226();
  }

  if (currTime_MS - prevTime_Sample_MS >= SAMPLE_INTERVAL_MS) {
    prevTime_Sample_MS = currTime_MS;
    sampleAllSensors();
    buildTelemetry();
    saveTelemetryToSPIFFS();
    transmitTelemetryLoRa();
    Serial.print(telemetryBuffer);
  }
}