#include <iostream>
#include <ostream>
#include <cstring>
#include <cassert>
#include <cstddef>

class Book
{
    public:
        Book() {}
        Book(
            const char* title,
            const char* author,
            const char* genre,
            unsigned int pages,
            float rating
        ) : pages(pages)
        {
            assert(
                std::strlen(title) <= 100 &&
                std::strlen(author) <= 100 &&
                std::strlen(genre) <= 50 &&
                0 <= rating && rating <= 10 &&
                "Wrong sizes of arguments"
            );

            std::strcpy(this->title, title);
            std::strcpy(this->author, author);
            std::strcpy(this->genre, genre);
            this->rating = rating;
        }

    friend std::ostream& operator << (std::ostream& out, const Book& book);

    private:
        char title[101];
        char author[101];
        char genre[51];
        unsigned int pages;
        float rating;
};

std::ostream& operator << (std::ostream& out, const Book& book)
{
    out << "Title: " << book.title
        << ", Author: " << book.author
        << ", Genre: " << book.genre
        << ", Pages: " << book.pages
        << ", Rating: " << book.rating << " out of 10";
    
    return out;
}

class Reader
{
    public:
        Reader(
            const char* name,
            std::size_t count = 0,
            Book* books = nullptr
        ) : name(new char[std::strlen(name) + 1]{'\0'}),
            count(count)
        {
            std::strcpy(this->name, name);
            
            if (count > 0 && books != nullptr)
            {
                this->books = new Book[count];
                
                for (std::size_t i = 0; i < count; ++i)
                {
                    this->books[i] = books[i];
                }
            }
        }
        Reader(const Reader& other)
        {
            this->copy(other);
        }
        ~Reader()
        {
            this->deallocate();
        }
        Reader& operator =(const Reader& other)
        {
            if (this != &other)
            {
                this->deallocate();
                this->copy(other);
            }

            return *this;
        }

        Reader& operator += (const Book& newBook)
        {
            Book* copyBooks = new Book[this->count + 1];
            for (std::size_t i = 0; i < this->count; ++i)
            {
                copyBooks[i] = this->books[i];
            }
            copyBooks[this->count] = newBook;
            ++this->count;

            delete[] this->books;
            this->books = copyBooks;

            return *this;
        }

        friend std::ostream& operator << (std::ostream& out, const Reader& reader);

    private:
        void copy(const Reader& other)
        {
            this->name = new char[std::strlen(other.name) + 1] { '\0' };
            std::strcpy(this->name, other.name);

            this->count = other.count;
            this->books = nullptr;

            if (other.books != nullptr) 
            {
                this->books = new Book[this->count];
                for (std::size_t i = 0; i < this->count; ++i)
                {
                    this->books[i] = other.books[i];
                }
            }
        }
        void deallocate()
        {
            delete[] this->books;
            delete[] this->name;
        }

    private:
        char* name;
        std::size_t count;
        Book* books;
};

std::ostream& operator << (std::ostream& out, const Reader& reader)
{
    out << "The reader " << reader.name << " has read the following books:\n";
    
    if (reader.books != nullptr)
    {
        for (std::size_t i = 0; i < reader.count; ++i)
        {
            out << "     " << reader.books[i] << "\n";
        }
    }

    return out;
}

int main()
{
    Book myBook1("gotino zaglavie", "gotin avtor", "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 123, 5.8),
        myBook2("aa", "Traicho", "alt", 107, 6.7);
    std::cout << myBook1 << '\n' << myBook2 << std::endl;

    Reader me("Dis");
    std::cout << me << std::endl;

    me += myBook1;
    me += myBook2;

    std::cout << me << std::endl;


    return 0;
}