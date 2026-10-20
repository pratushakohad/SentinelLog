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
    int totalLines = 0;
    int unclassifiedCount = 0;
    if(file.is_open()){
        while (getline(file,line)){
            cout<<line<<endl;
            totalLines++;
            if(line.find("[INFO]") != string::npos){
                infoCount++;
            }
            else if(line.find("[WARNING]") != string::npos){
                warningCount++;
            }
            else if(line.find("[ERROR]") != string::npos){
                errorCount++;
            }
            else{
                unclassifiedCount++;
            }
        }
        file.close();
        cout << "\n========== SentinelLog Analysis ==========" << endl;
        cout << "INFO entries  :"<<infoCount << endl;
        cout<< "WARNING entries  :"<<warningCount << endl;
        cout<< "ERROR entries  :"<< errorCount << endl;
        cout<< "Unclassified entries  :"<< unclassifiedCount << endl;
        cout<< "Total log lines  :"<< totalLines << endl;
        cout<<"Classified entries :"<< infoCount + warningCount + errorCount << endl;
    }else{
        cout<<"Unable to open log file !"<<endl;
    }
    return 0;
}