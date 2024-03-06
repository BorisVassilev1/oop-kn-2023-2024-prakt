#include <iostream>
#include "User.hpp"

int main()
{
    User user;
    
    user.setUsername("tervel4o");
    user.setEmail("gotin@abv.bg");
    user.setAge(26);
    user.setPassword("go6o@ot_po4ivka");

    std::cout << user.getUsername() << ' '
        << user.getEmail() << ' '
        << user.getAge() << " Adult: " << user.isAdult() << '\n'
        << "Password security level: " << user.getPasswordSecurity() << '\n';

    user.writeInFile("user.txt");

    return 0;
}