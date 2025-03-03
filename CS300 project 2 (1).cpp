#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

// Course structure to store details about each course
struct Course {
    string courseNum; // Course number
    string courseName; // Course name
    vector<string> PreReqs; // List of prerequisites

    // Default constructor
    Course() : courseNum(""), courseName("") {}

    // Constructor for course initialization
    Course(string aCourseNum, string aCourseName) {
        courseNum = aCourseNum;
        courseName = aCourseName;
    }
};

// Hash table (unordered_map) to store the courses by their course number
unordered_map<string, Course> courseTable;

// Function to load courses from a CSV file
bool loadCoursesCSV(const string& filename) {
    ifstream file(filename); // Open the file

    if (!file.is_open()) { // Check if the file opened successfully
        cout << "Error opening the file." << endl;
        return false;
    }

    string line;
    while (getline(file, line)) { // Read each line from the file
        stringstream ss(line); // Create a stringstream to parse the line
        string courseNum, courseName;
        string prereq;
        vector<string> prereqs; // List to hold prerequisites

        // Extract course number and course name from the line
        getline(ss, courseNum, ',');
        getline(ss, courseName, ',');

        // Read all prerequisites (if any) after the course name
        while (getline(ss, prereq, ',')) {
            prereqs.push_back(prereq); // Add each prerequisite to the list
        }

        // Create a Course object and insert it into the hash table
        Course course(courseNum, courseName);
        course.PreReqs = prereqs; // Assign prerequisites
        courseTable[courseNum] = course; // Insert the course into the table
    }

    file.close(); // Close the file
    return true;
}

// Function to print the details of a specific course
void printCourse(const string& courseNum) {
    if (courseTable.find(courseNum) != courseTable.end()) { // Check if the course exists in the table
        Course course = courseTable[courseNum]; // Retrieve the course from the table
        cout << course.courseNum << ", " << course.courseName << endl;
        cout << "Prerequisites: ";

        if (course.PreReqs.empty()) { // If no prerequisites, display "None"
            cout << "None" << endl;
        }
        else { // Otherwise, print the prerequisites
            for (const string& prereq : course.PreReqs) {
                cout << prereq << " ";
            }
            cout << endl;
        }
    }
    else { // If course not found
        cout << "Course not found." << endl;
    }
}

// Function to print the list of all courses
void printCourseList() {
    cout << "Here is a sample schedule: " << endl;
    for (const auto& coursePair : courseTable) { // Iterate over the hash table
        cout << coursePair.second.courseNum << ", " << coursePair.second.courseName << endl;
    }
}

int main() {
    int choice;
    bool dataLoaded = false; // Flag to track if data has been loaded

    // Main menu loop
    do {
        // Display the menu options
        cout << "Welcome to the course planner. " << endl;
        cout << "1. Load Data Structure. " << endl;
        cout << "2. Print Course List. " << endl;
        cout << "3. Print Course. " << endl;
        cout << "9. Exit " << endl;
        cout << "What would you like to do? ";
        cin >> choice;

        // Switch case to handle the user's choice
        switch (choice) {
        case 1: { // Load data structure option
            if (!dataLoaded) { // Check if data is already loaded
                if (loadCoursesCSV("CS 300 ABCU_Advising_Program_Input.csv")) { // Load courses from file
                    cout << "Courses loaded successfully." << endl;
                    dataLoaded = true; // Set dataLoaded flag to true
                }
                else {
                    cout << "Failed to load courses from the file." << endl;
                }
            }
            else { // If data is already loaded
                cout << "Data is already loaded." << endl;
            }
            break;
        }
        case 2: { // Print course list option
            if (dataLoaded) { // Check if data is loaded
                printCourseList(); // Print the list of all courses
            }
            else {
                cout << "Please load the data structure first." << endl;
            }
            break;
        }
        case 3: { // Print specific course option
            if (dataLoaded) { // Check if data is loaded
                string courseNum;
                cout << "What course do you want to know about? ";
                cin >> courseNum; // Get the course number from user
                printCourse(courseNum); // Print the course details
            }
            else {
                cout << "Please load the data structure first." << endl;
            }
            break;
        }
        case 9: { // Exit option
            cout << "Thank you for using the course planner!" << endl;
            break;
        }
        default: { // Invalid option
            cout << choice << " is not a valid option. " << endl;
            break;
        }
        }
    } while (choice != 9); // Repeat until the user chooses to exit

    return 0;
}
