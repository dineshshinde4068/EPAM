#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <sstream>
#include <string>

using namespace std;
class configLoader
{
     private:
        ifstream confFile;
        std::vector<string> vect;
        std::map<string,string> mp;
    public:
        configLoader();
        virtual ~configLoader();

        void readConfig();
        map<string,string> getConf();

};

#endif // CONFIGLOADER_H
