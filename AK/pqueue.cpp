/Patient Prioritization and Emergency Handling
#include <iostream>
#include <queue>
#include <string>

struct Patient {
    std::string name;
    int priority;
    std::string condition;

    bool operator<(const Patient& other) const {
        return priority < other.priority;
    }
};

void displayPatients(std::priority_queue<Patient> patients) {
    if (patients.empty()) {
        std::cout << "\nNo patients in the queue.\n";
        return;
    }
    std::cout << "\nCurrent Patients in Priority Queue:\n";
    while (!patients.empty()) {
        const Patient& patient = patients.top();
        std::cout << "Name: " << patient.name
                  << ", Emergency: " << patient.priority
                  << ", Medical issue: " << patient.condition << "\n";
        patients.pop();
    }
}

void addPatient(std::priority_queue<Patient>& patients) {
    Patient newPatient;
    std::cout << "\nEnter patient details:\n";
    std::cout << "Name: ";
    std::cin.ignore();
    std::getline(std::cin, newPatient.name);
    std::cout << "Emergency (1: Low Urgency, 10: Critical): ";
    std::cin >> newPatient.priority;
    std::cout << "Medical issue: ";
    std::cin.ignore();
    std::getline(std::cin, newPatient.condition);
    patients.push(newPatient);
    std::cout << "Patient added successfully!\n";
}

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
    patients.pop();
}

bool isQueueEmpty(const std::priority_queue<Patient>& patients) {
    return patients.empty();
}

int main() {
    std::priority_queue<Patient> patientQueue;
    int choice;
    while (true) {
        std::cout << "\n\nPatient Prioritisation and Emergency Handling:\n";
        std::cout << "1. Add Patient\n";
        std::cout << "2. Display Patients\n";
        std::cout << "3. Handle Next Patient\n";
        std::cout << "4. Check if Queue is Empty\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        if (choice == 5) break;
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
                std::cout << (isQueueEmpty(patientQueue) ? "\nThe queue is empty.\n" : "\nThe queue is not empty.\n");
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    std::cout << "Exiting program...\n";
    return 0;
}
}
