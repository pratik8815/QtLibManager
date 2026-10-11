// #include "library.h"
// #include <QFile>
// #include <QStringList>
// #include <QTextStream>

// Library::Library() {}

// void Library::loadFromCsv(const QString &filename)
// {
//     QFile file(filename);

//     if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//     {
//         return;
//     }

//     QTextStream in(&file);
//     while(!in.atEnd())
//     {
//         QString line = in.readLine();
//         QStringList parts = line.split(",");
//         if(parts.size() == 3)
//         {
//             QString title = parts[0];
//             int id = parts[1].toInt();
//             bool issued = (parts[2].toInt() == 1);
//             m_books.append(Book(title, id, issued));
//         }
//     }
//     file.close();
// }

// void Library::saveToCsv(const QString &filename) const
// {
//     QFile file(filename);

//     if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
//     {
//         return;
//     }

//     QTextStream out(&file);
//     for(const Book &b : m_books)
//     {
//         out << b.title() << "," << b.id() << "," << (b.isIssued() ? 1 : 0) << "\n";
//     }
//     file.close();
// }

// void Library::addBook(const Book &book)
// {
//     m_books.append(book);
// }

// // Book* Library::findBook(int id, const QString &title)
// // {
// //     for(int i  =0; i < m_books.size(); i++)
// //     {
// //         if(m_books[i].id() == id && m_books[i].title() == title)
// //         {
// //             return &m_books[i];
// //         }
// //     }
// //     return nullptr;
// // }

// Book* Library::findBook(int BookId)
// {
//     for(int i = 0; i < m_books.size(); i++)
//     {
//         if(m_books[i].id() == BookId)
//         {
//             return &m_books[i];
//         }
//     }
//     return nullptr;
// }

// bool Library::issuedBook(int bookId, int studentRollNo)
// {
//     Book *book = findBook(bookId);
//     if (book != nullptr && !book->isIssued()) {
//         book->setIssued(true);
//         book->setIssuedTo(studentRollNo);
//         return true;
//     }
//     return false;
// }

// bool Library::returnBook(int bookId, int studentRollNo)
// {
//     Book *book = findBook(bookId);
//     if (book != nullptr && book->isIssued() && book->issuedTo() == studentRollNo) {
//         book->setIssued(false);
//         book->setIssuedTo(-1);
//         return true;
//     }
//     return false;
// }
// // bool Library::issuedBook(int id, const QString &title)
// // {
// //     Book *book = findBook(id, title);
// //     if(book != nullptr && !book->isIssued())
// //     {
// //         book->setIssued(true);
// //         return true;
// //     }
// //     return false;
// // }

// // bool Library::returnBook(int id, const QString &title)
// // {
// //     Book *book = findBook(id, title);
// //     if(book != nullptr && book->isIssued())
// //     {
// //         book->setIssued(false);
// //         return true;
// //     }
// //     return false;
// // }

// QVector<Book> Library::allBooks() const
// {
//     return m_books;
// }

#include "library.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QDebug>

Library::Library()
{

}

// void Library::loadFromCsv(const QString &filename)
// {
//     QFile file(filename); //create a QFile object, doesnt open yet

//     if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) // actualy open the file here
//     {
//         return;  //if it fails (file doesnt exit, etc), just give up silently
//     }

//     QTextStream in(&file);  // wraps the file in a QTextStream for easy line-by-line reading

//     while(!in.atEnd())  // loop until we've read every line
//     {
//         QString line = in.readLine();   //read one line
//         QStringList parts = line.split(","); // split by comma

//         if(parts.size() == 4)
//         {
//             QString title = parts[0];
//             int id = parts[1].toInt();
//             int totalCopies = parts[2].toInt();
//             int issuedCopies = parts[3].toInt();
//             m_books.append(Book(title, id, totalCopies, issuedCopies));
//         }
//     }
//     file.close();
// }

bool Library::openDatabase(const QString &dbPath)
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE"); //registers SQLite as the driver Qt should use

    db.setDatabaseName(dbPath);  //points it at library.db

    if(!db.open())
    {
        qWarning() << "Failed to open database:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    if(!query.exec("CREATE TABLE IF NOT EXISTS books (" "id INTEGER PRIMARY KEY, " "title TEXT NOT NULL, " "totalCopies INTEGER NOT NULL DEFAULT 0, " "issuedCopies INTEGER NOT NULL DEFAULT 0)"))
    {
        qWarning() << "Failed to create table: " << query.lastError().text();
        return false;
    }
    return true;
}

void Library::loadFromDb()
{
    m_books.clear();
    QSqlQuery query("SELECT id, title, totalCopies, issuedCopies FROM books");

    while(query.next())
    {
        int id = query.value(0).toInt();
        QString title = query.value(1).toString();
        int total = query.value(2).toInt();
        int issued = query.value(3).toInt();
        m_books.append(Book(title, id, total, issued));
    }
}

void Library::saveToDb()
{
    QSqlQuery query;

    query.prepare("INSERT INTO books (id, title, totalCopies, issuedCopies) " "VALUES (:id, :title, :total, :issued)" "ON CONFLICT(id) DO UPDATE SET " "title = excluded.title, " "totalCopies = excluded.totalCopies, " "issuedCopies = excluded.issuedCopies");

    for(const Book &b : m_books)
    {
        query.bindValue(":id", b.id());
        query.bindValue(":title" ,b.title());
        query.bindValue(":total", b.totalCopies());
        query.bindValue(":issued", b.issuedCopies());

        if(!query.exec())
        {
            qWarning() << "Failed to save book: " << query.lastError().text();
        }
    }
}
// void Library::saveToCsv(const QString &filename) const
// {
//     QFile file(filename);

//     if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Truncate))
//     {
//         return;
//     }

//     QTextStream out(&file);

//     for(const Book &b : m_books)
//     {
//         out << b.title() << "," << b.id() << "," << b.totalCopies() << "," << b.issuedCopies() << "\n";
//     }

//     file.close();
// }

void Library::addBook(const Book &book)
{
    m_books.append(book);
}

Book* Library::findBook(int bookId)
{
    for(int i = 0; i < m_books.size(); i++)
    {
        if(m_books[i].id() == bookId)
        {
            return &m_books[i];
        }
    }
    return nullptr;
}

bool Library::issuedBook(int bookId)
{
    Book *book = findBook(bookId);

    if (book != nullptr && book->availableCopies() > 0)
    {
         book->setIssuedCopies(book->issuedCopies() + 1);
        return true;
    }

    return false;
}

bool Library::returnBook(int bookId)
{
    Book *book = findBook(bookId);

    if (book != nullptr && book->issuedCopies() > 0)
    {
        book->setIssuedCopies(book->issuedCopies() - 1);
        return true;
    }

    return false;
}

QVector<Book> Library::allBooks() const
{
    return m_books;
}

int Library::totalCopiesCount() const
{
    int total = 0;

    for (const Book &b : m_books)
    {
        total += b.totalCopies();
    }

    return total;
}

int Library::issuedCopiesCount() const
{
    int issued = 0;

    for (const Book &b : m_books)
    {
        issued += b.issuedCopies();
    }

    return issued;
}

int Library::availableCopiesCount() const
{
    return totalCopiesCount() - issuedCopiesCount();
}
