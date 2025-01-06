#include <iostream>
#include <queue>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>
#include <unordered_map>
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
               << std::setw(2) << std::setfill('0') << mins << " " << ampm;
    return timeStream.str();
}

// Struct for patient data (Code 1)
struct Patient {
    std::string name;
    int priority;  // Higher value means higher priority
    std::string condition;

    // Overloading operator for max-heap (priority queue)
    bool operator<(const Patient& other) const {
        return priority < other.priority;  // Higher priority comes first
    }
};

// Function to display the current patients in the priority queue (Code 1)
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

// Function to add a new patient (Code 1)
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

// Function to handle the next patient (Code 1)
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

// Function to check if the queue is empty (Code 1)
bool isQueueEmpty(const std::priority_queue<Patient>& patients) {
    return patients.empty();
}

// Define the structure for Appointment (Codes 2, 3, 4)
struct Appointment {
    int startTime;  // Start time in minutes
    int endTime;    // End time in minutes
    std::string description;
    std::string name;  // Name of the person
    std::string providerName; // Name of the provider

    Appointment(int start, int end, std::string desc, std::string n, std::string provider = "")
        : startTime(start), endTime(end), description(desc), name(n), providerName(provider) {}
};

// AVL Tree Node Definition (Codes 2, 3)
struct AVLNode {
    Appointment appointment;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const Appointment& app)
        : appointment(app), height(1), left(nullptr), right(nullptr) {}
};

// Function to get the height of a node (Codes 2, 3)
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Function to get the balance factor of a node (Codes 2, 3)
int balanceFactor(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Right rotation (Codes 2, 3)
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

// Left rotation (Codes 2, 3)
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

// Function to insert an appointment into the AVL Tree (Codes 2, 3)
AVLNode* insert(AVLNode* node, const Appointment& app) {
    // 1. Perform normal BST insertion
    if (node == nullptr)
        return new AVLNode(app);

    if (app.startTime < node->appointment.startTime)
        node->left = insert(node->left, app);
    else if (app.startTime > node->appointment.startTime)
        node->right = insert(node->right, app);
    else
        return node; // Duplicate start time, no insertion

    // 2. Update height of this ancestor node
    node->height = std::max(height(node->left), height(node->right)) + 1;

    // 3. Get the balance factor to check whether this node became unbalanced
    int balance = balanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases to consider:

    // Left Left Case
    if (balance > 1 && app.startTime < node->left->appointment.startTime)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && app.startTime > node->right->appointment.startTime)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && app.startTime > node->left->appointment.startTime) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && app.startTime < node->right->appointment.startTime) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // return the (unchanged) node pointer
    return node;
}

// Function to print all appointments in the AVL tree (in-order traversal) (Codes 2, 3)
void printAppointments(AVLNode* node) {
    if (node == nullptr)
        return;

    printAppointments(node->left);
    std::cout << "Name: " << node->appointment.name
              << ", From: " << convertToTimeStr(node->appointment.startTime)
              << ", To: " << convertToTimeStr(node->appointment.endTime)
              << ", Description: " << node->appointment.description
              << ", Provider: " << node->appointment.providerName << "\n";
    printAppointments(node->right);
}

// Segment Tree to check and resolve overlapping appointments by description (Code 2)
class SegmentTree {
public:
    SegmentTree(int maxTime) : maxTime(maxTime) {
        tree.resize(4 * maxTime, std::unordered_map<std::string, int>());
    }

        // Function to mark a range as booked for a specific appointment type
    void book(int startTime, int endTime, const std::string& type, int node = 1, int l = 0, int r = 0) {
        if (r == 0) r = maxTime;

        if (startTime >= r || endTime <= l) return;  // No overlap
        if (startTime <= l && r <= endTime) {
            tree[node][type] = 1;  // Mark as fully booked for the specific type
            return;
        }

        int mid = (l + r) / 2;
        book(startTime, endTime, type, 2 * node, l, mid);
        book(startTime, endTime, type, 2 * node + 1, mid, r);
    }

    // Function to check if a time range is free for a specific appointment type
    bool isFree(int startTime, int endTime, const std::string& type, int node = 1, int l = 0, int r = 0) {
        if (r == 0) r = maxTime;

        if (startTime >= r || endTime <= l) return true;  // No overlap
        if (startTime <= l && r <= endTime) return tree[node].find(type) == tree[node].end();  // Fully free for the type

        int mid = (l + r) / 2;
        return isFree(startTime, endTime, type, 2 * node, l, mid) && isFree(startTime, endTime, type, 2 * node + 1, mid, r);
    }

private:
    int maxTime;
    std::vector<std::unordered_map<std::string, int>> tree;
};

// Hash Map to track provider availability (Code 3)
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

// Function to generate hourly time slots based on provider type (Code 3)
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

