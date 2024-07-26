#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <limits> 
#include <cstdlib> 

#ifdef _WIN32
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

struct PasswordEntry {
    std::string website;
    std::string username;
    std::string password;
};

struct key {
    int security_key = 0;
};

// Encrypt/Decrypt function
std::string xorEncryptDecrypt(const std::string& input, char unlock_key) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ unlock_key;
    }
    return output;
}

// Key management functions
void setKey(key& k) {
    std::cout << "Enter Security Key: ";
    while (!(std::cin >> k.security_key)) {
        std::cout << "Invalid input. Please enter a valid integer for the security key: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
}

void getKey(const key& k, int input_key) {
    if (input_key == k.security_key) {
        std::cout << "Correct key: " << k.security_key << "\n";
    }
    else {
        std::cout << "Incorrect key!\n";
    }
}

// Password management functions
void addPassword(std::map<std::string, PasswordEntry>& passwords) {
    PasswordEntry entry;
    std::cout << "Enter website: ";
    std::cin >> entry.website;
    std::cout << "Enter username: ";
    std::cin >> entry.username;
    std::cout << "Enter password: ";
    std::cin >> entry.password;

    passwords[entry.website] = entry;

    std::ofstream file("passwords.txt", std::ios::app);
    if (file.is_open()) {
        std::string encryptedPassword = xorEncryptDecrypt(entry.password, 'X');
        file << entry.website << " " << entry.username << " " << encryptedPassword << "\n";
        file.close();
        std::cout << "Password saved successfully!\n";
    }
    else {
        std::cerr << "Unable to open file\n";
    }
}

void getPassword(const std::map<std::string, PasswordEntry>& passwords, const key& k, int& key_temp) {
    std::string website;
    std::cout << "Enter website to retrieve password: ";
    std::cin >> website;
    std::cout << "Insert security key: ";
    while (!(std::cin >> key_temp)) {
        std::cout << "Invalid input. Please enter a valid integer for the security key: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    }
    if (key_temp == k.security_key) {
        auto it = passwords.find(website);
        if (it != passwords.end()) {
            std::cout << "Website: " << it->second.website << "\n";
            std::cout << "Username: " << it->second.username << "\n";
            std::cout << "Password: " << it->second.password << "\n";
        }
        else {
            std::cout << "No entry found for " << website << "\n";
        }
    }
    else {
        std::cout << "Incorrect security key!\n";
    }
}

void loadPasswords(std::map<std::string, PasswordEntry>& passwords) {
    std::ifstream file("passwords.txt");
    if (file.is_open()) {
        PasswordEntry entry;
        while (file >> entry.website >> entry.username >> entry.password) {
            entry.password = xorEncryptDecrypt(entry.password, 'X');
            passwords[entry.website] = entry;
        }
        file.close();
    }
    else {
        std::cerr << "Unable to open file\n";
    }
}

// Windows Function (Clear Screen & Wait for Key Press)
void clearScreen() {
    std::system(CLEAR_COMMAND);
}


void waitForKeyPress() {
    std::cout << "Press any key to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
    std::cin.get();
}

// Main menu function
int main() {
    std::map<std::string, PasswordEntry> passwords;
    loadPasswords(passwords);
    key security_key;
    int key_temp = 0;  

    int choice;
    do {
        clearScreen();  
        std::cout << "1. Set Security Key\n";
        std::cout << "2. Add Password\n";
        std::cout << "3. Get Password\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        while (!(std::cin >> choice)) {
            std::cout << "Invalid input. Please enter a valid integer choice: ";
            std::cin.clear(); 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        }

        clearScreen();  
        switch (choice) {
        case 1:
            setKey(security_key);
            waitForKeyPress();
            break;
        case 2:
            addPassword(passwords);
            waitForKeyPress();  
            break;
        case 3:
            getPassword(passwords, security_key, key_temp);
            waitForKeyPress();  
            break;
        case 4:
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            waitForKeyPress();  
        }
    } while (choice != 4);

    return 0;
}
