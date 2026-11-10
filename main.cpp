#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include <algorithm>
using namespace std;
struct LogEntry
{
    string timestamp;
    string level;
    string message;
    bool validTimestamp;
};
string detectLogLevel(const string& line)
{
    if (line.find("[INFO]") != string::npos ||
        line.find(" INFO ") != string::npos)
    {
        return "INFO";
    }
    else if (line.find("[WARNING]") != string::npos ||
             line.find(" WARNING ") != string::npos)
    {
        return "WARNING";
    }
    else if (line.find("[ERROR]") != string::npos ||
             line.find(" ERROR ") != string::npos)
    {
        return "ERROR";
    }
    else if (line.find("[DEBUG]") != string::npos ||
             line.find(" DEBUG ") != string::npos)
    {
        return "DEBUG";
    }

    return "Unknown";
}
string detectTimestamp(const string& line)
{
    if (line.length() >= 21 && line[0] == '[' && line[20] == ']')
    {
        return line.substr(1, 19);
    }
    else if (line.length() >= 20 && line[10] == 'T' && line[19] == ' ')
    {
        string timestamp = line.substr(0, 19);
        timestamp[10] = ' ';
        return timestamp;
    }

    return "Unknown";
}
string extractMessage(const string& line)
{
    size_t messageStart;

    if (line.length() >= 21 && line[0] == '[' && line[20] == ']')
    {
        size_t position = line.find("] ", 20);

        if (position == string::npos)
        {
            return line;
        }

        messageStart = position + 2;
    }
    else if (line.length() >= 20 && line[10] == 'T' && line[19] == ' ')
    {
        messageStart = 20;
    }
    else
    {
        return line;
    }

    if (detectLogLevel(line) != "Unknown")
    {
        size_t levelEnd = line.find(" ", messageStart);

        if (levelEnd != string::npos)
        {
            return line.substr(levelEnd + 1);
        }
    }

    return line.substr(messageStart);
}
long long daysFromDate(int year, int month, int day)
{
    year -= (month <= 2);

    int era = (year >= 0 ? year : year - 399) / 400;
    unsigned int yearOfEra = year - era * 400;

    unsigned int dayOfYear =
        (153 * (month + (month > 2 ? -3 : 9)) + 2) / 5 + day - 1;

    unsigned int dayOfEra =
        yearOfEra * 365 + yearOfEra / 4 -
        yearOfEra / 100 + dayOfYear;

    return era * 146097LL + dayOfEra;
}
int main()
{
    map<string, int> ipCount;
    map<string, vector<string>> ipTimestamps;
    map<string, vector<long long>> ipTimeSeconds;
    ifstream file("sample.log");
    string line;
    string timestamp;
    bool validTimestamp = false;
    bool validFormat = true;
    int infoCount = 0;
    int warningCount = 0;
    int errorCount = 0;
    int debugCount = 0;
    int failedLoginCount = 0;
    string ipAddress = " ";
    int totalLines = 0;
    int unclassifiedCount = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            LogEntry  entry;
            totalLines++;
            if (line.find_first_not_of(" \t\r\n") == string::npos)
            {
                continue;
            }
            validFormat = true;
            entry.timestamp = detectTimestamp(line);

if (entry.timestamp != "Unknown")
{
    entry.validTimestamp = true;
}
else
{
    entry.validTimestamp = false;
}
            timestamp = entry.timestamp;
            validTimestamp = entry.validTimestamp;
            if (validTimestamp)
{
    for (int i = 0; i < timestamp.length(); i++)
    {
        if (i == 4 || i == 7)
        {
            if (timestamp[i] != '-')
                validFormat = false;
        }
        else if (i == 10)
        {
            if (timestamp[i] != ' ')
                validFormat = false;
        }
        else if (i == 13 || i == 16)
        {
            if (timestamp[i] != ':')
                validFormat = false;
        }
        else
        {
            if (!isdigit(static_cast<unsigned char>(timestamp[i])))
                validFormat = false;
        }
    }
}
if (!validFormat)
{
    validTimestamp = false;
    timestamp = "Unknown";
}
entry.timestamp = timestamp;
entry.validTimestamp = validTimestamp;
if (validTimestamp && validFormat)
{
    int month = stoi(timestamp.substr(5, 2));
    int day = stoi(timestamp.substr(8, 2));
    int hour = stoi(timestamp.substr(11, 2));
    int minute = stoi(timestamp.substr(14, 2));
    int second = stoi(timestamp.substr(17, 2));

    if (month < 1 || month > 12 ||
        day < 1 || day > 31 ||
        hour < 0 || hour > 23 ||
        minute < 0 || minute > 59 ||
        second < 0 || second > 59)
    {
        validTimestamp = false;
        timestamp = "Unknown";
    }
    if (validTimestamp)
{
    int year = stoi(timestamp.substr(0, 4));

    bool leapYear = (year % 400 == 0) ||
                    (year % 4 == 0 && year % 100 != 0);

    int daysInMonth[] = {
        31, leapYear ? 29 : 28, 31, 30,
        31, 30, 31, 31, 30, 31, 30, 31
    };

    if (year < 1 || day > daysInMonth[month - 1])
    {
        validTimestamp = false;
        timestamp = "Unknown";
    }
}
}
            entry.timestamp = timestamp;
            entry.validTimestamp = validTimestamp;
            long long totalSeconds = -1;

            if (validTimestamp)
            {
                int hour = stoi(timestamp.substr(11, 2));
                int minute = stoi(timestamp.substr(14, 2));
                int second = stoi(timestamp.substr(17, 2));
               int dateYear = stoi(timestamp.substr(0, 4));
int dateMonth = stoi(timestamp.substr(5, 2));
int dateDay = stoi(timestamp.substr(8, 2));

totalSeconds = (daysFromDate(dateYear, dateMonth, dateDay) * 86400LL)
               + (hour * 3600LL)
               + (minute * 60LL)
               + second;
            }
           entry.message = extractMessage(line);
entry.level = detectLogLevel(line);

if (entry.level == "INFO")
{
    infoCount++;
}
else if (entry.level == "WARNING")
{
    warningCount++;
}
else if (entry.level == "ERROR")
{
    errorCount++;
}
else if (entry.level == "DEBUG")
{
    debugCount++;
}
else
{
    unclassifiedCount++;
}
            if (line.find("Failed login attempt") != string::npos)
            {
                failedLoginCount++;
            }
            size_t ipPosition = line.find("from ");
            if (ipPosition != string::npos)
            {
                ipAddress = line.substr(ipPosition + 5);
                ipCount[ipAddress]++;
                if (validTimestamp)
                {
                    ipTimeSeconds[ipAddress].push_back(totalSeconds);
                    ipTimestamps[ipAddress].push_back(timestamp);
                }
            }
        }
            file.close();
            for (auto entry : ipTimeSeconds)
            {
                vector<long long> times = entry.second;
                sort(times.begin(), times.end());
                for (int i = 0; i < times.size(); i++)
                {
                    int attemptsWithinWindow = 1;

                    for (int j = i + 1; j < times.size(); j++)
                    {
                        if (times[j] - times[i] <= 900)
                        {
                            attemptsWithinWindow++;
                        }
                        else
                        {
                            break;
                        }
                    }
                    if (attemptsWithinWindow >= 3)
                    {
                        cout << "ALERT: IP " << entry.first
     << " made 3 or more failed login attempts within 15 minutes!"
     << endl;
                        break;
                    }
                }
            }
            int suspiciousIPCount = 0;
            int highestAttempts = 0;
            string highestRiskIP = "None";

            cout << "\n========== IP Address Analysis ==========" << endl;
            for (auto entry : ipCount)
            {
                cout << "IP Address: " << entry.first
                     << " | Failed Attempts: " << entry.second << endl;
                if (entry.second >= 3)
                {
                    suspiciousIPCount++;
                }
                if (entry.second > highestAttempts)
                {
                    highestAttempts = entry.second;
                    highestRiskIP = entry.first;
                }
                if (entry.second >= 5)
                {
                    cout << "Risk Level: HIGH" << endl;
                }
                else if (entry.second >= 3)
                {
                    cout << "Risk Level: MEDIUM" << endl;
                }
                else
                {
                    cout << "Risk Level: LOW" << endl;
                }
                if (entry.second >= 3)
                {
                    cout << "WARNING: Repeated failed login attempts detected!" << endl;
                    cout << "Source IP: " << entry.first << endl;
                    cout << "Attempts: " << entry.second << endl;
                }
            }
            cout << "\n============ SECURITY SUMMARY =============\n";
            cout << "Total Failed Login Attempts : " << failedLoginCount << endl;
            cout << "Suspicious IP Addresses :" << suspiciousIPCount << endl;
            cout << "Highest Risk IP :" << highestRiskIP << endl;
            cout << "Highest Failed Attempts :" << highestAttempts << endl;
            if (suspiciousIPCount > 0)
            {
                cout << "Overall Security Status : ALERT" << endl;
            }
            else
            {
                cout << "Overall Security Status : NORMAL" << endl;
            }

            cout << "\n========== SentinelLog Analysis ==========" << endl;
            cout << "INFO entries  :" << infoCount << endl;
            cout << "WARNING entries  :" << warningCount << endl;
            cout << "ERROR entries  :" << errorCount << endl;
            cout << "DEBUG entries  :" << debugCount << endl;
            cout << "Failed login attempts  :" << failedLoginCount << endl;
            if (failedLoginCount >= 3)
            {
                cout << "ALERT : Possible suspicious login activity detected!" << endl;
            }
            cout << "Unclassified entries  :" << unclassifiedCount << endl;
            cout << "Total log lines  :" << totalLines << endl;
            cout << "Classified entries :" << infoCount + warningCount + errorCount + debugCount << endl;
        }
         else
        {
            cout << "Unable to open log file !" << endl;
        }
        return 0;
    }