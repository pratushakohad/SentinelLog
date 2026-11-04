#include<map>
#include<iostream>
#include<fstream>
#include<string>
using namespace std;
int main(){
    map<string, int> ipCount;
    ifstream file("sample.log");
    string line;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    int debugCount = 0;
    int failedLoginCount = 0;
    string ipAddress = " ";
    int totalLines = 0;
    int unclassifiedCount = 0;
    if(file.is_open()){
        while (getline(file,line)){
            cout<<line<<endl;
            totalLines++;
            if (line.find_first_not_of(" \t\r\n") == string::npos) {
            continue;
            }
            if(line.find("[INFO]") != string::npos){
                infoCount++;
            }
            else if(line.find("[WARNING]") != string::npos){
                warningCount++;
            }
            else if(line.find("[ERROR]") != string::npos){
                errorCount++;
            }
            else if(line.find("[DEBUG]") != string::npos){
                debugCount++;
            }
            else{
                unclassifiedCount++;
            }
            if(line.find("Failed login attempt") != string::npos){
                failedLoginCount++;
            }
            size_t ipPosition = line.find("from ");
            if (ipPosition !=string::npos){
                ipAddress = line.substr(ipPosition + 5);
                cout << "Detected IP Address: "<<ipAddress <<endl;
            ipCount[ipAddress]++;
            }
        }
        file.close();
        cout << "\n========== IP Address Analysis ==========" << endl;

        for(auto entry : ipCount){
        cout << "IP Address: " << entry.first
         << " | Failed Attempts: " << entry.second << endl;

        if(entry.second >= 3){
        cout << "WARNING: Repeated failed login attempts detected!" << endl;
        cout << "Source IP: " << entry.first << endl;
        cout << "Attempts: " << entry.second << endl;
            }
        }
        cout << "\n========== SentinelLog Analysis ==========" << endl;
        cout << "INFO entries  :"<<infoCount << endl;
        cout<< "WARNING entries  :"<<warningCount << endl;
        cout<< "ERROR entries  :"<< errorCount << endl;
        cout<< "DEBUG entries  :"<< debugCount << endl;
        cout<< "Failed login attempts  :"<< failedLoginCount << endl;
        if(failedLoginCount >=3){
            cout << "ALERT : Possible suspicious login activity detected!"<< endl;
        }
        cout<< "Unclassified entries  :"<< unclassifiedCount << endl;
        cout<< "Total log lines  :"<< totalLines << endl;
        cout<<"Classified entries :"<< infoCount + warningCount + errorCount + debugCount << endl;
    }else{
        cout<<"Unable to open log file !"<<endl;
    }
    return 0;
}