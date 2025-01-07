//Appointment Confirmation and Post-Scheduling
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// Helper function to convert 12-hour time format to minutes
int convertToMinutes(const std::string& timeStr) {
    int hours, minutes;
    std::string ampm;
    std::stringstream ss(timeStr);

    ss >> hours >> std::skipws >> minutes >> ampm;
    if (ampm == "PM" && hours != 12) hours += 12;
    if (ampm == "AM" && hours == 12) hours = 0;

    return hours * 60 + minutes;
}

// Helper function to convert minutes to 12-hour time format
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

struct Appointment {
    int startTime, endTime;
    std::string description, name;

    Appointment(int start, int end, std::string desc, std::string n)
        : startTime(start), endTime(end), description(desc), name(n) {}
};

void bookAppointment(std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::string fromTime, toTime, description, name;

    std::cout << "Enter Name: ";
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

void cancelAppointment(std::unordered_map<std::string, std::vector<Appointment>>& specialtyAppointments) {
    std::string name;
    std::cout << "Enter Name to cancel appointment: ";
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
    std::cout << "Enter Patient Name: ";
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
    std::cout << "Patient feedback: ";
    std::cin.ignore();
    std::getline(std::cin, feedback);

    std::cout << "Thank you for sharing your feedback with us!\n";
}

int main() {
    std::unordered_map<std::string, std::vector<Appointment>> specialtyAppointments;
    int choice;

    do {
        std::cout << "\nAppointment Confirmation and Post-Scheduling \n"
                  << "1. Book Appointment\n"
                  << "2. Print All Appointments\n"
                  << "3. Cancel Appointment\n"
                  << "4. Send Reminder\n"
                  << "5. Collect Feedback\n"
                  << "6. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                bookAppointment(specialtyAppointments);
                break;
            case 2:
                printAppointments(specialtyAppointments);
                break;
            case 3:
                cancelAppointment(specialtyAppointments);
                break;
            case 4:
                sendReminder();
                break;
            case 5:
                collectFeedback();
                break;
            case 6:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
