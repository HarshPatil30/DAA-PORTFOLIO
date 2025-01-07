#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <algorithm>

// Shared Helper Functions
int convertToMinutes(const std::string& timeStr) {
    int hours, minutes;
    std::string ampm;
    std::stringstream ss(timeStr);
    ss >> hours >> std::skipws >> minutes >> ampm;
    if (ampm == "PM" && hours != 12) hours += 12;
    if (ampm == "AM" && hours == 12) hours = 0;
    return hours * 60 + minutes;
}

std::string convertToTimeStr(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    std::string ampm = (hours >= 12) ? "PM" : "AM";
    if (hours > 12) hours -= 12;
    if (hours == 0) hours = 12;
    std::stringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << hours << ":"
               << std::setw(2) << std::setfill('0') << mins << " " << ampm;
    return timeStream.str();
}

// Code 1: Patient Prioritization and Emergency Handling
struct Patient {
    std::string name;
    int priority;
    std::string condition;

    bool operator<(const Patient& other) const {
        return priority < other.priority;
    }
};

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

// Code 2: Appointment Scheduling and Slot Management
struct Appointment {
    int startTime, endTime;
    std::string description, name;
    Appointment(int start, int end, const std::string& desc, const std::string& n)
        : startTime(start), endTime(end), description(desc), name(n) {}
};

void bookAppointment(std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::string fromTime, toTime, description, name;
    std::cout << "\nEnter Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter(Time): ";
    std::getline(std::cin, fromTime);
    std::cout << "To(Time): ";
    std::getline(std::cin, toTime);
    std::cout << "Appointment Description: ";
    std::getline(std::cin, description);

    int startTime = convertToMinutes(fromTime);
    int endTime = convertToMinutes(toTime);
    bool isSlotAvailable = true;

    if (specialtyAppointments.find(description) == specialtyAppointments.end()) {
        specialtyAppointments[description] = {};
    }

    for (const auto& app : specialtyAppointments[description]) {
        if (!(endTime <= app.startTime || startTime >= app.endTime)) {
            isSlotAvailable = false;
            break;
        }
    }

    if (isSlotAvailable) {
        specialtyAppointments[description].emplace_back(startTime, endTime, description, name);
        std::cout << "Appointment added successfully!\n";
    } else {
        std::cout << "Time slot is already booked for this specialty.\n";
    }
}

void printAppointments(const std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::cout << "\nAppointments:\n";
    for (const auto& [specialty, appointments] : specialtyAppointments) {
        std::cout << "Specialty: " << specialty << "\n";
        for (const auto& app : appointments) {
            std::cout << "  Name: " << app.name << ", From: " << convertToTimeStr(app.startTime)
                      << ", To: " << convertToTimeStr(app.endTime) << "\n";
        }
    }
}

void checkSlotAvailability(const std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::string fromTime, toTime, description;
    std::cout << "\nEnter(Time): ";
    std::cin.ignore();
    std::getline(std::cin, fromTime);
    std::cout << "To(Time): ";
    std::getline(std::cin, toTime);
    std::cout << "Appointment Description: ";
    std::getline(std::cin, description);

    int startTime = convertToMinutes(fromTime);
    int endTime = convertToMinutes(toTime);
    bool isFree = true;

    if (specialtyAppointments.find(description) != specialtyAppointments.end()) {
        for (const auto& app : specialtyAppointments.at(description)) {
            if (!(endTime <= app.startTime || startTime >= app.endTime)) {
                isFree = false;
                break;
            }
        }
    } else {
        std::cout << "No appointments exist for this specialty.\n";
        return;
    }

    if (isFree) {
        std::cout << "Slot is available.\n";
    } else {
        std::cout << "Slot is already booked.\n";
    }
}

// Code 3: Patient Self-Scheduling Appointments
void selfScheduleAppointment(std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    bookAppointment(specialtyAppointments);
}

// Code 4: Appointment Confirmation and Post-Scheduling
void cancelAppointment(std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::string name;
    std::cout << "\nEnter Name to cancel appointment: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    bool found = false;
    for (auto& [specialty, appointments] : specialtyAppointments) {
        for (auto it = appointments.begin(); it != appointments.end(); ++it) {
            if (it->name == name) {
                appointments.erase(it);
                std::cout << "Appointment for " << name << " cancelled successfully.\n";
                found = true;
                break;
            }
        }
        if (found) break;
    }

    if (!found) std::cout << "Appointment not found.\n";
}

void sendReminder() {
    std::string patientName, specialty, time;
    std::cout << "\nEnter Patient Name: ";
    std::cin.ignore();
    std::getline(std::cin, patientName);
    std::cout << "Enter Specialty: ";
    std::getline(std::cin, specialty);
    std::cout << "Appointment Time: ";
    std::getline(std::cin, time);

    std::cout << "Reminder: " << patientName << ", your " << specialty
              << " appointment is scheduled for " << time << ".\n";
}

void collectFeedback() {
    std::string feedback;
    std::cout << "\nPatient feedback: ";
    std::cin.ignore();
    std::getline(std::cin, feedback);

    std::cout << "Thank you for sharing your feedback with us!\n";
}

// Main Menu
int main() {
    std::priority_queue<Patient> patientQueue;
    std::unordered_map<std::string, std::vector<Appointment>> specialtyAppointments;
    int choice;

    do {
        std::cout << "\nPatient Appointment Scheduling\n";
        std::cout << "1. Patient Prioritization and Emergency Handling\n";
        std::cout << "2. Appointment Scheduling and Slot Management\n";
        std::cout << "3. Patient Self-Scheduling Appointments\n";
        std::cout << "4. Appointment Confirmation and Post-Scheduling\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int subChoice;
                std::cout << "\n1. Add Patient\n2. Display Patients\n3. Handle Next Patient\nEnter sub-choice: ";
                std::cin >> subChoice;
                if (subChoice == 1) addPatient(patientQueue);
                else if (subChoice == 2) displayPatients(patientQueue);
                else if (subChoice == 3) handleNextPatient(patientQueue);
                else std::cout << "Invalid sub-choice.\n";
                break;
            }
            case 2: {
                int subChoice;
                std::cout << "\n1. Book Appointment\n2. Print All Appointments\n3. Check Slot Availability\nEnter sub-choice: ";
                std::cin >> subChoice;
                if (subChoice == 1) bookAppointment(specialtyAppointments);
                else if (subChoice == 2) printAppointments(specialtyAppointments);
                else if (subChoice == 3) checkSlotAvailability(specialtyAppointments);
                else std::cout << "Invalid sub-choice.\n";
                break;
            }
            case 3: {
                selfScheduleAppointment(specialtyAppointments);
                break;
            }
            case 4: {
                int subChoice;
                std::cout << "\n1. Cancel Appointment\n2. Send Reminder\n3. Collect Feedback\nEnter sub-choice: ";
                std::cin >> subChoice;
                if (subChoice == 1) cancelAppointment(specialtyAppointments);
                else if (subChoice == 2) sendReminder();
                else if (subChoice == 3) collectFeedback();
                else std::cout << "Invalid sub-choice.\n";
                break;
            }
            case 5:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}
