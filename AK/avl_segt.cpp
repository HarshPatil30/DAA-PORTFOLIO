// Appointment Scheduling and Slot Management

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <unordered_map>

// Convert 12-hour time format (AM/PM) to minutes
int convertToMinutes(const std::string& timeStr) {
    int hours, minutes;
    std::string ampm;
    std::stringstream ss(timeStr);
    ss >> hours >> std::skipws >> minutes >> ampm;
    if (ampm == "PM" && hours != 12) hours += 12;
    else if (ampm == "AM" && hours == 12) hours = 0;
    return hours * 60 + minutes;
}

// Convert minutes into 12-hour time format (AM/PM)
std::string convertToTimeStr(int minutes) {
    int hours = minutes / 60, mins = minutes % 60;
    std::string ampm = (hours >= 12) ? "PM" : "AM";
    if (hours > 12) hours -= 12;
    else if (hours == 0) hours = 12;
    std::stringstream timeStream;
    timeStream << std::setw(2) << std::setfill('0') << hours << ":"
               << std::setw(2) << std::setfill('0') << mins << " " << ampm;
    return timeStream.str();
}

struct Appointment {
    int startTime, endTime;
    std::string description, name;
    Appointment(int start, int end, const std::string& desc, const std::string& n)
        : startTime(start), endTime(end), description(desc), name(n) {}
};

struct AVLNode {
    Appointment appointment;
    int height;
    AVLNode *left, *right;
    AVLNode(const Appointment& app) : appointment(app), height(1), left(nullptr), right(nullptr) {}
};

int height(AVLNode* node) { return node ? node->height : 0; }
int balanceFactor(AVLNode* node) { return node ? height(node->left) - height(node->right) : 0; }

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

// Insert new appointment into AVL Tree
AVLNode* insert(AVLNode* node, const Appointment& app) {
    if (!node) return new AVLNode(app);

    // Insert in the correct subtree
    if (app.startTime < node->appointment.startTime) {
        node->left = insert(node->left, app);
    } else if (app.startTime > node->appointment.startTime) {
        node->right = insert(node->right, app);
    } else {
        return node;  // Duplicate appointment, no need to insert
    }

    // Update height of current node
    node->height = 1 + std::max(height(node->left), height(node->right));

    // Balance the node if needed
    int balance = balanceFactor(node);

    // Left-heavy situation
    if (balance > 1 && app.startTime < node->left->appointment.startTime)
        return rightRotate(node);

    // Right-heavy situation
    if (balance < -1 && app.startTime > node->right->appointment.startTime)
        return leftRotate(node);

    // Left-right situation
    if (balance > 1 && app.startTime > node->left->appointment.startTime) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right-left situation
    if (balance < -1 && app.startTime < node->right->appointment.startTime) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Print all appointments (in-order traversal)
void printAppointments(AVLNode* node) {
    if (!node) return;
    printAppointments(node->left);
    std::cout << "Name: " << node->appointment.name
              << ", From: " << convertToTimeStr(node->appointment.startTime)
              << ", To: " << convertToTimeStr(node->appointment.endTime)
              << ", Description: " << node->appointment.description << "\n";
    printAppointments(node->right);
}

class SegmentTree {
public:
    SegmentTree(int maxTime) : maxTime(maxTime) {
        tree.resize(4 * maxTime);
    }

    void book(int startTime, int endTime, const std::string& type, int node = 1, int l = 0, int r = 0) {
        if (!r) r = maxTime;
        if (startTime >= r || endTime <= l) return;
        if (startTime <= l && r <= endTime) {
            tree[node][type] = 1;
            return;
        }
        int mid = (l + r) / 2;
        book(startTime, endTime, type, 2 * node, l, mid);
        book(startTime, endTime, type, 2 * node + 1, mid, r);
    }

    bool isFree(int startTime, int endTime, const std::string& type, int node = 1, int l = 0, int r = 0) {
        if (!r) r = maxTime;
        if (startTime >= r || endTime <= l) return true;
        if (startTime <= l && r <= endTime) return tree[node].find(type) == tree[node].end();
        int mid = (l + r) / 2;
        return isFree(startTime, endTime, type, 2 * node, l, mid) && isFree(startTime, endTime, type, 2 * node + 1, mid, r);
    }

private:
    int maxTime;
    std::vector<std::unordered_map<std::string, int>> tree;
};

int main() {
    AVLNode* root = nullptr;
    SegmentTree segmentTree(1440);
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
            std::cin.ignore();
            std::getline(std::cin, fromTime);
            std::cout << "To(Time): ";
            std::getline(std::cin, toTime);
            std::cout << "Appointment Description: ";
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
