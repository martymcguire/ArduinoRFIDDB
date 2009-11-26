#include <EEPROM.h>
#include <RFIDDB.h>

RFIDDB rfiddb;

void setup()
{
  rfiddb = RFIDDB();
  Serial.begin(9600);
  Serial.println("Arduino Ready");
}

void loop()
{
  char inByte;
  if (Serial.available() > 0) {
    inByte = Serial.read();
    switch(inByte){
      case 'U':
        Serial.println("Upload time!");
        rfiddb.readTags();
        break;
      case 'P':
        rfiddb.printTags();
        break;
    }
  }
}
