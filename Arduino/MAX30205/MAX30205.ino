#include <Wire.h>
#define MAX20305_ADDRESS (0x90 >> 1)
#define MAX30205_CONF     0x01
#define MAX30205_TEMP     0x0
#define MAX30205_THYST    0x02
#define MAX30205_TOS      0x03

uint8_t max30205_readByte(uint8_t regAddress) {
  Wire.beginTransmission(MAX20305_ADDRESS);
  Wire.write(regAddress);
  Wire.endTransmission(false);

  if(Wire.requestFrom(MAX20305_ADDRESS, 1U, 1U) > 0) {
    return Wire.read();
  }
  else {
    return -1;
  }
}

bool max30205_writeByte(uint8_t regAddress, uint8_t data) {
  Wire.beginTransmission(0x90 >> 1);
  Wire.write(regAddress);
  Wire.write(data);

  if(Wire.endTransmission() != 0) {
    return false;
  }
  else {
    return true;
  }
}

float max30205_single_read() {
  //Set device in shut down mode
  max30205_writeByte(MAX30205_CONF, 0x01);

  //Trigger a single reading
  max30205_writeByte(MAX30205_CONF, 0x81);

  //Wait till reading is done
  while(max30205_readByte(MAX30205_CONF) >> 7 == 1){
    Serial.println(max30205_readByte(MAX30205_CONF));
    delay(10);
  }
  uint8_t raw_temp = max30205_readByte(MAX30205_TEMP);

  return (float)raw_temp * 0.00390625f;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);

  //Set device in shut down mode
  max30205_writeByte(MAX30205_CONF, 0x01);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Status: ");
  Serial.println(max30205_writeByte(MAX30205_CONF, 0x01));
  delay(100);
}
