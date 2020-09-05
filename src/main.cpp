#include <Arduino.h>
#include <SPI.h>
#include <mcp_can.h>

const int spiCSPin = 10;

byte data_byte_0 = 0xFF;

MCP_CAN CAN(spiCSPin);

void setup()
{
    Serial.begin(9600);

    while (CAN_OK != CAN.begin(CAN_500KBPS))
    {
        Serial.println("CAN BUS init Failed");
        delay(100);
    }
    Serial.println("CAN BUS Shield Init OK!");
}
  
void loop()
{ 
    data_byte_0++;
    byte stmp[1] = {data_byte_0};

    Serial.print("Writing CAN | ");
    for (int x=0; x<1; x++)
    {
        Serial.print(stmp[x]);
        Serial.print(" | ");
    }
    
    if  (data_byte_0%2 == 1) CAN.sendMsgBuf(0x01, 0, 1, stmp);
    else CAN.sendMsgBuf(0x02, 0, 1, stmp);
    Serial.println("");
}