#include <Arduino.h>
#include <nRF24L01.h>
#include <RF24.h>

#define ID 0x00
#define ALL 0xff

#define START 0Xf0
#define END 0xff

#define ACK 0x00
#define RGB 0x01
#define RAINBOW 0x02


RF24 radio(7,8); // CE, CSN

const byte address[6] = "000001";

void setup() {
  // Console PC connection
  Serial.begin(115200);
  
  radio.begin();
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MAX);
  rf.stopListening();
}

void loop() {
  
}

bool SendAck(){
}

void SendRGB(){

}

void SendRainbow(){
}

byte[] Protocol(byte function, byte trans, byte rec, byte value[]){
  switch(function){
    case 0x00:                                  // ACK
        byte[7] _protocol;
        FillHeader(&_protocol, function, trans, rec);
        _protocol[4] = 0x00;
        _protocol[5] = 0x00;
        _protocol[6] = END;
      break;
    case 0x00:                                  // ACK
        byte[10] _protocol;
        byte[4] _buf;
        FillHeader(&_protocol, function, trans, rec);
        _protocol[4] = 0x03;
        for(int i=0;i<3;i++){
          _protocol[i+5] = value[i];
        }
        for(int i=0;i<4;i++){
          _buf[i] = _protocol[4+i]
        }
        _protocol[5] = CheckSum(&_buf);
        _protocol[6] = END;
      break;
    case 0x02:                                  // ACK
        byte[7] _protocol;
        FillHeader(&_protocol, function, trans, rec);
        _protocol[4] = 0x00;
        _protocol[5] = 0x00;
        _protocol[6] = END;
      break;
  }
}

void FillHeader(byte* protocol, byte function, byte trans, byte rec){
  protocol[0] = START;
  protocol[1] = function;
  protocol[2] = trans;
  protocol[3] = rec;
}

byte CheckSum(byte* data){
  byte result = 0x00;
  for(int i=0;i<sizeof(data);i++){
    result += data[i] & 0x01;
  }
  return byte & 0x01;
}