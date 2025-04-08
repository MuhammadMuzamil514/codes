#include <iostream>
using namespace std;

int main() {
    const int MONTHS = 12;
    double rainfall[MONTHS];
    double totalRainfall = 0.0, averageRainfall;
    int highestMonth = 0, lowestMonth = 0;

    // Input rainfall data
    for (int i = 0; i < MONTHS; i++) {
        do {
            cout << "Enter the rainfall for month " << (i + 1) << ": ";
            cin >> rainfall[i];
            if (rainfall[i] < 0) {
                cout << "Rainfall cannot be negative. Please re-enter.\n";
            }
        } while (rainfall[i] < 0);

        // Add to total rainfall
        totalRainfall += rainfall[i];

        // Check for highest and lowest rainfall
        if (rainfall[i] > rainfall[highestMonth]) {
            highestMonth = i;
        }
        if (rainfall[i] < rainfall[lowestMonth]) {
            lowestMonth = i;
        }
    }

    // Calculate average rainfall
    averageRainfall = totalRainfall / MONTHS;

    // Output results
    cout << "\nTotal rainfall for the year: " << totalRainfall << endl;
    cout << "Average monthly rainfall: " << averageRainfall << endl;
    cout << "Month with the highest rainfall: Month " << (highestMonth + 1) << " with " << rainfall[highestMonth] << endl;
    cout << "Month with the lowest rainfall: Month " << (lowestMonth + 1) << " with " << rainfall[lowestMonth] << endl;

    return 0;
}

