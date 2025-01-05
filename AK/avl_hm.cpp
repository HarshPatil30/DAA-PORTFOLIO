#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <algorithm>

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
               << std::setw(2) << std::setfill('0') << mins << ampm;
    return timeStream.str();
}

// Define the structure for Appointment
struct Appointment {
    int startTime;  // Start time in minutes
    int endTime;    // End time in minutes
    std::string name;
    std::string providerName;
    std::string description;  // Type of appointment (e.g., general, dental, etc.)

    Appointment(int start, int end, const std::string& patientName, const std::string& provider, const std::string& desc)
        : startTime(start), endTime(end), name(patientName), providerName(provider), description(desc) {}
};

// AVL Tree Node Definition
struct AVLNode {
    Appointment appointment;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Appointment& app)
        : appointment(app), height(1), left(nullptr), right(nullptr) {}
};

// Function to get the height of a node
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Function to get the balance factor of a node
int balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation
AVLNode* rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;

    return x;
}

// Left rotation
AVLNode* leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;

    return y;
}

// Function to insert an appointment into the AVL Tree
AVLNode* insert(AVLNode* node, const Appointment& app) {
    if (node == nullptr)
        return new AVLNode(app);

    if (app.startTime < node->appointment.startTime)
        node->left = insert(node->left, app);
    else if (app.startTime > node->appointment.startTime)
        node->right = insert(node->right, app);
    else
        return node; // Duplicate start time, no insertion

    node->height = std::max(height(node->left), height(node->right)) + 1;

    int balance = balanceFactor(node);

    if (balance > 1 && app.startTime < node->left->appointment.startTime)
        return rightRotate(node);

    if (balance < -1 && app.startTime > node->right->appointment.startTime)
        return leftRotate(node);

    if (balance > 1 && app.startTime > node->left->appointment.startTime) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && app.startTime < node->right->appointment.startTime) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to print all appointments in the AVL tree (in-order traversal)
void printAppointments(AVLNode* node) {
    if (node == nullptr)
        return;

    printAppointments(node->left);
    std::cout << "From: " << convertToTimeStr(node->appointment.startTime)
              << ", To: " << convertToTimeStr(node->appointment.endTime)
              << ", Name: " << node->appointment.name
              << ", Provider: " << node->appointment.providerName
              << ", Description: " << node->appointment.description << "\n";
    printAppointments(node->right);
}

// Hash Map to track provider availability
class ProviderAvailability {
public:
    std::unordered_map<std::string, std::vector<int>> providerSchedule;
    std::unordered_map<std::string, std::vector<std::string>> providerSpecialization;

    void addProvider(const std::string& providerName, const std::vector<int>& availableSlots, const std::vector<std::string>& specializations) {
        providerSchedule[providerName] = availableSlots;
        providerSpecialization[providerName] = specializations;
    }

    bool isAvailable(const std::string& providerName, int startTime, int endTime) {
        if (providerSchedule.find(providerName) == providerSchedule.end()) {
            return false;  // Provider not found
        }
        const auto& slots = providerSchedule[providerName];
        for (int i = 0; i < slots.size() - 1; i++) {
            if (startTime >= slots[i] && endTime <= slots[i + 1]) {
                return true;
            }
        }
        return false;
    }

    std::vector<std::string> getDoctorsBySpecialization(const std::string& specialization) {
        std::vector<std::string> doctors;
        for (const auto& entry : providerSpecialization) {
            const std::vector<std::string>& specializations = entry.second;
            if (std::find(specializations.begin(), specializations.end(), specialization) != specializations.end()) {
                doctors.push_back(entry.first);
            }
        }
        return doctors;
    }

    std::vector<int> getAvailableSlots(const std::string& providerName) {
        if (providerSchedule.find(providerName) != providerSchedule.end()) {
            return providerSchedule[providerName];
        }
        return {};
    }
};

// Function to generate hourly time slots based on provider type
std::vector<int> generateDoctorSpecificSlots(const std::string& specialization) {
    std::vector<int> slots;

    if (specialization == "ENT" || specialization == "Dermatologist") {
        // Available hours for ENT, Dermatologists: 10:00 AM - 7:00 PM
        slots.push_back(600);  // 10:00 AM
        slots.push_back(1140); // 7:00 PM
    } else if (specialization == "Urologist" || specialization == "Psychiatrist" || specialization == "Gynaecologist") {
        // Available hours for Urologists, Psychiatrists, Gynaecologists: 12:00 PM - 5:00 PM
        slots.push_back(720);  // 12:00 PM
        slots.push_back(1020); // 5:00 PM
    } else {
        // Available hours for other doctors (Pediatricians, Dentists, General Physicians): 9:00 AM - 7:00 PM
        slots.push_back(540);  // 9:00 AM
        slots.push_back(1140); // 7:00 PM
    }

    return slots;
}

