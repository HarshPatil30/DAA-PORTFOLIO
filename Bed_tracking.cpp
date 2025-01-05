#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

class BedAvailabilityTracker {
private:
    // HospitalID -> BedType -> Available Beds
    unordered_map<int, unordered_map<string, int>> hospitalBeds;

public:
    // Add or update bed availability for a hospital
    void updateBedCount(int hospitalID, const string& bedType, int count) {
        hospitalBeds[hospitalID][bedType] = count;
        cout << "Updated: Hospital " << hospitalID << ", Bed Type: "
             << bedType << ", Available Beds: " << count << "\n";
    }

    // Get the number of available beds for a specific hospital and bed type
    int getAvailableBeds(int hospitalID, const string& bedType) {
        if (hospitalBeds.find(hospitalID) != hospitalBeds.end() &&
            hospitalBeds[hospitalID].find(bedType) != hospitalBeds[hospitalID].end()) {
            return hospitalBeds[hospitalID][bedType];
        }
        return 0; // Default to 0 if not found
    }

    // Get hospitals with available beds of a specific type
    vector<int> getHospitalsWithAvailableBeds(const string& bedType) {
        vector<int> result;
        for (const auto& [hospitalID, beds] : hospitalBeds) {
            if (beds.find(bedType) != beds.end() && beds.at(bedType) > 0) {
                result.push_back(hospitalID);
            }
        }
        return result;
    }

    // Display all hospital bed availability
    void displayAllBeds() {
        cout << "\nHospital Bed Availability:\n";
        for (const auto& [hospitalID, beds] : hospitalBeds) {
            cout << "Hospital " << hospitalID << ":\n";
            for (const auto& [bedType, count] : beds) {
                cout << "  " << bedType << ": " << count << " beds available\n";
            }
        }
    }
};

int main() {
    BedAvailabilityTracker tracker;
    int choice;

    do {
        cout << "\n--- Bed Availability Tracker ---\n";
        cout << "1. Update Bed Count\n";
        cout << "2. Query Bed Count\n";
        cout << "3. Get Hospitals with Available Beds\n";
        cout << "4. Display All Bed Availability\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int hospitalID, count;
            string bedType;
            cout << "Enter Hospital ID: ";
            cin >> hospitalID;
            cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            cin >> bedType;
            cout << "Enter Number of Beds: ";
            cin >> count;
            tracker.updateBedCount(hospitalID, bedType, count);
            break;
        }
        case 2: {
            int hospitalID;
            string bedType;
            cout << "Enter Hospital ID: ";
            cin >> hospitalID;
            cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            cin >> bedType;
            int availableBeds = tracker.getAvailableBeds(hospitalID, bedType);
            cout << "Available Beds in Hospital " << hospitalID
                 << " (" << bedType << "): " << availableBeds << "\n";
            break;
        }
        case 3: {
            string bedType;
            cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
            cin >> bedType;
            vector<int> hospitals = tracker.getHospitalsWithAvailableBeds(bedType);
            if (!hospitals.empty()) {
                cout << "Hospitals with available " << bedType << " beds:\n";
                for (int hospitalID : hospitals) {
                    cout << "  Hospital " << hospitalID << "\n";
                }
            } else {
                cout << "No hospitals with available " << bedType << " beds.\n";
            }
            break;
        }
        case 4:
            tracker.displayAllBeds();
            break;
        case 5:
            cout << "Exiting program. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
