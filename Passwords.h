#ifndef PASSWORDS_H
#define PASSWORDS_H

#include <string>
#include <iostream>
#include <map>

struct PasswordEntry {
    std::string website;
    std::string username;
    std::string password;
};

struct key {
    int security_key = 0;
};

std::string xorEncryptDecrypt(const std::string& input, char key);
void setKey(key& k);
void getKey(const key& k, int input_key);
void addPassword(std::map<std::string, PasswordEntry>& passwords);
void getPassword(const std::map<std::string, PasswordEntry>& passwords, const key& k);
void loadPasswords(std::map<std::string, PasswordEntry>& passwords);


#endif 
