#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cmath>
#include <stdexcept>

using namespace std;

struct Student {
    string id;
    string name;
    int age;
    string grade;
    string major;
    
    // Constructor with default values
    Student() : id(""), name(""), age(0), grade(""), major("") {}
};

// Function to trim whitespace
string trim(const string& str) {
    size_t first = str.find_first_not_of(" \t\n\r\"");
    if (first == string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r\"");
    return str.substr(first, (last - first + 1));
}

// Parse JSON manually (improved implementation)
vector<Student> parseJSON(const string& filename) {
    vector<Student> students;
    ifstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not open " << filename << endl;
        return students;
    }
    
    string line;
    Student current;
    bool inObject = false;
    
    while (getline(file, line)) {
        line = trim(line);
        
        if (line == "{") {
            inObject = true;
            current = Student();
        }
        else if (line == "}" || line == "},") {
            if (inObject && !current.id.empty()) {
                students.push_back(current);
                inObject = false;
            }
        }
        else if (inObject) {
            size_t colonPos = line.find(":");
            if (colonPos != string::npos) {
                string key = trim(line.substr(0, colonPos));
                string value = trim(line.substr(colonPos + 1));
                
                // Remove trailing comma
                if (!value.empty() && value.back() == ',') {
                    value = value.substr(0, value.length() - 1);
                }
                value = trim(value);
                
                if (key == "\"id\"") {
                    current.id = value;
                }
                else if (key == "\"name\"") {
                    current.name = value;
                }
                else if (key == "\"age\"") {
                    try {
                        current.age = stoi(value);
                    } catch (const invalid_argument& e) {
                        cerr << "Warning: Invalid age value '" << value << "' for student. Using 0." << endl;
                        current.age = 0;
                    } catch (const out_of_range& e) {
                        cerr << "Warning: Age value '" << value << "' out of range. Using 0." << endl;
                        current.age = 0;
                    }
                }
                else if (key == "\"grade\"") {
                    current.grade = value;
                }
                else if (key == "\"major\"") {
                    current.major = value;
                }
            }
        }
    }
    
    file.close();
    return students;
}

// Calculate average age
double calculateAverageAge(const vector<Student>& students) {
    if (students.empty()) return 0.0;
    
    int sum = 0;
    for (const auto& student : students) {
        sum += student.age;
    }
    return static_cast<double>(sum) / students.size();
}

// Calculate age standard deviation
double calculateAgeStdDev(const vector<Student>& students, double avg) {
    if (students.size() <= 1) return 0.0;
    
    double sum = 0.0;
    for (const auto& student : students) {
        sum += pow(student.age - avg, 2);
    }
    return sqrt(sum / students.size());
}

// Count students by major
map<string, int> countByMajor(const vector<Student>& students) {
    map<string, int> majorCounts;
    for (const auto& student : students) {
        string major = trim(student.major);
        majorCounts[major]++;
    }
    return majorCounts;
}

// Count students by grade
map<string, int> countByGrade(const vector<Student>& students) {
    map<string, int> gradeCounts;
    for (const auto& student : students) {
        string grade = trim(student.grade);
        gradeCounts[grade]++;
    }
    return gradeCounts;
}

// Find youngest and oldest students
pair<Student, Student> findAgeExtremes(const vector<Student>& students) {
    if (students.empty()) {
        return make_pair(Student(), Student());
    }
    
    Student youngest = students[0];
    Student oldest = students[0];
    
    for (const auto& student : students) {
        if (student.age < youngest.age) youngest = student;
        if (student.age > oldest.age) oldest = student;
    }
    
    return make_pair(youngest, oldest);
}

// Sort students by age (for output)
vector<Student> sortByAge(vector<Student> students) {
    sort(students.begin(), students.end(), 
         [](const Student& a, const Student& b) {
             return a.age < b.age;
         });
    return students;
}

// Display statistics
void displayStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students found in the database!" << endl;
        return;
    }
    
    cout << "========================================" << endl;
    cout << "   STUDENT STATISTICS REPORT" << endl;
    cout << "========================================" << endl << endl;
    
    // Total count
    cout << "Total Students: " << students.size() << endl << endl;
    
    // Age statistics
    double avgAge = calculateAverageAge(students);
    double stdDev = calculateAgeStdDev(students, avgAge);
    
    cout << "AGE STATISTICS:" << endl;
    cout << "  Average Age: " << fixed << setprecision(2) << avgAge << " years" << endl;
    cout << "  Standard Deviation: " << fixed << setprecision(2) << stdDev << endl;
    
    pair<Student, Student> extremes = findAgeExtremes(students);
    Student youngest = extremes.first;
    Student oldest = extremes.second;
    
    if (!students.empty()) {
        cout << "  Youngest: " << trim(youngest.name) << " (Age: " << youngest.age << ")" << endl;
        cout << "  Oldest: " << trim(oldest.name) << " (Age: " << oldest.age << ")" << endl << endl;
    }
    
    // Distribution by Major
    map<string, int> majorCounts = countByMajor(students);
    cout << "DISTRIBUTION BY MAJOR:" << endl;
    for (const auto& pair : majorCounts) {
        double percentage = (static_cast<double>(pair.second) / students.size()) * 100;
        cout << "  " << pair.first << ": " << pair.second << " (" 
             << fixed << setprecision(1) << percentage << "%)" << endl;
    }
    cout << endl;
    
    // Distribution by Grade
    map<string, int> gradeCounts = countByGrade(students);
    cout << "DISTRIBUTION BY GRADE:" << endl;
    for (const auto& pair : gradeCounts) {
        double percentage = (static_cast<double>(pair.second) / students.size()) * 100;
        cout << "  " << pair.first << ": " << pair.second << " (" 
             << fixed << setprecision(1) << percentage << "%)" << endl;
    }
    cout << endl;
    
    cout << "========================================" << endl;
    cout << "  Report generated successfully!" << endl;
    cout << "========================================" << endl;
}

// Save detailed report to file
void saveDetailedReport(const vector<Student>& students, const string& filename) {
    ofstream file(filename);
    
    if (!file.is_open()) {
        cerr << "Error: Could not create report file!" << endl;
        return;
    }
    
    file << "DETAILED STUDENT REPORT" << endl;
    file << "==============================================" << endl << endl;
    
    vector<Student> sortedStudents = sortByAge(students);
    
    file << left << setw(15) << "ID" 
         << setw(25) << "Name" 
         << setw(8) << "Age" 
         << setw(10) << "Grade" 
         << setw(20) << "Major" << endl;
    file << string(78, '-') << endl;
    
    for (const auto& student : sortedStudents) {
        file << left << setw(15) << trim(student.id)
             << setw(25) << trim(student.name)
             << setw(8) << student.age
             << setw(10) << trim(student.grade)
             << setw(20) << trim(student.major) << endl;
    }
    
    file.close();
    cout << "\nDetailed report saved to: " << filename << endl;
}

int main() {
    // Read students from JSON file
    vector<Student> students = parseJSON("students.json");
    
    if (students.empty()) {
        cout << "No students found or error reading file!" << endl;
        return 1;
    }
    
    // Display statistics
    displayStatistics(students);
    
    // Save detailed report
    saveDetailedReport(students, "student_report.txt");
    
    return 0;
}
