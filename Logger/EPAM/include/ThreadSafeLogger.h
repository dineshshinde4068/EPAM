#ifndef THREADSAFELOGGER_H
#define THREADSAFELOGGER_H

#include<iostream>
#include <string>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <mutex>
#include "configLoader.h"

using namespace std;
class ThreadSafeLogger
{
     private:

          mutex mx;
          ofstream logFile;
          bool isFileOpen;
          static ThreadSafeLogger* instance;
          configLoader cfg;
          bool isFileBasedLog;
          bool isErrorDisabled;
          bool isWarningDisabled;

        ThreadSafeLogger() = default;
    public:
        static ThreadSafeLogger* getInstance()
        {
            if(instance==nullptr)
            {
                instance=new ThreadSafeLogger();
                getInstance()->cfg.readConfig();
            }

            return instance;
        }



        void loadConfig();
      //2. Write function to  give timestamp in YYYYMMDDHHMMSS format to identy the event.
     //static std::string getTimestamp()
     //This function gives timestamp in YYYYMMDDHHMMSS format to identy the event.
    std::string getTimestamp();

     //3. Log file name is generated based on combination of ddmmyyyy.log format.
    //Idea is to have single file for whole day.
    //As day changes file would change to log.

    //Log file name is generated based on combination of ddmmyyyy.log format.
    //Idea is to have single file for whole day.
    //As day changes file would change to log.
    std::string getFileName();

    //Trace log
     void TraceLevelLog(const char* message);

     //Trace log
    void DebugLevelLog(const char* message);

     //Trace log
     void ErrorLevelLog(const char* message);

     //Trace log
     void WarningLevelLog(const char* message);

     //Trace log
     void InfoLevelLog(const char* message);

    // dump data
    void dumpData(const char* logType,const char* message);
        //unlock mutex


    protected:


};



#endif // THREADSAFELOGGER_H
