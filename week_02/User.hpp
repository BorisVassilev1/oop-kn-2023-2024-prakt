#ifndef USER_HPP
#define USER_HPP

class User
{
public:
    const char* getUsername() const;
    const char* getEmail() const;
    unsigned int getAge() const;

    void setUsername(const char* username);
    void setEmail(const char* email);
    void setAge(unsigned int age);
    void setPassword(const char* password);

    bool isAdult() const;
    unsigned int getPasswordSecurity() const;

    bool writeInFile(const char* fileName) const;

private:
    bool isValidEmail(const char* str) const;
    bool isSpecialSymbol(char c) const;
    bool isDigit(char c) const;

private:
    enum GENDER {
        UNKNOWN = -1,

        MALE,
        FEMALE,
        OTHER,

        GENDER_COUNT
    };

private:
    char username[64];
    char email[101];
    unsigned int age;
    char password[32];
    GENDER gender;
};

#endif