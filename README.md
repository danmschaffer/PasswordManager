Password Manager in C++
This project is a simple, console-based password manager written in C++. It allows users to securely store and retrieve passwords for various websites using basic encryption.

**Features**
- **Password Storage:** Store website credentials (website, username, password) securely.
- **Encryption:** Encrypts passwords using a simple XOR-based encryption.
- **Security Key:** Protect access to stored passwords with a user-defined security key.
- **File Persistence:** Saves encrypted passwords to a file (passwords.txt) and loads them upon startup.
- **Cross-Platform:** Clears the console screen using platform-specific commands (Windows and Unix-based systems).
**How It Works**
Encryption/Decryption
Passwords are encrypted and decrypted using a simple XOR cipher with a single character key.
```
std::string xorEncryptDecrypt(const std::string& input, char unlock_key) {
    std::string output = input;
    for (size_t i = 0; i < input.size(); ++i) {
        output[i] = input[i] ^ unlock_key;
    }
    return output;
}
```
**Adding a Password**
Users can add new passwords by providing the website, username, and password. The password is encrypted and saved to passwords.txt.

**Retrieving a Password**
Users can retrieve passwords by providing the website and the correct security key. If the key matches, the password is decrypted and displayed.

**Key Management**
Users set a security key that must be used to retrieve passwords. This ensures that only authorized users can access the stored credentials.

**Usage**

**Set Security Key:** Define a security key to protect your passwords.

**Add Password:** Store a new password by providing website, username, and password.

**Get Password:** Retrieve a password by entering the website and the correct security key.

**Exit:** Exit the program.

**Code Structure**
-Main Menu: Provides options to set the security key, add a password, retrieve a password, or exit the program.
-Password Management: Functions to add, retrieve, and load passwords from the file.
-Encryption: Simple XOR-based encryption and decryption.

**Example**
```
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
```
Dependencies
C++ Standard Library

License
This project is licensed under the MIT License.

Feel free to modify this description to better suit your needs!
