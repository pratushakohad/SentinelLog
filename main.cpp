#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    ifstream file("sample.log");
    string line;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    if(file.is_open()){
        while (getline(file,line)){
            cout<<line<<endl;
            if(line.find("[INFO]") != string::npos){
                infoCount++;
            }
            if(line.find("[WARNING]") != string::npos){
                warningCount++;
            }
            if(line.find("[ERROR]") != string::npos){
                errorCount++;
            }
        }
        file.close();
        cout << "\n========== SentinelLog Analysis ==========" << endl;
        cout << "INFO entries  :"<<infoCount << endl;
        cout<< "WARNING entries  :"<<warningCount << endl;
        cout<< "ERROR entries  :"<< errorCount << endl;
        cout<<"Total entries :"<< infoCount + warningCount + errorCount << endl;
    }else{
        cout<<"Unable to open log file !"<<endl;
    }
    return 0;
}