int main() {
    ProviderAvailability providerAvailability;
    AVLNode* root = nullptr;

    // Adjusting available slots for each doctor type
    providerAvailability.addProvider("Dr. James", generateDoctorSpecificSlots("Pediatrician"), {"Pediatrician"});
    providerAvailability.addProvider("Dr. Nadia", generateDoctorSpecificSlots("Pediatrician"), {"Pediatrician"});
    providerAvailability.addProvider("Dr. Emily", generateDoctorSpecificSlots("General physician"), {"General physician"});
    providerAvailability.addProvider("Dr. Kumar", generateDoctorSpecificSlots("Urologist"), {"Urologist"});
    providerAvailability.addProvider("Dr. Sarah", generateDoctorSpecificSlots("Psychiatrist"), {"Psychiatrist"});
    providerAvailability.addProvider("Dr. Smith", generateDoctorSpecificSlots("Psychiatrist"), {"Psychiatrist"});
    providerAvailability.addProvider("Dr. Patel", generateDoctorSpecificSlots("Dentist"), {"Dentist"});
    providerAvailability.addProvider("Dr. Sofia", generateDoctorSpecificSlots("Dentist"), {"Dentist"});
    providerAvailability.addProvider("Dr. Ellen", generateDoctorSpecificSlots("Dermatologist"), {"Dermatologist"});
    providerAvailability.addProvider("Dr. Olivia", generateDoctorSpecificSlots("ENT"), {"ENT"});
    providerAvailability.addProvider("Dr. Abhay", generateDoctorSpecificSlots("ENT"), {"ENT"});
    providerAvailability.addProvider("Dr. Jacob", generateDoctorSpecificSlots("General physician"), {"General physician"});
    providerAvailability.addProvider("Dr. Riya", generateDoctorSpecificSlots("Gynaecologist"), {"Gynaecologist"});

    int choice;
    do {
        std::cout << "\nSelf-Scheduling Appointments \n";
        std::cout << "1. Book Appointment\n";
        std::cout << "2. Print All Appointments\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            std::string name, providerName, description;
            std::string startTimeStr, endTimeStr;

            std::cout << "Enter Name: ";
            std::cin.ignore();
            std::getline(std::cin, name);

            std::cout << "Enter Appointment Description: ";
            std::cout << "(Dentist|Dermatologist|ENT|General Physician|Gynaecologist|Pediatrician|Psychiatrist|Urologist|Others): ";
            std::getline(std::cin, description);

            if (description == "Others") {
                std::cout << "Contact the clinic to schedule an appointment.\n";
                continue;
            }

            std::vector<std::string> doctors = providerAvailability.getDoctorsBySpecialization(description);
            std::cout << "Available Doctors: \n";
            for (const auto& doctor : doctors) {
                std::cout << doctor << "\n";
            }

            std::cout << "Select preferred doctor: ";
            std::getline(std::cin, providerName);

            std::vector<int> availableSlots = providerAvailability.getAvailableSlots(providerName);
            std::cout << "Available time slots for " << providerName << ": " << convertToTimeStr(availableSlots[0]) << " - " << convertToTimeStr(availableSlots[1]) << "\n";

            std::cout << "Time(start): ";
            std::getline(std::cin, startTimeStr);

            std::cout << "Time(end): ";
            std::getline(std::cin, endTimeStr);

            int startTime = convertToMinutes(startTimeStr);
            int endTime = convertToMinutes(endTimeStr);

            if (providerAvailability.isAvailable(providerName, startTime, endTime)) {
                Appointment app(startTime, endTime, name, providerName, description);
                root = insert(root, app);
                std::cout << "Appointment placed successfully!\n";
            } else {
                std::cout << "The Doctor is not available during the requested time.\n";
            }
        } else if (choice == 2) {
            std::cout << "\nAppointments:\n";
            printAppointments(root);
        }

    } while (choice != 3);

    return 0;
}