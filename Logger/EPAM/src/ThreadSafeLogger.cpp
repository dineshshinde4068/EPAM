#include "ThreadSafeLogger.h"

ThreadSafeLogger* ThreadSafeLogger::instance=nullptr;

void ThreadSafeLogger::loadConfig()
{
     std::map<string,string> mmp;
     mmp=cfg.getConf();
     std::map<string,string>::iterator itr=mmp.find("isFileBasedLog");
     if(itr!= mmp.end())
     {
         //cout<<"loading paramaeter isFileBasedLog"<<endl;
         isFileBasedLog=stoi(itr->second);
     }

     //Check whether config loaded properly or not
   /*std::map<string,string>::iterator iitr=mmp.begin();

    for(iitr;iitr!=mmp.end();iitr++)
    {
         cout<<"key "<<iitr->first<< " value "<<iitr->second<<endl;
    }
     */
}


 void ThreadSafeLogger::dumpData(const char* logType,const char* message)
    {
        //Here lock mutex
         std::lock_guard<mutex> lock(mx);
            string str= getTimestamp() + logType + message;
            if(isFileBasedLog)
            {
                logFile.open(getFileName(),std::ios_base::app);

                logFile<<str<<endl;

                logFile.close();
                isFileOpen=false;
            }else
            {
                //code to dump log on console or database side
                cout<<str<<endl;
            }

        //unlock mutex
    }


     void ThreadSafeLogger::TraceLevelLog(const char* message)
    {
        getInstance()->dumpData("[TRACE]    ",message);
    }

     //Trace log
    void ThreadSafeLogger::DebugLevelLog(const char* message)
    {
        //cout << "message=" << message << endl;
        getInstance()->dumpData("[DEBUG]    ",message);
    }

     //Trace log
     void ThreadSafeLogger::ErrorLevelLog(const char* message)
    {
        getInstance()->dumpData("[X ERROR]    ",message);
    }

     //Trace log
     void ThreadSafeLogger::WarningLevelLog(const char* message)
    {
        getInstance()->dumpData("[!WARNING]    ",message);
    }

     //Trace log
     void ThreadSafeLogger::InfoLevelLog(const char* message)
    {
        getInstance()->dumpData("[INFO]    ",message);
    }

    std::string ThreadSafeLogger::getFileName()
    {
        std::time_t t=std::time(nullptr);
        std::tm* now=std::localtime(&t);
        std::string str;
        if(now->tm_mon+1 <10)
        {
              std::ostringstream ss;
              ss << std::setw(2) << std::setfill('0') <<now->tm_mon+1;
              std::string month(ss.str());
              str=to_string(now->tm_mday)+month+to_string(now->tm_year+1900);
        }
        else
              str=to_string(now->tm_mday)+to_string(now->tm_mon+1)+to_string(now->tm_year+1900);

              str=str+".log";
            return str;

    }

    std::string ThreadSafeLogger::getTimestamp()
    {
         std::time_t t=std::time(nullptr);
         std::tm* now=std::localtime(&t);
         std::string str;
         if(now->tm_mon+1 <10)
         {
              std::ostringstream ss;
              ss << std::setw(2) << std::setfill('0') <<now->tm_mon+1;
              std::string month(ss.str());
              str=to_string(now->tm_year+1900)+":"+month+":"+to_string(now->tm_mday)+":"+to_string(now->tm_hour)+":"+to_string(now->tm_min)+":"+to_string(now->tm_sec) + "   ";
         }
         else
              str=to_string(now->tm_year+1900)+":"+to_string(now->tm_mon+1)+":"+to_string(now->tm_mday)+":"+to_string(now->tm_hour)+":"+to_string(now->tm_min)+":"+to_string(now->tm_sec) + "   ";

         return str;

     }