// Main function to manage patient appointment scheduling (Integrated code)
int main() {
    std::priority_queue<Patient> patientQueue;
    AVLNode* appointmentRoot = nullptr;  // Root of the AVL Tree for appointments
    SegmentTree segmentTree(1440);  // For a day (1440 minutes)
    ProviderAvailability providerAvailability;
    std::unordered_map<std::string, std::vector<Appointment>> specialtyAppointments;  // Appointments by specialty

    // Adjusting available slots for each doctor type (Code 3)
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
        std::cout << "\nPatient Appointment Scheduling:\n";
        std::cout << "1. Patient Prioritization and Emergency Handling\n";
        std::cout << "2. Appointment Scheduling and Slot Management\n";
        std::cout << "3. Patient Self-Scheduling\n";
        std::cout << "4. Appointment Confirmation and Post-Scheduling\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                int subChoice;
                do {
                    std::cout << "\nPatient Prioritization and Emergency Handling:\n";
                    std::cout << "1. Add Patient\n";
                    std::cout << "2. Display Patients\n";
                    std::cout << "3. Handle Next Patient\n";
                    std::cout << "4. Check if Queue is Empty\n";
                    std::cout << "5. Exit\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> subChoice;

                    switch (subChoice) {
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
                            std::cout << "Exiting sub-menu...\n";
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                    }
                } while (subChoice != 5);
                break;
            }
            case 2: {
                int subChoice;
                do {
                                        std::cout << "\nAppointment Scheduling and Slot Management\n";
                    std::cout << "1. Add Appointment\n";
                    std::cout << "2. Print All Appointments\n";
                    std::cout << "3. Check Slot Availability\n";
                    std::cout << "4. Exit\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> subChoice;

                    switch (subChoice) {
                        case 1: {
                            std::string fromTime, toTime, description, name;
                            std::cout << "Enter Name: ";
                            std::cin.ignore();  // Clear the input buffer
                            std::getline(std::cin, name);
                            std::cout << "Enter(Time): ";
                            std::getline(std::cin, fromTime);
                            std::cout << "To(Time): ";
                            std::getline(std::cin, toTime);
                            std::cout << "Enter Appointment Description: ";
                            std::getline(std::cin, description);

                            int startTime = convertToMinutes(fromTime);
                            int endTime = convertToMinutes(toTime);

                            if (segmentTree.isFree(startTime, endTime, description)) {
                                Appointment app(startTime, endTime, description, name);
                                appointmentRoot = insert(appointmentRoot, app);
                                segmentTree.book(startTime, endTime, description);
                                std::cout << "Appointment added successfully!\n";
                            } else {
                                std::cout << "Time slot is already booked.\n";
                            }
                            break;
                        }
                        case 2:
                            std::cout << "\nAppointments:\n";
                            printAppointments(appointmentRoot);
                            break;
                        case 3: {
                            std::string fromTime, toTime, description;
                            std::cout << "Enter(Time): ";
                            std::cin.ignore();  // Clear the input buffer
                            std::getline(std::cin, fromTime);
                            std::cout << "To(Time): ";
                            std::getline(std::cin, toTime);
                            std::cout << "Enter Appointment Description: ";
                            std::getline(std::cin, description);

                            int startTime = convertToMinutes(fromTime);
                            int endTime = convertToMinutes(toTime);

                            if (segmentTree.isFree(startTime, endTime, description)) {
                                std::cout << "Slot is available.\n";
                            } else {
                                std::cout << "Slot is already booked.\n";
                            }
                            break;
                        }
                        case 4:
                            std::cout << "Exiting sub-menu...\n";
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                    }
                } while (subChoice != 4);
                break;
            }
            case 3: {
                int subChoice;
                do {
                    std::cout << "\nSelf-Scheduling Appointments\n";
                    std::cout << "1. Book Appointment\n";
                    std::cout << "2. Print All Appointments\n";
                    std::cout << "3. Exit\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> subChoice;

                    if (subChoice == 1) {
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
                            appointmentRoot = insert(appointmentRoot, app);
                            std::cout << "Appointment placed successfully!\n";
                        } else {
                            std::cout << "The Doctor is not available during the requested time.\n";
                        }
                    } else if (subChoice == 2) {
                        std::cout << "\nAppointments:\n";
                        printAppointments(appointmentRoot);
                    }

                } while (subChoice != 3);
                break;
            }
            case 4: {
                int subChoice;
                do {
                    std::cout << "\nAppointment Confirmation and Post-Scheduling\n";
                    std::cout << "1. Book Appointment\n";
                    std::cout << "2. Print All Appointments\n";
                    std::cout << "3. Cancel Appointment\n";
                    std::cout << "4. Send Reminder\n";
                    std::cout << "5. Collect Feedback\n";
                    std::cout << "6. Exit\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> subChoice;

                    switch (subChoice) {
                        case 1: {
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
                            break;
                        }
                        case 2:
                            std::cout << "\nAppointments:\n";
                            for (const auto& [specialty, appointments] : specialtyAppointments) {
                                std::cout << "Specialty: " << specialty << "\n";
                                for (const auto& app : appointments) {
                                    std::cout << "  Name: " << app.name
                                              << ", From: " << convertToTimeStr(app.startTime)
                                              << ", To: " << convertToTimeStr(app.endTime) << "\n";
                                }
                            }
                            break;
                        case 3: {
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
                            break;
                        }
                        case 4: {
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
                            break;
                        }
                        case 5: {
                            std::string feedback;
                            std::cout << "Patient feedback: ";
                            std::cin.ignore();  // Clear input buffer
                            std::getline(std::cin, feedback);

                            if (feedback.find("good") != std::string::npos) {
                                                                std::cout << "Thank you for sharing your feedback with us!\n";
                            } else {
                                std::cout << "Thank you for sharing your feedback with us!\n";
                            }
                            break;
                        }
                        case 6:
                            std::cout << "Exiting sub-menu...\n";
                            break;
                        default:
                            std::cout << "Invalid choice. Please try again.\n";
                    }
                } while (subChoice != 6);
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
