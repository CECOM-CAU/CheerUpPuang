#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <stdlib.h>

#define ID 0x00
#define ALL 0xff

#define START 0Xf0
#define END 0xff

#define ACK 0x00
#define RGB 0x01
#define RAINBOW 0x02

RF24 radio(7,8); // CE, CSN
bool SendAck();
void SendRGB();
void SendRainbow();
void Protocol(uint8_t* buf, uint8_t function, uint8_t trans, uint8_t rec, uint8_t* value);
void FillHeader(uint8_t* protocol, uint8_t function, uint8_t trans, uint8_t rec);
uint8_t CheckSum(uint8_t* data);
const uint64_t address = 0x00000000;
void setup() {
  // Console PC connection
  Serial.begin(115200);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  radio.stopListening();
}

void loop() {
  
}

bool SendAck(){
}

void SendRGB(){
}

void SendRainbow(){
  uint8_t _protocol[7];
  Protocol(&_protocol[0], RAINBOW, ID, ALL, NULL);
  radio.write(&_protocol, 7);
}

void Protocol(uint8_t* buf, uint8_t function, uint8_t trans, uint8_t rec, uint8_t* value){
  switch(function){
    case 0x00:                                  // ACK
        FillHeader(buf, function, trans, rec);
        buf[4] = 0x00;
        buf[5] = 0x00;
        buf[6] = END;
      break;
    case 0x01:                                  // RGB
        uint8_t _buf[4];
        FillHeader(buf, function, trans, rec);
        buf[4] = 0x03;
        for(int i=0;i<3;i++){
          buf[i+5] = value[i];
        }
        for(int i=0;i<4;i++){
          _buf[i] = buf[4+i];
        }
        buf[5] = CheckSum(&_buf[0]);
        buf[6] = END;
      break;
    case 0x02:                                  // RAINBOW
        FillHeader(buf, function, trans, rec);
        buf[4] = 0x00;
        buf[5] = 0x00;
        buf[6] = END;
      break;
  }
}

void FillHeader(uint8_t* protocol, uint8_t function, uint8_t trans, uint8_t rec){
  protocol[0] = START;
  protocol[1] = function;
  protocol[2] = trans;
  protocol[3] = rec;
}

uint8_t CheckSum(uint8_t* data){
  uint8_t result = 0x00;
  for(int i=0;i<sizeof(data);i++){
    result += data[i] & 0x01;
  }
  return result & 0x01;
}