#include <Wire.h>
#define TMP117_ADDRESS    0x48
#define TMP117_CONF       0x01
#define TMP117_TEMP       0x00
#define TMP117_TLOW       0x02
#define TMP117_THIGH      0x03
#define TMP117_ EEPROM_UL 0x04
#define TMP117_DEVICE_ID  0x0F

uint16_t tmp117_read_word(uint8_t regAddress) {
  uint8_t num_bytes = 2;
  uint16_t read_word = 0;
  delay(100);
  Wire.beginTransmission(TMP117_ADDRESS);
  Wire.write(regAddress);
  Wire.endTransmission(false);
  Wire.requestFrom(TMP117_ADDRESS, 2U);

  for(int i = num_bytes-1; i>=0 && Wire.available(); i--) {
    read_word += Wire.read() << (i*8);
    Wire.endTransmission(false);
  }

  return read_word;
}

bool tmp117_write_word(uint8_t regAddress, uint16_t data) {
  uint8_t buf[2];
  buf[0] = (uint8_t) (data >> 8);
  buf[1] = (uint8_t) data & 0x00FF;
  Serial.println(buf[0]);
  Serial.println(buf[1]);
  Wire.beginTransmission(TMP117_ADDRESS);
  Wire.write(regAddress);
  Wire.endTransmission(false);
  Wire.write(buf, 2U);

  if(Wire.endTransmission() != 0) {
    return false;
  }
  else {
    return true;
  }
}

//float tmp117_single_temp_read() {
//  //Set device in shut down mode
//  max30205_writeByte(MAX30205_CONF, 0x01);
//
//  //Trigger a single reading
//  max30205_writeByte(MAX30205_CONF, 0x81);
//
//  //Wait till reading is done
//  while(max30205_readByte(MAX30205_CONF) >> 7 == 1){
//    Serial.println(max30205_readByte(MAX30205_CONF));
//    delay(10);
//  }
//  uint8_t raw_temp = max30205_readByte(MAX30205_TEMP);
//
//  return (float)raw_temp * 0.00390625f;
//}

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);

  //Set device in shut down mode
//  max30205_writeByte(MAX30205_CONF, 0x01);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(tmp117_write_word(TMP117_CONF, 0x0610));
  Serial.print("Status: ");
  Serial.println(tmp117_read_word(TMP117_CONF), HEX);
//  Serial.print("Status1: ");
//  Serial.println(tmp117_read_word(TMP117_CONF), HEX);
  delay(500);
//  Serial.print("Status2: ");
//  Serial.println(tmp117_read_word(TMP117_CONF), HEX);
//  delay(1000);
//  Serial.print("Status3: ");
//  Serial.println(tmp117_read_word(TMP117_CONF), HEX);
//  delay(100);
}
