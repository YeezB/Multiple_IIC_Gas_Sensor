/*!
  * @file  initiativereport.ino
  * @brief The sensor actively reports all data
  * @n Experimental method: Connect the sensor communication pin to the main control, then burn codes into it. 
  * @n Communication mode selection, dial switch SEL:0: IIC, 1: UART
@n I2C address selection, the default I2C address is 0x74, A1 and A0 are combined into 4 types of IIC addresses
                | A1 | A0 |
                | 0  | 0  |    0x74
                | 0  | 1  |    0x75
                | 1  | 0  |    0x76
                | 1  | 1  |    0x77   default i2c address
  * @n Experimental phenomenon: Print all data via serial port
*/
#include "DFRobot_MultiGasSensor.h"
//Enabled by default, use IIC communication at this time. Use UART communication when disabled
#define I2C_COMMUNICATION

#ifdef  I2C_COMMUNICATION
#define I2C_ADDRESS_H2S    0x74
#define I2C_ADDRESS_NH3    0x75
#define I2C_ADDRESS_SO2    0x76
#define I2C_ADDRESS_NO2    0x77
  DFRobot_GAS_I2C gas_H2S(&Wire ,I2C_ADDRESS_H2S);
  DFRobot_GAS_I2C gas_NH3(&Wire ,I2C_ADDRESS_NH3);
  DFRobot_GAS_I2C gas_SO2(&Wire ,I2C_ADDRESS_SO2);
  DFRobot_GAS_I2C gas_NO2(&Wire ,I2C_ADDRESS_NO2);
#else
#if (!defined ARDUINO_ESP32_DEV) && (!defined __SAMD21G18A__)
/**
  UNO:pin_2-----RX
      pin_3-----TX
*/
  SoftwareSerial mySerial(2,3);
  DFRobot_GAS_SoftWareUart gas(&mySerial);
#else
/**
  ESP32:IO16-----RX
        IO17-----TX
*/
  DFRobot_GAS_HardWareUart gas(&Serial2); //ESP32HardwareSerial
#endif
#endif

void setup() {

  Serial.begin(115200);

  while(!gas_H2S.begin())
  {
    Serial.println("NO H2S Deivces !");
    delay(1000);
  }
  Serial.println("The H2S device is connected successfully!");

  while(!gas_NH3.begin())
  {
    Serial.println("NO NH3 Deivces !");
    delay(1000);
  }
  Serial.println("The NH3 device is connected successfully!");

  while(!gas_SO2.begin())
  {
    Serial.println("NO SO2 Deivces !");
    delay(1000);
  }
  Serial.println("The SO2 device is connected successfully!");

  while(!gas_NO2.begin())
  {
    Serial.println("NO NO2 Deivces !");
    delay(1000);
  }
  Serial.println("The NO2 device is connected successfully!");

  gas_H2S.changeAcquireMode(gas_H2S.PASSIVITY);
  delay(1000);
  gas_NH3.changeAcquireMode(gas_NH3.PASSIVITY);
  delay(1000);
  gas_SO2.changeAcquireMode(gas_SO2.PASSIVITY);
  delay(1000);
  gas_NO2.changeAcquireMode(gas_NO2.PASSIVITY);
  delay(1000);

  gas_H2S.setTempCompensation(gas_H2S.OFF);
  gas_NH3.setTempCompensation(gas_NH3.OFF);
  gas_SO2.setTempCompensation(gas_SO2.OFF);
  gas_NO2.setTempCompensation(gas_NO2.OFF);
}

void loop() {

  Serial.print("Ambient ");
  Serial.print(gas_H2S.queryGasType());
  Serial.print(" concentration is: ");
  Serial.print(gas_H2S.readGasConcentrationPPM());
  Serial.println(" %vol");
  //The measurement unit will only be %vol when the sensor is SEN0465
  //Otherwise the unit will be PPM
  Serial.print("The board temperature is: ");
  Serial.print(gas_H2S.readTempC());
  Serial.println(" ℃");
  Serial.println();
  delay(1000);

  Serial.print("Ambient ");
  Serial.print(gas_NH3.queryGasType());
  Serial.print(" concentration is: ");
  Serial.print(gas_NH3.readGasConcentrationPPM());
  Serial.println(" %vol");
  Serial.print("The board temperature is: ");
  Serial.print(gas_NH3.readTempC());
  Serial.println(" ℃");
  Serial.println();
  delay(1000);

  Serial.print("Ambient ");
  Serial.print(gas_SO2.queryGasType());
  Serial.print(" concentration is: ");
  Serial.print(gas_SO2.readGasConcentrationPPM());
  Serial.println(" %vol");
  Serial.print("The board temperature is: ");
  Serial.print(gas_SO2.readTempC());
  Serial.println(" ℃");
  Serial.println();
  delay(1000);

  Serial.print("Ambient ");
  Serial.print(gas_NO2.queryGasType());
  Serial.print(" concentration is: ");
  Serial.print(gas_NO2.readGasConcentrationPPM());
  Serial.println(" %vol");
  Serial.print("The board temperature is: ");
  Serial.print(gas_NO2.readTempC());
  Serial.println(" ℃");
  Serial.println();
  delay(1000);
}