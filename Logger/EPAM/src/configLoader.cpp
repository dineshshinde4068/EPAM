#include "configLoader.h"

configLoader::configLoader()
{
    //ctor
}

configLoader::~configLoader()
{
    //dtor
}

map<string,string> configLoader::getConf()
{
  return mp;
}
void configLoader::readConfig()
{
    confFile.open("conf.properties",std::ios::in);
    if (confFile.is_open())
    {
        std::string line;
        while(getline(confFile,line))
        {
            //cout<<line<<endl;
            vect.push_back(line);// either tokenize string before = ,and after = and store inside map.
            stringstream check1(line);
            string intermediate;
            int i=0;
            std::string sArr[2];
            std::string key;
            std::string value;
            while(getline(check1,intermediate,'='))
            {
                    //cout<<intermediate<<endl;

                    if(i==0){
                        key=intermediate;
                        i++;
                    }else if(i==1)
                    {
                        value=intermediate;
                        i++;
                    }
                    if(i==2)
                    {
                        //cout<<"key : "<<key<< " value "<<value<<endl;
                        mp.insert(make_pair(key,value));
                        i=0;
                        key.clear();
                        value.clear();
                    }
            }
        }
    }else
    {
            cout<<"file not found"<<endl;
    }

    confFile.close();

}
