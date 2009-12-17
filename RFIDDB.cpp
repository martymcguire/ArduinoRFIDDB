/*
  RFIDDB.h - HackPittsburgh RFID System DB
  Author: Marty McGuire <marty@hackpittsburgh.org>, Nov. 2009
  Released under CC3.0-BY-SA - http://creativecommons.org/licenses/by-sa/3.0/
  */

#include "WProgram.h"
#include "RFIDDB.h"
#include "../EEPROM/EEPROM.h"

RFIDDB::RFIDDB()
{
  _tagSize = 10;
  _numTags = EEPROM.read(0);
  if((_numTags == 0) || (_numTags > 51)){
    Serial.print("Bogus number of tags reported: ");
    Serial.println(_numTags, DEC);
    _numTags = 0;
  }
  if(_numTags > 0){
    _dataSize = _tagSize * sizeof(char) * _numTags;
    _tagData = (char*) malloc(_dataSize);
    for(int i = 1; i < _dataSize + 1; i++){
      _tagData[i - 1] = (char) EEPROM.read(i);
    }
  }
}

int RFIDDB::numTags()
{
  return _numTags;
}

void RFIDDB::printTags()
{
  Serial.print("Printing ");
  Serial.print(_numTags);
  Serial.println(" tags.");
  for(int i = 0; i < _numTags; i++){
    Serial.print("Tag #");
    Serial.print(i + 1);
    Serial.print(": ");
    for(int j = 0; j < _tagSize; j++){
      Serial.print(_tagData[ (_tagSize * i) + j ], BYTE);
    }
    Serial.println();
  }
}

void RFIDDB::readTags()
{
  char inByte;
  int done = 0;
  free(_tagData);
  _tagData = NULL;
  _numTags = -1;
  _dataSize = 0;
  int currTag = 0;
  int idx = 0;
  while(!done){
    if(Serial.available() > 0){
      inByte = Serial.read();
      // get the total number of records, if we don't already have it
      if(_numTags == -1){
        _numTags = (int) inByte;
        Serial.print("Expecting ");
        Serial.print(_numTags, DEC);
        Serial.println(" tags.");
        _dataSize = _tagSize * sizeof(char) * _numTags;
        _tagData = (char*) malloc(_dataSize);
        EEPROM.write(0, _numTags);
        if(_numTags == 0) { done = 1; } // no tags to write
      } else {
        // otherwise, put this byte wherever it goes
        _tagData[currTag * _tagSize + idx] = inByte; // RAM
        EEPROM.write(currTag * _tagSize + idx + 1, inByte); // EEPROM
        // then, increment counters and/or set that we're done
        idx++;
        if(idx >= _tagSize){
          Serial.print("Wrote ID #: ");
          Serial.println(currTag + 1);
          idx = 0;
          currTag++;
          if(currTag >= _numTags){
            done = 1;
          }
        }
      }
    }
  }
  Serial.println("Finished!");
}

bool RFIDDB::validTag(char* tag){
  bool ok = true;
  for(int i = 0; i < _numTags; i++){
    ok = true;
    for(int j = 0; j < _tagSize; j++){
      if(tag[j] != _tagData[(i * _tagSize) + j]){
        ok = false;
      }
    }
    if(ok) { return true; }
  }
  return false;
}
