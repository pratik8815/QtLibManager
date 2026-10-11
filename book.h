#ifndef BOOK_H
#define BOOK_H
#include <QString>

class Book
{
public:
    Book(QString title = "", int id = 0, int totalCopies = 0, int issuedCopies = 0);

    QString title() const;
    int id() const;
    int totalCopies() const;
    int issuedCopies() const;
    int availableCopies() const;

    void setIssuedCopies(int count);

private:
    QString m_title;
    int m_id;
    int m_totalCopies;
    int m_issuedCopies;
};
#endif // BOOK_H