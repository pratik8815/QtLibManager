#ifndef LIBRARY_H
#define LIBRARY_H
#include <QVector>
#include "book.h"

class Library
{
public:

    Library();
    void addBook(const Book &book);
    Book* findBook(int bookId);
    bool issuedBook(int bookId);
    bool returnBook(int bookId);
    QVector<Book> allBooks() const;

    //void loadFromCsv(const QString &filename);
    //void saveToCsv(const QString &filename) const;

    bool openDatabase(const QString &dbPath = "library.db");
    void loadFromDb();
    void saveToDb();

    int totalCopiesCount() const;
    int issuedCopiesCount() const;
    int availableCopiesCount() const;

private:
    QVector<Book> m_books;
};
#endif