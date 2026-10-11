// #include "book.h"

// Book::Book(QString title,int id, bool issued, int issuedTo) : m_title(std::move(title)), m_id(id), m_issued(issued){}

// QString Book::title() const
// {
//     return m_title;
// }

// int Book::id() const
// {
//     return m_id;
// }

// bool Book::isIssued() const
// {
//     return m_issued;
// }

// int Book::issuedTo() const
// {
//     return m_issuedTo;
// }



// void Book::setIssued(bool issued)
// {
//     m_issued = issued;
// }

// void Book::setIssuedTo(int rollNo)
// {
//     m_issuedTo = rollNo;
// }

#include "book.h"

Book::Book(QString title, int id, int totalCopies, int issuedCopies)
    : m_title(std::move(title)), m_id(id), m_totalCopies(totalCopies), m_issuedCopies(issuedCopies)
{
}

QString Book::title() const
{
    return m_title;
}
int Book::id() const
{
    return m_id;
}
int Book::totalCopies() const
{
    return m_totalCopies;
}
int Book::issuedCopies() const
{
    return m_issuedCopies;
}
int Book::availableCopies() const
{
    return m_totalCopies - m_issuedCopies;
}

void Book::setIssuedCopies(int count)
{
    m_issuedCopies = count;
}
