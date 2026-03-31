void buildTelemetry() {
  snprintf(
    telemetryBuffer,
    TELEMETRY_BUFFER_SIZE,
    "%ld %.2f %.2f %.6f %.6f %.2f %d %d %.3f |\n"
    "%.4f %.4f %.4f %.4f %.4f %.4f %.4f %.4f %.4f |\n"
    "%u %u %.2f %.4f %.2f %.2f %.2f |\n"
    "%.3f %.3f %.3f %.3f %.3f %.3f |\n"
    "%.2f %.3f %.3f %.3f |\n",
    pressure, altitude, baroTemp, lat, lon, gpsAlt, sats, saveState, elapsedTime_S,
    accX, accY, accZ, gyroX, gyroY, gyroZ, magX, magY, magZ,
    nir, red, lux, ndvi, co2, scdTemp, scdHumid,
    uv1, uv2, uv3, uv4, uv5, uvAvg,
    mcpTemp, busVoltage, current, power
  );
}

void saveTelemetryToSPIFFS() { 
  saveState = 0;

  if (!hasSPIFFS) {
    buildTelemetry();
    return;
  }

  File f = SPIFFS.open("/log.txt", FILE_APPEND);
  if (!f) {
    buildTelemetry();
    return;
  }

  saveState = 1;
  buildTelemetry();
  f.print(telemetryBuffer);
  f.close();
}

void transmitTelemetryLoRa() {
  if (!hasLoRa) return;

  LoRa.beginPacket();
  LoRa.print(telemetryBuffer);
  LoRa.endPacket();
}