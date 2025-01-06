//Appointment Confirmation and Post-Scheduling
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// Helper function to convert 12-hour time format (AM/PM) to minutes
int convertToMinutes(const std::string& timeStr) {
    int hours, minutes;
    std::string ampm;
    std::stringstream ss(timeStr);

    ss >> hours >> std::skipws >> minutes >> ampm;

    if (ampm == "PM" && hours != 12) {
        hours += 12;  // Convert PM to 24-hour format
    } else if (ampm == "AM" && hours == 12) {
        hours = 0;  // Convert 12 AM to 0 hours
    }

    return hours * 60 + minutes;
}

// Helper function to convert minutes into 12-hour time format (AM/PM)
std::string convertToTimeStr(int minutes) {
    int hours = minutes / 60;
    int mins = minutes % 60;
    std::string ampm = "AM";

    if (hours >= 12) {
        if (hours > 12) hours -= 12;  // Convert to 12-hour format
        ampm = "PM";
    } else if (hours == 0) {
        hours = 12;  // 12 AM case
    }

    std::stringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << hours << ":"
               << std::setw(2) << std::setfill('0') << mins << " " << ampm;
    return timeStream.str();
}

// Define the structure for Appointment
struct Appointment {
    int startTime;  // Start time in minutes
    int endTime;    // End time in minutes
    std::string description;
    std::string name;  // Name of the person

    Appointment(int start, int end, std::string desc, std::string n)
        : startTime(start), endTime(end), description(desc), name(n) {}
};

int main() {
    std::unordered_map<std::string, std::vector<Appointment>> specialtyAppointments;  // Appointments by specialty
    int choice;

    do {
        std::cout << "\nAppointment Confirmation and Post-Scheduling \n";
        std::cout << "1. Book Appointment\n";
        std::cout << "2. Print All Appointments\n";
        std::cout << "3. Cancel Appointment\n";
        std::cout << "4. Send Reminder\n";
        std::cout << "5. Collect Feedback\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string fromTime, toTime, description, name;

            std::cout << "Enter Name: ";
            std::cin.ignore();  // Clear the input buffer
            std::getline(std::cin, name);
            std::cout << "Enter(Time): ";
            std::getline(std::cin, fromTime);
            std::cout << "To(Time): ";
            std::getline(std::cin, toTime);
            std::cout << "Enter Appointment Description (e.g., general, dental): ";
            std::getline(std::cin, description);

            int startTime = convertToMinutes(fromTime);
            int endTime = convertToMinutes(toTime);

            // Check if the time slot is available for the specified specialty
            bool isSlotAvailable = true;
            for (const auto& app : specialtyAppointments[description]) {
                if (!(endTime <= app.startTime || startTime >= app.endTime)) {
                    isSlotAvailable = false;
                    break;
                }
            }

            if (isSlotAvailable) {
                Appointment app(startTime, endTime, description, name);
                specialtyAppointments[description].push_back(app);
                std::cout << "Appointment added successfully!\n";
            } else {
                std::cout << "Time slot is already booked for this specialty.\n";
            }
        } else if (choice == 2) {
            std::cout << "\nAppointments:\n";
            for (const auto& [specialty, appointments] : specialtyAppointments) {
                std::cout << "Specialty: " << specialty << "\n";
                for (const auto& app : appointments) {
                    std::cout << "  Name: " << app.name
                              << ", From: " << convertToTimeStr(app.startTime)
                              << ", To: " << convertToTimeStr(app.endTime) << "\n";
                }
            }
        } else if (choice == 3) {
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

            if (!found) {
                std::cout << "Appointment not found.\n";
            }
        } else if (choice == 4) {
            std::string patientName, specialty, time;
            std::cout << "Enter Patient Name: ";
            std::cin.ignore();
            std::getline(std::cin, patientName);
            std::cout << "Enter Specialty (e.g., general, dental): ";
            std::getline(std::cin, specialty);
            std::cout << "Enter Appointment Time: ";
            std::getline(std::cin, time);

            std::cout << "Reminder: " << patientName << ", your " << specialty
                      << " appointment is scheduled for " << time << ".\n";
        } else if (choice == 5) {
            std::string feedback;
            std::cout << "Patient feedback: ";
            std::cin.ignore();  // Clear input buffer
            std::getline(std::cin, feedback);

            if (feedback.find("good") != std::string::npos) {
                std::cout << "Thank you for sharing your feedback with us!\n";
            } else {
                std::cout << "Thank you for sharing your feedback with us!\n";
            }
        }

    } while (choice != 6);

    return 0;
}
