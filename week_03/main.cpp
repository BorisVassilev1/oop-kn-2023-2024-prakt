#include <iostream>
#include "BankAccount.hpp"

int main()
{
    BankAccount ba("fjgjrio4983473289", "Tervel Stoyanov", 5), ba2, ba3(ba);

    ba.printInfo();
    ba2.printInfo();
    ba3.printInfo();

    ba.depositMoney(10);
    std::cout << ba.getBalance() << ' '
        << ba3.getBalance() << std::endl;

    ba2 = ba;
    ba2.printInfo();    

    return 0;
}