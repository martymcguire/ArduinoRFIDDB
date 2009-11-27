/*
  RFIDDB.h - HackPittsburgh RFID System DB
  Author: Marty McGuire <marty@hackpittsburgh.org>, Nov. 2009
  Released under CC3.0-BY-SA - http://creativecommons.org/licenses/by-sa/3.0/
*/
#ifndef RFIDDB_h
#define RFIDDB_h

#include "WProgram.h"

class RFIDDB
{
  public:
    RFIDDB();
    int numTags();
    bool validTag(char* tag);
    void printTags();
    void readTags();
  private:
    int   _tagSize;
    int   _numTags;
    int   _dataSize;
    char* _tagData;
};

#endif
