#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

// Enum for Patient Priority (High, Medium, Low)
enum class PatientPriority {
    High,   // Emergency, ICU
    Medium, // General
    Low     // Non-urgent cases
};

// Class to manage the reservation system
class BedReservationSystem {
private:
    std::unordered_map<std::string, int> availableBeds;  // Bed Type -> Available Beds
    std::unordered_map<int, std::pair<std::string, PatientPriority>> reservations; // PatientID -> {BedType, Priority}

public:
    // Add or update bed availability for a specific bed type
    void updateAvailableBeds(const std::string& bedType, int count) {
        availableBeds[bedType] = count;
    }

    // Reserve a bed for a patient based on priority and available beds
    bool reserveBed(int patientID, const std::string& bedType, PatientPriority priority) {
        if (availableBeds[bedType] > 0) {
            availableBeds[bedType]--;
            reservations[patientID] = {bedType, priority};
            std::cout << "Patient " << patientID << " reserved a " << bedType << " bed.\n";
            return true;
        } else {
            std::cout << "No available " << bedType << " beds for Patient " << patientID << ".\n";
            return false;
        }
    }

    // Cancel a reservation for a patient
    bool cancelReservation(int patientID) {
        auto it = reservations.find(patientID);
        if (it != reservations.end()) {
            availableBeds[it->second.first]++;
            reservations.erase(it);
            std::cout << "Reservation for Patient " << patientID << " has been cancelled.\n";
            return true;
        } else {
            std::cout << "No reservation found for Patient " << patientID << ".\n";
            return false;
        }
    }

    // Display available beds for each bed type
    void displayAvailableBeds() {
        std::cout << "\nAvailable Beds:\n";
        for (const auto& entry : availableBeds) {
            std::cout << "Bed Type: " << entry.first << ", Available Beds: " << entry.second << "\n";
        }
    }

    // Display current reservations
    void displayReservations() {
        std::cout << "\nCurrent Reservations:\n";
        for (const auto& entry : reservations) {
            std::cout << "Patient " << entry.first << " - Bed Type: " << entry.second.first
                      << ", Priority: " << (entry.second.second == PatientPriority::High ? "High" :
                                           entry.second.second == PatientPriority::Medium ? "Medium" : "Low") << "\n";
        }
    }
};

// Function to add/update bed availability
void updateBedAvailability(BedReservationSystem& system) {
    std::string bedType;
    int bedCount;
    std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
    std::cin >> bedType;
    std::cout << "Enter the number of available beds: ";
    std::cin >> bedCount;
    system.updateAvailableBeds(bedType, bedCount);
    std::cout << "Bed availability updated successfully.\n";
}

// Function to reserve a bed for a patient
void reserveBed(BedReservationSystem& system) {
    int patientID;
    std::string bedType;
    int priorityInput;
    std::cout << "Enter Patient ID: ";
    std::cin >> patientID;
    std::cout << "Enter Bed Type (e.g., ICU, General, Emergency): ";
    std::cin >> bedType;
    std::cout << "Enter Patient Priority (0: High, 1: Medium, 2: Low): ";
    std::cin >> priorityInput;

    PatientPriority priority = static_cast<PatientPriority>(priorityInput);
    system.reserveBed(patientID, bedType, priority);
}

// Function to cancel a reservation
void cancelReservation(BedReservationSystem& system) {
    int patientID;
    std::cout << "Enter Patient ID to cancel reservation: ";
    std::cin >> patientID;
    system.cancelReservation(patientID);
}

// Function to display available beds
void displayBeds(BedReservationSystem& system) {
    system.displayAvailableBeds();
}

// Function to display current reservations
void displayReservations(BedReservationSystem& system) {
    system.displayReservations();
}

int main() {
    BedReservationSystem system;
    int choice;

    do {
        std::cout << "\n--- Bed Reservation and Scheduling System ---\n";
        std::cout << "1. Update Bed Availability\n";
        std::cout << "2. Reserve Bed for Patient\n";
        std::cout << "3. Cancel Bed Reservation\n";
        std::cout << "4. Display Available Beds\n";
        std::cout << "5. Display Current Reservations\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            updateBedAvailability(system);
            break;
        case 2:
            reserveBed(system);
            break;
        case 3:
            cancelReservation(system);
            break;
        case 4:
            displayBeds(system);
            break;
        case 5:
            displayReservations(system);
            break;
        case 6:
            std::cout << "Exiting program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}

