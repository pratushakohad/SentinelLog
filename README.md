# SentinelLog

**A C++-based cybersecurity log analysis tool that detects suspicious login activity and identifies potentially risky IP addresses.**

## About the Project

SentinelLog is a beginner-friendly cybersecurity project developed using C++. It reads and analyzes log files to identify security-related events, monitor failed login attempts, and detect potentially suspicious activity.

The project supports custom application logs and Linux Syslog entries. It also performs IP address analysis and detects repeated failed login attempts within a 15-minute time window.

## Features

### Log File Processing
- Reads log files line by line.
- Handles missing or inaccessible log files.
- Handles blank lines and unclassified log entries.
- Extracts timestamps from supported log formats.

### Log Analysis
- Classifies log entries into INFO, WARNING, ERROR, and DEBUG categories.
- Counts total log lines and classified entries.
- Identifies unclassified entries.
- Counts failed login attempts.

### Linux Syslog Parsing
- Parses Syslog priority values.
- Extracts severity numbers and maps them to project log categories.
- Extracts timestamps, hostnames, process names, process IDs, and messages.
- Handles invalid Syslog priority values and process IDs.

### IP Address Analysis
- Extracts source IP addresses from failed login messages.
- Counts failed login attempts for each IP address.
- Assigns LOW, MEDIUM, and HIGH risk levels.
- Identifies repeated failed login attempts.

### Suspicious Activity Detection
- Detects three or more failed login attempts within a 15-minute window.
- Generates alerts for suspicious login activity.
- Displays a security summary containing total failed attempts, suspicious IP addresses, highest-risk IP, and overall security status.

## Technologies Used

- **Language:** C++
- **Compiler:** GCC (g++)
- **Editor:** Visual Studio Code
- **Concepts:** File Handling, String Processing, Maps, Vectors, Functions, Sorting, and Time-Based Analysis.
- **Version Control:** Git and GitHub

## Project Structure

```text
SentinelLog/
│
├── main.cpp
├── sample.log
├── README.md
├── .gitignore
│
└── tests/
    ├── 15min_test.log
    ├── duplicate_time_test.log
    ├── exact_15min_test.log
    ├── missing_level.log
    ├── syslog_test.log
    └── two_attempts_test.log
```

## How to Run

### Prerequisites

- Windows operating system
- GCC C++ compiler
- Visual Studio Code (recommended)

### 1. Clone the Repository

```bash
git clone https://github.com/pratushakohad/SentinelLog.git
```

### 2. Open the Project Folder

```bash
cd SentinelLog
```

### 3. Compile the Program

```bash
g++ main.cpp -o SentinelLog
```

### 4. Run the Program

```powershell
.\SentinelLog.exe
```

Make sure `sample.log` is present in the project folder because it is the default input file.

## Test Cases

The `tests` folder contains sample log files designed to check different parts of SentinelLog.

| Test File | Purpose |
|---|---|
| `15min_test.log` | Tests failed login attempts inside and outside a 15-minute window. |
| `duplicate_time_test.log` | Tests multiple attempts with identical timestamps. |
| `exact_15min_test.log` | Tests the exact 900-second boundary. |
| `missing_level.log` | Tests log entries with missing severity labels. |
| `syslog_test.log` | Tests Linux Syslog parsing and severity handling. |
| `two_attempts_test.log` | Tests whether two failed attempts avoid the 15-minute alert. |

### Running a Test File

The program currently reads `sample.log` by default.

To test another file, temporarily change the input filename in `main.cpp`.

For example:

```cpp
ifstream file("tests/syslog_test.log");
```

Compile and run the program again. Replace the filename with the test file you want to examine.

After testing, restore the original input:

```cpp
ifstream file("sample.log");
```

## Project Status

**Active Development**

SentinelLog is an ongoing learning and development project. Its current focus is improving log parsing, security analysis, and suspicious activity detection.

## Future Improvements

- Apache log parsing.
- Nginx log parsing.
- Improved IP address validation.
- More advanced threat detection.
- Better analysis reports and user interface.

## Learning Goals

This project aims to develop practical knowledge of:

- C++ programming and problem-solving.
- File handling and string manipulation.
- Data structures such as maps and vectors.
- Log parsing and analysis.
- Basic cybersecurity concepts.
- Git and GitHub version control.

---

**Author:** Pratusha Kohad

**GitHub Repository:** https://github.com/pratushakohad/SentinelLog