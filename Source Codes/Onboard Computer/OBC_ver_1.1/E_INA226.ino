bool ina226WriteRegister(uint8_t reg, uint16_t value) {
  I2C2.beginTransmission(INA226_ADDR);
  I2C2.write(reg);
  I2C2.write((value >> 8) & 0xFF);
  I2C2.write(value & 0xFF);
  return (I2C2.endTransmission() == 0);
}

bool ina226ReadRegister(uint8_t reg, uint16_t &value) {
  I2C2.beginTransmission(INA226_ADDR);
  I2C2.write(reg);
  if (I2C2.endTransmission(false) != 0) return false;

  if (I2C2.requestFrom((int)INA226_ADDR, 2) != 2) return false;

  uint8_t   msb           = I2C2.read();
  uint8_t   lsb           = I2C2.read();
  value = ((uint16_t)msb << 8) | lsb; 
  return true;
}

void initINA226() {
  ina226WriteRegister(INA226_REG_CONFIG, 0x4527);                         // Average 16, conv time 1.1ms, continuous shunt + bus
}

void updateINA226() {
  uint16_t  rawBus        = 0;
  uint16_t  rawShuntU     = 0;

  if (!ina226ReadRegister(INA226_REG_BUSVOLT, rawBus)) return;
  if (!ina226ReadRegister(INA226_REG_SHUNTVOLT, rawShuntU)) return;

  int16_t   rawShunt      = (int16_t)rawShuntU;


            busVoltage    = rawBus * 0.00125f;                                         // Bus voltage LSB = 1.25 mV

  float     shuntVoltage  = rawShunt * 0.0000025f;                             // Shunt voltage LSB = 2.5 uV

            current       = shuntVoltage / INA226_SHUNT_OHMS;
            power         = busVoltage * current;
}