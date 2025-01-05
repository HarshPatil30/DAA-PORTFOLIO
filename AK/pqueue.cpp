#include <iostream>
#include <queue>
#include <string>
#include <vector>

// Struct for patient data
struct Patient {
    std::string name;
    int priority;  // Higher value means higher priority
    std::string condition;

    // Overloading operator for max-heap (priority queue)
    bool operator<(const Patient& other) const {
        return priority < other.priority;  // Higher priority comes first
    }
};

// Function to display the current patients in the priority queue
void displayPatients(const std::priority_queue<Patient>& patients) {
    if (patients.empty()) {
        std::cout << "\nNo patients in the queue.\n";
        return;
    }

    std::cout << "\nCurrent Patients in Priority Queue:\n";
    std::priority_queue<Patient> tempQueue = patients;  // Make a copy to preserve the original
    while (!tempQueue.empty()) {
        const Patient& patient = tempQueue.top();
        std::cout << "Name: " << patient.name
                  << ", Emergency: " << patient.priority
                  << ", Medical issue: " << patient.condition << "\n";
        tempQueue.pop();
    }
}

// Function to add a new patient
void addPatient(std::priority_queue<Patient>& patients) {
    Patient newPatient;
    std::cout << "\nEnter patient details:\n";
    std::cout << "Name: ";
    std::cin.ignore();  // Clear input buffer
    std::getline(std::cin, newPatient.name);
    std::cout << "Emergency: ";
    std::cout << "(1: Low Urgency, 10: Critical): ";
    std::cin >> newPatient.priority;
    std::cout << "Medical issue: ";
    std::cin.ignore();  // Clear input buffer
    std::getline(std::cin, newPatient.condition);

    patients.push(newPatient);
    std::cout << "Patient added successfully!\n";
}

// Function to handle the next patient
void handleNextPatient(std::priority_queue<Patient>& patients) {
    if (patients.empty()) {
        std::cout << "\nNo patients to handle.\n";
        return;
    }

    const Patient& nextPatient = patients.top();
    std::cout << "\nHandling next patient:\n";
    std::cout << "Name: " << nextPatient.name
              << ", Emergency: " << nextPatient.priority
              << ", Medical issue: " << nextPatient.condition << "\n";

    patients.pop();  // Remove the patient from the queue
}

// Function to check if the queue is empty
bool isQueueEmpty(const std::priority_queue<Patient>& patients) {
    return patients.empty();
}

int main() {
    std::priority_queue<Patient> patientQueue;
    int choice;

    do {
        std::cout << "\n\nPatient Prioritization and Emergency Handling:\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. Display Patients\n";
        std::cout << "3. Handle Next Patient\n";
        std::cout << "4. Check if Queue is Empty\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addPatient(patientQueue);
                break;
            case 2:
                displayPatients(patientQueue);
                break;
            case 3:
                handleNextPatient(patientQueue);
                break;
            case 4:
                if (isQueueEmpty(patientQueue)) {
                    std::cout << "\nThe queue is empty.\n";
                } else {
                    std::cout << "\nThe queue is not empty.\n";
                }
                break;
            case 5:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
