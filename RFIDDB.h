/*
  RFIDDB.h - HackPittsburgh RFID System DB
  Author: Marty McGuire <marty@hackpittsburgh.org>, Nov. 2009
  Released under CC3.0-BY-SA - http://creativecommons.org/licenses/by-sa/3.0/
*/
#ifndef RFIDDB_h
#define RFIDDB_h

#include "WProgram.h"

// TODO: Include this directly
//#include <EEPROM.h>

#define DONT_BUFFER_TAG_IDS

#define TAG_LENGTH  10      // Length of a tag, in bytes
#define MAX_TAGS    50      // Maximum number of tags we can hold

class RFIDDB
{
  public:
    RFIDDB();
    int getNumTags();
    bool validTag(char* tag);
    void printTags();
    void readTags();
  private:
    int   tagSize;
    int   numTags;
#ifndef DONT_BUFFER_TAG_IDS
    int   dataSize;
    char tagData[MAX_TAGS][TAG_LENGTH];
#endif
};

#endif
