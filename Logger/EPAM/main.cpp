#include <iostream>
#include "ThreadSafeLogger.h"
#include <thread>
#include <string>
#include <vector>
#include <string>
using namespace std;


void init()
{
    std::stringstream ss;
    ss << std::this_thread::get_id();
    int tid = std::stoi(ss.str());
    std::string id ="Testing of log line for EPAM : "+ std::to_string(tid);
    for(size_t i  = 0; i < 3; ++i)
    {
        ThreadSafeLogger::getInstance()->DebugLevelLog(id.c_str());
        ThreadSafeLogger::getInstance()->ErrorLevelLog(id.c_str());
        ThreadSafeLogger::getInstance()->InfoLevelLog(id.c_str());
        ThreadSafeLogger::getInstance()->WarningLevelLog(id.c_str());
        ThreadSafeLogger::getInstance()->TraceLevelLog(id.c_str());
    }

}

int main()
{
    cout<<"Process started"<<endl;
    ThreadSafeLogger::getInstance()->loadConfig();
    cout<<"config loaded"<<endl;

    cout << "==================== logger console starts ====================" << endl;
    std::vector<thread> threads(10); //it should be configurable based on conf

    for(auto& thread : threads)
    {
        thread =std::thread(init);
    }

    for(auto& thread : threads)
    {
        thread.join();
    }

    cout << "==================== logger console ends   ====================" << endl;
    return 0;
}
