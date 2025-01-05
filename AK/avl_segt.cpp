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

// Function to print all appointments in the AVL tree (in-order traversal)
void printAppointments(AVLNode* node) {
    if (node == nullptr)
        return;

    printAppointments(node->left);
    std::cout << "Name: " << node->appointment.name
              << ", From: " << convertToTimeStr(node->appointment.startTime)
              << ", To: " << convertToTimeStr(node->appointment.endTime)
              << ", Description: " << node->appointment.description << "\n";
    printAppointments(node->right);
}

// Segment Tree to check and resolve overlapping appointments by description
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

// Main function to manage appointment scheduling
int main() {
    AVLNode* root = nullptr;  // Root of the AVL Tree
    SegmentTree segmentTree(1440);  // For a day (1440 minutes)

    int choice;
    do {
        std::cout << "\nAppointment Scheduling and Slot Management\n";
        std::cout << "1. Add Appointment\n";
        std::cout << "2. Print All Appointments\n";
        std::cout << "3. Check Slot Availability\n";
        std::cout << "4. Exit\n";
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
            std::cout << "Enter Appointment Description: ";
            std::getline(std::cin, description);

            int startTime = convertToMinutes(fromTime);
            int endTime = convertToMinutes(toTime);

            if (segmentTree.isFree(startTime, endTime, description)) {
                Appointment app(startTime, endTime, description, name);
                root = insert(root, app);
                segmentTree.book(startTime, endTime, description);
                std::cout << "Appointment added successfully!\n";
            } else {
                std::cout << "Time slot is already booked.\n";
            }
        }
        else if (choice == 2) {
            std::cout << "\nAppointments:\n";
            printAppointments(root);
        }
        else if (choice == 3) {
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
        }

    } while (choice != 4);

    return 0;
}
