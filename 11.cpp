#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
    // Part (a): Writing data to the file
    ofstream outFile("grades.txt");
    if (!outFile) {
        cout << "Error creating file!" << endl;
        return 1;
    }

    int n;
    cout << "Enter the number of students: ";
    cin >> n;

    string name;
    int grade;

    for (int i = 0; i < n; ++i) {
        cout << "Enter the name of student " << i + 1 << ": ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter the grade of " << name << ": ";
        cin >> grade;

        // Write data to the file
        outFile << name << " " << grade << endl;
    }

    outFile.close();
    cout << "Data successfully written to 'grades.txt'." << endl;

    // Part (b): Reading data from the file and calculating average grade
    ifstream inFile("grades.txt");
    if (!inFile) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string studentName;
    int studentGrade;
    int totalGrades = 0;
    int count = 0;

    while (inFile >> studentName >> studentGrade) {
        totalGrades += studentGrade;
        ++count;
    }

    inFile.close();

    // Calculate and display the average grade
    if (count > 0) {
        double averageGrade = static_cast<double>(totalGrades) / count;
        cout << "The average grade of the students is: " << averageGrade << endl;
    } else {
        cout << "No data to calculate the average grade." << endl;
    }

    return 0;
}

