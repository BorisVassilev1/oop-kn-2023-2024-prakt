#include <cstring>
#include <cstddef>
#include <fstream>
#include <iostream>

#include "User.hpp"

const char* User::getUsername() const
{
    return this->username;
}

const char* User::getEmail() const
{
    return this->email;
}

unsigned int User::getAge() const
{
    return this->age;
}

void User::setUsername(const char* username)
{
    if (std::strlen(username) < 64)
    {
        std::strcpy(this->username, username);
        return;
    }

    std::cout << "Too long username\n";
}

void User::setEmail(const char* email)
{
    if (this->isValidEmail(email))
    {
        std::strcpy(this->email, email);
        return;
    }

    std::cout << "Invalid email\n";
}

void User::setAge(unsigned int age)
{
    this->age = age;
}

void User::setPassword(const char* password)
{
    if (std::strlen(password))
    {
        std::strcpy(this->password, password);
        return;
    }

    std::cout << "Too long password\n";
}

bool User::isAdult() const
{
    return this->age >= 18;
}

unsigned int User::getPasswordSecurity() const
{
    std::size_t size = std::strlen(this->password);

    unsigned int securityLevel = 0;
    if (size > 10)
    {
        ++securityLevel;
    }

    bool usedDigits[] = {
        false, false, false, false, false,
        false, false, false, false, false
    };

    for (std::size_t i = 0; i < size; ++i)
    {
        if (this->isSpecialSymbol(this->password[i]))
        {
            ++securityLevel;
        } else if (
            this->isDigit(this->password[i]) &&
            usedDigits[this->password[i] - '0'] == false
        ) {
            ++securityLevel;
            usedDigits[this->password[i] - '0'] = true;
        }
    }

    return securityLevel;
}

bool User::writeInFile(const char* fileName) const
{
    std::ofstream out(fileName);

    if (!out.is_open())
    {
        std::cout << "Error while opening file...\n";
        return false;
    }

    out << this->username << ' '
        << this->email << ' '
        << this->password << ' '
        << this->age << '\n';
    out.close();
    
    return true;
}

bool User::isValidEmail(const char* email) const
{
    std::size_t size = std::strlen(email);
    if (size > 100)
    {
        return false;
    }

    std::size_t pos = 0;
    while (isSpecialSymbol(email[pos]) == false)
    {
        ++pos;
    }
    
    if (email[pos] != '@')
    {
        return false;
    }
    
    ++pos;
    while (isSpecialSymbol(email[pos]) == false)
    {
        ++pos;
    }
    
    return pos == size;
}

// Alphabet: a-z,A-Z,0-9,-,_,.
bool User::isSpecialSymbol(char c) const
{
    return !(
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        isDigit(c) || c == '-' ||
        c == '_' || c == '.'
    );
}

bool User::isDigit(char c) const
{
    return c >= '0' && c <= '9';
}
