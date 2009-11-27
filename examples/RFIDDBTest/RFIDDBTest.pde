#include <EEPROM.h>
#include <RFIDDB.h>

RFIDDB rfiddb;
char* testTag = "22007AC2C5";
char* fakeTag = "2222222222";

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
      case 'T':
        Serial.print(testTag);
        if(rfiddb.validTag(testTag)){
          Serial.println(" is in the RFIDDB");
        } else {
          Serial.println(" is NOT in the RFIDDB");
        }
        Serial.print(fakeTag);
        if(rfiddb.validTag(fakeTag)){
          Serial.println(" is in the RFIDDB");
        } else {
          Serial.println(" is NOT in the RFIDDB");
        }
    }
  }
}
