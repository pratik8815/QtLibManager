// #include "booklistdialog.h"
// #include "ui_booklistdialog.h"
// #include <booklistdialog.h>
// #include <QTableWidgetItem>

// BookListDialog::BookListDialog(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::BookListDialog)
// {
//     ui->setupUi(this);
// }

// BookListDialog::~BookListDialog()
// {
//     delete ui;
// }

// void BookListDialog::showBooks(const QVector<Book> &books)
// {
//     ui->tableWidgetBook->setRowCount(books.size());
//     ui->tableWidgetBook->setColumnCount(3);

//     QStringList headers;
//     headers << "Title" << "Roll No" << "Issued";
//     ui->tableWidgetBook->setHorizontalHeaderLabels(headers);

//     for(int i = 0; i < books.size(); i++)
//     {
//         ui->tableWidgetBook->setItem(i, 0, new QTableWidgetItem(books[i].title()));
//         ui->tableWidgetBook->setItem(i, 1, new QTableWidgetItem(QString::number(books[i].id())));
//         ui->tableWidgetBook->setItem(i, 2, new QTableWidgetItem(books[i].isIssued() ? "Yes" : "No"));
//     }
// }
#include "booklistdialog.h"
#include "ui_booklistdialog.h"
#include <QTableWidgetItem>

BookListDialog::BookListDialog(QWidget *parent) : QDialog(parent)    , ui(new Ui::BookListDialog)
{
    ui->setupUi(this);
}

BookListDialog::~BookListDialog()
{
    delete ui;
}

void BookListDialog::showBooks(const QVector<Book> &books)
{
    ui->tableWidgetBook->setRowCount(books.size());
    ui->tableWidgetBook->setColumnCount(5);

    QStringList headers;
    headers << "Title" << "Book ID" << "Total Copies" << "Issued" << "Available";
    ui->tableWidgetBook->setHorizontalHeaderLabels(headers);

    for(int i = 0; i < books.size(); i++)
    {
        ui->tableWidgetBook->setItem(i, 0, new QTableWidgetItem(books[i].title()));
        ui->tableWidgetBook->setItem(i, 1, new QTableWidgetItem(QString::number(books[i].id())));
        ui->tableWidgetBook->setItem(i, 2, new QTableWidgetItem(QString::number(books[i].totalCopies())));
        ui->tableWidgetBook->setItem(i, 3, new QTableWidgetItem(QString::number(books[i].issuedCopies())));
        ui->tableWidgetBook->setItem(i, 4, new QTableWidgetItem(QString::number(books[i].availableCopies())));
    }
}