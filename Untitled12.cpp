#include <iostream>
#include <fstream>
using namespace std;

int main() {
    // Create an ofstream object to handle file output
    ofstream outFile("student.txt");

    // Check if the file is successfully opened
    if (!outFile) {
        cout << "Error creating file!" << endl;
        return 1;
    }

    // Take input for three students
    string student1, student2, student3;
    cout << "Enter the name of the first student: ";
    getline(cin, student1);
    cout << "Enter the name of the second student: ";
    getline(cin, student2);
    cout << "Enter the name of the third student: ";
    getline(cin, student3);

    // Write the student names to the file
    outFile << "Student 1: " << student1 << endl;
    outFile << "Student 2: " << student2 << endl;
    outFile << "Student 3: " << student3 << endl;

    // Close the file
    outFile.close();

    cout << "Data successfully written to 'student.txt'." << endl;

    return 0;
}

