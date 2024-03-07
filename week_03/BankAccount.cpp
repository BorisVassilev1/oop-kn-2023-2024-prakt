#include <iostream>
#include <cstring>
#include "BankAccount.hpp"

BankAccount::BankAccount()
    : balance(0),
      iban(new char[1] { '\0' }),
      name(new char[1] { '\0' }) {}

BankAccount::BankAccount(const char* iban, const char* name, double balance)
    : balance(balance),
      iban(new char[std::strlen(iban) + 1] { '\0' }),
      name(new char[std::strlen(name) + 1] { '\0' })
{
    std::strcpy(this->iban, iban);
    std::strcpy(this->name, name);

    this->balance = balance;
}
BankAccount::BankAccount(const BankAccount& other)
{
    this->copy(other);
}
BankAccount& BankAccount::operator = (const BankAccount& other)
{
    if (this != &other)
    {
        this->deallocate();
        this->copy(other);
    }

    return *this;
}

BankAccount::~BankAccount()
{
    this->deallocate();
}

void BankAccount::depositMoney(double sum)
{
    this->balance += sum;
}
void BankAccount::withdrawMoney(double sum)
{
    if (this->balance >= sum)
    {
        this->balance -= sum;
        return;
    }

    std::cout << "Not enough money in the account\n";
}
    
double BankAccount::getBalance() const
{
    return this->balance;
}
void BankAccount::printInfo() const
{
    std::cout << "IBAN: " << this->iban << ", "
        << "Name: " << this->name << ", "
        << "Balance: " << this->balance << std::endl;
}

void BankAccount::copy(const BankAccount& other) 
{
    this->balance = other.balance;

    this->iban = new char[std::strlen(other.iban) + 1] { '\0' };
    std::strcpy(this->iban, other.iban);

    this->name = new char[std::strlen(other.name) + 1] { '\0' };
    std::strcpy(this->name, other.name);
}
void BankAccount::deallocate()
{
    delete[] this->name;
    delete[] this->iban;
}